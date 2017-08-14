from hepquery.backends.root import *

dataset = ROOTDataset.fromfiles("Events", "/mnt/data/DYJetsToLL_*/*.root")

histogram = numpy.zeros(50, dtype=numpy.int64)

def fcn(tree, histogram):
    for event in tree:    
        for muon in event.Muon:        
            bin = int(muon.pt)
            if bin >= 0 and bin < 50:
                histogram[bin] += 1

dataset.foreach(fcn, histogram, numba=False, debug=True)

# print("")
# for i in range(50):
#     print("{0:8d} {1}".format(histogram[i], "*" * (80 * histogram[i] // histogram.max())))
