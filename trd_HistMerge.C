#include <vector>
#include <fstream>
#include <iostream>
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

void trd_HistMerge(){
	
	TString rootFilesGEM[] = {"RootOutput/cern24/merged/Run_005284_2012810Entries_Output.root", "RootOutput/cern24/merged/Run_005256_129038Entries_Output.root", "RootOutput/cern24/merged/Run_005306_559615Entries_Output.root", "RootOutput/ps25/Run_006268_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root"};
	TString rootFilesMMG[] = {"RootOutput/cern24/merged/Run_005284_2012810Entries_Output.root", "RootOutput/cern24/merged/Run_005256_129038Entries_Output.root", "RootOutput/cern24/merged/Run_005306_559615Entries_Output.root", "RootOutput/ps25/Run_006268_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root"};
  
  
  TList *histListGEM = new TList;
  TList *histListMMG = new TList;
	TString name1 = "f125_el";
	TString name2 = "mmg1_f125_el";
	TString name3 = "urw_f125_el_x";
	
	int colorList[] = {94,2,209,6,7,1,4,51};
	TString legendListGEM[] = {"CERN 6400V/3380V Xe(1st Bottle)","CERN 6350V/3350V Xe(1st Bottle)","CERN 6400V/3380V Xe (2nd Bottle)","PS25 6300V/3300V Xe (100CCPM)","FERMI 6200V/3200V Xe"};
  TString legendListMMG[] = {"CERN 5100V/1630V Xe(1st Bottle)","CERN 5000V/1580V Xe(1st Bottle)","CERN 5100V/1630V Xe (2nd Bottle)","PS25 5000V/1550V Xe (100CCPM)","FERMI 4825V/625V Xe"};
  
	TLegend *l1 = new TLegend(0.7, 0.65, 0.9, 0.9);
  TLegend *l2 = new TLegend(0.7, 0.65, 0.9, 0.9);
	
  //-- Triple GEM-TRD
	for (int i=0; i<sizeof(rootFilesGEM)/sizeof(rootFilesGEM[0]); i++) {
		const TString& rootFile = rootFilesGEM[i];
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
				histListGEM->Add(readObject);
				l1->AddEntry(readObject, legendListGEM[i], "lp");
			}
		}
		file->Close();
	}
  
  //-- MMG1-TRD
  for (int i=0; i<sizeof(rootFilesMMG)/sizeof(rootFilesMMG[0]); i++) {
    const TString& rootFile = rootFilesMMG[i];
    TFile *file = TFile::Open(rootFile, "READ");
    TList *HistDQM = (TList *)file->Get("HistDQM");
    TIter next(HistDQM);
    
    while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
      TString histName = readObject->GetName();
      if (histName == name2) {
        readObject->SetLineColor(colorList[i]);
        readObject->SetLineWidth(2);
        double elScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(elScaleFactor);
        histListMMG->Add(readObject);
        l2->AddEntry(readObject, legendListMMG[i], "lp");
      }
    }
    file->Close();
  }
	
	TCanvas *c1 = new TCanvas("c1","GEMTRD ADC Distributions at Varied HV in Xe", 1600, 1000);
	gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	gPad->SetGridx();
 	gPad->SetGridy();
	
	TH1 *firstHist1 = (TH1 *)histListGEM->First();
  if (firstHist1) {
    firstHist1->GetXaxis()->SetTitle("ADC amplitude");
    firstHist1->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist1->SetMaximum(1);
    firstHist1->SetTitle("GEMTRD ADC Distributions in XeCO2");
  }
	
	histListGEM->Draw("same");
  l1->Draw();
	c1->SaveAs("GEMTRD_ADC_Xe_Comparison_v1.png");
  
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Distributions at Varied HV in Xe", 1600, 1000);
  c2->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  
  TH1 *firstHist2 = (TH1 *)histListMMG->First();
  if (firstHist2) {
    firstHist2->GetXaxis()->SetTitle("ADC amplitude");
    firstHist2->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist2->SetMaximum(1);
    firstHist2->SetTitle("MMG1-TRD ADC Distributions in XeCO2");
  }
  
  histListMMG->Draw("same");
  l2->Draw();
  c2->SaveAs("MMG1TRD_ADC_Xe_Comparison_v1.png");
  
  
}
