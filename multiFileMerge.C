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

using namespace std;
//using namespace ROOT;

void multiFileMerge(){
  /*  
    TFile *fin = new TFile("/Users/souravtarafdar/sPHENIX/G4sim/svtx_pix_maps_pion/g4svtx_eval_50pionevt.root");
    TTree *ntp_track = (TTree*)fin->Get("ntp_track");
  */
  
  //A chain is a collection of files containg TTree objects
  //Use TChain for multiple files - All constructors are equivalent
  TChain ch("fdctest");
  //ArCO2 files
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002019.evio.disproot");
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002024.evio.disproot");
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002039.evio.disproot");
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002057.evio.disproot");
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002062.evio.disproot");
  
  //XeCO2 files
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002036.evio.disproot");
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002037.evio.disproot");
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002038.evio.disproot");
//  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002060.evio.disproot"); //Bad run
//  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002031.evio.disproot"); //Bad run
  ch.Add("~TRDPrototype/disprootFiles/hd_rawdata_002053.evio.disproot");
  
  char buffer[21];
  int nTrees = GetNtrees();
  sprintf(buffer, "%d", nTrees);
  
  int EVENT;
  int RunNumber;
  int trig=0;
  float dped=0.;
  int dchmax=0;
  float dsig=0;
  int dwid=0;
  int dsmax=0;
  float wmax=0.;
  float wped=0.;
  int wchmax=0;
  float wcent=0;
  float wfit=0;
  float wmcent=0;
  float wmfit=0;
  float wsig=0;
  int wwid=0;
  int wsmax=0;
  float w2ped=0.;
  int w2chmax=0;
  float w2sig=0;
  int w2wid=0;
  int w2smax=0;
  float dcharge=0.;
  float wcharge=0.;
  float w2charge=0.;
  float dmcharge=0.;
  float wmcharge=0.;
  float w2mcharge=0.;
  int dsize=0;
  int wsize=0;
  int w2size=0;

  ch.SetBranchAddress("ev", &EVENT);
  ch.SetBranchAddress( "runNumber", &RunNumber);
  ch.SetBranchAddress("max_w", &wmax);
  ch.SetBranchAddress("ped_d", &dped);
  ch.SetBranchAddress("ped_w", &wped);
  ch.SetBranchAddress("ped_w2", &w2ped); 
  ch.SetBranchAddress("q_d", &dcharge);
  ch.SetBranchAddress("q_w", &wcharge);
  ch.SetBranchAddress("q_w2", &w2charge);
  ch.SetBranchAddress("qm_d", &dmcharge);
  ch.SetBranchAddress("qm_w", &wmcharge);
  ch.SetBranchAddress("qm_w2", &w2mcharge);
  ch.SetBranchAddress("dsig", &dsig);
  ch.SetBranchAddress("dwid", &dwid);
  ch.SetBranchAddress("wcent", &wcent);
  ch.SetBranchAddress("wfit", &wfit);
  ch.SetBranchAddress("wmcent", &wmcent);
  ch.SetBranchAddress("wmfit", &wmfit);
  ch.SetBranchAddress("wsig", &wsig);
  ch.SetBranchAddress("wwid", &wwid);
  ch.SetBranchAddress("w2sig", &w2sig);
  ch.SetBranchAddress("w2wid", &w2wid);
  ch.SetBranchAddress("t_d", &dsmax);
  ch.SetBranchAddress("t_w", &wsmax);
  ch.SetBranchAddress("t_w2", &w2smax);
  ch.SetBranchAddress("dch", &dchmax);
  ch.SetBranchAddress("wch", &wchmax);
  ch.SetBranchAddress("w2ch", &w2chmax);
  ch.SetBranchAddress("dsz", &dsize);
  ch.SetBranchAddress("wsz", &wsize);
  ch.SetBranchAddress("w2sz", &w2size);
  ch.SetBranchAddress("trig", &trig);
  ch.SetBranchAddress("wnhit", &wnhit);
  ch.SetBranchAddress("wthit", &wthit);
  ch.SetBranchAddress("wahit", &wahit);
  ch.SetBranchAddress("wmhit", &wmhit);
  ch.SetBranchAddress("wchit", &wchit);
  ch.SetBranchAddress("w2nhit", &w2nhit);
  ch.SetBranchAddress("w2thit", &w2thit);
  ch.SetBranchAddress("w2ahit", &w2ahit);
  ch.SetBranchAddress("w2mhit", &w2mhit);
  ch.SetBranchAddress("w2chit", &w2chit);
  ch.SetBranchAddress("unhit", &unhit);
  ch.SetBranchAddress("uthit", &uthit);
  ch.SetBranchAddress("uahit", &uahit);
  ch.SetBranchAddress("dnhit", &dnhit);
  ch.SetBranchAddress("dthit", &dthit);
  ch.SetBranchAddress("dahit", &dahit);
  ch.SetBranchAddress("dmhit", &dmhit);
  ch.SetBranchAddress("dchit", &dchit);
  
  
  ch.Merge(combined_fdctest.root); //Merge all entries in the chain to a new tree in this new file
  //ch.MakeClass("treeAnalyzer");
  ch.ls
  
  
  //// GEM Histos ////
  TH2D *w2AvsT = new TH2D("w2AvsT","GEM Amplitude vs Time",300,-0.5,299.5,240,-0.5,239.5);
//  TH2D *w2AvsTnorm = new TH2D("w2AvsTnorm","GEM Amplitude vs Time norm",300,-0.5,299.5,240,-0.5,239.5);
  TH2D *w2CvsT = new TH2D("w2CvsT","GEM Width (transverse) vs Time",300,-0.5,299.5,240,-0.5,239.5);
//  TH2D *w2CvsL = new TH2D("w2CvsL","GEM Width (longitudinal) vs Time",300,-0.5,299.5,240,-0.5,239.5);
  TH2D *w2AvsB = new TH2D("w2AvsB","GEM Amplitude vs Time (background)",300,-0.5,299.5,240,-0.5,239.5);
  TH2D *w2CvsB = new TH2D("w2CvsB","GEM Counts vs Time (background)",300,-0.5,299.5,240,-0.5,239.5);
  TH2D *w2YvsB = new TH2D("w2YvsB","GEM X vs Y (background)",240,-0.5,239.5,240,-0.5,239.5);
  TH2D *w2TYvsB = new TH2D("w2TYvsB","GEM TY vs Time (background)",300,-0.5,299.5,240,-0.5,239.5);
  TH2D *w2AvsD = new TH2D("w2AvsD","GEM Amplitude vs Distance",1000,0.,35.,240,-0.5,239.5);
//  w2AvsTnorm->Sumw2();
  w2AvsT->Sumw2();
  w2CvsT->Sumw2();
//  w2CvsL->Sumw2();
  w2AvsB->Sumw2();
  w2CvsB->Sumw2();
  w2YvsB->Sumw2();
  w2TYvsB->Sumw2();
  w2AvsD->Sumw2();

  TAxis *xaxis = (TAxis*)w2AvsT->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  TAxis *yaxis = (TAxis*)w2AvsT->GetYaxis();
  yaxis->SetTitle("Channel");
  xaxis = (TAxis*)w2AvsB->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  yaxis = (TAxis*)w2AvsB->GetYaxis();
  yaxis->SetTitle("Channel");
  xaxis = (TAxis*)w2CvsB->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  yaxis = (TAxis*)w2CvsB->GetYaxis();
  yaxis->SetTitle("Channel");
  
  //// MMG Histos ////
  TH2D *dAvsT = new TH2D("dAvsT","MMG Amplitude vs Time",300,-0.5,299.5,200,-0.5,199.5);
//  TH2D *dAvsTnorm = new TH2D("dAvsTnorm","MMG Amplitude vs Time norm",300,-0.5,299.5,200,-0.5,199.5);
  TH2D *dCvsT = new TH2D("dCvsT","MMG Width (transverse) vs Time",300,-0.5,299.5,200,-0.5,199.5);
//  TH2D *dCvsL = new TH2D("dCvsL","MMG Width (longitudinal) vs Time",300,-0.5,299.5,200,-0.5,199.5);
  TH2D *dAvsB = new TH2D("dAvsB","MMG Amplitude vs Time (background)",300,-0.5,299.5,200,-0.5,199.5);
  TH2D *dCvsB = new TH2D("dCvsB","MMG Counts vs Time (background)",300,-0.5,299.5,200,-0.5,199.5);
  TH2D *dYvsB = new TH2D("dYvsB","MMG X vs Y (background)",200,-0.5,199.5,200,-0.5,199.5);
  TH2D *dTYvsB = new TH2D("dTYvsB","MMG TY vs Time (background)",1000,-0.5,999.5,200,-0.5,199.5);
  TH2D *dAvsD = new TH2D("dAvsD","MMG Amplitude vs Distance",1000,0.,35.,200,-0.5,199.5);
//  dAvsTnorm->Sumw2();
  dAvsT->Sumw2();
  dCvsT->Sumw2();
//  dCvsL->Sumw2();
  dAvsB->Sumw2();
  dCvsB->Sumw2();
  dYvsB->Sumw2();
  dTYvsB->Sumw2();
  dAvsD->Sumw2();
  
  xaxis = (TAxis*)dAvsT->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  yaxis = (TAxis*)dAvsT->GetYaxis();
  yaxis->SetTitle("Channel");
  xaxis = (TAxis*)dAvsB->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  yaxis = (TAxis*)dAvsB->GetYaxis();
  yaxis->SetTitle("Channel");
  xaxis = (TAxis*)dCvsT->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  yaxis = (TAxis*)dCvsT->GetYaxis();
  yaxis->SetTitle("Channel");
  xaxis = (TAxis*)dCvsB->GetXaxis();
  xaxis->SetTitle("Time (*8 ns)");
  yaxis = (TAxis*)dCvsB->GetYaxis();
  yaxis->SetTitle("Channel");
  
  //// 1D Comparisons ////
  
  
}

