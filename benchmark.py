import time
import glob

import numpy

import ROOT
from hepquery.cache import Cache
from hepquery.backends.root import ROOTDataset

cache = Cache.adopt("/mnt/cache", 100*1024**3)

dataset = ROOTDataset.fromfiles("Events", "/mnt/data/DYJetsToLL_*/*.root", cache=cache)

# chain = ROOT.TChain("Events")
# for filename in sorted(glob.glob("/mnt/data/DYJetsToLL*/*.root")):
#     chain.Add(filename)
# dataset = ROOTDataset.fromchain(chain, cache=cache)

histogram = numpy.zeros(100, dtype=numpy.int64)

def fcn(tree, histogram):
    for event in tree:    
        for muon in event.Muon:        
            bin = int(muon.pt)
            if bin >= 0 and bin < 100:
                histogram[bin] += 1

dataset.foreachtree(fcn, histogram, numba=True, debug=True)

print("")
for i in range(100):
    print("{0:8d} {1}".format(histogram[i], "*" * (80 * histogram[i] // histogram.max())))
