import time
import glob

import ROOT
from hepquery.backends.root import *

# dataset = ROOTDataset.fromfiles("Events",
#                                 "/mnt/data/DYJetsToLL_M_50_HT_600toInf_13TeV_2/*.root",
#                                 "/mnt/data/DYJetsToLL_M_50_HT_400to600_13TeV_2/*.root",
#                                 "/mnt/data/DYJetsToLL_M_50_HT_200to400_13TeV_2/*.root",
#                                 "/mnt/data/DYJetsToLL_M_50_HT_100to200_13TeV_2/*.root",
#                                 )

chain = ROOT.TChain("Events")
for filename in glob.glob("/mnt/data/DYJetsToLL*/*.root"):
    chain.Add(filename)

dataset = ROOTDataset.fromchain(chain)

histogram = numpy.zeros(100, dtype=numpy.int64)

def fcn(tree, histogram):
    for event in tree:    
        for muon in event.Muon:        
            bin = int(muon.pt)
            if bin >= 0 and bin < 100:
                histogram[bin] += 1

dataset.foreach(fcn, histogram, numba=True, debug=True)

# print("")
# for i in range(100):
#     print("{0:8d} {1}".format(histogram[i], "*" * (80 * histogram[i] // histogram.max())))
