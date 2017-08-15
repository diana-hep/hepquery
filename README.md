# HEPQuery

HEPQuery is a project to provide a fast, query-engine style interface to High Energy Physics (HEP) data. It's related to

   * [Femtocode](https://github.com/diana-hep/femtocode) query language`*`
   * [PLUR](https://github.com/diana-hep/plur) data representation
   * [Parallelization with Zookeeper](https://github.com/JThanat/femto-mesos/tree/master) Thanat's summer project (see also [his writeup](https://cds.cern.ch/record/2278211?ln=en))

(`*`The Femtocode project is on hold while we develop the data representation and use [Numba-compiled Python](http://numba.pydata.org/) as a query language. Data representation should be independent of language for modularity.
Here is an old poster describing the motivation and feasibility studies.

![Femtocode poster](docs/pivarski-femtocode-poster.png)

# Demo

Although it's in the early stages of development, you can check out and run some examples of HEPQuery. First get the dependencies:

   * [Revision 203 of PLUR](https://github.com/diana-hep/plur/releases/tag/rev203); install with `python setup.py install --user`
   * [Numba](https://numba.pydata.org/#installing); e.g. from [Conda](https://conda.io/miniconda.html).
   * [ROOT with BulkAPI](https://github.com/jpivarski/root/tree/root-bulkapi-fastread-v2); `git clone https://github.com/jpivarski/root.git -b root-bulkapi-fastread-v2` and [compile ROOT](https://root.cern.ch/building-root). This is for a ROOT → Numpy feature that is scheduled for ROOT version 6.12 (this winter).
   * **Not** Femtocode; it is not necessary.

Finally, git-clone Revision XYZ of HEPQuery and install it with `python setup.py install --user`.

Import two features:

```python
from hepquery.backends.root import ROOTDataset
from hepquery.cache import Cache
```

for loading data from ROOT and representing them as PLUR for calculations, optionally caching the PLUR for faster iteration.

Next, create a 100 GB cache on some fast disk (SSD):

```python
cache = Cache.adopt("/mnt/cache", 100*1024**3)
```

and point to the ROOT data, backed by the cache:

```python
dataset = ROOTDataset.fromfiles("Events", "/mnt/data/DYJetsToLL*/*.root", cache=cache)
```

Create a "query" by defining a function to be executed on the data. The interface is a little rough right now; you have to write the function to be executed separately on each TTree in your sample. In the future, a suite of high-level functionals (map, filter, reduce) will be provided. (But this _does_ demonstrate that random access is possible and efficient.)

```python
histogram = numpy.zeros(100, dtype=numpy.int32)

def fcn(tree, histogram):
    for event in tree:
        for muon in event.Muon:        # just fill a histogram of muon.pt
            bin = int(muon.pt)
            if bin >= 0 and bin < 100:
                histogram[bin] += 1
```

All mutable data must be passed in as an explicit argument, such as `histogram` here.

Run it in debug mode to see how the code gets transformed and to measure the rate of access/computation.

```
>>> dataset.foreachtree(fcn, histogram, numba=True, debug=True)

BEFORE:

def fcn(tree, histogram):
    for event in tree:
        for muon in event.Muon:
            bin = int(muon.pt)
            if ((bin >= 0) and (bin < 100)):
                histogram[bin] += 1

    return None 

AFTER:

def fcn(array_0, array_1, array_2, histogram):
    for event in range(array_0[1]):
        for muon in range(array_1[event], array_1[(event + 1)]):
            bin = int(array_2[muon])
            if ((bin >= 0) and (bin < 100)):
                histogram[bin] += 1

    return None 

array_0 -->     Events-Lo (None)
array_1 -->     Events-Ld-R_Muon-Lo (Muon)
array_2 -->     Events-Ld-R_Muon-Ld-R_pt (Muon.pt)

  2% done; reading: 40.328 MB/s, computing: 105.775 MHz (...HT_100to200_13TeV_2_0.root)
  3% done; reading: 195.188 MB/s, computing: 104.218 MHz (...HT_100to200_13TeV_2_1.root)
  5% done; reading: 220.695 MB/s, computing: 106.389 MHz (...T_100to200_13TeV_2_10.root)
  7% done; reading: 219.343 MB/s, computing: 106.408 MHz (...T_100to200_13TeV_2_11.root)
  ...
 97% done; reading: 262.094 MB/s, computing: 66.308 MHz (...HT_600toInf_13TeV_2_7.root)
 98% done; reading: 337.129 MB/s, computing: 67.579 MHz (...HT_600toInf_13TeV_2_8.root)
100% done; reading: 232.974 MB/s, computing: 67.133 MHz (...HT_600toInf_13TeV_2_9.root)
========================================================================================
total time spent compiling: 0.353 sec
             opening files: 0.078 sec
              reading data: 0.238 sec (46.302 MB --> 194.745 MB/s)
                 computing: 0.061 sec (5389283 entries --> 87.645 MHz)

      from start to finish: 0.734 sec
```

For a fast SSD disk (top speed of 370 MB/s), you can expect single-threaded rates like

|   | cold files on disk  | files paged to RAM by OS |
|:-:|:-------------------:|:------------------------:|
| first read (from ROOT)  |  45 MB/s |  320 MB/s |
| subsequent (from cache) | 185 MB/s | 1100 MB/s |

If you turned on the cache, you'll find Numpy arrays in `/mnt/cache`. These are uncompressed and faster to load than ROOT branches, though the new BulkAPI feature is itself an order of magnitude faster than `TTree::Draw` (from files paged to RAM by OS).

The data representation has been designed for fast sequential access, but you can also work with data interactively for testing. It's slower, but quick enough for human feedback. (Like the sequential case, data are only pulled from files on demand.)

```python
>>> first = dataset[0]

>>> first._fields
['AK4CHS', 'AK4Puppi', 'AK8CHS', 'AddAK8CHS', 'AddCA15CHS', 'AddCA15Puppi', 'AddCA8Puppi', 'CA15CHS',
'CA15Puppi', 'CA8Puppi', 'Electron', 'GenEvtInfo', 'GenParticle', 'Info', 'Muon', 'PV', 'Photon', 'Tau']

>>> first.Muon
[<Muon at 0x0>, <Muon at 0x1>]

>>> first.Muon[0].pt, first.Muon[1].pt
(68.385483, 22.299986)

>>> first.Muon[0].toJson()
{'staPhi': 0.9862945079803467,
 'puppiChHadIso': 1.477783203125,
 'staPt': 60.26984786987305,
 'trkIso': 0.46461474895477295,
 'nPixLayers': 3,
 'caloComp': 0.9701600074768066,
 'puppiChHadIsoNoLep': 1.477783203125,
 'puppiNeuHadIso': 0.6455078125,
 'd0': -0.00047574163181707263,
 'puppiNeuHadIsoNoLep': 0.6455078125,
 'nTkHits': 15,
 'pt': 68.38548278808594,
 'nTkLayers': 10,
 'pfEta': -1.1107865571975708,
 'typeBits': 110,
 'nMatchStn': 4,
 'selectorBits': 32767999,
 'nPixHits': 3,
 'tkNchi2': 0.7523882389068604,
 'segComp': 0.8842684626579285,
 'trkID': -1,
 'phi': 0.9892331957817078,
 'muNchi2': 1.0204561948776245,
 'chHadIso': 1.477813959121704,
 'dz': 0.0008993322844617069,
 'pfPhi': 0.9892331957817078,
 'sip3d': -0.5136342644691467,
 'nValidHits': 25,
 'chi2LocPos': 2.272005319595337,
 'glbKink': 7438.8271484375,
 'hcalIso': 0.6413036584854126,
 'pfPt': 68.38548278808594,
 'ecalIso': 0.6047968864440918,
 'puIso': 5.423295974731445,
 'ptErr': 1.2126946449279785,
 'neuHadIso': 0.6455274224281311,
 'q': -1,
 'trkHitFrac': 1.0,
 'eta': -1.1107865571975708,
 'pogIDBits': 31,
 'puppiGammaIso': 0.953369140625,
 'gammaIso': 0.0,
 'staEta': -1.1058242321014404,
 'trkKink': 4.588568687438965,
 'puppiGammaIsoNoLep': 0.953369140625}

>>> dataset[2].Muon
[<Muon at 0x2>, <Muon at 0x3>]

>>> dataset[:10]
[<Events at 0x0>, <Events at 0x1>, <Events at 0x2>, <Events at 0x3>, <Events at 0x4>,
 <Events at 0x5>, <Events at 0x6>, <Events at 0x7>, <Events at 0x8>, <Events at 0x9>]

>>> [x.Muon for x in dataset[:10]]
[[<Muon at 0x0>, <Muon at 0x1>], [], [<Muon at 0x2>, <Muon at 0x3>], [],
[<Muon at 0x4>, <Muon at 0x5>], [<Muon at 0x6>], [<Muon at 0x7>], [],
[<Muon at 0x8>, <Muon at 0x9>], [<Muon at 0xa>, <Muon at 0xb>]]
```

# Why this is great

By tinkering on the command line, I computed dimuon masses and found many of them to be at the Z pole:

```python
>>> from math import *
>>> for event in dataset[:100]:
...   for i in range(len(event.Muon)):
...     for j in range(i + 1, len(event.Muon)):       # don't repeat muons!
...       mu1 = event.Muon[i]
...       mu2 = event.Muon[j]
...       print(sqrt(2*mu1.pt*mu2.pt*(cosh(mu1.eta - mu2.eta) - cos(mu1.phi - mu2.phi))))
...
79.4338346557
92.5052493945
0.598194203213
18.8711156173
15.1082554054
81.1394932173
87.8975581394
0.980486484959
88.1068221632
129.770271113
16.3836532317
19.843856908
93.4938739107
90.2348773065
79.3163019793
99.8607947969
24.014843766
91.4711202884
12.4382808061
38.7604436416
2.94827494271
170.118897504
86.4521328047
94.6742801779
11.6830843263
81.3369416087
88.0011171039
90.0088846793
49.634896739
25.0800349343
1.92515639982
131.469054102
84.2063636711
96.1914788068
85.749143422
7.59674671131
111.24118453
6.66398279986
91.4703128558
```

So I put _exactly this Python code_ into the sequential optimizer and ran over the 21.5 GB dataset in under a second, computing at a rate of 14 million events per second (single threaded).

```python
histogram = numpy.zeros(100, dtype=numpy.int32)

from math import *
def fcn(tree, histogram):
    for event in tree:
        for i in range(len(event.Muon)):
            for j in range(i + 1, len(event.Muon)):
                mu1 = event.Muon[i]
                mu2 = event.Muon[j]
                mass = sqrt(2*mu1.pt*mu2.pt*(cosh(mu1.eta - mu2.eta) - cos(mu1.phi - mu2.phi)))

                bin = int(mass)
                if bin >= 0 and bin < 100:
                    histogram[bin] += 1

dataset.foreachtree(fcn, histogram, numba=True, debug=True,
                    environment={"sqrt": sqrt, "cosh": cosh, "cos": cos})

print("")
for i in range(100):
    print("{0:8d} {1}".format(histogram[i], "*" * (80 * histogram[i] // histogram.max())))
```

Again, apologies for the rough interface (having to explicitly pass math functions to the `environment` and lacking built-in histogramming). However, I hope you can see that this will be fast enough to do exploratory data analysis on unskimmed data, especially when parallelized.
