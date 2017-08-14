#!/usr/bin/env python

# Copyright 2017 DIANA-HEP
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from types import MethodType
import glob
import os
import sys
import time

import ROOT
import numpy

from plur.types import *
from plur.types.primitive import withrepr
from plur.types.arrayname import ArrayName
from plur.python.data import fromarrays
import plur.compile.code

from hepquery.util import *

class ROOTDataset(object):
    @staticmethod
    def fromtree(tree, **options):
        return ROOTDatasetFromTree(tree, **options)

    @staticmethod
    def fromchain(chain, **options):
        return ROOTDatasetFromChain(chain, **options)

    @staticmethod
    def fromfiles(treepath, *filepaths, **options):
        return ROOTDatasetFromFiles(treepath, filepaths, **options)

    def __init__(self):
        raise TypeError("use ROOTDataset.fromtree, ROOTDataset.fromchain, or ROOTDataset.fromfiles to create a ROOTDataset")

    @staticmethod
    def normalizename(name):
        return name    # FIXME!

    @staticmethod
    def branch2dtype(branch):
        leaves = list(branch.GetListOfLeaves())
        if len(leaves) != 1:
            raise NotImplementedError("TBranch::GetListOfLeaves()->GetEntries() == {0}".format(len(leaves)))
        leaf = leaves[0]

        leaftype = leaf.GetTypeName()
        if leaftype == "Bool_t":
            return boolean.of
        elif leaftype == "Char_t":
            return int8.of
        elif leaftype == "Short_t":
            return int16.of
        elif leaftype == "Int_t":
            return int32.of
        elif leaftype == "Long_t" or leaftype == "Long64_t":
            return int64.of
        elif leaftype == "Float_t" or leaftype == "Double32_t":
            return float32.of
        elif leaftype == "Double_t":
            return float64.of
        elif leaftype == "UChar_t":
            return uint8.of
        elif leaftype == "UShort_t":
            return uint16.of
        elif leaftype == "UInt_t":
            return uint32.of
        elif leaftype == "ULong_t" or leaftype == "ULong64_t":
            return uint64.of
        else:
            raise NotImplementedError("TLeaf::GetTypeName() == \"{0}\"".format(leaftype))

    @staticmethod
    def branch2array(tree, branchname, count2offset=False):
        branch = tree.GetBranch(branchname)

        # infer the Numpy dtype from the TLeaf type, but it starts as big-endian
        dtype = ROOTDataset.branch2dtype(branch).newbyteorder(">")

        # this is a (slight) overestimate of the size (due to ROOT headers per cluster)
        if count2offset:
            size = branch.GetTotalSize() + 1
        else:
            size = branch.GetTotalSize()

        # allocate some memory
        array = numpy.empty(size, dtype=dtype)

        # fill it
        if count2offset:
            entries, bytes = branch.FillNumpyArray(array[1:])
        else:
            entries, bytes = branch.FillNumpyArray(array)

        # clip it to the actual length, which we know exactly after filling
        if count2offset:
            array = array[: (bytes // array.dtype.itemsize) + 1]
        else:
            array = array[: (bytes // array.dtype.itemsize)]

        # swap the byte order: physical and interpreted
        array = array.byteswap(True).view(array.dtype.newbyteorder("="))

        # if this is to be an offset array, compute the cumulative sum of counts
        if count2offset:
            array[0] = 0
            numpy.cumsum(array[1:], out=array[1:])

        return array

    @staticmethod
    def tree2type(tree, prefix=None, delimiter="-"):
        if prefix is None:
            prefix = ROOTDataset.normalizename(tree.GetName())

        column2branch = {}
        column2dtype = {}

        def recurse(name, branch):
            if len(branch.GetListOfBranches()) == 0:
                try:
                    dtype = ROOTDataset.branch2dtype(branch)

                    out = withrepr(Primitive(dtype), copy=True)
                    out.column = name.str()
                    out.branch = branch.GetName()
                    out.dtype = out.of

                    column2branch[out.column] = out.branch
                    column2dtype[out.column] = out.dtype

                    return out

                except NotImplementedError:
                    return None

            def getfields(name):
                fields = {}
                for b in branch.GetListOfBranches():
                    n = b.GetName()
                    if "." in n:
                        n = n[n.rindex(".") + 1:]
                    n = ROOTDataset.normalizename(n)
                    if n not in fields:
                        tpe = recurse(name.toRecord(n), b)
                        if tpe is not None:
                            fields[n] = tpe
                return fields

            className = branch.GetClassName()

            if className == "TClonesArray":
                assert len(branch.GetListOfLeaves()) == 1   # is this always true?

                fields = getfields(name.toListData())
                if len(fields) == 0:
                    return None

                out = List(Record(**fields))
                out.of.column = None
                out.of.branch = None
                out.of.dtype = None

                out.column = name.toListOffset().str()
                out.branch = branch.GetName()
                out.dtype = ROOTDataset.branch2dtype(branch)

                column2branch[out.column] = out.branch
                column2dtype[out.column] = out.dtype

                return out

            else:
                fields = getfields(name)
                if len(fields) == 0:
                    return None

                out = Record(**fields)
                out.column = None
                out.branch = None
                out.dtype = None
                return out

        name = ArrayName(prefix, delimiter=delimiter)
        fields = {}
        for b in tree.GetListOfBranches():
            tpe = recurse(name.toListData().toRecord(ROOTDataset.normalizename(b.GetName())), b)
            if tpe is not None:
                fields[b.GetName()] = tpe

        if len(fields) == 0:
            raise NotImplementedError("none of the branches in this ROOT TTree could be converted into PLUR types")

        tpe = List(Record(**fields))
        tpe.of.column = None
        tpe.of.branch = None
        tpe.of.dtype = None
        tpe.column = name.toListOffset().str()
        tpe.branch = None
        tpe.dtype = int64.of

        column2branch[tpe.column] = tpe.branch
        column2dtype[tpe.column] = tpe.dtype

        return tpe, prefix, column2branch, column2dtype

    def compile(self, fcn, paramtypes={}, environment={}, numba=None, debug=False):
        cfcn, columns = plur.compile.code.local(fcn, paramtypes, environment, numba, debug, self._column2branch)
        return cfcn, columns

    def foreachtree(self, fcn, *otherargs, **options):
        debug = options.get("debug", False)
        if debug:
            totalopen = 0.0
            totalio = 0.0
            totalrun = 0.0
            totalentries = 0
            totalbytes = 0
            stopwatch1 = time.time()

        cfcn, columns = self.compile(fcn, (self.type,), **options)
        arraynames = [ArrayName.parse(c, self.prefix) for c in columns]
        
        if debug:
            print("")
            longestline = 0

        toparrayname = ArrayName(self.prefix).toListOffset()
        toparray = numpy.array([0, 0], dtype=numpy.int64)

        fcnargs = []
        for column, arrayname in zip(columns, arraynames):
            if arrayname == toparrayname:
                array = toparray
            else:
                array = numpy.array([], dtype=self._column2dtype[column])
            fcnargs.append(array)

        fcnargs.extend(otherargs)
        try:
            cfcn(*fcnargs)
        except:
            sys.stderr.write("Failed to test-run function with empty arrays (to force compilation)\n")
            raise

        if debug:
            stopwatch2 = time.time()

        self._rewind()
        while self._hasnext():
            if debug:
                stopwatch3 = time.time()

            partition = self._partition()
            self._next(self.cache is None or any(not self.cache.has("{0}.{1}.{2}".format(column, partition, self._column2dtype[column])) for column, arrayname in zip(columns, arraynames)))

            if debug:
                stopwatch4 = time.time()

            fcnargs = []
            nbytes = 0
            cachetotouch = []
            for column, arrayname in zip(columns, arraynames):
                array = None

                if self.cache is not None:
                    cachename = "{0}.{1}.{2}".format(column, partition, self._column2dtype[column])

                    if self.cache.has(cachename):
                        cachetotouch.append(cachename)

                        tmpfilename = os.path.join(self.cacheuser, "tmp")
                        try:
                            self.cache.linkfile(cachename, tmpfilename)
                            array = numpy.fromfile(open(tmpfilename, "rb"), dtype=self._column2dtype[column])
                        finally:
                            if os.path.exists(tmpfilename):
                                os.remove(tmpfilename)

                        if arrayname == toparrayname:
                            toparray = array

                if array is None:
                    if arrayname == toparrayname:
                        toparray[1] = self.tree.GetEntries()
                        array = toparray
                    else:
                        array = ROOTDataset.branch2array(self.tree, self._column2branch[column], len(arrayname.path) > 0 and arrayname.path[-1] == (ArrayName.LIST_OFFSET,))

                    if self.cache is not None:
                        try:
                            tmpfilename = os.path.join(self.cacheuser, "tmp")
                            array.tofile(open(tmpfilename, "wb"))
                            self.cache.newfile(cachename, tmpfilename)
                        finally:
                            if os.path.exists(tmpfilename):
                                os.remove(tmpfilename)

                fcnargs.append(array)
                nbytes += array.nbytes

            nentries = toparray[1]
            totalentries += nentries
            totalbytes += nbytes

            fcnargs.extend(otherargs)

            if self.cache is not None:
                self.cache.touch(*cachetotouch)

            if debug:
                stopwatch5 = time.time()

            try:
                cfcn(*fcnargs)
            except:
                sys.stderr.write("Failed while processing \"{0}\"\n".format(self._identity()))
                raise

            if debug:
                stopwatch6 = time.time()

                line = "{0:3d}% done; reading: {1:.3f} MB/s, computing: {2:.3f} MHz ({3})".format(
                    int(round(self._percent())),
                    nbytes/(stopwatch5 - stopwatch4)/1024**2,
                    toparray[1]/(stopwatch6 - stopwatch5)/1e6,
                    "..." + self._identity()[-26:] if len(self._identity()) > 29 else self._identity())
                print(line)
                longestline = max(longestline, len(line))

                totalopen += stopwatch4 - stopwatch3
                totalio += stopwatch5 - stopwatch4
                totalrun += stopwatch6 - stopwatch5

        if debug:
            print("=" * longestline)
            print("""
total time spent compiling: {0:.3f} sec
             opening files: {1:.3f} sec
              reading data: {2:.3f} sec ({3:.3f} MB --> {4:.3f} MB/s)
                 computing: {5:.3f} sec ({6:d} entries --> {7:.3f} MHz)

      from start to finish: {8:.3f} sec""".format(
                stopwatch2 - stopwatch1,
                totalopen,
                totalio,
                totalbytes/1024.0**2,
                totalbytes/totalio/1024**2,
                totalrun,
                totalentries,
                totalentries/totalrun/1e6,
                time.time() - stopwatch1).lstrip())

    class LazyArray(object):
        def __init__(self, tree, branchname, start, count2offset):
            self.tree = tree
            self.branchname = branchname
            self.start = start
            self.count2offset = count2offset
            self.array = None

        def __getitem__(self, i):
            if self.array is None:
                self.array = ROOTDataset.branch2array(self.tree, self.branchname, self.count2offset)
            return self.array[i - self.start]

    def __getitem__(self, entry):
        if isinstance(entry, slice):
            if entry.step is None:
                step = 1
            else:
                step = entry.step

            if step == 0:
                raise ValueError("slice step cannot be zero")
            elif step < 0:
                raise NotImplementedError("negative slice steps are not supported yet")

            if entry.start is None:
                start = 0
            else:
                start = entry.start

            if entry.stop is None:
                raise NotImplementedError("slices without an upper bound are not supported yet")
            else:
                stop = entry.stop

            return [self[i] for i in range(start, stop, step)]

        if entry < 0:
            raise NotImplementedError("negative indexes are not supported yet")

        if not hasattr(self, "_start2lazyarrays"):
            self._start2lazyarrays = {}

        tree, start = self._findentry(entry)

        if start in self._start2lazyarrays:
            lazyarrays = self._start2lazyarrays[start]

        else:
            toparrayname = ArrayName(self.prefix).toListOffset()

            lazyarrays = {}
            for column, branchname in self._column2branch.items():
                arrayname = ArrayName.parse(column, self.prefix)
                if arrayname == toparrayname:
                    array = numpy.array([0, self.tree.GetEntries()], dtype=numpy.int64)
                else:
                    array = self.LazyArray(self.tree, branchname, 0, len(arrayname.path) > 0 and arrayname.path[-1] == (ArrayName.LIST_OFFSET,))

                lazyarrays[column] = array

            self._start2lazyarrays[start] = lazyarrays

        plur = fromarrays(self.prefix, lazyarrays, tpe=self.type)[i]
        plur.__repr__ = ROOTDataset._RecordRepr
        return plur

class ROOTDatasetFromTree(ROOTDataset):
    def __init__(self, tree, prefix=None, cache=None):
        self.tree = tree
        if not self.tree:
            raise IOError("tree not valid")

        self._rewind()
        self._next(True)

        self.type, self.prefix, self._column2branch, self._column2dtype = ROOTDataset.tree2type(self.tree, prefix)
        self.cache = cache
        if cache is not None:
            self.cacheuser = cache.newuser({self.prefix: [{"file": tree.GetFile().GetName(), "tree": tree.GetName()}]})

    def _rewind(self):
        self._dummyindex = 0

    def _hasnext(self):
        return self._dummyindex < 1

    def _next(self, loadroot):
        if not self._hasnext(): raise StopIteration
        self._dummyindex += 1

    def _percent(self):
        return 0.0 if self._dummyindex == 0 else 100.0

    def _identity(self):
        return self.tree.GetName()

    def _partition(self):
        return self._dummyindex

    def _findentry(self, entry):
        return self.tree, 0

class ROOTDatasetFromChain(ROOTDataset):
    def __init__(self, chain, prefix=None, cache=None):
        self.chain = chain

        self._rewind()
        if not self._hasnext():
            raise IOError("empty TChain")
        self._next(True)

        self.type, self.prefix, self._column2branch, self._column2dtype = ROOTDataset.tree2type(self.tree, prefix)
        self.cache = cache
        if cache is not None:
            self.cacheuser = cache.newuser({self.prefix: [{"file": x.GetTitle(), "tree": x.GetName()} for x in self.chain.GetListOfFiles()]})

    def _rewind(self):
        self._filename = ""
        self._entryindex = 0
        self._treeindex = 0

    def _hasnext(self):
        return self._treeindex < self.chain.GetNtrees()

    def _next(self, loadroot):
        if not self._hasnext(): raise StopIteration

        if loadroot:
            self.chain.LoadTree(self._entryindex)
            self.tree = self.chain.GetTree()
            if not self.tree:
                raise IOError("tree number {0} not valid in TChain".format(self._treeindex))
            self._filename = self.chain.GetFile().GetName()
            self._entryindex += self.tree.GetEntries()
        else:
            chainelement = self.chain.GetListOfFiles()[self._treeindex]
            self._filename = chainelement.GetTitle()
            self._entryindex += chainelement.GetEntries()

        self._treeindex += 1

    def _percent(self):
        return 100.0 * self._treeindex / self.chain.GetNtrees()

    def _identity(self):
        return self._filename

    def _partition(self):
        return self._treeindex

    def _findentry(self, entry):
        subentry = self.chain.LoadTree(entry)
        self.tree = self.chain.GetTree()
        if not self.tree:
            raise IOError("tree for entry {0} not valid in TChain".format(entry))
        return self.tree, entry - subentry

class ROOTDatasetFromFiles(ROOTDataset):
    def __init__(self, treepath, filepaths, prefix=None, cache=None):
        self.treepath = treepath
        self.filepaths = [y for x in filepaths for y in sorted(glob.glob(os.path.expanduser(x)))]

        self._rewind()
        if not self._hasnext():
            raise IOError("empty file list")
        self._next(True)

        self.type, self.prefix, self._column2branch, self._column2dtype = ROOTDataset.tree2type(self.tree, prefix)
        self.cache = cache
        if cache is not None:
            self.cacheuser = cache.newuser({self.prefix: [{"file": x, "tree": self.treepath} for x in self.filepaths]})

    def _rewind(self):
        self._fileindex = 0
        self._filename = ""

    def _hasnext(self):
        return self._fileindex < len(self.filepaths)

    def _next(self, loadroot):
        if not self._hasnext(): raise StopIteration

        if loadroot:
            self.file = ROOT.TFile(self.filepaths[self._fileindex])
            if not self.file or self.file.IsZombie():
                raise IOError("could not read file \"{0}\"".format(self.filepaths[self._fileindex]))
            self.tree = self.file.Get(self.treepath)
            if not self.tree:
                raise IOError("tree \"{0}\" not found in file \"{1}\"".format(self.treepath, self.filepaths[self._fileindex]))

        self._filename = self.filepaths[self._fileindex]
        self._fileindex += 1

    def _percent(self):
        return 100.0 * self._fileindex / len(self.filepaths)

    def _identity(self):
        return self._filename

    def _partition(self):
        return self._fileindex

    def _findentry(self, entry):
        if not hasattr(self, "_numentries"):
            self._numentries = []

        oldfileindex = self._fileindex

        firstentry = 0
        lastentry = 0
        self._rewind()
        while self._hasnext():
            if self._fileindex < len(self._numentries):
                numentries = self._numentries[self._fileindex]

                lastentry += numentries
                if entry < lastentry:
                    self._next(self._fileindex != oldfileindex)
                    return self.tree, firstentry
                else:
                    self._next(False)

            else:
                self._next(True)
                numentries = self.tree.GetEntries()
                self._numentries.append(numentries)

                lastentry += numentries
                if entry < lastentry:
                    return self.tree, firstentry

            firstentry += numentries

        raise IndexError("ROOTDataset index {0} out of range ({1})".format(entry, lastentry))
