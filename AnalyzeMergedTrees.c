#include <iostream>
#include <vector>
#include "vector"
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
#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TLine.h>
#include <TBox.h>
#include <TObject.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TROOT.h>
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

void AnalyzeMergedTrees(){
  
	TStopwatch timer;
  	timer.Start();
	
	//TChain ch("events");
	//ch.Add("~/eic/output_trd_testing_pion.edm4hep.root");
	//ch.Add("~/eic/output_trd_testing_pion_low.edm4hep.root");
	//ch.Add("~/eic/output_trd_testing_electron.edm4hep.root");
	//ch.Add("~/eic/output_trd_testing_electron_low.edm4hep.root");
	//ch.Add("~/eic/output_trd_testing_muon.edm4hep.root");
	//ch.Add("~/eic/output_trd_testing_muon_low.edm4hep.root");
	
	TFile *inputFile = TFile::Open("combined_events.root");
	if (!inputFile || inputFile->IsZombie()) {
		std::cerr <<"Cannot open input file - exiting..."<< std::endl;
		return;
	}
	TTree *eventsTree = dynamic_cast<TTree*>(inputFile->Get("events"));
	if (!eventsTree) {
		std::cerr <<"File opened, but cannot access tree 'events' - exiting..."<< std::endl;
		return;
	}
	
  	Long64_t nEnts = eventsTree->GetEntries();
  	cout << "Total # of entries: " << nEnts <<  endl;
	
	//// Define Histos ////
	TH1F *pz_pion_low = new TH1F("pz_pion_low","Pz Distribution 1-10 GeV/c",200,0.,11);
	TH1F *pz_electron_low = new TH1F("pz_electron_low","Pz Distribution 1-10 GeV/c",200,0.,11);
	TH1F *pz_muon_low = new TH1F("pz_muon_low","Pz Distribution 1-10 GeV/c",200,10,51);
    TH1F *pz_pion_low_truth = new TH1F("pz_pion_low_truth","Pz Distribution 1-10 GeV/c",200,0.,11);
    TH1F *pz_electron_low_truth = new TH1F("pz_electron_low_truth","Pz Distribution 1-10 GeV/c",200,0.,11);
	TH1F *pz_muon_low_truth = new TH1F("pz_muon_low_truth","Pz Distribution 1-10 GeV/c",200,10,51);
	
	TH1F *pz_pion = new TH1F("pz_pion","Pz Distribution 10-50 GeV/c",200,10,51);
	TH1F *pz_electron = new TH1F("pz_electron","Pz Distribution 10-50 GeV/c",200,10,51);
	TH1F *pz_muon = new TH1F("pz_muon","Pz Distribution 10-50 GeV/c",200,10,51);
    TH1F *pz_pion_truth = new TH1F("pz_pion_truth","Pz Distribution 10-50 GeV/c",200,10,51);
    TH1F *pz_electron_truth = new TH1F("pz_electron_truth","Pz Distribution 10-50 GeV/c",200,10,51);
	TH1F *pz_muon_truth = new TH1F("pz_muon_truth","Pz Distribution 10-50 GeV/c",200,10,51);
	
	// Fixed size dimensions of array or collections stored in the TTree if any.
    static constexpr Int_t kMaxMCParticles = 2;
    static constexpr Int_t kMaxEventHeader = 1;
    static constexpr Int_t kMaxMPGDTRDEndcapHits = 1434;
	
	//// Declaration of leaf types ////
    //Int_t MCParticles_;
    Int_t MCParticles_PDG;				  	//[MCParticles_]
    //Int_t MCParticles_generatorStatus[kMaxMCParticles];   	//[MCParticles_]
    //Int_t MCParticles_simulatorStatus[kMaxMCParticles];   //[MCParticles_]
    //Float_t MCParticles_charge[kMaxMCParticles];   		//[MCParticles_]
    //Float_t MCParticles_time[kMaxMCParticles];   			//[MCParticles_]
    //Double_t MCParticles_mass[kMaxMCParticles];   		//[MCParticles_]
    //Float_t MCParticles_momentum_x[kMaxMCParticles];   	//[MCParticles_]
    //Float_t MCParticles_momentum_y[kMaxMCParticles];   	//[MCParticles_]
	//Int_t EventHeader_;
    //Int_t EventHeader_eventNumber[kMaxEventHeader];   		//[EventHeader_]
    //Int_t EventHeader_runNumber[kMaxEventHeader];   		//[EventHeader_]
    //ULong_t EventHeader_timeStamp[kMaxEventHeader];   		//[EventHeader_]
    //Float_t EventHeader_weight[kMaxEventHeader];   			//[EventHeader_]
    //Int_t MPGDTRDEndcapHits_;
    Float_t MCParticles_momentum_z;   		//[MCParticles_]
	Float_t MPGDTRDEndcapHits_momentum_z;   //[MPGDTRDEndcapHits_]
	
	//// List of branches ////
    //TBranch *b_MCParticles_;   //!
    TBranch *b_MCParticles_PDG = eventsTree->GetBranch("MCParticles.PDG");
	if (!b_MCParticles_PDG) {
		std::cerr <<"Cannot find MCParticles.PDG in Tree 'events'"<<std::endl;
	}
    //TBranch *b_MCParticles_generatorStatus;   //!
    //TBranch *b_MCParticles_simulatorStatus;   //!
    //TBranch *b_MCParticles_charge;   //!
    //TBranch *b_MCParticles_time;   //!
    //TBranch *b_MCParticles_mass;   //!
    //TBranch *b_MCParticles_momentum_x;   //!
    //TBranch *b_MCParticles_momentum_y;   //!
	//TBranch *b_EventHeader_;   //!
    //TBranch *b_EventHeader_eventNumber;   //!
    //TBranch *b_EventHeader_runNumber;   //!
    //TBranch *b_EventHeader_timeStamp;   //!
    //TBranch *b_EventHeader_weight;   //!
    //TBranch *b_MPGDTRDEndcapHits_;   //!
    TBranch *b_MCParticles_momentum_z = eventsTree->GetBranch("MCParticles.momentum.z");   //!
    TBranch *b_MPGDTRDEndcapHits_momentum_z = eventsTree->GetBranch("MPGDTRDEndcapHits.momentum.z");   //!
	
	//// Assign branches to respective leaf values ////
	//.SetAddress("MCParticles", &MCParticles_, &b_MCParticles_);
    b_MCParticles_PDG->SetAddress(&MCParticles_PDG);
	b_MCParticles_momentum_z->SetAddress(&MCParticles_momentum_z);
	b_MPGDTRDEndcapHits_momentum_z->SetAddress(&MPGDTRDEndcapHits_momentum_z);
	
	//// Read TTree ////
	for(Long64_t i=0; i<5; i++) {
		
		eventsTree->GetEntry(i);
		//MCParticles_PDG[i] = b_MCParticles_PDG->GetEntry(i);
		//MCParticles_momentum_z[i] = b_MCParticles_momentum_z->GetEntry(i);
		//MPGDTRDEndcapHits_momentum_z[i] = b_MPGDTRDEndcapHits_momentum_z->GetEntry(i);
		cout<<"Event #: "<<i<<endl;
		cout<<"Without PID: "<<MCParticles_momentum_z<<endl;
		if (MCParticles_PDG == -211) {
			if (MCParticles_momentum_z != 0) {
				pz_pion_truth->Fill(MCParticles_momentum_z);
				cout<<"With PID: "<<MCParticles_momentum_z<<endl;
				//pz_pion_low_truth->Fill(truthMom_z);
			}
			if (MPGDTRDEndcapHits_momentum_z != 0) {
				pz_pion->Fill(MPGDTRDEndcapHits_momentum_z);
				//pz_pion_low->Fill(hitMom_z);
			}
		}
		if (MCParticles_PDG == 11) {
			if (MCParticles_momentum_z != 0) {
                pz_electron_truth->Fill(MCParticles_momentum_z);
				//pz_electron_low_truth->Fill(truthMom_z);
            }
            if (MPGDTRDEndcapHits_momentum_z != 0) {
                pz_electron->Fill(MPGDTRDEndcapHits_momentum_z);
				//pz_electron_low->Fill(hitMom_z);
            }
		}
		if (MCParticles_PDG == 13) {
            if (MCParticles_momentum_z != 0) {
                pz_muon_truth->Fill(MCParticles_momentum_z);
                //pz_muon_low_truth->Fill(truthMom_z);
            }
            if (MPGDTRDEndcapHits_momentum_z != 0) {
                pz_muon->Fill(MPGDTRDEndcapHits_momentum_z);
                //pz_muon_low->Fill(hitMom_z);
            }
        }
		
	}//// end entry loop ////
	
	//// Draw Histos ////
	TCanvas *c1 = new TCanvas("c1","c1",1200,800);
	gStyle->SetOptStat(00000);
	c1->cd();
	//gPad->SetLogy();
	
	pz_pion->SetLineColor(2);
	pz_pion->GetXaxis()->SetTitle("Pz [GeV/c]");
	pz_pion->GetYaxis()->SetTitle("Counts");
	pz_pion->GetYaxis()->SetRangeUser(0, 200);
	pz_pion->Draw();
	
	pz_pion_truth->SetLineColor(208);
    pz_pion_truth->SetLineStyle(3);
    pz_pion_truth->SetLineWidth(3);
    pz_pion_truth->Draw("same");
	
	pz_electron->SetLineColor(4);
    pz_electron->Draw("same");
	
	pz_electron_truth->SetLineColor(64);
	pz_electron_truth->SetLineStyle(3);
    pz_electron_truth->SetLineWidth(3);
    pz_electron_truth->Draw("same");
	
	pz_muon->SetLineColor(8);
    pz_muon->Draw("same");
	
	pz_muon_truth->SetLineColor(3);
    pz_muon_truth->SetLineStyle(3);
    pz_muon_truth->SetLineWidth(3);
    pz_muon_truth->Draw("same");
	
	TLegend *l1 = new TLegend(0.5, 0.8, 0.9, 0.9);
	l1->SetNColumns(2);
	l1->AddEntry(pz_electron, "e-", "L");
	l1->AddEntry(pz_electron_truth, "e- [truth]", "L");
	l1->AddEntry(pz_pion, "pi-", "L");
	l1->AddEntry(pz_pion_truth, "pi- [truth]", "L");
	l1->AddEntry(pz_muon, "mu-", "L");
    l1->AddEntry(pz_muon_truth, "mu- [truth]", "L");
	l1->Draw();
	
/*	//// Truth ////
	TCanvas *c2 = new TCanvas("c2","c2",1200,800);
    gStyle->SetOptStat(00000);
    c2->cd();
	
    pz_pion_low->SetLineColor(2);
    pz_pion_low->GetXaxis()->SetTitle("Pz [GeV/c]");
    pz_pion_low->GetYaxis()->SetTitle("Counts");
    pz_pion_low->GetYaxis()->SetRangeUser(0, 200);
    pz_pion_low->Draw();

    pz_electron_low->SetLineColor(4);
    pz_electron_low->Draw("same");
	
	pz_pion_low_truth->SetLineColor(208);
    pz_pion_low_truth->SetLineStyle(3);
    pz_pion_low_truth->SetLineWidth(3);
    pz_pion_low_truth->Draw("same");
	
    pz_electron_low_truth->SetLineColor(64);
    pz_electron_low_truth->SetLineStyle(3);
    pz_electron_low_truth->SetLineWidth(3);
    pz_electron_low_truth->Draw("same");
	
	pz_muon_low->SetLineColor(8);
    pz_muon_low->Draw("same");

    pz_muon_low_truth->SetLineColor(153);
    pz_muon_low_truth->SetLineStyle(3);
    pz_muon_low_truth->SetLineWidth(3);
    pz_muon_low_truth->Draw("same");
	
    TLegend *l2 = new TLegend(0.5, 0.8, 0.9, 0.9);
    l2->SetNColumns(2);
    l2->AddEntry(pz_electron_low, "e-", "L");
    l2->AddEntry(pz_pion_low, "pi-", "L");
    l2->AddEntry(pz_muon_low, "mu-", "L");
    l2->AddEntry(pz_electron_truth_low, "e- [truth]", "L");
    l2->AddEntry(pz_pion_truth_low, "pi- [truth]", "L");
    l2->AddEntry(pz_muon_truth_low, "mu- [truth]", "L");
    l2->Draw();
*/	
	
	timer.Stop();
	timer.Print();
}
