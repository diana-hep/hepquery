import time
import glob

import ROOT
from root_numpy import tree2array

starttime = time.time()
for filename in sorted(glob.glob("/mnt/data/uncompressed/DYJetsToLL*/*.root")):
    file = ROOT.TFile(filename)
    tree = file.Get("Events")
    arr = tree2array(tree, branches=["Muon.pt"])
print time.time() - starttime

time.sleep(5)

starttime = time.time()
for filename in sorted(glob.glob("/mnt/data/uncompressed/DYJetsToLL*/*.root")):
    file = ROOT.TFile(filename)
    tree = file.Get("Events")
    arr = tree2array(tree, branches=["Muon.pt"])
print time.time() - starttime

time.sleep(5)

starttime = time.time()
for filename in sorted(glob.glob("/mnt/data/uncompressed/DYJetsToLL*/*.root")):
    file = ROOT.TFile(filename)
    tree = file.Get("Events")
    arr = tree2array(tree, branches=["Muon.pt"])
print time.time() - starttime

