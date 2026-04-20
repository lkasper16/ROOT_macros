#include <vector>
#include <fstream>
#include <iostream>
#include <string>
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

void maxLateAmpCompare(){
	
	TString rootFiles[] = {"RootOutput/ps25/Run_006297_Output.root", "RootOutput/ps25/Run_006304_Output.root", "RootOutput/ps25/Run_006384_Output.root", "RootOutput/ps25/Run_006388_Output.root"};
	TList *gemList = new TList;
  TList *mmgList = new TList;
  TList *urwList = new TList;
  
	TString name1 = "f125_el_max_late";
	TString name2 = "mmg1_f125_el_max_late";
  TString name3 = "urw_f125_el_xmax_late";
	int colorList[] = {1,94,51,209,4};
	TString legendList[] = {"Cu, Low Gain","Cu, High Gain","Al, Low Gain","Al, High Gain"};
  TString urwLegendList[] = {"Low TF, Low Gain","Low TF, High Gain","High TF, Low Gain","High TF, High Gain"};
	TLegend *l1 = new TLegend(0.70, 0.7, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.70, 0.7, 0.9, 0.9);
  TLegend *l3 = new TLegend(0.65, 0.7, 0.9, 0.9);
  
	for (int i=0; i<sizeof(rootFiles)/sizeof(rootFiles[0]); i++) {
		const TString& rootFile = rootFiles[i];
		TFile *file = TFile::Open(rootFile, "READ");
		TList *HistDQM = (TList *)file->Get("HistDQM");
		TIter next(HistDQM);
		
		while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
			TString histName = readObject->GetName();
			if (histName == name1) {
				readObject->SetLineColor(colorList[i]);
				readObject->SetMarkerColor(colorList[i]);
        readObject->SetLineWidth(2);
				double scaleFactor = 1./readObject->GetEntries();
				readObject->Scale(scaleFactor);
        readObject->RebinX(3);
				gemList->Add(readObject);
				l1->AddEntry(readObject, legendList[i], "lp");
			} else if (histName == name2) {
        readObject->SetMarkerColor(colorList[i]);
        readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
        double scaleFactor = 1./readObject->GetEntries();
        readObject->Scale(scaleFactor);
        readObject->RebinX(3);
        l2->AddEntry(readObject, legendList[i], "lp");
        mmgList->Add(readObject);
			} else if (histName == name3) {
        readObject->SetMarkerColor(colorList[i]);
        readObject->SetLineColor(colorList[i]);
        readObject->SetLineWidth(2);
        double scaleFactor = 1./readObject->GetEntries();
        readObject->Scale(scaleFactor);
        readObject->RebinX(3);
        l3->AddEntry(readObject, urwLegendList[i], "lp");
        urwList->Add(readObject);
      }
		}
		file->Close();
	}
	
	TCanvas *c1 = new TCanvas("c1","GEM-TRD Max ADC in Late Time", 1300, 1000);
	gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetGridx();
 	gPad->SetGridy();
	TH1 *firstHist = (TH1 *)gemList->First();
  if (firstHist) {
    //firstHist->GetXaxis()->SetTitle("ADC amplitude");
    //firstHist->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist->SetTitle("GEM-TRD Max ADC Values in Late Time in Xe:CO2 90:10");
  }
	gemList->Draw("same");
  l1->Draw();
	c1->SaveAs("gem_lateMax_Comparison_v1.png");
  
  TCanvas *c2 = new TCanvas("c2","MMG-TRD Max ADC in Late Time", 1300, 1000);
  gStyle->SetOptStat(00000);
  c2->cd();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstMMGHist = (TH1 *)mmgList->First();
  if (firstMMGHist) {
    firstMMGHist->SetTitle("MMG-TRD Max ADC Values in Late Time in Xe:CO2 90:10");
  }
  mmgList->Draw("same");
  l2->Draw();
  c2->SaveAs("mmg_lateMax_Comparison_v1.png");
  
  TCanvas *c3 = new TCanvas("c3","uRWELL-TRD Max ADC in Late Time", 1300, 1000);
  gStyle->SetOptStat(00000);
  c3->cd();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstURWHist = (TH1 *)urwList->First();
  if (firstURWHist) {
    firstURWHist->SetTitle("uRWELL-TRD Max ADC Values in Late Time in Xe:CO2 90:10");
    firstURWHist->GetXaxis()->SetRangeUser(0.,2700.);
  }
  urwList->Draw("same");
  l3->Draw();
  c3->SaveAs("urw_lateMax_Comparison_v1.png");
}
