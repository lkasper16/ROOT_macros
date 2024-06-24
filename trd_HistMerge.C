#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <TTree.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TList.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TLine.h>
#include <TList.h>
#include <TObject.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TProfile.h>

//bool changeToDirectory(const TString& directoryPath) {
//    if (gSystem->AccessPathName(directoryPath) == 0) {
//        if (gSystem->ChangeDirectory(directoryPath) == 0) {
//            return true; // Successfully changed to the directory
//        }
//    }
//    return false; // Directory doesn't exist or failed to change
//}

void trd_HistMerge(){
	
	//TString inputDir = "~fermiDataAnalysis/cherDownUpNoBoxOutput/RootOutput";
	TString inputDir = "../fermiDataAnalysis/patternRecognitionTracks/v5/RootOutput";
	
//	if (!changeToDirectory(inputDir)) {
//        std::cerr << "Error: Directory '" << inputDir << "' does not exist or cannot be accessed." << std::endl;
//        return;
//  }
	
	TString rootFiles[] = {"Run_003202_Output.root", "Run_003288_Output.root", "Run_003218_Output.root"};
	TList *histList = new TList;
	TString name1 = "f125_el";
    TString name2 = "f125_pi";
	TString name3 = "mmg1_f125_el";
    TString name4 = "mmg1_f125_pi";
	TString name5 = "urw_f125_el";
	TString name6 = "urw_f125_pi";
	int colorList[] = {94,51,209};
	TString legendList[] = {"GEM 6200V/3200V (10 GeV)","MMG-1 4800V/675V (10 GeV)","uRWell 4500V/540V (3 GeV)"};
	TLegend *l1 = new TLegend(0.75, 0.65, 0.9, 0.9);
	
	for (int i=0; i<sizeof(rootFiles)/sizeof(rootFiles[0]); i++) {
		const TString& rootFile = rootFiles[i];
		TFile *file = TFile::Open(rootFile, "READ");
		TList *HistDQM = (TList *)file->Get("HistDQM");
		TIter next(HistDQM);
		
		while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
			TString histName = readObject->GetName();
			if (histName == name1 && rootFile == "Run_003202_Output.root") {
				readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
				double elScaleFactor = 1./readObject->GetEntries();
				readObject->Scale(elScaleFactor);
				histList->Add(readObject);
				l1->AddEntry(readObject, legendList[i], "l");
			} else if (histName == name2 && rootFile == "Run_003202_Output.root") {
				readObject->SetLineStyle(3);
 	        	readObject->SetMarkerStyle(3);
          		readObject->SetMarkerColor(colorList[i]);
          		readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
          		double piScaleFactor = 1./readObject->GetEntries();
          		readObject->Scale(piScaleFactor);
         		histList->Add(readObject);
			} else if (histName == name3 && rootFile == "Run_003288_Output.root") {
				readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
				double elScaleFactor = 1./readObject->GetEntries();
				readObject->Scale(elScaleFactor);
				histList->Add(readObject);
				l1->AddEntry(readObject, legendList[i], "l");
			} else if (histName == name4 && rootFile == "Run_003288_Output.root") {
				readObject->SetLineStyle(3);
 	        	readObject->SetMarkerStyle(3);
          		readObject->SetMarkerColor(colorList[i]);
          		readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
          		double piScaleFactor = 1./readObject->GetEntries();
          		readObject->Scale(piScaleFactor);
         		histList->Add(readObject);
			} else if (histName == name5 && rootFile == "Run_003218_Output.root") {
				readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
				double elScaleFactor = 1./readObject->GetEntries();
				readObject->Scale(elScaleFactor);
				histList->Add(readObject);
				l1->AddEntry(readObject, legendList[i], "l");
			} else if (histName == name6 && rootFile == "Run_003218_Output.root") {
				readObject->SetLineStyle(3);
 	        	readObject->SetMarkerStyle(3);
          		readObject->SetMarkerColor(colorList[i]);
          		readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
          		double piScaleFactor = 1./readObject->GetEntries();
          		readObject->Scale(piScaleFactor);
         		histList->Add(readObject);
			}
		}
		file->Close();
	}
	
	TCanvas *c1 = new TCanvas("c1","Prototype ADC Distributions at Max HV Applied", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	gPad->SetGridx();
 	gPad->SetGridy();
	
	TH1 *firstHist = (TH1 *)histList->First();
    if (firstHist) {
        firstHist->GetXaxis()->SetTitle("ADC amplitude");
        firstHist->GetYaxis()->SetTitle("Counts / numEntries");
        firstHist->SetTitle("Prototype ADC Distributions in XeCO2");
    }
	
	histList->Draw("same");
    l1->Draw();
	c1->SaveAs("TRD_ADC_Xe_Comparison_v1.png");
}
