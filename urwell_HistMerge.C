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
	
	//TString rootFiles[] = {"Run_006247_Output.root", "Run_006245_Output.root", "Run_006244_Output.root","Run_006209_Output.root","Run_006246_Output.root"}; //Varied TF
	//TString rootFiles[] = {"Run_006253_Output.root", "Run_006251_Output.root", "Run_006248_Output.root","Run_006249_Output.root"}; //Varied rWELL V (IF)
  //TString rootFiles[] = {"Run_006214_Output.root", "Run_006212_Output.root", "Run_006211_Output.root","Run_006209_Output.root","Run_006213_Output.root","Run_006215_Output.root","Run_006216_Output.root"}; //Varied DF
  TString rootFiles[] = {"Run_006243_Output.root", "Run_006218_Output.root", "Run_006217_Output.root","Run_006209_Output.root","Run_006250_Output.root"}; //Varied GEM dV
  
  
	TList *histList = new TList;
	TString name1 = "urw_f125_el_x";
	//TString name2 = "urw_f125_pi";
	int colorList[] = {94,51,209,6,7,1,4,2};
	//TString legendList[] = {"1.925 kV/cm","1.95 kV/cm","1.975 kV/cm","1.2 kV/cm","2.025 kV/cm"}; //Varied TF
  //TString legendList[] = {"485 V","490 V","495 V","500 V"}; //Varied rWELL V (IF)
  //TString legendList[] = {"1.365 kV/cm","1.372 kV/cm","1.378 kV/cm","1.385 kV/cm","1.391 kV/cm","1.398 kV/cm","1.404 kV/cm"}; //Varied DF
  TString legendList[] = {"370 V","375 V","380 V","385 V","390 V"}; //Varied GEM dV
  
	TLegend *l1 = new TLegend(0.75, 0.6, 0.9, 0.9);
	
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
	
	//TCanvas *c1 = new TCanvas("c1","uRWell X ADC Distributions, Varied TF", 1200, 800);
	//TCanvas *c1 = new TCanvas("c1","uRWell X ADC Distributions, Varied IF", 1200, 800);
  //TCanvas *c1 = new TCanvas("c1","uRWell X ADC Distributions, Varied DF", 1200, 800);
  TCanvas *c1 = new TCanvas("c1","uRWell X ADC Distributions, Varied GEM dV", 1200, 800);
  
  gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	gPad->SetGridx();
 	gPad->SetGridy();
	
	  TH1 *firstHist = (TH1 *)histList->First();
    if (firstHist) {
        firstHist->GetXaxis()->SetTitle("ADC amplitude (X Plane)");
        firstHist->GetYaxis()->SetTitle("Counts / numEntries");
        //firstHist->SetTitle("uRWell-TRD in ArCO2, 1.385kV/cm DF, 385V GEM dV, 490V WELL"); //Varied TF
        //firstHist->SetTitle("uRWell-TRD in ArCO2, 1.361kV/cm DF, 375V GEM dV, 1.95kV/cm TF"); //Varied rWELL V (IF)
        //firstHist->SetTitle("uRWell-TRD in ArCO2, 2kV/cm TF, 385V GEM dV, 490V WELL"); //Varied DF
        firstHist->SetTitle("uRWell-TRD in ArCO2, 2kV/cm TF, 1.385kV/cm DF, 490V WELL"); //Varied GEM dV
    }
	
	  histList->Draw("same");
    //l1->SetHeader("Transfer Field","C"); //Varied TF
    //l1->SetHeader("rWell Voltage","C"); //Varied rWELL V (IF)
    //l1->SetHeader("Drift Field","C"); //Varied DF
    l1->SetHeader("GEM #Delta V","C"); //Varied GEM dV
    
    l1->Draw();
		//c1->SaveAs("urw_ADC_TF_Comparison_v1.png"); //Varied TF
		//c1->SaveAs("urw_ADC_IF_Comparison_v1.png"); //Varied rWELL V (IF)
    //c1->SaveAs("urw_ADC_DF_Comparison_v1.png"); //Varied DF
    c1->SaveAs("urw_ADC_GEMdV_Comparison_v1.png"); //Varied GEM dV
    
}
