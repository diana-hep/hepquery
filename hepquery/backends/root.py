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

import ROOT
import numpy
from plur.types import *
from plur.types.primitive import withrepr

def plurtype(tree):
    def recurse(branch):
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

                out.column = branch.GetName()
                out.root = branch
                return out

            return None

        fields = {}
        for b in branch.GetListOfBranches():
            tpe = recurse(b)
            if tpe is not None:
                n = b.GetName()
                if "." in n:
                    n = n[n.rindex(".") + 1:]
                if n not in fields:
                    fields[n] = tpe

        if len(fields) == 0:
            return None

        className = branch.GetClassName()

        if className == "TClonesArray":
            assert len(branch.GetListOfLeaves()) == 1

            out = List(Record(**fields))
            out.of.column = None
            out.of.root = None

            out.column = branch.GetListOfLeaves()[0].GetName()
            out.root = branch.GetListOfLeaves()[0]
            return out

        else:
            out = Record(**fields)
            out.column = None
            out.root = None
            return out

    fields = {}
    for b in tree.GetListOfBranches():
        tpe = recurse(b)
        if tpe is not None:
            fields[b.GetName()] = tpe

    if len(fields) == 0:
        raise NotImplementedError("none of the branches in this ROOT TTree could be converted into PLUR types")
    else:
        return List(Record(**fields))
