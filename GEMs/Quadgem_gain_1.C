#include "TString.h"
#include "TDatime.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"
#include <sstream>

            
//Channel 8 & 9 for old set of gems g8i, g9i. 8 is cathode, 9 is anode
void Quadgem_gain_1(){
  cout << "define variables" << endl;
  const int N = 4;
  TGraph *g_an[N] ;
  TGraph *g_cat[N] ;
  TGraph *gtemp_an[N] ;
  TGraph *gtemp_cat[N] ;
  TString temp_cat;
  TString temp_an;
  TString cat;
  TString an;

  TF1 *fxray_an[N];
  TF1 *fxray_cat[N];

  TString xray_an;
  TString xray_cat;
          
  ifstream ifs[N];
  ostringstream filename[N];
  int N1[N];
  cout << "Read files" << endl;
  //Quad gem with reverse bias primary measurement
  filename[0] << "PA_14-26_dvgem335V.txt";
  ifs[0].open(filename[0].str());

  filename[1] << "PA_13-50_dvgem340V.txt";
  ifs[1].open(filename[1].str());

  filename[2] << "PA_14-13_dvgem342V.txt";
  ifs[2].open(filename[2].str());

  filename[3] << "PA_13-00_PRIMARY.txt";
  ifs[3].open(filename[3].str());

  cout << "Files open" << endl;

  //8 is cathode, 9 is anode
  Double_t t[N], g1i[N] , g2i[N], g3i[N], g4i[N], g5i[N] , g6i[N], g7i[N], g8i[N], g9i[N], g10i[N];
                
  for (int i = 0 ; i < N; i++){
                    
    g_an[i] = new TGraph();
    an = Form("g_an%d", i);
    g_an[i]->SetName(an);
                    
    g_cat[i] = new TGraph();
    cat = Form("g_cat%d", i);
    g_cat[i]->SetName(cat);

    gtemp_an[i] = new TGraph();
    temp_an = Form("gtemp_an%d", i);
    gtemp_an[i]->SetName(temp_an);
                    
    gtemp_cat[i] = new TGraph();
    temp_cat= Form("gtemp_cat%d", i);
    gtemp_cat[i]->SetName(temp_cat);

    // when scanning for different gains ch 8 and 9 
    while(ifs[i] >> t[i] >> g1i[i] >> g2i[i] >> g3i[i] >> g4i[i] >> g5i[i] >> g6i[i] >> g7i[i] >> g8i[i] >> g9i[i] >> g10i[i])
      {              
	gtemp_cat[i]->SetPoint(gtemp_cat[i]->GetN(), t[i] , g8i[i]);
	gtemp_an[i]->SetPoint(gtemp_an[i]->GetN(), t[i] , g9i[i]);
      }
	
/*    // when trying to stabilize detector over long run
    while(ifs[i] >> t[i] >> g1i[i] >> g2i[i] >> g3i[i] >> g4i[i] >> g5i[i] >> g6i[i] >> g7i[i] >> g8i[i] >> g9i[i] >> g10i[i])
      {
	//Channel 8 and 9 were used as cathode and anode for quadgem respectively
	gtemp_cat[i]->SetPoint(gtemp_cat[i]->GetN(), t[i] , g8i[i]);
	gtemp_an[i]->SetPoint(gtemp_an[i]->GetN(), t[i] , g9i[i]);
      }
*/	  
    N1[i] = gtemp_cat[i]->GetN();
    
    cout << "total entries in each graph  :" << i << " " << N1[i] << endl; 

    Double_t temp_t[N1[i]][N];
    Double_t an_i[N1[i]][N];
    Double_t cat_i[N1[i]][N];
    Double_t t_scale[N1[i]][N];
    
    for(int j =0 ; j < N1[i]; j++){
      temp_t[j][i] = gtemp_cat[i]->GetX()[j];
      an_i[j][i] = gtemp_an[i]->GetY()[j];
      cat_i[j][i] = gtemp_cat[i]->GetY()[j];
      t_scale[j][i] = temp_t[j][i]-temp_t[0][i];

      //cout << " " << " t :" << t_scale[j][i] << " anode I: " << an_i[j][i] << " cathode I: " <<  cat_i[j][i] << endl;
	  
      g_an[i]->SetPoint(j, t_scale[j][i], an_i[j][i]);
      g_cat[i]->SetPoint(j, t_scale[j][i], cat_i[j][i]);

      g_an[i]->SetLineColor(2);
      g_cat[i]->SetLineColor(4);
    }
    
/*    xray_an = Form("fxray_an%d", i);
    fxray_an[i] = new TF1(xray_an, "pol0", 200, 500);
    fxray_an[i]->SetName(xray_an);
    fxray_an[i]->SetLineColor(2);

    xray_cat = Form("fxray_cat%d", i);
    fxray_cat[i] = new TF1(xray_cat, "pol0", 200, 500);
    fxray_cat[i]->SetName(xray_cat);
    fxray_cat[i]->SetLineColor(4);    
*/    
  }
    
    TCanvas *c0 = new TCanvas("c0","c0", 1200, 800);
    c0->Divide(3,2);
    c0->cd(1);
    gStyle->SetOptStat("neMR");
    TH1D *h1 = new TH1D("h1","h1", 600, -0.1, 599.9);
    h1->SetTitle("dV_GEM  =  335 V");
    h1->GetYaxis()->SetRangeUser(-40., 80.);
    h1->GetXaxis()->SetRangeUser(0., 550.);
    h1->GetXaxis()->SetTitle("Time [seconds]");
    h1->GetYaxis()->SetTitle("current [nA]");
    h1->Draw();
    
    fxray_an[0] = new TF1("fxray_an[0]", "pol0", 200, 400);
    fxray_an[0]->SetName("fxray_an[0]");
    fxray_an[0]->SetLineColor(2);
    fxray_cat[0] = new TF1("fxray_cat[0]", "pol0", 200, 400);
    fxray_cat[0]->SetName("fxray_cat[0]");
    fxray_cat[0]->SetLineColor(4);
    
    g_an[0]->Fit("fxray_an[0]","R");
    g_cat[0]->Fit("fxray_cat[0]", "R");
    g_an[0]->Draw("sameL");
    g_cat[0]->Draw("sameL");

    Float_t anFit0 = fxray_an[0]->GetParameter(0);
    Float_t catFit0 = fxray_cat[0]->GetParameter(0);

    TLegend *legend1_0 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_0->SetFillStyle(0);
    legend1_0->SetBorderSize(0);
    legend1_0->SetTextSize(0.04);
    legend1_0->AddEntry("","X ray I = 75 uA", "");
    legend1_0->AddEntry("","X ray V = 40 kV", "");
    legend1_0->AddEntry(g_an[0], "Anode current","L");
    legend1_0->AddEntry(g_cat[0], "Cathode current","L");
//    legend1_0->AddEntry(anFit0, "Annode Value:" + anFit0 + " nA", "");
//    legend1_0->AddEntry(catFit0, "Cathode Value:" + catFit0 + " nA", "");
    legend1_0->Draw();
    
    c0->cd(2);
    TH1D *h2 = new TH1D("h2","h2", 1250, -0.1, 1249.9);
    h2->SetTitle("dV_GEM  =  340 V");
    h2->GetYaxis()->SetRangeUser(-45., 105.);
    h2->GetXaxis()->SetRangeUser(0., 1250.);
    h2->GetXaxis()->SetTitle("Time [seconds]");
    h2->GetYaxis()->SetTitle("current [nA]");
    h2->Draw();
    
    fxray_an[1] = new TF1("fxray_an[1]", "pol0", 1100, 1210);
    fxray_cat[1] = new TF1("fxray_cat[1]", "pol0", 1100, 1210);
    fxray_an[1]->SetName("fxray_an[1]");
    fxray_cat[1]->SetName("fxray_cat[1]");
    fxray_an[1]->SetLineColor(2);
    fxray_cat[1]->SetLineColor(4);
    
    g_an[1]->Fit("fxray_an[1]","R");
    g_cat[1]->Fit("fxray_cat[1]", "R");
    g_an[1]->Draw("sameL");
    g_cat[1]->Draw("sameL");

    TLegend *legend1_1 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_1->SetFillStyle(0);
    legend1_1->SetBorderSize(0);
    legend1_1->SetTextSize(0.04);
    legend1_1->AddEntry("","X ray I = 75 uA", "");
    legend1_1->AddEntry("","X ray V = 40 kV", "");
    legend1_1->AddEntry(g_an[1], "Anode current","L");
    legend1_1->AddEntry(g_cat[1], "Cathode current","L");
    legend1_1->Draw();

    c0->cd(3);
    TH1D *h3 = new TH1D("h3","h3", 700, -0.1, 699.9);
    h3->SetTitle("dV_GEM  =  342 V");
    h3->GetYaxis()->SetRangeUser(-60., 130.);
    h3->GetXaxis()->SetRangeUser(0., 625.);
    h3->GetXaxis()->SetTitle("Time [seconds]");
    h3->GetYaxis()->SetTitle("current [nA]");
    h3->Draw();
    
    fxray_an[2] = new TF1("fxray_an[2]", "pol0", 400, 545);
    fxray_cat[2] = new TF1("fxray_cat[2]", "pol0", 400, 545);
    fxray_an[2]->SetName("fxray_an[2]");
    fxray_cat[2]->SetName("fxray_cat[2]");
    fxray_an[2]->SetLineColor(2);
    fxray_cat[2]->SetLineColor(4);
    
    g_an[2]->Fit("fxray_an[2]","R");
    g_cat[2]->Fit("fxray_cat[2]", "R");
    g_an[2]->Draw("sameL");
    g_cat[2]->Draw("sameL");
	
    TLegend *legend1_2 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_2->SetFillStyle(0);
    legend1_2->SetBorderSize(0);
    legend1_2->SetTextSize(0.04);
    legend1_2->AddEntry("","X ray I = 75 uA", "");
    legend1_2->AddEntry("","X ray V = 40 kV", "");
    legend1_2->AddEntry(g_an[2], "Anode current","L");
    legend1_2->AddEntry(g_cat[2], "Cathode current","L");
    legend1_2->Draw();
    
    c0->cd(4);
    TH1D *h4 = new TH1D("h4","h4", 1000, -0.1, 999.9);
    h4->SetTitle("Primary");
    h4->GetYaxis()->SetRangeUser(-0.01, 0.15);
    h4->GetXaxis()->SetRangeUser(0., 800.);
    h4->GetXaxis()->SetTitle("Time [seconds]");
    h4->GetYaxis()->SetTitle("current [nA]");
    h4->Draw();
    
    fxray_an[3] = new TF1("fxray_an[3]", "pol0", 260, 660);
    fxray_cat[3] = new TF1("fxray_cat[3]", "pol0", 260, 660);
    fxray_an[3]->SetName("fxray_an[3]");
    fxray_cat[3]->SetName("fxray_cat[3]");
    fxray_an[3]->SetLineColor(2);
    fxray_cat[3]->SetLineColor(4);
    
    g_an[3]->Fit("fxray_an[3]","R");
    g_cat[3]->Fit("fxray_cat[3]", "R");
    g_an[3]->Draw("sameL");
    g_cat[3]->Draw("sameL");
    
    TLegend *legend1_3 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_3->SetFillStyle(0);
    legend1_3->SetBorderSize(0);
    legend1_3->SetTextSize(0.04);
    //legend1_3->AddEntry(g_an[1],"dv GEM = 356 V","");
    legend1_3->AddEntry("","X ray I = 75 uA", "");
    legend1_3->AddEntry("","X ray V = 40 kV", "");
    legend1_3->AddEntry(g_an[3], "Anode current","L");
    legend1_3->AddEntry(g_cat[3], "Cathode current","L");
    legend1_3->Draw();
    	
    TCanvas *c0_0 = new TCanvas("c0_0","c0_0", 1200, 800);
    c0_0->cd();
    gStyle->SetOptStat("neMR");
    TH1D *h0_0 = new TH1D("h0_0","h0_0", 5000, -0.1, 4999.9);
    h0_0->SetTitle("dV_GEM  =  335 V");
    h0_0->GetYaxis()->SetRangeUser(-40., 80.);
    h0_0->GetXaxis()->SetRangeUser(0., 500.);
    h0_0->GetXaxis()->SetTitle("Time [seconds]");
    h0_0->GetYaxis()->SetTitle("current [nA]");
    h0_0->Draw("E");
    g_an[0]->Draw("sameL");
    g_cat[0]->Draw("sameL");

    TLegend *legend0 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend0->SetFillStyle(0);
    legend0->SetBorderSize(0);
    legend0->SetTextSize(0.05);
    legend0->AddEntry(g_an[0], "Anode current","L");
    legend0->AddEntry(g_cat[0], "Cathode current","L");
    legend0->Draw();

    TCanvas *c0_1 = new TCanvas("c0_1","c0_1", 1200, 800);
    c0_1->cd();
    gStyle->SetOptStat("neMR");
    TH1D *h0_1 = new TH1D("h0_1","h0_1", 5000, -0.1, 4999.9);
    h0_1->SetTitle("dV_GEM  =  340 V");
    h0_1->GetYaxis()->SetRangeUser(-45., 105.);
    h0_1->GetXaxis()->SetRangeUser(0., 1250.);
    h0_1->GetXaxis()->SetTitle("Time [seconds]");
    h0_1->GetYaxis()->SetTitle("current [nA]");
    h0_1->Draw();
    g_an[1]->Draw("sameL");
    g_cat[1]->Draw("sameL");

    TLegend *legend1 = new TLegend(0.55, 0.30, 0.75, 0.50, NULL, "brNDC");
    legend1->SetFillStyle(0);
    legend1->SetBorderSize(0);
    legend1->SetTextSize(0.05);
    legend1->AddEntry(g_an[1], "Annode Current", "L");
    legend1->AddEntry(g_cat[1], "Cathode Current", "L");
    
    TCanvas *c0_2 = new TCanvas("c0_2","c0_2", 1200, 800);
    c0_2->cd();
    gStyle->SetOptStat("neMR");
    TH1D *h0_2 = new TH1D("h0_2","h0_2", 5000, -0.1, 4999.9);
    h0_2->SetTitle("dV_GEM  =  342 V");
    h0_2->GetYaxis()->SetRangeUser(-60., 135.);
    h0_2->GetXaxis()->SetRangeUser(0., 600.);
    h0_2->GetXaxis()->SetTitle("Time [seconds]");
    h0_2->GetYaxis()->SetTitle("current [nA]");
    h0_2->Draw();
    g_an[2]->Draw("sameL");
    g_cat[2]->Draw("sameL");

    TLegend *legend2 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend2->SetFillStyle(0);
    legend2->SetBorderSize(0);
    legend2->SetTextSize(0.05);
    legend2->AddEntry(g_an[2], "Anode current","L");
    legend2->AddEntry(g_cat[2], "Cathode current","L");
    legend2->Draw();
    
    TCanvas *c0_3 = new TCanvas("c0_3","c0_3", 1200, 800);
    c0_3->cd();
    gStyle->SetOptStat("neMR");
    TH1D *h0_3 = new TH1D("h0_3","h0_3", 5000, -0.1, 4999.9);
    h0_3->SetTitle("PRIMARY");
    h0_3->GetYaxis()->SetRangeUser(-0.01, 0.15);
    h0_3->GetXaxis()->SetRangeUser(0., 800.);
    h0_3->GetXaxis()->SetTitle("Time [seconds]");
    h0_3->GetYaxis()->SetTitle("current [nA]");
    h0_3->Draw();
    g_an[3]->Draw("sameL");
    g_cat[3]->Draw("sameL");

    TLegend *legend3 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend3->SetFillStyle(0);
    legend3->SetBorderSize(0);
    legend3->SetTextSize(0.05);
    legend3->AddEntry(g_an[3], "Anode current","L");
    legend3->AddEntry(g_cat[3], "Cathode current","L");
    legend3->Draw();
    
    Float_t p0_xray_an[N],p0_xray_cat[N];
    Float_t IBF[N];
    cout << "calculate IBF : " << endl;
    
    for(int i = 0; i < N; i++ ){
    p0_xray_an[i] = fxray_an[i]->GetParameter(0);
    p0_xray_cat[i] = fxray_cat[i]->GetParameter(0);

    IBF[i] = ((p0_xray_cat[i]) / (p0_xray_an[i]))*100.*(-1.0) ;

    cout << " x-ray anode :" << p0_xray_an[i]  << " x ray cathode " << p0_xray_cat[i] << endl;
    cout << " IBF :" << IBF[i] << endl;
    }
    
    const int n = 3;
    //drift = 1 kV/cm, transfer = induction = 2 kV/cm
    Float_t V[n] = {335, 340, 342};
//    cout << "Voltages: " << V[n] << endl;    

    //////////////////////////
    //Effective Gain
    const int slope_pA = 3397; // charge per mV
    const int primary_arco2_70_30 = 217;
    const int primary_arco2_80_20 = 223;
    Float_t eff_gain[n];
    
    //ArCO2 (70:30)
    for (int i =0 ; i < n; i++) {
    eff_gain[i] = (p0_xray_an[i])/(p0_xray_cat[3]);
    }

    TGraph *effgain =  new TGraph(n, V , eff_gain);
    effgain->SetName("effgain");
    effgain->SetMarkerStyle(20);
    effgain->SetMarkerSize(2.0);
    effgain->SetMarkerColor(4);

    TGraph *ibf = new TGraph(n, V, IBF);
    ibf->SetName("ibf");
    ibf->SetMarkerStyle(20);
    ibf->SetMarkerSize(2.0);
    ibf->SetMarkerColor(2);

    TCanvas *c1 = new TCanvas("c1","c1", 1200, 800);
    c1->cd();
    TH1F *hist0 = new TH1F("hist0","",30,330,350);
    hist0->SetTitle("Effective Gain");
    hist0->GetYaxis()->SetRangeUser(0, 1600.);
    hist0->GetYaxis()->SetTitle("(I_an)/(I_PRIMARY)");
    hist0->GetXaxis()->SetTitle("dV GEM [V]");
    hist0->Draw("");
    effgain->Draw("sameP");

    TLegend *legendh0 = new TLegend(0.35,.80,.55,0.93, NULL, "brNDC");
    legendh0->SetFillStyle(0);
    legendh0->SetBorderSize(0);
    legendh0->SetTextSize(0.05);
    legendh0->AddEntry(effgain, "ArCO2(70:30)","P");
    legendh0->Draw();

    TCanvas *c2 = new TCanvas("c2","c2", 1200, 800);
    c2->cd();
    gStyle->SetOptStat("000000");
    TH1F *hist1 = new TH1F("hist1","",30,325,350);
    hist1->SetTitle("IBF");
    hist1->GetYaxis()->SetTitle("IBF");
    hist1->GetXaxis()->SetTitle("dV GEM [V]");
    hist1->GetYaxis()->SetRangeUser(20, 60);
    hist1->Draw("");
    ibf->Draw("SameP");

    TLegend *legendh1 = new TLegend(0.35,.80,.55,0.93, NULL, "brNDC");
    legendh1->SetFillStyle(0);
    legendh1->SetBorderSize(0);
    legendh1->SetTextSize(0.05);
    legendh1->AddEntry(ibf, "ArCO2(70:30)","P");
    legendh1->Draw();

    TFile *fout = new TFile("quadgem_gain_ibf_arco2_7030.root", "RECREATE");
    effgain->Write();
    ibf->Write();
    fout->Close();
    
    /*
  TFile *fout = new TFile("test_gr.root", "RECREATE");
  for (int i = 1; i < 7; i++){
    g_cat[i]->Write();
    g_an[i]->Write();
    gtemp_an[i]->Write();
    gtemp_cat[i]->Write();
    
  }
    */
}

