#include <TCanvas.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH1.h>
#include <TFile.h>
#include <TList.h>
#include <TString.h>
#include <iostream>
#include <TLegend.h>

void rejectionFactors() {
	
	TString rootFiles[] = {"mlp_run005268_333717Entries.root", "mlp_run005264_1282180Entries.root", "mlp_run005278_1602819Entries.root", "mlp_run005284_2012810Entries.root", "mlp_run005306_559615Entries.root"};
	TString mmgrootFiles[] = {"mlp_mmg_run005268_333717Entries.root", "mlp_mmg_run005264_1282180Entries.root", "mlp_mmg_run005278_1602819Entries.root", "mlp_mmg_run005284_2012810Entries.root", "mlp_mmg_run005306_559615Entries.root"};
  TList *gemList = new TList;
  TList *mmgList = new TList;
  int colorList[] = {1,94,51,209,4};
	TString legendList[] = {"No Rad","15cm Fleece","23cm Fleece","23cm Fleece","15cm Foil"};
	TString legendList2[] = {"No Rad","15cm Fleece","23cm Fleece","23cm Fleece","21cm Foil"};
	TLegend *l1 = new TLegend(0.75, 0.65, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.75, 0.65, 0.9, 0.9);
	int ngemList=0, nmmgList=0;
  
  for (int i=0; i<sizeof(rootFiles)/sizeof(rootFiles[0]); i++) {
		const TString& rootFile = rootFiles[i];
		TFile *file = TFile::Open(rootFile, "READ");
		if (!file || file->IsZombie()) {
      std::cerr << "Error: Could not open file " << rootFile << std::endl;
      continue;
    }
		
		TObject *obj1 = file->Get("hrejection_errors");
		if (obj1 && obj1->InheritsFrom("TH1")) {
      TH1 *gem_rej = (TH1*)obj1;
      gem_rej->SetLineColor(colorList[i]);
      gem_rej->SetLineWidth(2);
      gem_rej->SetMarkerStyle(21);
      gem_rej->SetMarkerColor(colorList[i]);
      gem_rej->SetDirectory(0);
      gemList->Add(gem_rej);
      ngemList++;
      l1->AddEntry(gem_rej, legendList[i], "l");
    } else {
      std::cerr << "Error: Object 'hrejection_errors' in " << rootFile << " is not a TH1 histogram or is missing." << std::endl;
    }
		
		file->Close();
	}
	
	for (int i=0; i<sizeof(mmgrootFiles)/sizeof(mmgrootFiles[0]); i++) {
		const TString& mmgrootFile = mmgrootFiles[i];
		TFile *file = TFile::Open(mmgrootFile, "READ");
		if (!file || file->IsZombie()) {
      std::cerr << "Error: Could not open file " << mmgrootFile << std::endl;
      continue;
    }
		
		TObject *obj2 = file->Get("hrejection_errors");
		if (obj2 && obj2->InheritsFrom("TH1")) {
      TH1 *mmg_rej = (TH1*)obj2;
      mmg_rej->SetLineColor(colorList[i]);
		  mmg_rej->SetLineWidth(2);
		  //mmg_rej->SetLineStyle(3);
		  mmg_rej->SetMarkerColor(colorList[i]);
 	    mmg_rej->SetMarkerStyle(47);
 	    mmg_rej->SetMarkerSize(2);
 	    mmg_rej->SetDirectory(0);
		  mmgList->Add(mmg_rej);
		  nmmgList++;
		  l2->AddEntry(mmg_rej, legendList2[i], "l");
		} else {
      std::cerr << "Error: Object 'hrejection_errors' in " << mmgrootFile << " is not a TH1 histogram or is missing." << std::endl;
    }
		
		file->Close();
	}
	
	TCanvas *c1 = new TCanvas("c1","Rejection Factor Comparison", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->cd();
 	gPad->SetGridy();
	TH1 *firstHist = (TH1 *)gemList->First();
  if (firstHist) {
    firstHist->GetXaxis()->SetTitle("Electron Efficiency [%]");
    firstHist->GetYaxis()->SetTitle("Rejection Factor");
    firstHist->GetYaxis()->SetRangeUser(0., 24.);
    firstHist->SetTitle("Pion Rejection in XeCO2 90:10");
  }
	gemList->Draw("same");
	mmgList->Draw("same");
	l1->SetHeader("Radiator Material", "C");
  l1->Draw();
	c1->SaveAs("rej_comparison_v2.png");
	
	TCanvas *c2 = new TCanvas("c2","GEM Rejection Factor Comparison", 1200, 800);
	gStyle->SetOptStat(00000);
	c2->cd();
 	gPad->SetGridy();
	TH1 *firstHist2 = (TH1 *)gemList->First();
  if (firstHist2) {
    firstHist2->GetXaxis()->SetTitle("Electron Efficiency [%]");
    firstHist2->GetYaxis()->SetTitle("Rejection Factor");
    firstHist2->GetYaxis()->SetRangeUser(0., 24.);
    firstHist2->SetTitle("GEM-TRD Pion Rejection in XeCO2 90:10");
  }
	gemList->Draw("same");
	l1->SetHeader("Radiator Material", "C");
  l1->Draw();
	c2->SaveAs("rej_comparison_gem_v2.png");
	
	TCanvas *c3 = new TCanvas("c3","MMG Rejection Factor Comparison", 1200, 800);
	gStyle->SetOptStat(00000);
	c3->cd();
 	gPad->SetGridy();
	TH1 *firstHist3 = (TH1 *)mmgList->First();
  if (firstHist3) {
    firstHist3->GetXaxis()->SetTitle("Electron Efficiency [%]");
    firstHist3->GetYaxis()->SetTitle("Rejection Factor");
    firstHist3->GetYaxis()->SetRangeUser(0., 24.);
    firstHist3->SetTitle("MMG1-TRD Pion Rejection in XeCO2 90:10");
  }
	mmgList->Draw("same");
	l2->SetHeader("Radiator Material", "C");
  l2->Draw();
	c3->SaveAs("rej_comparison_mmg_v2.png");
	
}
