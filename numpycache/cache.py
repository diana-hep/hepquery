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

import os
import shutil
import math

import numpy

class Cache(object):
    def __init__(self, directory, limitbytes, maxperdir=100, delimiter="."):
        self.directory = directory
        self.limitbytes = limitbytes
        self.maxperdir = maxperdir
        self.delimiter = delimiter
        self._formatter = "{0:0" + str(int(math.ceil(math.log(100, 10)))) + "d}"

        self.lookup = {}
        self.order = []
        self.numbytes = 0
        self.depth = 0
        self.number = 0

    @staticmethod
    def overwrite(directory, limitbytes, maxperdir=100, delimiter="."):
        if os.path.exists(directory):
            shutil.rmtree(directory)
        os.mkdir(directory)
        return Cache(directory, limitbytes, maxperdir, delimiter)

    @staticmethod
    def adopt(directory, limitbytes, maxperdir=100, delimiter="."):
        out = Cache(directory, limitbytes, maxperdir, delimiter)

        def recurse(dep, num, path):
            paths = os.listdir(path)
            paths.sort()

            if all(os.path.isdir(fn) for fn in paths):
                assert all(int(fn) < maxperdir for fn in paths)
                for fn in paths:
                    n = int(fn)
                    recurse(dep + 1, (num + n) * maxperdir, os.path.join(path, fn))

            elif all(not os.path.isdir(fn) for fn in paths):
                for fn in paths:
                    assert fn.count(delimiter) >= 2

                    upton = fn.index(delimiter)
                    n = int(fn[:upton])
                    name = fn[upton : fn.index(delimiter, upton + 1)]

                    self.lookup[name] = fn
                    self.order.append(name)
                    self.number = num + n

            else:
                assert False, "subpaths must be all directories or all files at {0}".format(path)

        recurse(1, 0, directory)
        return out

    def newfile(self, name, dtype, shape):
        # increase number
        number = self.number
        self.number += 1

        # maybe increase depth
        while number >= self.maxperdir**(self.depth + 1):
            self.depth += 1
            tmp = os.path.join(self.directory, "tmp")
            os.mkdir(tmp)
            for fn in os.listdir(self.directory):
                if fn != "tmp":
                    os.rename(os.path.join(self.directory, fn), os.path.join(tmp, fn))
            os.rename(tmp, os.path.join(self.directory, self._formatter.format(0)))

        # create directories in path if necessary
        path = self.directory
        for d in range(self.depth, 0, -1):
            factor = self.maxperdir**d

            fn = self._formatter.format(number // factor)
            number = number % factor

            path = os.path.join(path, fn)
            if not os.path.exists(path):
                os.mkdir(path)

        # return new filename
        fn = self._formatter.format(number)
        return os.path.join(path, self.delimiter.join([fn, name, dtype] + [str(x) for x in shape]))
