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
import time

import ROOT
import numpy

from plur.types import *
from plur.types.primitive import withrepr
from plur.types.arrayname import ArrayName
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
        raise TypeError("use a factory method: fromtree, fromchain, fromfiles")

    def _rewind(self):
        pass

    def _hasnext(self):
        pass

    def _next(self):
        pass

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

    def tree2type(self, tree, prefix=None, delimiter="-"):
        if prefix is None:
            prefix = ROOTDataset.normalizename(tree.GetName())

        def recurse(name, branch):
            if len(branch.GetListOfBranches()) == 0:
                try:
                    dtype = ROOTDataset.branch2dtype(branch)

                    out = withrepr(Primitive(dtype), copy=True)
                    out.column = name.str()
                    out.branch = branch.GetName()
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

                out.column = name.toListOffset().str()
                out.branch = branch.GetName()
                return out

            else:
                fields = getfields(name)
                if len(fields) == 0:
                    return None

                out = Record(**fields)
                out.column = None
                out.branch = None
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
        tpe.column = name.toListOffset().str()
        tpe.branch = None
        return tpe, prefix

    def compile(self, fcn, paramtypes={}, environment={}, numba=None, debug=False):
        cfcn, columns = plur.compile.code.local(fcn, paramtypes, environment, numba, debug)
        column2branch = {}

        def recurse(tpe):
            if tpe.column in columns and tpe.branch is not None:
                column2branch[tpe.column] = tpe.branch
            # P
            if isinstance(tpe, Primitive):
                pass
            # L
            elif isinstance(tpe, List):
                recurse(tpe.of)
            # U
            elif isinstance(tpe, Union):
                for t in tpe.of:
                    recurse(t)
            # R
            elif isinstance(tpe, Record):
                for n, t in tpe.of:
                    recurse(t)
            else:
                raise "unexpected type object: {0}".format(tpe)

        recurse(self.type)
        return cfcn, columns, column2branch

    def branch2array(self, branchname, count2offset=False):
        branch = self.tree.GetBranch(branchname)

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

    def foreach(self, fcn, *otherargs, **options):
        cfcn, columns, column2branch = self.compile(fcn, (self.type,), **options)
        arraynames = [ArrayName.parse(c, self.prefix) for c in columns]

        toparrayname = ArrayName(self.prefix).toListOffset()
        toparray = numpy.array([0, self.tree.GetEntries()], dtype=numpy.int64)

        fcnargs = []
        for column, arrayname in zip(columns, arraynames):
            if arrayname == toparrayname:
                fcnargs.append(toparray)
            else:
                fcnargs.append(self.branch2array(column2branch[column], arrayname.isListOffset))
        fcnargs.extend(otherargs)

        cfcn(*fcnargs)
        
class ROOTDatasetFromTree(ROOTDataset):
    def __init__(self, tree, prefix=None, cache=None):
        self.tree = tree
        if not self.tree:
            raise IOError("tree not valid")

        self.type, self.prefix = self.tree2type(self.tree, prefix)
        self.cache = cache

class ROOTDatasetFromChain(ROOTDataset):
    def __init__(self, chain, prefix=None, cache=None):
        self.chain = chain

        self._rewind()
        if not self._hasnext():
            raise IOError("empty TChain")
        self._next()

        self.type, self.prefix = self.tree2type(self.tree, prefix)
        self.cache = cache

    def _rewind(self):
        self._treeindex = 0
        self._entryindex = 0

    def _hasnext(self):
        return self._treeindex < self.chain.GetNtrees()

    def _next(self):
        if not self._hasnext(): raise StopIteration
        self.chain.LoadTree(self._entryindex)
        self.tree = self.chain.GetTree()
        if not self.tree:
            raise IOError("tree number {0} not valid in TChain".format(self._treeindex))
        self._treeindex += 1
        self._entryindex += self.chain.GetEntries()

class ROOTDatasetFromFiles(ROOTDataset):
    def __init__(self, treepath, filepaths, prefix=None, cache=None):
        self.treepath = treepath
        self.filepaths = [y for x in filepaths for y in glob.glob(os.path.expanduser(x))]

        self._rewind()
        if not self._hasnext():
            raise IOError("empty file list")
        self._next()

        self.type, self.prefix = self.tree2type(self.tree, prefix)
        self.cache = cache

    def _rewind(self):
        self._fileindex = 0

    def _hasnext(self):
        return self._fileindex < len(self.filepaths)

    def _next(self):
        if not self._hasnext(): raise StopIteration
        self.file = ROOT.TFile(self.filepaths[self._fileindex])
        if not self.file or self.file.IsZombie():
            raise IOError("could not read file \"{0}\"".format(self.filepaths[self._fileindex]))
        self.tree = self.file(self.treepath)
        if not self.tree:
            raise IOError("tree \"{0}\" not found in file \"{1}\"".format(self.treepath, self.filepaths[self._fileindex]))
        self._fileindex += 1







def fcn(tree):
    out = 0.0
    for event in tree:    
        print "event", event
        for muon in event.Muon:        
            print "muon", muon
            out += muon.pt
    return out

file = ROOT.TFile("/mnt/data/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_0.root")
tree = file.Get("Events")

dataset = ROOTDataset.fromtree(tree)

dataset.foreach(fcn, debug=True)
