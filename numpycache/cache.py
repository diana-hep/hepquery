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
import re

import numpy

class Cache(object):
    def __init__(self, directory, limitbytes, maxperdir=100, delimiter="."):
        self.directory = directory
        self.limitbytes = limitbytes
        self.maxperdir = maxperdir
        self.delimiter = delimiter
        self._formatter = "{0:0" + str(int(math.ceil(math.log(maxperdir, 10)))) + "d}"

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
        out.depth = None
        out.number = None

        digits = re.compile("^[0-9]{" + str(int(math.ceil(math.log(maxperdir, 10)))) + "}$")
        def recurse(d, n, path):
            items = os.listdir(os.path.join(directory, path))
            items.sort()

            # directories should all have numerical names (with the right number of digits)
            if all(os.path.isdir(os.path.join(directory, path, fn)) and digits.match(fn) for fn in items):
                for fn in items:
                    recurse(d + 1, (n + int(fn)) * maxperdir, os.path.join(path, fn))

            # a directory of files should all be files; no mixing of files and directories
            elif all(not os.path.isdir(os.path.join(directory, path, fn)) for fn in items):
                for fn in items:
                    assert fn.count(delimiter) >= 2
                    i1 = fn.index(delimiter) + 1
                    i2 = fn.index(delimiter, i1)
                    name = fn[i1:i2]
                    number = n + int(fn[:i1 - 1])

                    out.lookup[name] = os.path.join(path, fn)
                    out.order.append(name)
                    out.numbytes += 0
                    if out.depth is None:
                        out.depth = d
                    else:
                        assert out.depth == d, "some files are at depth {0}, others at {1}".format(out.depth, d)
                    if out.number is not None:
                        assert number > out.number
                    out.number = number

            else:
                assert False, "directory contents must all be directories (named /{0}/ because maxperdir is {1}) or all be files:\n\n    {2}".format(digits.pattern, maxperdir, path)

        recurse(0, 0, "")
        out.number += 1
        return out

    def newfilename(self, name, shape, dtype):
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
        path = ""
        for d in range(self.depth, 0, -1):
            factor = self.maxperdir**d

            fn = self._formatter.format(number // factor)
            number = number % factor

            path = os.path.join(path, fn)
            if not os.path.exists(os.path.join(self.directory, path)):
                os.mkdir(os.path.join(self.directory, path))

        # return new filename
        fn = self._formatter.format(number)
        return os.path.join(path, self.delimiter.join([fn, name] + [str(x) for x in shape] + [dtype]))

    def cleanup(self, path):
        while path != "":
            path, fn = os.path.split(path)
            if path != "" and len(os.listdir(os.path.join(self.directory, path))) == 0:
                os.rmdir(os.path.join(self.directory, path))