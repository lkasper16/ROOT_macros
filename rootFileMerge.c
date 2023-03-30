#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "vector"
#include <TTree.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TRandom2.h>
#include <TRandom.h>
#include <TStopwatch.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TList.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TLine.h>
#include <TBox.h>
#include <TObject.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

using namespace std;

void rootFileMerge(){
  
  TStopwatch timer;
  timer.Start();
  
  //A chain is a collection of files containg TTree objects
  //Use TChain for multiple files - All constructors are equivalent
  TChain fChain("events");
  fChain.Add("~/eic/output_trd_testing_pion.edm4hep.root");
  //fChain.Add("~/eic/output_trd_testing_pion_low.edm4hep.root");
  fChain.Add("~/eic/output_trd_testing_electron.edm4hep.root");
  //fChain.Add("~/eic/output_trd_testing_electron_low.edm4hep.root");
  fChain.Add("~/eic/output_trd_testing_muon.edm4hep.root");
  //fChain.Add("~/eic/output_trd_testing_muon_low.edm4hep.root");
  
  int nTrees = fChain.GetNtrees();
  int nEnts = fChain.GetEntries();
  cout << "# of trees: " << nTrees <<  endl;
  cout << "# of entries: " << nEnts <<  endl;
/*  
  int EVENT;
  int RunNumber;
  int trig=0;
  float dped=0.;
  int dchmax=0;
  float dsig=0;
  int dwid=0;
  int dsmax=0;
  float w2ped=0.;
  int w2chmax=0;
  float w2sig=0;
  int w2wid=0;
  int w2smax=0;
  float dcharge=0.;
  float w2charge=0.;
  float dmcharge=0.;
  float w2mcharge=0.;
  int dsize=0;
  int w2size=0;
  int w2nhit;
  float w2thit[1000];
  float w2ahit[1000];
  float w2mhit[1000];
  int w2chit[1000];
  int dnhit;
  float dthit[1000];
  float dahit[1000];
  float dmhit[1000];
  int dchit[1000];
*/
  
  static constexpr Int_t kMaxMCParticles = 2;
  static constexpr Int_t kMaxEventHeader = 1;
  static constexpr Int_t kMaxMPGDTRDEndcapHits = 1434;
  
  // Declaration of leaf types
  //Int_t           MCParticles_;
  Int_t           MCParticles_PDG[kMaxMCParticles];   //[MCParticles_]
  Int_t           MCParticles_generatorStatus[kMaxMCParticles];   //[MCParticles_]
  Int_t           MCParticles_simulatorStatus[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_charge[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_time[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_mass[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_vertex_x[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_vertex_y[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_vertex_z[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_endpoint_x[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_endpoint_y[kMaxMCParticles];   //[MCParticles_]
  Double_t        MCParticles_endpoint_z[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_momentum_x[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_momentum_y[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_momentum_z[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_momentumAtEndpoint_x[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_momentumAtEndpoint_y[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_momentumAtEndpoint_z[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_spin_x[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_spin_y[kMaxMCParticles];   //[MCParticles_]
  Float_t         MCParticles_spin_z[kMaxMCParticles];   //[MCParticles_]
  Int_t           MCParticles_colorFlow_a[kMaxMCParticles];   //[MCParticles_]
  Int_t           MCParticles_colorFlow_b[kMaxMCParticles];   //[MCParticles_]
  UInt_t          MCParticles_parents_begin[kMaxMCParticles];   //[MCParticles_]
  UInt_t          MCParticles_parents_end[kMaxMCParticles];   //[MCParticles_]
  UInt_t          MCParticles_daughters_begin[kMaxMCParticles];   //[MCParticles_]
  UInt_t          MCParticles_daughters_end[kMaxMCParticles];   //[MCParticles_]
  //Int_t           EventHeader_;
  Int_t           EventHeader_eventNumber[kMaxEventHeader];   //[EventHeader_]
  Int_t           EventHeader_runNumber[kMaxEventHeader];   //[EventHeader_]
  ULong_t         EventHeader_timeStamp[kMaxEventHeader];   //[EventHeader_]
  Float_t         EventHeader_weight[kMaxEventHeader];   //[EventHeader_]
  //Int_t           MPGDTRDEndcapHits_;
  ULong_t         MPGDTRDEndcapHits_cellID[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Float_t         MPGDTRDEndcapHits_EDep[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Float_t         MPGDTRDEndcapHits_time[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Float_t         MPGDTRDEndcapHits_pathLength[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Int_t           MPGDTRDEndcapHits_quality[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Double_t        MPGDTRDEndcapHits_position_x[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Double_t        MPGDTRDEndcapHits_position_y[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Double_t        MPGDTRDEndcapHits_position_z[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Float_t         MPGDTRDEndcapHits_momentum_x[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Float_t         MPGDTRDEndcapHits_momentum_y[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  Float_t         MPGDTRDEndcapHits_momentum_z[kMaxMPGDTRDEndcapHits];   //[MPGDTRDEndcapHits_]
  
  // List of branches
  //TBranch        *b_MCParticles_;   //!
  TBranch        *b_MCParticles_PDG;   //!
  TBranch        *b_MCParticles_generatorStatus;   //!
  TBranch        *b_MCParticles_simulatorStatus;   //!
  TBranch        *b_MCParticles_charge;   //!
  TBranch        *b_MCParticles_time;   //!
  TBranch        *b_MCParticles_mass;   //!
  TBranch        *b_MCParticles_vertex_x;   //!
  TBranch        *b_MCParticles_vertex_y;   //!
  TBranch        *b_MCParticles_vertex_z;   //!
  TBranch        *b_MCParticles_endpoint_x;   //!
  TBranch        *b_MCParticles_endpoint_y;   //!
  TBranch        *b_MCParticles_endpoint_z;   //!
  TBranch        *b_MCParticles_momentum_x;   //!
  TBranch        *b_MCParticles_momentum_y;   //!
  TBranch        *b_MCParticles_momentum_z;   //!
  TBranch        *b_MCParticles_momentumAtEndpoint_x;   //!
  TBranch        *b_MCParticles_momentumAtEndpoint_y;   //!
  TBranch        *b_MCParticles_momentumAtEndpoint_z;   //!
  TBranch        *b_MCParticles_spin_x;   //!
  TBranch        *b_MCParticles_spin_y;   //!
  TBranch        *b_MCParticles_spin_z;   //!
  TBranch        *b_MCParticles_colorFlow_a;   //!
  TBranch        *b_MCParticles_colorFlow_b;   //!
  TBranch        *b_MCParticles_parents_begin;   //!
  TBranch        *b_MCParticles_parents_end;   //!
  TBranch        *b_MCParticles_daughters_begin;   //!
  TBranch        *b_MCParticles_daughters_end;   //!
  //TBranch        *b_EventHeader_;   //!
  TBranch        *b_EventHeader_eventNumber;   //!
  TBranch        *b_EventHeader_runNumber;   //!
  TBranch        *b_EventHeader_timeStamp;   //!
  TBranch        *b_EventHeader_weight;   //!
  //TBranch        *b_MPGDTRDEndcapHits_;   //!
  TBranch        *b_MPGDTRDEndcapHits_cellID;   //!
  TBranch        *b_MPGDTRDEndcapHits_EDep;   //!
  TBranch        *b_MPGDTRDEndcapHits_time;   //!
  TBranch        *b_MPGDTRDEndcapHits_pathLength;   //!
  TBranch        *b_MPGDTRDEndcapHits_quality;   //!
  TBranch        *b_MPGDTRDEndcapHits_position_x;   //!
  TBranch        *b_MPGDTRDEndcapHits_position_y;   //!
  TBranch        *b_MPGDTRDEndcapHits_position_z;   //!
  TBranch        *b_MPGDTRDEndcapHits_momentum_x;   //!
  TBranch        *b_MPGDTRDEndcapHits_momentum_y;   //!
  TBranch        *b_MPGDTRDEndcapHits_momentum_z;   //!
  
  //fChain.SetBranchAddress("MCParticles", &MCParticles_, &b_MCParticles_);
  fChain.SetBranchAddress("MCParticles.PDG", MCParticles_PDG, &b_MCParticles_PDG);
  fChain.SetBranchAddress("MCParticles.generatorStatus", MCParticles_generatorStatus, &b_MCParticles_generatorStatus);
  fChain.SetBranchAddress("MCParticles.simulatorStatus", MCParticles_simulatorStatus, &b_MCParticles_simulatorStatus);
  fChain.SetBranchAddress("MCParticles.charge", MCParticles_charge, &b_MCParticles_charge);
  fChain.SetBranchAddress("MCParticles.time", MCParticles_time, &b_MCParticles_time);
  fChain.SetBranchAddress("MCParticles.mass", MCParticles_mass, &b_MCParticles_mass);
  fChain.SetBranchAddress("MCParticles.vertex.x", MCParticles_vertex_x, &b_MCParticles_vertex_x);
  fChain.SetBranchAddress("MCParticles.vertex.y", MCParticles_vertex_y, &b_MCParticles_vertex_y);
  fChain.SetBranchAddress("MCParticles.vertex.z", MCParticles_vertex_z, &b_MCParticles_vertex_z);
  fChain.SetBranchAddress("MCParticles.endpoint.x", MCParticles_endpoint_x, &b_MCParticles_endpoint_x);
  fChain.SetBranchAddress("MCParticles.endpoint.y", MCParticles_endpoint_y, &b_MCParticles_endpoint_y);
  fChain.SetBranchAddress("MCParticles.endpoint.z", MCParticles_endpoint_z, &b_MCParticles_endpoint_z);
  fChain.SetBranchAddress("MCParticles.momentum.x", MCParticles_momentum_x, &b_MCParticles_momentum_x);
  fChain.SetBranchAddress("MCParticles.momentum.y", MCParticles_momentum_y, &b_MCParticles_momentum_y);
  fChain.SetBranchAddress("MCParticles.momentum.z", MCParticles_momentum_z, &b_MCParticles_momentum_z);
  fChain.SetBranchAddress("MCParticles.momentumAtEndpoint.x", MCParticles_momentumAtEndpoint_x, &b_MCParticles_momentumAtEndpoint_x);
  fChain.SetBranchAddress("MCParticles.momentumAtEndpoint.y", MCParticles_momentumAtEndpoint_y, &b_MCParticles_momentumAtEndpoint_y);
  fChain.SetBranchAddress("MCParticles.momentumAtEndpoint.z", MCParticles_momentumAtEndpoint_z, &b_MCParticles_momentumAtEndpoint_z);
  fChain.SetBranchAddress("MCParticles.spin.x", MCParticles_spin_x, &b_MCParticles_spin_x);
  fChain.SetBranchAddress("MCParticles.spin.y", MCParticles_spin_y, &b_MCParticles_spin_y);
  fChain.SetBranchAddress("MCParticles.spin.z", MCParticles_spin_z, &b_MCParticles_spin_z);
  fChain.SetBranchAddress("MCParticles.colorFlow.a", MCParticles_colorFlow_a, &b_MCParticles_colorFlow_a);
  fChain.SetBranchAddress("MCParticles.colorFlow.b", MCParticles_colorFlow_b, &b_MCParticles_colorFlow_b);
  fChain.SetBranchAddress("MCParticles.parents_begin", MCParticles_parents_begin, &b_MCParticles_parents_begin);
  fChain.SetBranchAddress("MCParticles.parents_end", MCParticles_parents_end, &b_MCParticles_parents_end);
  fChain.SetBranchAddress("MCParticles.daughters_begin", MCParticles_daughters_begin, &b_MCParticles_daughters_begin);
  fChain.SetBranchAddress("MCParticles.daughters_end", MCParticles_daughters_end, &b_MCParticles_daughters_end);
  //fChain.SetBranchAddress("EventHeader", &EventHeader_, &b_EventHeader_);
  fChain.SetBranchAddress("EventHeader.eventNumber", EventHeader_eventNumber, &b_EventHeader_eventNumber);
  fChain.SetBranchAddress("EventHeader.runNumber", EventHeader_runNumber, &b_EventHeader_runNumber);
  fChain.SetBranchAddress("EventHeader.timeStamp", EventHeader_timeStamp, &b_EventHeader_timeStamp);
  fChain.SetBranchAddress("EventHeader.weight", EventHeader_weight, &b_EventHeader_weight);
  //fChain.SetBranchAddress("MPGDTRDEndcapHits", &MPGDTRDEndcapHits_, &b_MPGDTRDEndcapHits_);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.cellID", MPGDTRDEndcapHits_cellID, &b_MPGDTRDEndcapHits_cellID);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.EDep", MPGDTRDEndcapHits_EDep, &b_MPGDTRDEndcapHits_EDep);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.time", MPGDTRDEndcapHits_time, &b_MPGDTRDEndcapHits_time);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.pathLength", MPGDTRDEndcapHits_pathLength, &b_MPGDTRDEndcapHits_pathLength);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.quality", MPGDTRDEndcapHits_quality, &b_MPGDTRDEndcapHits_quality);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.position.x", MPGDTRDEndcapHits_position_x, &b_MPGDTRDEndcapHits_position_x);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.position.y", MPGDTRDEndcapHits_position_y, &b_MPGDTRDEndcapHits_position_y);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.position.z", MPGDTRDEndcapHits_position_z, &b_MPGDTRDEndcapHits_position_z);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.momentum.x", MPGDTRDEndcapHits_momentum_x, &b_MPGDTRDEndcapHits_momentum_x);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.momentum.y", MPGDTRDEndcapHits_momentum_y, &b_MPGDTRDEndcapHits_momentum_y);
  fChain.SetBranchAddress("MPGDTRDEndcapHits.momentum.z", MPGDTRDEndcapHits_momentum_z, &b_MPGDTRDEndcapHits_momentum_z);  
/*  
  ch.SetBranchAddress("ev", &EVENT);
  ch.SetBranchAddress( "runNumber", &RunNumber);
  ch.SetBranchAddress("ped_d", &dped);
  ch.SetBranchAddress("ped_w2", &w2ped); 
  ch.SetBranchAddress("q_d", &dcharge);
  ch.SetBranchAddress("q_w2", &w2charge);
  ch.SetBranchAddress("qm_d", &dmcharge);
  ch.SetBranchAddress("qm_w2", &w2mcharge);
  ch.SetBranchAddress("dsig", &dsig);
  ch.SetBranchAddress("dwid", &dwid);
  ch.SetBranchAddress("w2sig", &w2sig);
  ch.SetBranchAddress("w2wid", &w2wid);
  ch.SetBranchAddress("t_d", &dsmax);
  ch.SetBranchAddress("t_w2", &w2smax);
  ch.SetBranchAddress("dch", &dchmax);
  ch.SetBranchAddress("w2ch", &w2chmax);
  ch.SetBranchAddress("dsz", &dsize);
  ch.SetBranchAddress("w2sz", &w2size);
  ch.SetBranchAddress("trig", &trig);
  ch.SetBranchAddress("w2nhit", &w2nhit);
  ch.SetBranchAddress("w2thit", &w2thit);
  ch.SetBranchAddress("w2ahit", &w2ahit);
  ch.SetBranchAddress("w2mhit", &w2mhit);
  ch.SetBranchAddress("w2chit", &w2chit);
  ch.SetBranchAddress("dnhit", &dnhit);
  ch.SetBranchAddress("dthit", &dthit);
  ch.SetBranchAddress("dahit", &dahit);
  ch.SetBranchAddress("dmhit", &dmhit);
  ch.SetBranchAddress("dchit", &dchit);
*/  
  TFile* outputFile = TFile::Open("combined_events.root","RECREATE");
  //outputFile->mkdir("~/TRDPrototype/")->cd();
  fChain.Merge(outputFile, 0); //Merge all entries in the chain to a new tree in this new file
  fChain.MakeClass("chainAnalyzer");
  fChain.ls();
  
  timer.Stop();
  timer.Print(); 

}
