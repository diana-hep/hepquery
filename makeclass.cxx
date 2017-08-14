#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TH1I.h"
#include "TROOT.h"

double diff(struct timeval endTime, struct timeval startTime) {
  return (1000L * 1000L * (endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec)) / 1000.0 / 1000.0;
}

void makeclass() {
  struct timeval startTime, endTime;

  gROOT->SetBatch(kTRUE);

  // TChain* chain = new TChain("Events");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_0.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_1.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_10.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_11.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_12.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_13.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_14.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_15.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_16.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_17.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_18.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_19.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_2.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_20.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_21.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_22.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_23.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_3.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_4.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_5.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_6.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_7.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_8.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_9.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_0.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_1.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_10.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_2.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_3.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_4.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_5.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_6.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_7.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_8.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_200to400_13TeV_2/DYJetsToLL_M_50_HT_200to400_13TeV_2_9.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_0.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_1.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_10.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_11.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_2.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_3.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_4.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_5.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_6.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_7.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_8.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_400to600_13TeV_2/DYJetsToLL_M_50_HT_400to600_13TeV_2_9.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_0.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_1.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_10.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_2.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_3.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_4.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_5.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_6.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_7.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_8.root");
  // chain->Add("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_600toInf_13TeV_2/DYJetsToLL_M_50_HT_600toInf_13TeV_2_9.root");

  TFile* file;
  TTree* tree;
  TBranch* branch;
  TLeaf* leaf;
  Long64_t entries;
  int leaflength;
  char* branchdata;

  file = new TFile("/mnt/data/uncompressed/DYJetsToLL_M_50_HT_100to200_13TeV_2/DYJetsToLL_M_50_HT_100to200_13TeV_2_0.root");
  file->GetObject("Events", tree);
  branch = (TBranch*)tree->GetBranch("Muon.pt");
  leaf = (TLeaf*)branch->GetListOfLeaves()->First();
  
  entries = tree->GetEntries();

  tree->SetMakeClass(1);

  leaflength = leaf->GetLenType();
  branchdata = new char[leaflength];
  branch->SetAddress(branchdata);

  for (Long64_t i = 0;  i < entries;  i++) {
    branch->GetEntry(i);
    float* data = (float*)branchdata;
    
    std::cout << data[0] << std::endl;
  }


  // Double_t *buffer = new Double_t[1000];

  // branch->SetAddress(buffer);
  // Long64_t numEvents = chain->GetEntries();

  // TH1I* histogram = new TH1I("name", "title", 100, 0.0, 100.0);

  // gettimeofday(&startTime, 0);
  // for (Long64_t i = 0;  i < numEvents;  i++) {
  //   branch->GetEntry(i);

  //   for (int j = 0;  j < branch->GetBranchCount()->GetNdata();  ++j) {
  //     histogram->Fill(buffer[j]);

  //     std::cout << buffer[j] << " ";

  //   }
  //   std::cout << std::endl;

  // }
  // gettimeofday(&endTime, 0);
  // std::cout << diff(endTime, startTime) << " sec" << std::endl;

  // usleep(5000000);

}
