#include <iostream>
#include <fstream>
#include <string>
//#include <TTree.h>
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
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TLine.h>
#include <TBox.h>
#include <TObject.h>
#include <TLegend.h>
#include <TProfile.h>

using namespace std;

void plot_trk_quality(){
  /*
  
    TFile *fin = new TFile("/Users/souravtarafdar/sPHENIX/G4sim/svtx_pix_maps_pion/g4svtx_eval_50pionevt.root");
  
    TTree *ntp_track = (TTree*)fin->Get("ntp_track");
  */

  TChain ch("tracks");
  
  
  ch.Add("/sphenix/user/isibf5y/ECCE_defmac/macros/detectors/EICDetector/barrel_mRwell_pim/midrap_mRWell_pim_eval_*.root"); // 5 pi- per event , stupid , kept the same file name as for MMG but indeed its for mRwell as depicted in the mother folder !
  
  
  
  
 

  Int_t event;
  Int_t         trackID;
  Float_t         px;
  Float_t         py;
  Float_t         pz;
  Int_t         charge;
  
  Float_t         dca2d;
  //Float_t         dca2dsigma;
  Float_t         pcax;
  Float_t         pcay;
  Float_t         pcaz;
  
  Int_t         gtrackID;
  Float_t         gflavor;
  
  Float_t         gpx;
  Float_t         gpy;
  Float_t         gpz;
  Float_t         gvx;
  Float_t         gvy;
  Float_t         gvz;
  
  

   
  
  ch.SetBranchAddress("event", &event);
  ch.SetBranchAddress("trackID", &trackID);
  ch.SetBranchAddress("px", &px);
  ch.SetBranchAddress("py", &py);
  ch.SetBranchAddress("pz", &pz);
  ch.SetBranchAddress("charge", &charge);
  ch.SetBranchAddress("dca2d", &dca2d); 
  ch.SetBranchAddress("pcax", &pcax);
  ch.SetBranchAddress("pcay", &pcay);
  ch.SetBranchAddress("pcaz", &pcaz);

  ch.SetBranchAddress("gpx", &gpx);
  ch.SetBranchAddress("gpy", &gpy);
  ch.SetBranchAddress("gpz", &gpz);
  
 
 
   
  
  Float_t pt_pi, pt_tr_pi, pur_pi, pt_res_pi, dptopt_pi, true_pt, dpt; // pion tracks
  Float_t p_pi, p_tr_pi, p_res_pi, dpop_pi, true_p, dp ; 
  Float_t rap_tr, rap_reco;
  
  TH1F *h_event = new TH1F("h_event","", 2001, -0.5,2000.5 );
  
  

  //Embedded pion tracks
  
  // For mid rapidity
  TH1F *h_rap_reco = new TH1F("h_rap_reco","h_rap_reco",50, -1.5, 1.5);
  TH1F *h_rap_tr = new TH1F("h_rap_tr","h_rap_tr",50, -1.5, 1.5);
  /*
  //For forward and backward rapidity
  TH1F *h_rap_reco = new TH1F("h_rap_reco","h_rap_reco",50, -3.6, 3.6);
  TH1F *h_rap_tr = new TH1F("h_rap_tr","h_rap_tr",50, -3.6, 3.6);
  */
  //pT
  TH1F *h_pt_reco = new TH1F("h_pt_reco","h_pt_reco",100, -0.1, 20.0);
  TH1F *h_px_reco = new TH1F("h_px_reco","h_px_reco",100, -20., 20.0);
  TH1F *h_py_reco = new TH1F("h_py_reco","h_py_reco",100, -20, 20.0);
  TH1F *h_pz_reco = new TH1F("h_pz_reco","h_pz_reco",100, -0.1, 20.0);
  
  TH1F *h_ptres_pi = new TH1F("h_ptres_pi"," ", 100, 0.1, 2.1);
  TH2F *h_rpt_tpt_pi = new TH2F("h_rpt_tpt_pi"," ", 120, -0.1,41.9, 120, -0.1, 41.9);
  TH2F *h_ptres_tpt_pi = new TH2F("h_ptres_tpt_pi","pt-reco/pt-true vs pt-true ", 120, -0.1,41.9, 50, 0.9 , 1.09); 
  
  TH2F *h_dptopt_tpt_pi = new TH2F("h_dptopt_tpt_pi", "dpt/pt vs pt ", 120.,-0.1, 41.9, 20,-0.05,0.05);
  TProfile *pr_dptopt_tpt_pi = new TProfile("pr_dptopt_tpt_pi"," ", 200, -0.1, 41.9, -0.05, 0.05);

  TH2F *h_dpt_tpt_pi = new TH2F("h_dpt_tpt_pi", "dpt vs pt ", 120.,-0.1, 41.9, 40,-5.,5.);

  TH2F *h_pt_vs_eta_tr = new TH2F("h_pt_vs_eta_tr", " pT vs eta " , 100, -0.1, 30., 50, -3.6, 3.6);
  TH2F *h_pt_vs_eta_reco = new TH2F("h_pt_vs_eta_reco", " pT vs eta " , 100, -0.1, 30., 50, -3.6, 3.6);
  
  //P
  TH1F *h_p_reco = new TH1F("h_p_reco","h_p_reco",100, -0.1, 20.0);
  TH1F *h_pres_pi = new TH1F("h_pres_pi"," ", 100, 0.1, 2.1);
  TH2F *h_rp_tp_pi = new TH2F("h_rp_tp_pi"," ", 120, -0.1, 20.9, 120, -0.1, 20.9);
  TH2F *h_pres_tp_pi = new TH2F("h_pres_tp_pi","p-reco/p-true vs p-true ", 120, -0.1, 20.9, 50, 0.9 , 1.09); 
  
  TH2F *h_dpop_tp_pi = new TH2F("h_dpop_tp_pi", "dp/p vs p ", 120.,-0.1, 20.9, 20,-0.05,0.05);
  TProfile *pr_dpop_tp_pi = new TProfile("pr_dpop_tp_pi"," ", 200, -0.1, 41.9, -0.05, 0.05);

  TH2F *h_dp_tp_pi = new TH2F("h_dp_tp_pi", "dp vs p ", 120.,-0.1, 20.9, 40,-5.,5.);

  TH2F *h_dca2d_pi = new TH2F("h_dca2d_pi"," ", 120 ,-0.1, 41.9, 50., -0.001, 0.005);
  TProfile *pr_dca2d_pi = new TProfile("pr_dca2d_pi"," ", 120, -0.1, 41.9, -0.001, 0.005); 

  TH2F *h_p_vs_eta_tr = new TH2F("h_p_vs_eta_tr", " p vs eta " , 100, -0.1, 20., 50, -3.6, 3.6);
  TH2F *h_p_vs_eta_reco = new TH2F("h_p_vs_eta_reco", " p vs eta " , 100, -0.1, 30., 50, -3.6, 3.6);
  

  TH1F *h_reco_ptbin[40];
  TH1F *h_true_ptbin[40];
  TH1F *h_reco_pbin[40];
  TH1F *h_true_pbin[40];
  
  for(int k = 0; k < 40; k++) {
    char hname_r[500], htitle_r[500], hname_tr[500], htitle_tr[500];
    char hnamep_r[500], htitlep_r[500], hnamep_tr[500], htitlep_tr[500];

    sprintf(hname_r, "h_reco_ptbin_%d", k);
    sprintf(htitle_r, "%d < pt < %d+1 ", k, k);
    h_reco_ptbin[k]= new TH1F(hname_r, htitle_r, 40, -0.5, 19.5);

    sprintf(hname_tr, "h_true_ptbin_%d", k);
    sprintf(htitle_tr, "%d < pt < %d+1 ", k, k);
    h_true_ptbin[k]= new TH1F(hname_tr, htitle_tr, 40, -0.5, 19.5);

    sprintf(hnamep_r, "h_reco_pbin_%d", k);
    sprintf(htitlep_r, "%d < p < %d+1 ", k, k);
    h_reco_pbin[k]= new TH1F(hnamep_r, htitlep_r, 40, -0.5, 19.5);

    sprintf(hnamep_tr, "h_true_pbin_%d", k);
    sprintf(htitlep_tr, "%d < p < %d+1 ", k, k);
    h_true_pbin[k]= new TH1F(hnamep_tr, htitlep_tr, 40, -0.5, 19.5);
    
  }
  
  pr_dca2d_pi->SetMarkerStyle(20);
  pr_dca2d_pi->SetMarkerColor(1);

  pr_dptopt_tpt_pi->SetMarkerStyle(20);
  pr_dptopt_tpt_pi->SetMarkerColor(1);

  Int_t Nent = ch.GetEntries();
 
  cout << "Nent :" << Nent <<  endl;

  for(int i = 0; i < Nent; i++){
     
    ch.GetEntry(i);

    pt_pi = sqrt(px*px +py*py);
    pt_tr_pi = sqrt(gpx*gpx +gpy*gpy);
    dptopt_pi = (pt_pi-pt_tr_pi)/pt_pi;
    dpt = (pt_pi - pt_tr_pi);
      
    if(pt_tr_pi!=0) pt_res_pi = pt_pi/pt_tr_pi;
    //cout << "pt :" << pt << " pt_tr :" << pt_tr << " pt_res :" << pt_res << endl;

    p_pi = sqrt(px*px +py*py+ pz*pz);
    p_tr_pi = sqrt(gpx*gpx +gpy*gpy+gpz*gpz);
    dpop_pi = (p_pi-p_tr_pi)/p_pi;
    dp = (p_pi - p_tr_pi);

    rap_reco = 0.5*log((p_pi+pz)/(p_pi-pz));
    rap_tr = 0.5*log((p_tr_pi+gpz)/(p_tr_pi-gpz));
    
    h_rap_reco->Fill(rap_reco);
    h_rap_tr->Fill(rap_tr);

    h_pt_vs_eta_tr->Fill(pt_tr_pi, rap_tr);
    h_p_vs_eta_tr->Fill(p_tr_pi, rap_tr);

    h_pt_vs_eta_reco->Fill(pt_pi, rap_reco);
    h_p_vs_eta_reco->Fill(p_pi, rap_reco);
      
    if(p_tr_pi!=0) p_res_pi = p_pi/p_tr_pi;
    h_pz_reco->Fill(pz);
    h_px_reco->Fill(px);
    h_py_reco->Fill(py);
    h_p_reco->Fill(p_pi);
    h_pt_reco->Fill(pt_pi);
    h_ptres_pi->Fill(pt_res_pi);
    h_ptres_tpt_pi->Fill(pt_tr_pi, pt_res_pi);
    h_dptopt_tpt_pi->Fill(pt_tr_pi, dptopt_pi);
    pr_dptopt_tpt_pi->Fill(pt_tr_pi, dptopt_pi);
    h_rpt_tpt_pi->Fill(pt_pi,pt_tr_pi);
    h_dpt_tpt_pi->Fill(pt_pi, dpt); 

    h_pres_pi->Fill(p_res_pi);
    h_pres_tp_pi->Fill(p_tr_pi, p_res_pi);
    h_dpop_tp_pi->Fill(p_tr_pi, dpop_pi);
    pr_dpop_tp_pi->Fill(p_tr_pi, dpop_pi);
    h_rp_tp_pi->Fill(p_pi,p_tr_pi);
    h_dp_tp_pi->Fill(p_pi, dp); 

    h_dca2d_pi->Fill(pt_tr_pi, dca2d);
    pr_dca2d_pi->Fill(pt_tr_pi, dca2d);
     
    for(int m = 0; m < 40; m++){

      Float_t mf = m;
      Float_t trp_min = mf/2.0 - 0.5;
      Float_t trp_max = trp_min + 0.5;
          
      //cout << "true p min :" << trp_min << " true p max :" << trp_max << endl;
      //cout << "mf :" << mf << " true p min :" << trp_min << " true p max :" << trp_max << endl;
      if(p_tr_pi > trp_min && p_tr_pi <= trp_max ){
	//if(fabs(TMath::ATan2(-gpy,-gpx))<0.1) continue;
	h_true_pbin[m]->Fill(p_tr_pi) ;
	//cout << " m :" << m << " tr p cut :" << tr_pcut << " true p :" << true_p << endl;
	if(fabs(p_pi - p_tr_pi ) < (/*0.028*/ 0.05*p_tr_pi) ){ //%p match
	  //if(fabs(TMath::ATan2(-gpy,-gpx))<0.1) continue;
	  h_reco_pbin[m]->Fill(p_tr_pi) ;
	    
	}
	 
      } // p bin selection
      
    } // 1 D p bins
        
  } // end of reco track loop

 
  
  //Calculate track efficiency
  Float_t Ntrue[40], Nreco[40], tr_p[40], eff[40];
  int k = 0;
  for(int i = 0; i < 40; i++){

    Ntrue[k] = h_true_pbin[k] ->GetEntries();
    Nreco[k] = h_reco_pbin[k] ->GetEntries();
    tr_p[k] = h_true_pbin[k]->GetMean();
    if(Ntrue[k]!=0)eff[k] = Nreco[k]/Ntrue[k];
    k++;
  }
 
  TGraph *gr_trk_eff =  new TGraph(k , tr_p, eff);
  gr_trk_eff->SetName("gr_trk_eff");
  gr_trk_eff->SetMarkerStyle(20);
  TCanvas *c1 = new TCanvas("c1","c1");
  c1->cd();
  gr_trk_eff->Draw("AP");
  

  //Finding resolution
  //Resolution in terms of sigma 
  float mean_trpt3[60], meane_trpt3[60], sigma_trpt3[60], sigmae_trpt3[60]; 
  float x_trpt3[60], ex_trpt3[60];

  float mean_trp3[60], meane_trp3[60], sigma_trp3[60], sigmae_trp3[60]; 
  float x_trp3[60], ex_trp3[60];
  
  
  TH1D *h_ptres3_trpt[60];
  TH1D *h_pres3_trp[60];

  for(int k = 0; k < 120; k=k+2) {
    char hname3[500], htitle3[500];
    char hnamep3[500], htitlep3[500];

    sprintf(hname3, "h_ptres3_trpt_%d", k/2);
    sprintf(htitle3, "pt_bin_%d ", k/2);
    h_ptres3_trpt[k/2]= new TH1D(hname3, htitle3, 50, -0.06, 0.06);
    // h_ptres3_trpt[k/2]= new TH1D(hname3, htitle3, 70, 0.5, 3.5);
    
    sprintf(hnamep3, "h_pres3_trp_%d", k/2);
    sprintf(htitlep3, "p_bin_%d ", k/2);
    h_pres3_trp[k/2]= new TH1D(hnamep3, htitlep3, 50, -0.06, 0.06);
    // h_ptres3_trpt[k/2]= new TH1D(hnamep3, htitlep3, 70, 0.5, 3.5);

  }
  
  TF1 *f3 = new TF1("f3","gaus", -0.04, 0.04);
  f3->SetParameters(1.,1.);

  TF1 *fp = new TF1("fp","gaus", -0.04, 0.04);
  fp->SetParameters(1.,1.);
  int n =0 ;
  for(int m = 0 ; m < 120; m = m+2){
    //for(int m = 0 ; m < 120; m = m+4){
    //pT resolution
    h_ptres3_trpt[n] = h_dptopt_tpt_pi->ProjectionY(Form("ptbin%d",m+1), m, m+1);
    //h_ptres3_trpt[n] = h_dpt_tpt_pi->ProjectionY(Form("ptbin%d",m+2), m, m+2);
   
    h_ptres3_trpt[n]->Fit("f3");
    sigma_trpt3[n] = 100.*(f3->GetParameter(2));
    sigmae_trpt3[n] = 100.*(f3->GetParError(2));
    mean_trpt3[n]= f3->GetParameter(1);
    meane_trpt3[n]= f3->GetParError(1);
    
    x_trpt3[n] = h_dptopt_tpt_pi->GetXaxis()->GetBinCenter(m+2);
    ex_trpt3[n] = h_dptopt_tpt_pi->GetXaxis()->GetBinWidth(m+2);
    //x_trpt3[n] = h_dpt_tpt_pi->GetXaxis()->GetBinCenter(m+2);
    
    //cout << "x :" << x_trpt3[n] << " sigma :" << sigma_trpt3[n] << " mean :" << mean_trpt3[n] << endl;
    /*
      if(mean_trpt3[n] !=0 )sigma_trpt3[n] /= mean_trpt3[n];
      if(meane_trpt3[n] !=0 )sigmae_trpt3[n] /= meane_trpt3[n];
    */
    //if(x_trpt3[n] !=0) sigma_trpt3[n] /= x_trpt3[n];

    //p resolution
    h_pres3_trp[n] = h_dpop_tp_pi->ProjectionY(Form("pbin%d",m+1), m, m+1);
    //h_pres3_trp[n] = h_dp_tp_pi->ProjectionY(Form("bin%d",m+2), m, m+2);
   
    h_pres3_trp[n]->Fit("fp");
    sigma_trp3[n] = 100.*(fp->GetParameter(2));
    sigmae_trp3[n] = 100.*(fp->GetParError(2));
    mean_trp3[n]= fp->GetParameter(1);
    meane_trp3[n]= fp->GetParError(1);
    
    x_trp3[n] = h_dpop_tp_pi->GetXaxis()->GetBinCenter(m+2);
    ex_trp3[n] = h_dpop_tp_pi->GetXaxis()->GetBinWidth(m+2);
    
    cout  << "pt res :" << sigma_trpt3[n] << " p res :" << sigma_trp3[n] <<  endl;
    n++;
  }
   
  TGraphErrors *gr_sig_res_pi = new TGraphErrors(n, x_trpt3, sigma_trpt3, ex_trp3, sigmae_trpt3);
  gr_sig_res_pi->SetName("gr_sig_res_pi");
  gr_sig_res_pi->SetMarkerStyle(20);
  gr_sig_res_pi->SetMarkerSize(0.5);
  gr_sig_res_pi->SetMarkerColor(2);

  TGraphErrors *gr_sig_pres_pi = new TGraphErrors(n, x_trp3, sigma_trp3, ex_trp3, sigmae_trp3);
  gr_sig_pres_pi->SetName("gr_sig_pres_pi");
  gr_sig_pres_pi->SetMarkerStyle(20);
  gr_sig_pres_pi->SetMarkerSize(0.5);
  gr_sig_pres_pi->SetMarkerColor(2);

  TF1 *f0_1 = new TF1("f0_1","TMath::Sqrt([0]*[0]+[1]*[1]*x*x)",0,24.5);
  f0_1->SetParameters(1.00, 1.);
  gr_sig_res_pi->Fit("f0_1");
  
  //Finding dca resolution

  float mean_dca[120], meany_tr_dca[120], meane_dca[120], rms_dca[120], rmse_dca[120], mean_tr_dca[120]; 
  float x_dca[120];

  int j5 = 0;
  for(int i = 0; i < 121; i=i+2 ){
   
   
    mean_dca[j5] =  h_dca2d_pi->ProjectionY("hprojY", i, i+1)->GetMean();
    meany_tr_dca[j5] =  h_dca2d_pi->ProjectionX("hprojX", i, i+1)->GetMean();
    meane_dca[j5] =  h_dca2d_pi->ProjectionY("hprojY", i, i+1)->GetMeanError();
    rms_dca[j5] =  h_dca2d_pi->ProjectionY("hprojrY", i, i+1)->GetRMS();
    rmse_dca[j5] =  h_dca2d_pi->ProjectionY("hprojreY", i, i+1)->GetRMSError();
    x_dca[j5] = h_dca2d_pi->GetXaxis()->GetBinCenter(i+2);
    //x_dca[j5] =  meany_tr_dca[j5];
    /*
      if(mean_dca[j5] > 0) rms_dca[j5] /= mean_dca[j5]; 
      if(mean_dca[j5] > 0) rmse_dca[j5] /= mean_dca[j5];
    */
    j5++;
  }

  TGraphErrors *gr_resdca_pi = new TGraphErrors(j5,x_dca,rms_dca,meane_dca,rmse_dca);
  gr_resdca_pi->SetName("gr_resdca_pi");
  gr_resdca_pi->SetMarkerStyle(26);
  gr_resdca_pi->SetMarkerSize(0.5);
  gr_resdca_pi->SetMarkerColor(2);

  
  
  TFile *fout = new TFile("pim_barrelmRwell_defmac_wocaldirc.root", "recreate");
 

  
  h_event->Write();
  h_px_reco->Write();
  h_py_reco->Write();
  h_pz_reco->Write();
  h_p_reco->Write();
  h_pt_reco->Write();
 
  
  h_rap_reco->Write();
  h_rap_tr->Write();

  h_pt_vs_eta_tr->Write();
  h_p_vs_eta_tr->Write();
  h_pt_vs_eta_reco->Write();
  h_p_vs_eta_reco->Write();

  h_ptres_pi->Write();
  h_ptres_tpt_pi->Write();
  h_rpt_tpt_pi->Write();
  h_dptopt_tpt_pi->Write();
  pr_dptopt_tpt_pi->Write();

  h_pres_pi->Write();
  h_pres_tp_pi->Write();
  h_rp_tp_pi->Write();
  h_dpop_tp_pi->Write();
  pr_dpop_tp_pi->Write();
  
  h_dca2d_pi->Write();
  pr_dca2d_pi->Write();
  
  for(int i =0 ; i < 60; i++) {
    h_ptres3_trpt[i]->Write();
    h_pres3_trp[i]->Write();
  }
  
  gr_sig_res_pi->Write();
  f0_1->Write();
  gr_sig_pres_pi->Write();
  gr_resdca_pi->Write();
  gr_trk_eff->Write();
  

}

