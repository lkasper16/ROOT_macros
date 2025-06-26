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

void urwell_HistMerge(){
	
	TString rootFiles1[] = {"Run_006247_Output.root", "Run_006245_Output.root", "Run_006244_Output.root","Run_006261_Output.root","Run_006246_Output.root"}; //Varied TF
	TString rootFiles2[] = {"Run_006253_Output.root", "Run_006251_Output.root", "Run_006248_Output.root","Run_006249_Output.root"}; //Varied rWELL V (IF)
  TString rootFiles3[] = {"Run_006214_Output.root", "Run_006212_Output.root", "Run_006211_Output.root","Run_006261_Output.root","Run_006213_Output.root","Run_006215_Output.root","Run_006216_Output.root"}; //Varied DF
  TString rootFiles4[] = {"Run_006243_Output.root", "Run_006218_Output.root", "Run_006217_Output.root","Run_006261_Output.root","Run_006250_Output.root"}; //Varied GEM dV
  
	TList *histList1 = new TList;
  TList *histList2 = new TList;
  TList *histList3 = new TList;
  TList *histList4 = new TList;
  
	TString name1 = "urw_f125_el_x";
	int colorList[] = {94,2,209,6,7,1,4,51};
	TString legendList1[] = {"1.925 kV/cm","1.95 kV/cm","1.975 kV/cm","2 kV/cm","2.025 kV/cm"}; //Varied TF
  TString legendList2[] = {"485 V","490 V","495 V","500 V"}; //Varied rWELL V (IF)
  TString legendList3[] = {"1.365 kV/cm","1.372 kV/cm","1.378 kV/cm","1.385 kV/cm","1.391 kV/cm","1.398 kV/cm","1.404 kV/cm"}; //Varied DF
  TString legendList4[] = {"370 V","375 V","380 V","385 V","390 V"}; //Varied GEM dV
  
	TLegend *l1 = new TLegend(0.75, 0.6, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.75, 0.6, 0.9, 0.9);
  TLegend *l3 = new TLegend(0.75, 0.6, 0.9, 0.9);
  TLegend *l4 = new TLegend(0.75, 0.6, 0.9, 0.9);
  
  //Varied TF
	for (int i=0; i<sizeof(rootFiles1)/sizeof(rootFiles1[0]); i++) {
		const TString& rootFile = rootFiles1[i];
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
				histList1->Add(readObject);
				l1->AddEntry(readObject, legendList1[i], "l");
			}
		}
		file->Close();
	}
  
  //Varied rWELL V (IF)
  for (int i=0; i<sizeof(rootFiles2)/sizeof(rootFiles2[0]); i++) {
    const TString& rootFile = rootFiles2[i];
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
        histList2->Add(readObject);
        l2->AddEntry(readObject, legendList2[i], "l");
      }
    }
    file->Close();
  }
  
  //Varied DF
  for (int i=0; i<sizeof(rootFiles3)/sizeof(rootFiles3[0]); i++) {
    const TString& rootFile = rootFiles3[i];
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
        histList3->Add(readObject);
        l3->AddEntry(readObject, legendList3[i], "l");
      }
    }
    file->Close();
  }
  
  //Varied GEM dV
  for (int i=0; i<sizeof(rootFiles4)/sizeof(rootFiles4[0]); i++) {
    const TString& rootFile = rootFiles4[i];
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
        histList4->Add(readObject);
        l4->AddEntry(readObject, legendList4[i], "l");
      }
    }
    file->Close();
  }
	
	TCanvas *c1 = new TCanvas("c1","uRWell X ADC Distributions, Varied TF", 1600, 1000);
	TCanvas *c2 = new TCanvas("c2","uRWell X ADC Distributions, Varied IF", 1600, 1000);
  TCanvas *c3 = new TCanvas("c3","uRWell X ADC Distributions, Varied DF", 1600, 1000);
  TCanvas *c4 = new TCanvas("c4","uRWell X ADC Distributions, Varied GEM dV", 1600, 1000);
  
  gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	gPad->SetGridx();
 	gPad->SetGridy();
	
	TH1 *firstHist1 = (TH1 *)histList1->First();
  if (firstHist1) {
    firstHist1->GetXaxis()->SetTitle("ADC amplitude (X Plane)");
    firstHist1->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist1->SetTitle("uRWell-TRD in ArCO2, 1.385kV/cm DF, 385V GEM dV, 490V WELL"); //Varied TF
  }
	histList1->Draw("same");
  l1->SetHeader("Transfer Field","C"); //Varied TF
  l1->Draw();
	c1->SaveAs("urw_ADC_TF_Comparison_v1.png"); //Varied TF
  
  c2->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstHist2 = (TH1 *)histList2->First();
  if (firstHist2) {
    firstHist2->GetXaxis()->SetTitle("ADC amplitude (X Plane)");
    firstHist2->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist2->SetTitle("uRWell-TRD in ArCO2, 1.361kV/cm DF, 375V GEM dV, 1.95kV/cm TF"); //Varied rWELL V (IF)
  }
  histList2->Draw("same");
  l2->SetHeader("rWell Voltage","C"); //Varied rWELL V (IF)
  l2->Draw();
  c2->SaveAs("urw_ADC_IF_Comparison_v1.png"); //Varied rWELL V (IF)
  
  c3->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstHist3 = (TH1 *)histList3->First();
  if (firstHist3) {
    firstHist3->GetXaxis()->SetTitle("ADC amplitude (X Plane)");
    firstHist3->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist3->SetTitle("uRWell-TRD in ArCO2, 2kV/cm TF, 385V GEM dV, 490V WELL"); //Varied DF
  }
  histList3->Draw("same");
  l3->SetHeader("Drift Field","C"); //Varied DF
  l3->Draw();
  c3->SaveAs("urw_ADC_DF_Comparison_v1.png"); //Varied DF
  
  c4->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstHist4 = (TH1 *)histList4->First();
  if (firstHist4) {
    firstHist4->GetXaxis()->SetTitle("ADC amplitude (X Plane)");
    firstHist4->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist4->SetTitle("uRWell-TRD in ArCO2, 2kV/cm TF, 1.385kV/cm DF, 490V WELL"); //Varied GEM dV
  }
  histList4->Draw("same");
  l4->SetHeader("GEM #Delta V","C"); //Varied GEM dV
  l4->Draw();
  c4->SaveAs("urw_ADC_GEMdV_Comparison_v1.png"); //Varied GEM dV
  
}
