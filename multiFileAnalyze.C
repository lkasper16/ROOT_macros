#include <iostream>
#include <vector>
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
#include <TH1D.h>
#include <TH2D.h>
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
//using namespace ROOT;

bool CheckValue(ROOT::Internal::TTreeReaderValueBase& value) {
   if (value.GetSetupStatus() < 0) {
      std::cerr << "Error " << value.GetSetupStatus()
                << "setting up reader for " << value.GetBranchName() << '\n';
      return false;
   }
   return true;
}

void multiFileAnalyze(){
  
  	TStopwatch timer;
  	timer.Start();
  	//Use TChain for multiple files - All constructors are equivalent
  	TChain ch("fdctest");
	
	//// ArCO2 files ////
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002057.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002024.evio.disproot");
    ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002039_NewMapping.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002057.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002062.evio.disproot");
// 	ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002069.evio.disproot");

	//// XeCO2 files ////
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002029.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002031.evio.disproot");
    ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002037.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002038.evio.disproot");
//  ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002053.evio.disproot");
// 	ch.Add("~/TRDPrototype/disprootFiles/hd_rawdata_002068.evio.disproot");
  	
  	int nTrees = ch.GetNtrees();
  	int nEnts = ch.GetEntries();
  	cout << "Total # of trees: " << nTrees <<  endl;
  	cout << "Total # of entries: " << nEnts <<  endl;
	
	//TFile* outputFile = TFile::Open("combined_fdctest.root","RECREATE");
  	//outputFile->mkdir("~/TRDPrototype/")->cd();
  	//ch.Merge(outputFile, 0); //Merge all entries in the chain to a new tree in this new file
	//ch.MakeClass("treeAnalyzer");
	//ch.ls();
  	
	//// Define Histograms ////
  	//TH1D *h1_qm = new TH1D("h1_qm","Max Amplitude Distribution", 4300, -1, 4299);
  	TH2D *w2AvsTXe = new TH2D("w2AvsTXe","GEM Amplitude vs Time in Xe",300,-0.5,299.5,240,-0.5,239.5);
  	w2AvsTXe->Sumw2();
  	TH2D *dAvsTXe = new TH2D("dAvsTXe","MMG Amplitude vs Time in Xe",300,-0.5,299.5,200,-0.5,199.5);
  	dAvsTXe->Sumw2();
	TH2D *w2AvsTAr = new TH2D("w2AvsTAr","GEM Amplitude vs Time in Ar",300,-0.5,299.5,240,-0.5,239.5);
    w2AvsTAr->Sumw2();
    TH2D *dAvsTAr = new TH2D("dAvsTAr","MMG Amplitude vs Time in Ar",300,-0.5,299.5,200,-0.5,199.5);
    dAvsTAr->Sumw2();
 	
	TH1D *qm_d_XeCO2 = new TH1D("qm_d_XeCO2","Max Amplitude Distribution - Half Fleece Rad",1000,0.,4500);
	TH1D *qm_w2_XeCO2 = new TH1D("qm_w2_XeCO2","Max Amplitude Distribution - Half Fleece Rad",1000,0.,5000);
	TH1D *qm_d_ArCO2 = new TH1D("qm_d_ArCO2","Max Amplitude Distribution - Half Fleece Rad",1000,0.,4500);
    TH1D *qm_w2_ArCO2 = new TH1D("qm_w2_ArCO2","Max Amplitude Distribution - Half Fleece Rad",1000,0.,4500);

	//// Define TREE variables ////
	int EVENT;
	int RunNumber;
	int samples;
	int isamp=0;
	int trig=0;
	
	float dped=0.;
	int dchmax=0;
	float dsig=0;
	int dwid=0;
	int dsmax=0;
	//float dAmpmax=0.;
	float w2ped=0.;
	int w2chmax=0;
	float w2sig=0;
	int w2wid=0;
	int w2smax=0;
	//float w2Ampmax=0.;
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
	
	/*
  	TTreeReader myReader("fdctest", outputFile); // name of tree and file/chain (&f/&ch)
  	TTreeReaderValue<Float_t> dmcharge(myReader, "qm_d");
  	TTreeReaderValue<Float_t> w2mcharge(myReader, "qm_w2");
  	TTreeReaderValue<Int_t> EVENT(myReader, "ev");
	TTreeReaderValue<Int_t> RunNumber(myReader, "runNumber");
	TTreeReaderValue<Int_t> dchmax(myReader, "dch");
	TTreeReaderValue<Int_t> w2chmax(myReader, "w2ch");
	TTreeReaderValue<Float_t> dsmax(myReader, "t_d");
	TTreeReaderValue<Float_t> w2smax(myReader, "t_w2");
	TTreeReaderValue<Float_t> dped(myReader, "ped_d");
	TTreeReaderValue<Float_t> dsig(myReader, "dsig");
	TTreeReaderValue<Int_t> dwid(myReader, "dwid");
	TTreeReaderValue<Float_t> w2ped(myReader, "ped_w2");
	TTreeReaderValue<Float_t> w2sig(myReader, "w2sig");
	TTreeReaderValue<Int_t> w2wid(myReader, "w2wid");
	TTreeReaderValue<Float_t> dcharge(myReader, "q_d");
	TTreeReaderValue<Float_t> w2charge(myReader, "q_w2");
	TTreeReaderValue<Int_t> dsize(myReader, "dsz");
	TTreeReaderValue<Int_t> w2size(myReader, "w2sz");
	TTreeReaderValue<Int_t> w2nhit(myReader, "w2nhit");
	TTreeReaderValue<Int_t> dnhit(myReader, "dnhit");
	TTreeReaderArray<Float_t> w2thit(myReader, "w2thit");
	TTreeReaderArray<Float_t> w2ahit(myReader, "w2ahit");
	TTreeReaderArray<Float_t> w2mhit(myReader, "w2mhit");
	TTreeReaderArray<Float_t> w2chit(myReader, "w2chit");
	TTreeReaderArray<Float_t> dthit(myReader, "dthit");
	TTreeReaderArray<Float_t> dahit(myReader, "dahit");
	TTreeReaderArray<Float_t> dmhit(myReader, "dmhit");
	TTreeReaderArray<Float_t> dchit(myReader, "dchit");
*/	
	ch.SetBranchAddress("ev", &EVENT);
	ch.SetBranchAddress("runNumber", &RunNumber);
	ch.SetBranchAddress("qm_d", &dmcharge);
	ch.SetBranchAddress("qm_w2", &w2mcharge);
	ch.SetBranchAddress("dch", &dchmax);
	ch.SetBranchAddress("w2ch", &w2chmax);
	ch.SetBranchAddress("t_d", &dsmax);
	ch.SetBranchAddress("t_w2", &w2smax);
	ch.SetBranchAddress("ped_d", &dped);
	ch.SetBranchAddress("ped_w2", &w2ped);
	ch.SetBranchAddress("q_d", &dcharge);
	ch.SetBranchAddress("q_w2", &w2charge);
	ch.SetBranchAddress("dsig", &dsig);
	ch.SetBranchAddress("dwid", &dwid);
	ch.SetBranchAddress("w2sig", &w2sig);
	ch.SetBranchAddress("w2wid", &w2wid);
	ch.SetBranchAddress("dsz", &dsize);
	ch.SetBranchAddress("w2sz", &w2size);
	//ch.SetBranchAddress("trig", &trig);
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
	
	//// Reading Tree ////
 	for(int i = 0; i < nEnts; i++){
		
		ch.GetEntry(i);
/*		//// Loop through all events ////
		bool firstEntry = true;
		while (myReader.Next()) {
			if (firstEntry) {
        		// Check that branches exist and their types match our expectation.
            	if (!CheckValue(EVENT)) return false;
            	if (!CheckValue(RunNumber)) return false;
            	firstEntry = false;
        	}
*/
		if (RunNumber == 2037) {
				
			if(dmcharge > 0){
				qm_d_XeCO2->Fill(dmcharge);  
			}
			if(w2mcharge > 0) {
			    qm_w2_XeCO2->Fill(w2mcharge);  
			}
			
			w2AvsTXe->Fill(w2smax,w2chmax);
			dAvsTXe->Fill (dsmax,dchmax);
		}	
		if (RunNumber == 2039) {
			
			if(dmcharge > 0){
                qm_d_ArCO2->Fill(dmcharge);
            }	
			if(w2mcharge > 0){
                qm_w2_ArCO2->Fill(w2mcharge);
            }
			
			w2AvsTAr->Fill(w2smax,w2chmax);
            dAvsTAr->Fill (dsmax,dchmax);
		}
 	} // End loop over TChain entries
	
	TCanvas *c1 = new TCanvas("c1","c1", 1200, 800);
	gStyle->SetOptStat(00000);
	//c1->cd();
	
	TPad *pad1 = new TPad("pad1","qm plot",0.01,0.49,0.51,0.92);
	TPad *pad2 = new TPad("pad2","dAvsT Xe plot",0.52,0.92,0.51,0.92);
    TPad *pad3 = new TPad("pad3","dAvsT Ar plot",0.02,0.50,0.2,0.5);
	TPad *pad4 = new TPad("pad4","w2AvsT Xe plot",0.52,0.92,0.21,0.5);
    TPad *pad5 = new TPad("pad5","w2AvsT Ar plot",0.03,0.51,0.001,0.2);
	pad1->Draw();
	pad2->Draw();
	pad3->Draw();
	pad4->Draw();
	pad5->Draw();
	
	pad1->cd();
	gPad->SetLogy();
	
	qm_d_XeCO2->SetLineColor(2);
	qm_d_XeCO2->GetXaxis()->SetTitle("Maximum ADC values");
	//qm_d_XeCO2->GetXaxis()->CenterTitle();
	//qm_d_XeCO2->GetXaxis()->SetTitleSize(0.2);
	qm_d_XeCO2->GetYaxis()->SetTitle("Counts");
	qm_d_XeCO2->GetYaxis()->SetRangeUser(0.1, 10000);
	qm_d_XeCO2->Draw();
	
	qm_w2_XeCO2->SetLineColor(4);
    qm_w2_XeCO2->Draw("same");
	
	qm_d_ArCO2->SetLineColor(208);
	qm_d_ArCO2->SetLineStyle(3);
	qm_d_ArCO2->SetLineWidth(3);
    qm_d_ArCO2->Draw("same");
	
	qm_w2_ArCO2->SetLineColor(64);
    qm_w2_ArCO2->SetLineStyle(3);
	qm_w2_ArCO2->SetLineWidth(3);
    qm_w2_ArCO2->Draw("same");
	
	TLegend *l1 = new TLegend(0.5, 0.8, 0.9, 0.9);
	l1->AddEntry(qm_w2_XeCO2, "GEM XeCO2", "L");
	l1->AddEntry(qm_d_XeCO2, "MMG XeCO2", "L");
	l1->AddEntry(qm_w2_ArCO2, "GEM ArCO2", "L");
	l1->AddEntry(qm_d_ArCO2, "MMG ArCO2", "L");
	l1->Draw();
	
	pad4->cd();
	
	w2AvsTXe->Draw("colz");
    TAxis *xaxis = (TAxis*)w2AvsTXe->GetXaxis();
    xaxis->SetTitle("Time (*8 ns)");
    TAxis *yaxis = (TAxis*)w2AvsTXe->GetYaxis();
    yaxis->SetTitle("Channel");
	
	pad2->cd();
	
	dAvsTXe->Draw("colz");
	xaxis = (TAxis*)dAvsTXe->GetXaxis();
    xaxis->SetTitle("Time (*8 ns)");
    yaxis = (TAxis*)dAvsTXe->GetYaxis();
    yaxis->SetTitle("Channel");
	
	pad5->cd();
	
 	w2AvsTAr->Draw("colz");
	xaxis = (TAxis*)w2AvsTAr->GetXaxis();
    xaxis->SetTitle("Time (*8 ns)");
    yaxis = (TAxis*)w2AvsTAr->GetYaxis();
    yaxis->SetTitle("Channel");
	
	pad4->cd();
	
    dAvsTAr->Draw("colz");
	xaxis = (TAxis*)dAvsTAr->GetXaxis();
    xaxis->SetTitle("Time (*8 ns)");
    yaxis = (TAxis*)dAvsTAr->GetYaxis();
    yaxis->SetTitle("Channel");
	
	c1->Update();
	
	timer.Stop();
    timer.Print();
	
}
