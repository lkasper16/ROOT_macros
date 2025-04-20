#include <TCanvas.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH1.h>
#include <TFile.h>
#include <TList.h>
#include <TString.h>
#include <iostream>
#include <TLegend.h>

void TRD2025_efficiency() {

  	
	// --- SET FILE NAME ---
	TFile *file = TFile::Open("hd_root_131100_3mil_TRDTrack.root");
	//TFile *file = TFile::Open("hd_root_1073TRDTrack.root");
	if (!file || file->IsZombie()) {
      	std::cerr << "Error: Could not open file" << std::endl;
    }
	
	TList *xList = new TList;
    TList *yList = new TList;
    TLegend *l1 = new TLegend(0.55, 0.65, 0.9, 0.9);
    int nxList=0, nyList=0;
	TCanvas *c1 = new TCanvas("c1",file->GetName(),1600,1200);
    c1->Divide(2,1);
    c1->GetPad(1)->SetLeftMargin(0.15);
    c1->GetPad(2)->SetLeftMargin(0.15);
	
	TObject *objx_p = file->Get("TRDTrack/ExtrapsX");
	if (objx_p && objx_p->InheritsFrom("TH1")) {
    	TH1 *xPass = (TH1*)objx_p;
		xPass->SetDirectory(0);
		xList->Add(xPass);
		nxList++;
    } else {
      	std::cerr << "Error: Object 'TRDTrack/ExtrapsX' is not a TH1 histogram or is missing." << std::endl;
    }
	
	TObject *objy_p = file->Get("TRDTrack/ExtrapsY");
    if (objy_p && objy_p->InheritsFrom("TH1")) {
        TH1 *yPass = (TH1*)objy_p;
		yPass->SetDirectory(0);
		yList->Add(yPass);
		nyList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/ExtrapsY' is not a TH1 histogram or is missing." << std::endl;
    }
	
	TObject *objx_s = file->Get("TRDTrack/seenPointsSingleX");
    if (objx_s && objx_s->InheritsFrom("TH1")) {
        TH1 *xSeen = (TH1*)objx_s;
		xSeen->SetDirectory(0);
		xList->Add(xSeen);
		nxList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/seenPointsSingleX' is not a TH1 histogram or is missing." << std::endl;
    }
	
	TObject *objy_s = file->Get("TRDTrack/seenPointsSingleY");
    if (objy_s && objy_s->InheritsFrom("TH1")) {
        TH1 *ySeen = (TH1*)objy_s;
		ySeen->SetDirectory(0);
		yList->Add(ySeen);
		nyList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/seenPointsSingleY' is not a TH1 histogram or is missing." << std::endl;
    }
	
	file->Close();

	c1->cd(1);
	TH1 *px = (TH1 *)xList->FindObject("ExtrapsX");
	TH1 *sx = (TH1 *)xList->FindObject("seenPointsSingleX");
	if (px && sx) {
		for (int i=0; i<=sx->GetNbinsX(); i++) {
            if (sx->GetBinContent(i) > px->GetBinContent(i)) {
                sx->SetBinContent(i,0);
                px->SetBinContent(i,0);
            }
        }
		
		TGraphAsymmErrors *EFFX = new TGraphAsymmErrors();
		EFFX->Divide(sx,px,"cl=0.683 b(1,1) mode");
		EFFX->SetMarkerStyle(7);
		EFFX->GetXaxis()->SetTitle("Position (in GlueX Coordinates) [cm]");
        EFFX->GetYaxis()->SetTitle("(Track Extrap. Seen) / (Track Extrap. Expected)");
        EFFX->SetTitle("GEMTRD X Plane Extrapolation Efficiency Estimate");
        EFFX->Draw("ap");
		
    } else {
		std::cerr << "Error: Cannot divide X plane histos!" << std::endl;
	}
	
	c1->cd(2);
    TH1 *py = (TH1 *)yList->FindObject("ExtrapsY");
    TH1 *sy = (TH1 *)yList->FindObject("seenPointsSingleY");
    if (py && sy) {
		for (int i=0; i<=sy->GetNbinsX(); i++) {
			if (sy->GetBinContent(i) > py->GetBinContent(i)) {
				sy->SetBinContent(i,0);
				py->SetBinContent(i,0);
			}
		}
		
		TGraphAsymmErrors *EFFY = new TGraphAsymmErrors();
		EFFY->Divide(sy,py,"cl=0.683 b(1,1) mode");
        EFFY->SetMarkerStyle(7);
        EFFY->GetXaxis()->SetTitle("Position (in GlueX Coordinates) [cm]");
        EFFY->GetYaxis()->SetTitle("(Track Extrap. Seen) / (Track Extrap. Expected)");
        EFFY->SetTitle("GEMTRD Y Plane Extrapolation Efficiency Estimate; Position (in GlueX Coordinates) [cm]");
        EFFY->Draw("ap");
		
    } else {
		std::cerr << "Error: Cannot divide Y plane histos!" << std::endl;
	}
	
	c1->SaveAs("efficiencyCheck.png");
	
}
