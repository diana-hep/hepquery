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

import time
from types import MethodType

import ROOT
import numpy
from plur.types import *
from plur.types.primitive import withrepr
from plur.types.arrayname import ArrayName
from plur.compile.code import local

from hepquery.util import *

def normalize(name):
    return name

def plurtype(tree, prefix, delimiter="-", offsettype=numpy.dtype(numpy.int32)):
    def recurse(name, branch):
        if len(branch.GetListOfBranches()) == 0:
            if len(branch.GetListOfLeaves()) == 1:
                leaf = branch.GetListOfLeaves()[0]
                leaftype = leaf.GetTypeName()

                if leaftype == "Bool_t":
                    out = withrepr(boolean, copy=True)
                elif leaftype == "Char_t":
                    out = withrepr(int8, copy=True)
                elif leaftype == "Short_t":
                    out = withrepr(int16, copy=True)
                elif leaftype == "Int_t":
                    out = withrepr(int32, copy=True)
                elif leaftype == "Long_t" or leaftype == "Long64_t":
                    out = withrepr(int64, copy=True)
                elif leaftype == "Float_t" or leaftype == "Double32_t":
                    out = withrepr(float32, copy=True)
                elif leaftype == "Double_t":
                    out = withrepr(float64, copy=True)
                elif leaftype == "UChar_t":
                    out = withrepr(uint8, copy=True)
                elif leaftype == "UShort_t":
                    out = withrepr(uint16, copy=True)
                elif leaftype == "UInt_t":
                    out = withrepr(uint32, copy=True)
                elif leaftype == "ULong_t" or leaftype == "ULong64_t":
                    out = withrepr(uint64, copy=True)
                else:
                    return None

                out.column = name.str()
                out.root = branch
                return out

            return None

        def getfields(name):
            fields = {}
            for b in branch.GetListOfBranches():
                n = b.GetName()
                if "." in n:
                    n = n[n.rindex(".") + 1:]
                n = normalize(n)
                if n not in fields:
                    tpe = recurse(name.toRecord(n), b)
                    if tpe is not None:
                        fields[n] = tpe
            return fields

        className = branch.GetClassName()

        if className == "TClonesArray":
            assert len(branch.GetListOfLeaves()) == 1

            fields = getfields(name.toListData())
            if len(fields) == 0:
                return None

            out = List(Record(**fields))
            out.of.column = None
            out.of.root = None

            out.column = name.toListOffset().str()
            out.root = branch.GetListOfLeaves()[0]
            return out

        else:
            fields = getfields(name)
            if len(fields) == 0:
                return None

            out = Record(**fields)
            out.column = None
            out.root = None
            return out

    name = ArrayName(prefix, delimiter=delimiter)
    fields = {}
    for b in tree.GetListOfBranches():
        tpe = recurse(name.toListData().toRecord(normalize(b.GetName())), b)
        if tpe is not None:
            fields[b.GetName()] = tpe

    if len(fields) == 0:
        raise NotImplementedError("none of the branches in this ROOT TTree could be converted into PLUR types")
    else:
        out = List(Record(**fields))
        out.of.column = None
        out.of.root = None
        out.column = name.toListOffset().str()
        out.root = None
        return out

def branchesAndLeaves(tpe, filter=None):
    def recurse(tpe):
        if not hasattr(tpe, "root"):
            raise TypeError("type is missing ROOT information (e.g. create with hepquery.backends.root.plurtype)")

        if tpe.root is None:
            out = []
        else:
            out = [(tpe.column, tpe.root)]

        # P
        if isinstance(tpe, Primitive):
            return out
        # L
        elif isinstance(tpe, List):
            return out + [(tpe.column, tpe.root)] + recurse(tpe.of)
        # U
        elif isinstance(tpe, Union):
            return out + [(tpe.column, tpe.root), (tpe.column2, tpe.root2)] + sum([recurse(t) for t in tpe.of], [])
        # R
        elif isinstance(tpe, Record):
            return out + sum([recurse(t) for n, t in tpe.of], [])
        else:
            raise "unexpected type object: {0}".format(tpe)

    out = sum([recurse(t) for n, t in tpe.of.of], [])
    if filter is None:
        return dict(out)
    else:
        return dict([(c, r) for c, r in out if c in filter])

def countToOffset(countarray):
    out = numpy.empty(countarray.shape[0] + 1, dtype=countarray.dtype)
    out[0] = 0
    numpy.cumsum(countarray, out=out[1:])
    return out

def foreach(chain, fcn, otherargs=(), debug=True):
    # if isinstance(chain, TChain):

    # elif isinstance(chain, TTree):
    #     tree = chain

    # else:
    #     raise TypeError("first argument must be a TChain or TTree, not {0}".format(chain))

    otherargs = tuple(otherargs)

    if debug:
        listoffiles = list(chain.GetListOfFiles())

    cumentries = 0
    chain.LoadTree(cumentries)

    tree = chain.GetTree()

    tpe = plurtype(tree, tree.GetName())

    compiledfcn, arraynames = local(fcn, (tpe,), debug=debug)

    brlf = branchesAndLeaves(tpe, arraynames)
    iterargs = [brlf[n] for n in arraynames if n != ArrayName(tree.GetName()).toListOffset().str()]
    postprocess = [ArrayName.parse(n, tree.GetName()).isListOffset for n in arraynames]
    
    if debug:
        print("\nRUN:\n")

    toparray = numpy.array([0, 0], dtype=numpy.int64)
    for treeindex in xrange(chain.GetNtrees()):
        if debug:
            startTime = time.time()

        if treeindex != 0:
            cumentries += tree.GetEntries()
            chain.LoadTree(cumentries)
            tree = chain.GetTree()
            iterargs = [tree.GetBranch(x.GetName()) if isinstance(x, ROOT.TBranch) else tree.GetLeaf(x.GetName()) for x in iterargs]

        for cluster in tree.GetNumpyIterator(*iterargs, return_new_buffers=False):
            toparray[0] = cluster[0]  # start
            toparray[1] = cluster[1]  # end
                
            fcnargs = [toparray]
            for i, x in enumerate(cluster[2:]):
                if postprocess[i]:
                    fcnargs.append(countToOffset(x))
                else:
                    fcnargs.append(x)
            fcnargs.extend(otherargs)

            for arg in fcnargs:
                print arg.shape, arg

            compiledfcn(*fcnargs)

        if debug:
            print("{0}/{1}\t{2} in {3}\t{4} entries/sec".format(
                treeindex,
                chain.GetNtrees(),
                listoffiles[treeindex].GetName(),
                listoffiles[treeindex].GetTitle(),
                tree.GetEntries() / (time.time() - startTime)))

if not hasattr(ROOT.TChain, "foreach"):
    ROOT.TChain.foreach = MethodType(foreach, None, ROOT.TChain)




def fcn(tree):
    out = 0.0
    for event in tree:    
        print "event", event
        for muon in event.Muon:        
            print "muon", muon
            out += muon.pt
    return out

chain = ROOT.TChain("Events")
chain.Add("../TTJets_13TeV_amcatnloFXFX_pythia8_2_77.root")
chain.foreach(fcn)

