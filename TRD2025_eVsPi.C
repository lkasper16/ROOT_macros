#include <TCanvas.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH1.h>
#include <TFile.h>
#include <TList.h>
#include <TString.h>
#include <iostream>
#include <TLegend.h>

void TRD2025_eVsPi() {

  	TList *histList = new TList;
	int nList=0;
  	
	// --- SET FILE NAME ---
	TFile *file = TFile::Open("hd_root_131100_3mil_TRDTrack.root");
	//TFile *file = TFile::Open("hd_root_1073TRDTrack.root");
	if (!file || file->IsZombie()) {
      	std::cerr << "Error: Could not open file" << std::endl;
    }
	
	TCanvas *c1 = new TCanvas("c1",file->GetName(),1400,1200);
    c1->Divide(2,1);
	gStyle->SetOptStat(0);
    c1->GetPad(1)->SetLeftMargin(0.15);
    c1->GetPad(2)->SetLeftMargin(0.15);
	TLegend *l1 = new TLegend(0.6, 0.78, 0.9, 0.9);
    TLegend *l2 = new TLegend(0.6, 0.78, 0.9, 0.9);
	
	//--X
	
	TObject *obj1 = file->Get("TRDTrack/Electron/ProjectionXHitvsTime_el");
	if (obj1 && obj1->InheritsFrom("TH2")) {
    	TH2 *el_2dx = (TH2*)obj1;
		el_2dx->SetDirectory(0);
		histList->Add(el_2dx);
		nList++;
    } else {
      	std::cerr << "Error: Object 'TRDTrack/Electron/ProjectionXHitvsTime_el' is not a TH2 histogram or is missing." << std::endl;
    }
	
	TObject *obj2 = file->Get("TRDTrack/Electron/ProjectionXHitvsTime_QW_el");
    if (obj2 && obj2->InheritsFrom("TH2")) {
        TH2 *el_q_2dx = (TH2*)obj2;
		el_q_2dx->SetDirectory(0);
		histList->Add(el_q_2dx);
		nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Electron/ProjectionXHitvsTime_QW_el' is not a TH2 histogram or is missing." << std::endl;
    }
	
	TObject *obj3 = file->Get("TRDTrack/Pion/ProjectionXHitvsTime_pi");
    if (obj3 && obj3->InheritsFrom("TH2")) {
        TH2 *pi_2dx = (TH2*)obj3;
		pi_2dx->SetDirectory(0);
		histList->Add(pi_2dx);
		nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Pion/ProjectionXHitvsTime_pi' is not a TH2 histogram or is missing." << std::endl;
    }
	
	TObject *obj4 = file->Get("TRDTrack/Pion/ProjectionXHitvsTime_QW_pi");
    if (obj4 && obj4->InheritsFrom("TH2")) {
        TH2 *pi_q_2dx = (TH2*)obj4;
		pi_q_2dx->SetDirectory(0);
		histList->Add(pi_q_2dx);
		nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Pion/ProjectionXHitvsTime_QW_pi' is not a TH2 histogram or is missing." << std::endl;
    }
	
	//--Y
	
	TObject *obj5 = file->Get("TRDTrack/Electron/ProjectionYHitvsTime_el");
    if (obj5 && obj5->InheritsFrom("TH2")) {
        TH2 *el_2dy = (TH2*)obj5;
        el_2dy->SetDirectory(0);
        histList->Add(el_2dy);
        nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Electron/ProjectionYHitvsTime_el' is not a TH2 histogram or is missing." << std::endl;
    }
	
	TObject *obj6 = file->Get("TRDTrack/Electron/ProjectionYHitvsTime_QW_el");
    if (obj6 && obj6->InheritsFrom("TH2")) {
        TH2 *el_q_2dy = (TH2*)obj6;
        el_q_2dy->SetDirectory(0);
        histList->Add(el_q_2dy);
        nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Electron/ProjectionYHitvsTime_QW_el' is not a TH2 histogram or is missing." << std::endl;
    }
	
    TObject *obj7 = file->Get("TRDTrack/Pion/ProjectionYHitvsTime_pi");
    if (obj7 && obj7->InheritsFrom("TH2")) {
        TH2 *pi_2dy = (TH2*)obj7;
        pi_2dy->SetDirectory(0);
        histList->Add(pi_2dy);
        nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Pion/ProjectionYHitvsTime_pi' is not a TH2 histogram or is missing." << std::endl;
    }
	
    TObject *obj8 = file->Get("TRDTrack/Pion/ProjectionYHitvsTime_QW_pi");
    if (obj8 && obj8->InheritsFrom("TH2")) {
        TH2 *pi_q_2dy = (TH2*)obj8;
        pi_q_2dy->SetDirectory(0);
        histList->Add(pi_q_2dy);
        nList++;
    } else {
        std::cerr << "Error: Object 'TRDTrack/Pion/ProjectionYHitvsTime_QW_pi' is not a TH2 histogram or is missing." << std::endl;
    }
	
	file->Close();

	TH2 *el_2dx = (TH2 *)histList->FindObject("ProjectionXHitvsTime_el");
	TH2 *pi_2dx = (TH2 *)histList->FindObject("ProjectionXHitvsTime_pi");
	TH2 *el_q_2dx = (TH2 *)histList->FindObject("ProjectionXHitvsTime_QW_el");
    TH2 *pi_q_2dx = (TH2 *)histList->FindObject("ProjectionXHitvsTime_QW_pi");
	TH2 *el_2dy = (TH2 *)histList->FindObject("ProjectionYHitvsTime_el");
    TH2 *pi_2dy = (TH2 *)histList->FindObject("ProjectionYHitvsTime_pi");
    TH2 *el_q_2dy = (TH2 *)histList->FindObject("ProjectionYHitvsTime_QW_el");
    TH2 *pi_q_2dy = (TH2 *)histList->FindObject("ProjectionYHitvsTime_QW_pi");
	
	c1->cd(1);
	if (el_2dx && pi_2dx && el_2dy && pi_2dy) {
		
		auto *el_projx = el_2dx->ProjectionY("el_projx",314,714)->Rebin(10);
		auto *pi_projx = pi_2dx->ProjectionY("pi_projx",314,714)->Rebin(10);
		
		el_projx->SetLineWidth(2);
    	el_projx->SetMarkerStyle(7);
    	el_projx->Divide(pi_projx);
	    el_projx->GetYaxis()->SetTitle("Electron (Point_Hits) / Pion (Point_Hits)");
		el_projx->SetTitle("Electron / Pion Drift Response");
		el_projx->SetMaximum(.75);
		el_projx->Draw();
		
		auto *el_projy = el_2dy->ProjectionY("el_projy",130,380)->Rebin(8);
        auto *pi_projy = pi_2dy->ProjectionY("pi_projy",130,380)->Rebin(8);

        el_projy->SetLineWidth(2);
		el_projy->SetLineColor(2);
        el_projy->SetMarkerStyle(7);
        el_projy->SetMarkerColor(2);
        el_projy->Divide(pi_projy);
        el_projy->Draw("same");
		l1->AddEntry(el_projx, "X Plane Proj.", "lp");
		l1->AddEntry(el_projy, "Y Plane Proj.", "lp");
		l1->Draw();
		
    } else {
		std::cerr << "Error: Cannot divide unweighted histos!" << std::endl;
	}
	
	c1->cd(2);
	if (el_q_2dx && pi_q_2dx && el_q_2dy && pi_q_2dy) {
		
        auto *el_q_projx = el_q_2dx->ProjectionY("el_q_projx",314,714)->Rebin(10);
        auto *pi_q_projx = pi_q_2dx->ProjectionY("pi_q_projx",314,714)->Rebin(10);
		
        el_q_projx->SetLineWidth(2);
        el_q_projx->SetMarkerStyle(7);
        el_q_projx->Divide(pi_q_projx);
		el_q_projx->GetYaxis()->SetTitle("Electron (Point_Hits) / Pion (Point_Hits)");
        el_q_projx->SetTitle("Electron / Pion Drift Response (q-Weighted)");
		el_q_projx->SetMaximum(.75);
		el_q_projx->Draw();
		
		auto *el_q_projy = el_q_2dy->ProjectionY("el_q_projy",130,380)->Rebin(8);
        auto *pi_q_projy = pi_q_2dy->ProjectionY("pi_q_projy",130,380)->Rebin(8);

        el_q_projy->SetLineWidth(2);
        el_q_projy->SetLineColor(2);
		el_q_projy->SetMarkerStyle(7);
        el_q_projy->SetMarkerColor(2);
        el_q_projy->Divide(pi_q_projy);
        el_q_projy->Draw("same");
		
		l2->AddEntry(el_q_projx, "X Plane Proj.", "lp");
        l2->AddEntry(el_q_projy, "Y Plane Proj.", "lp");
        l2->Draw();
		
    } else {
		std::cerr << "Error: Cannot divide weighted histos!" << std::endl;
	}
	
	c1->SaveAs("eVsPi_TRD2025.png");
	
}
