#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>

#include "TChain.h"
#include "TH1I.h"
#include "TROOT.h"

double diff(struct timeval endTime, struct timeval startTime) {
  return (1000L * 1000L * (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec)) / 1000.0 / 1000.0;
}

void ttreedraw2() {
  struct timeval startTime, endTime;

  gROOT->SetBatch(kTRUE);

  TH1I* histogram = new TH1I("name", "title", 100, 0.0, 100.0);

  TFile* file;
  TTree* tree;
  double totaltime;

  totaltime = 0.0;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_11.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_12.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_13.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_14.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_15.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_16.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_17.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_18.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_19.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_20.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_21.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_22.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_23.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_11.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  std::cout << totaltime << " sec" << std::endl;

  usleep(5000000);

  //////////////////////////////////////////////////////////////////////////////

  totaltime = 0.0;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_11.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_12.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_13.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_14.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_15.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_16.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_17.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_18.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_19.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_20.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_21.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_22.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_23.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_11.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_0.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_1.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_10.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_2.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_3.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_4.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_5.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_6.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_7.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_8.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_9.root");
  file->GetObject("Events", tree);
  gettimeofday(&startTime, 0);
  tree->Draw("Muon.pt >> +histogram");
  gettimeofday(&endTime, 0);
  totaltime += diff(endTime, startTime);
  delete tree;
  delete file;

  std::cout << totaltime << " sec" << std::endl;

}
