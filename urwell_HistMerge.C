#include <vector>
#include <fstream>
#include <iostream>
#include <string>
//#include <filesystem>
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

void urwell_HistMerge(){
	
	//TString inputDir = "~fermiDataAnalysis/cherDownUpNoBoxOutput/RootOutput";
	TString inputDir = "../fermiDataAnalysis/patternRecognitionTracks/v5/RootOutput";
	
//	if (!changeToDirectory(inputDir)) {
//        std::cerr << "Error: Directory '" << inputDir << "' does not exist or cannot be accessed." << std::endl;
//        return;
//  }
	
	TString rootFiles[] = {"Run_006247_Output.root", "Run_006245_Output.root", "Run_006244_Output.root","Run_006209_Output.root","Run_006246_Output.root"};
	TList *histList = new TList;
	TString name1 = "urw_f125_el_x";
	//TString name2 = "urw_f125_pi";
	int colorList[] = {94,51,209,6,7,1,2};
	TString legendList[] = {"1.925 kV/cm","1.95 kV/cm","1.975 kV/cm","1.2 kV/cm","2.025 kV/cm"};
	TLegend *l1 = new TLegend(0.75, 0.65, 0.9, 0.9);
	
	for (int i=0; i<sizeof(rootFiles)/sizeof(rootFiles[0]); i++) {
		const TString& rootFile = rootFiles[i];
		TFile *file = TFile::Open(rootFile, "READ");
		TList *HistDQM = (TList *)file->Get("HistDQM");
		TIter next(HistDQM);
		
		while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
			TString histName = readObject->GetName();
			if (histName == name1) {
				readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
				double elScaleFactor = 1./readObject->GetEntries();
				readObject->Scale(elScaleFactor);
				histList->Add(readObject);
				l1->AddEntry(readObject, legendList[i], "l");
			} /*else if (histName == name2) {
				readObject->SetLineStyle(3);
 	        	readObject->SetMarkerStyle(3);
          		readObject->SetMarkerColor(colorList[i]);
          		readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
          		double piScaleFactor = 1./readObject->GetEntries();
          		readObject->Scale(piScaleFactor);
         		//l1->AddEntry(readObject, legendList[i], "l");
         		histList->Add(readObject);
			}*/
		}
		file->Close();
	}
	
	TCanvas *c1 = new TCanvas("c1","uRWell X ADC Distributions, Varied TF", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	gPad->SetGridx();
 	gPad->SetGridy();
	
	  TH1 *firstHist = (TH1 *)histList->First();
    if (firstHist) {
        firstHist->GetXaxis()->SetTitle("ADC amplitude (X Plane)");
        firstHist->GetYaxis()->SetTitle("Counts / numEntries");
        firstHist->SetTitle("uRWell-TRD in ArCO2, 1.385kV/cm DF, 385V GEM dV, 490V WELL");
    }
	
	  histList->Draw("same");
    l1->SetHeader("Transfer Field","C");
    l1->Draw();
		c1->SaveAs("urw_ADC_TF_Comparison_v1.png");
}
