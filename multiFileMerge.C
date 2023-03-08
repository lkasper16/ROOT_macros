#include <iostream>
#include <fstream>
#include <string>
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

void multiFileMerge(){
  
  TStopwatch timer;
  timer.Start();
  
  //A chain is a collection of files containg TTree objects
  //Use TChain for multiple files - All constructors are equivalent
  TChain ch("fdctest");
  //// ArCO2 files ////
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002019.evio.disproot");
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002024.evio.disproot");
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002039.evio.disproot");
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002057.evio.disproot");
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002062.evio.disproot");
  
  //// XeCO2 files ////
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002036.evio.disproot");
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002037.evio.disproot");
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002038.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002060.evio.disproot"); //Bad run
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002031.evio.disproot"); //Bad run
  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002053.evio.disproot");
  
  int nTrees = ch.GetNtrees();
  int nEnts = ch.GetEntries();
  cout << "# of trees: " << nTrees <<  endl;
  cout << "# of entries: " << nEnts <<  endl;
  
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
  
  TFile* outputFile = TFile::Open("combined_fdctest.root","RECREATE");
  //outputFile->mkdir("~/TRDPrototype/")->cd();
  ch.Merge(outputFile, 0); //Merge all entries in the chain to a new tree in this new file
  ch.MakeClass("treeAnalyze");
  ch.ls();
  
  timer.Stop();
  timer.Print(); 

}

