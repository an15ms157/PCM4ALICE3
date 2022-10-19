#include <iostream>
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"

#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"

#include "./headers/ALICE3_setup.h"

void meson_MassResolution(){

//SET THIS VARIABLES: 

StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or
gStyle->SetLineWidth(2);
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetPadTopMargin(0.05);
gStyle->SetPadRightMargin(0.05);
gStyle->SetTitleSize(0.06);
gStyle->SetTitleSize(0.06,"Y");
gStyle->SetTitleOffset(1,"Y");
gStyle->SetTitleOffset(1,"X");
gStyle->SetLabelSize(0.04);
gStyle->SetLabelSize(0.04,"Y");
gStyle->SetFrameLineWidth(2);
gStyle->SetNdivisions(505,"X");
gStyle->SetNdivisions(505,"Y");
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);

//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);


// INPUT SETUP 

Int_t ScaleFactor_Pi0_F, ScaleFactor_Pi0_B, ScaleFactor_Eta_F, ScaleFactor_Eta_B;

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/PbPb/PbPb_100event_perfile/ana_pTcut_withft3_check.root";
gSystem->Exec("mkdir plots/meson_MassResolution");
gSystem->cd("plots/meson_MassResolution");

switch(collisionSystem){
    case 0:{
    ScaleFactor_Pi0_F = 1;
    ScaleFactor_Pi0_B = 1;
    ScaleFactor_Eta_F = 10;
    ScaleFactor_Eta_B = 10;
        
    ltb_Eta_B = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    ltb_Pi0_F = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    ltb_Pi0_B = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    ltb_Eta_F = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    
    ltb_Pi0_B_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Pi0_B));
    ltb_Pi0_F_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Pi0_F));
    ltb_Eta_B_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Eta_B));
    ltb_Eta_F_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Eta_F));

    gSystem->Exec("mkdir pp");
    gSystem->cd("./pp");
    gSystem->pwd();
    cout << "pp system"<< "using root file:"<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{
    ScaleFactor_Pi0_F = 50;
    ScaleFactor_Pi0_B = 50;
    ScaleFactor_Eta_F = 1000;
    ScaleFactor_Eta_B = 1000;
    
    fileRec = new TFile(input_file_loc.Data());
    ltb_Eta_B = new TLatex(0.2,0.7,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    ltb_Pi0_F = new TLatex(0.2,0.7,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    ltb_Pi0_B = new TLatex(0.2,0.7,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    ltb_Eta_F = new TLatex(0.2,0.7,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");

    ltb_Pi0_F_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Pi0_F));
    ltb_Pi0_B_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Pi0_B));
    ltb_Eta_F_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Eta_F));
    ltb_Eta_B_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Eta_B));

    gSystem->Exec("mkdir PbPb");
    gSystem->cd("./PbPb");
    gSystem->pwd();
    cout << "PbPb system, using input root file:"<< input_file_loc.Data() << endl;

        break;
    }
}





// INPUT CONDITIONS:

//Pi0
TH1D * hInvMassGG_B_SmearedP = (TH1D*) fileRec->Get("hInvMassGGB_SmearedP");  
hInvMassGG_B_SmearedP->Sumw2();
TH1D * hInvMassGGPi0_B_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0B_SmearedP");
hInvMassGGPi0_B_SmearedP->Sumw2();

TH1D * hInvMassGG_F_SmearedP = (TH1D*) fileRec->Get("hInvMassGGF_SmearedP");  
hInvMassGG_F_SmearedP->Sumw2();
TH1D * hInvMassGGPi0_F_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0F_SmearedP");
hInvMassGGPi0_F_SmearedP->Sumw2();

float_t Pi0_fit_xmin = 0.1;
float_t Pi0_fit_xmax = 0.2;
float_t Pi0_plot_xmin = 0.1;
float_t Pi0_plot_xmax = 0.18;

float_t Pi0_Gaussian_param0_start  = 0.1;
float_t Pi0_Gaussian_param1_start  = 0.13;
float_t Pi0_Gaussian_param2_start  = 0.01;


// Eta: 
TH1D * hInvMassGGEta_B_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaB_SmearedP");
hInvMassGGEta_B_SmearedP->Sumw2();
TH1D * hInvMassGGEta_F_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaF_SmearedP");
hInvMassGGEta_F_SmearedP->Sumw2();


float_t Eta_fit_xmin = 0.45;
float_t Eta_fit_xmax = 0.65;
float_t Eta_plot_xmin = 0.5;
float_t Eta_plot_xmax = 0.6;

float_t Eta_Gaussian_param0_start  = 0.1;
float_t Eta_Gaussian_param1_start  = 0.547;
float_t Eta_Gaussian_param2_start  = 0.01;










///////////////  Pi0 InVmass FIT PLOT    ///////////////

/////  Pi0  Barrel /////

TCanvas c_meson_MassResolution_Pi0_B(Form("meson_MassResolution_%s_%s",LightMeson[0][0].Data(),(RapidityBlock[0][0]).Data()), Form("meson_MassResolution_%s_%s",LightMeson[0][0].Data(),(RapidityBlock[0][0]).Data()), 800, 800);

SetStyleHistoTH1ForGraphs(hInvMassGG_B_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGG_B_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGPi0_B_SmearedP,20,0.8, kRed+2 , kRed+2);


hInvMassGGPi0_B_SmearedP->Scale(ScaleFactor_Pi0_B);
TF1 *gs_meson_MassResolution_Pi0_B = new TF1("gs_meson_MassResolution_Pi0_B", "gaus(0)", Pi0_fit_xmin, Pi0_fit_xmax);
gs_meson_MassResolution_Pi0_B->SetParameters(Pi0_Gaussian_param0_start, Pi0_Gaussian_param1_start, Pi0_Gaussian_param2_start);
hInvMassGGPi0_B_SmearedP->Fit(gs_meson_MassResolution_Pi0_B,"QRME+");
gs_meson_MassResolution_Pi0_B->SetLineColor(kAzure+2);
gs_meson_MassResolution_Pi0_B->SetLineWidth(2);

double Pi0_B_mean = gs_meson_MassResolution_Pi0_B->GetParameter(1);
double Pi0_B_sigma = gs_meson_MassResolution_Pi0_B->GetParameter(2);

ltb_Eta_B_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Pi0_B));

TString ltl_meson_mu_MassResolution_Pi0_B = Form("#mu: %f MeV/c^{2}", Pi0_B_mean);
TString ltl_meson_sigma_MassResolution_Pi0_B = Form("#sigma: %f MeV/c^{2}", Pi0_B_sigma);

hInvMassGG_B_SmearedP->GetXaxis()->SetRangeUser(Pi0_plot_xmin,Pi0_plot_xmax); 
hInvMassGG_B_SmearedP->SetMinimum(0); 
hInvMassGG_B_SmearedP->DrawCopy();
hInvMassGGPi0_B_SmearedP->Draw("E1,SAME");
gs_meson_MassResolution_Pi0_B->Draw("SAME");


auto l_meson_MassResolution_Pi0_B = new TLegend(0.7, 0.3, 0.8, 0.5);
l_meson_MassResolution_Pi0_B->SetHeader(Form("%s %s",(LightMeson[0][1]).Data(), (RapidityBlock[0][1]).Data()), "C");
l_meson_MassResolution_Pi0_B->SetBorderSize(0);
l_meson_MassResolution_Pi0_B->SetFillStyle(0);
l_meson_MassResolution_Pi0_B->SetTextSize(TextSize);
l_meson_MassResolution_Pi0_B->AddEntry(hInvMassGG_B_SmearedP,"Invariant Mass","p");
l_meson_MassResolution_Pi0_B->AddEntry(hInvMassGGPi0_B_SmearedP,"#splitline{Invariant Mass with}{smeared Momentum}","p");
l_meson_MassResolution_Pi0_B->AddEntry(gs_meson_MassResolution_Pi0_B,"Gaussian Fit","l");
l_meson_MassResolution_Pi0_B->Draw("SAME");


TLatex *ltl_meson_MassResolution_Mass_Pi0_B = new TLatex(0.7,0.75,ltl_meson_mu_MassResolution_Pi0_B.Data());
SetStyleTLatex( ltl_meson_MassResolution_Mass_Pi0_B, TextSize,4);
ltl_meson_MassResolution_Mass_Pi0_B->Draw("SAME");


TLatex *ltl_meson_MassResolution_Sigma_Pi0_B = new TLatex(0.7,0.7,ltl_meson_sigma_MassResolution_Pi0_B.Data());
SetStyleTLatex( ltl_meson_MassResolution_Sigma_Pi0_B, TextSize,4);
ltl_meson_MassResolution_Sigma_Pi0_B->Draw("SAME");

SetStyleTLatex( ltb_Pi0_B, TextSize,4);
ltb_Pi0_B->Draw("SAME");

SetStyleTLatex( ltb_Pi0_B_Additional_text, TextSize,4);
ltb_Pi0_B_Additional_text->Draw("SAME");

c_meson_MassResolution_Pi0_B.SaveAs(Form("meson_MassResolution_%s_%s.png",LightMeson[0][0].Data(),(RapidityBlock[0][1]).Data()));



/////  Pi0  Forward /////

TCanvas c_meson_MassResolution_Pi0_F(Form("meson_MassResolution_%s_%s",LightMeson[0][0].Data(),(RapidityBlock[1][0]).Data()), Form("meson_MassResolution_%s_%s",LightMeson[0][0].Data(),(RapidityBlock[1][0]).Data()), 800, 800);

SetStyleHistoTH1ForGraphs(hInvMassGG_F_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGG_F_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGPi0_F_SmearedP,20,0.8, kRed+2 , kRed+2);


hInvMassGGPi0_F_SmearedP->Scale(ScaleFactor_Pi0_F);
TF1 *gs_meson_MassResolution_Pi0_F = new TF1("gs_meson_MassResolution_Pi0_F", "gaus(0)", Pi0_fit_xmin, Pi0_fit_xmax);
gs_meson_MassResolution_Pi0_F->SetParameters(Pi0_Gaussian_param0_start, Pi0_Gaussian_param1_start, Pi0_Gaussian_param2_start);
hInvMassGGPi0_F_SmearedP->Fit(gs_meson_MassResolution_Pi0_F,"QRME+");
gs_meson_MassResolution_Pi0_F->SetLineColor(kAzure+2);
gs_meson_MassResolution_Pi0_F->SetLineWidth(2);

double Pi0_F_mean = gs_meson_MassResolution_Pi0_F->GetParameter(1);
double Pi0_F_sigma = gs_meson_MassResolution_Pi0_F->GetParameter(2);

ltb_Eta_F_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Pi0_F));

TString ltl_meson_mu_MassResolution_Pi0_F = Form("#mu: %f MeV/c^{2}", Pi0_F_mean);
TString ltl_meson_sigma_MassResolution_Pi0_F = Form("#sigma: %f MeV/c^{2}", Pi0_F_sigma);

hInvMassGG_F_SmearedP->GetXaxis()->SetRangeUser(Pi0_plot_xmin,Pi0_plot_xmax); 
hInvMassGG_F_SmearedP->SetMinimum(0); 
hInvMassGG_F_SmearedP->DrawCopy();
hInvMassGGPi0_F_SmearedP->Draw("E1,SAME");
gs_meson_MassResolution_Pi0_F->Draw("SAME");


auto l_meson_MassResolution_Pi0_F = new TLegend(0.7, 0.3, 0.8, 0.5);
l_meson_MassResolution_Pi0_F->SetHeader(Form("%s %s",(LightMeson[0][1]).Data(), (RapidityBlock[1][1]).Data()),"c");
l_meson_MassResolution_Pi0_F->SetBorderSize(0);
l_meson_MassResolution_Pi0_F->SetFillStyle(0);
l_meson_MassResolution_Pi0_F->SetTextSize(TextSize);
l_meson_MassResolution_Pi0_F->AddEntry(hInvMassGG_F_SmearedP,"Invariant Mass","p");
l_meson_MassResolution_Pi0_F->AddEntry(hInvMassGGPi0_F_SmearedP,"#splitline{Invariant Mass with}{smeared Momentum}","p");
l_meson_MassResolution_Pi0_F->AddEntry(gs_meson_MassResolution_Pi0_F,"Gaussian Fit","l");
l_meson_MassResolution_Pi0_F->Draw("SAME");


TLatex *ltl_meson_MassResolution_Mass_Pi0_F = new TLatex(0.7,0.75,ltl_meson_mu_MassResolution_Pi0_F.Data());
SetStyleTLatex( ltl_meson_MassResolution_Mass_Pi0_F, TextSize,4);
ltl_meson_MassResolution_Mass_Pi0_F->Draw("SAME");


TLatex *ltl_meson_MassResolution_Sigma_Pi0_F = new TLatex(0.7,0.7,ltl_meson_sigma_MassResolution_Pi0_F.Data());
SetStyleTLatex( ltl_meson_MassResolution_Sigma_Pi0_F, TextSize,4);
ltl_meson_MassResolution_Sigma_Pi0_F->Draw("SAME");

SetStyleTLatex( ltb_Pi0_F, TextSize,4);
ltb_Pi0_F->Draw("SAME");

SetStyleTLatex( ltb_Pi0_F_Additional_text, TextSize,4);
ltb_Pi0_F_Additional_text->Draw("SAME");

c_meson_MassResolution_Pi0_F.SaveAs(Form("meson_MassResolution_%s_%s.png",LightMeson[0][0].Data(),(RapidityBlock[1][1]).Data()));








///////////////  Eta InVmass FIT PLOT    ///////////////

/////  Eta  Barrel /////

TCanvas c_meson_MassResolution_Eta_B(Form("meson_MassResolution_%s_%s",LightMeson[1][0].Data(),(RapidityBlock[0][0]).Data()), Form("meson_MassResolution_%s_%s",LightMeson[1][0].Data(),(RapidityBlock[0][0]).Data()), 800, 800);

SetStyleHistoTH1ForGraphs(hInvMassGG_B_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGG_B_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGEta_B_SmearedP,20,0.8, kRed+2 , kRed+2);


hInvMassGGEta_B_SmearedP->Scale(ScaleFactor_Eta_B);
TF1 *gs_meson_MassResolution_Eta_B = new TF1("gs_meson_MassResolution_Eta_B", "gaus(0)", Eta_fit_xmin, Eta_fit_xmax);
gs_meson_MassResolution_Eta_B->SetParameters(Eta_Gaussian_param0_start, Eta_Gaussian_param1_start, Eta_Gaussian_param2_start);
hInvMassGGEta_B_SmearedP->Fit(gs_meson_MassResolution_Eta_B,"QRME+");
gs_meson_MassResolution_Eta_B->SetLineColor(kAzure+2);
gs_meson_MassResolution_Eta_B->SetLineWidth(2);

double Eta_B_mean = gs_meson_MassResolution_Eta_B->GetParameter(1);
double Eta_B_sigma = gs_meson_MassResolution_Eta_B->GetParameter(2);

ltb_Eta_B_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Eta_B));

TString ltl_meson_mu_MassResolution_Eta_B = Form("#mu: %f MeV/c^{2}", Eta_B_mean);
TString ltl_meson_sigma_MassResolution_Eta_B = Form("#sigma: %f MeV/c^{2}", Eta_B_sigma);

hInvMassGG_B_SmearedP->GetXaxis()->SetRangeUser(Eta_plot_xmin,Eta_plot_xmax); 
hInvMassGG_B_SmearedP->SetMinimum(0); 
hInvMassGG_B_SmearedP->DrawCopy();
hInvMassGGEta_B_SmearedP->Draw("E1,SAME");
gs_meson_MassResolution_Eta_B->Draw("SAME");


auto l_meson_MassResolution_Eta_B = new TLegend(0.7, 0.3, 0.8, 0.5);
l_meson_MassResolution_Eta_B->SetHeader(Form("%s %s",(LightMeson[1][1]).Data(), (RapidityBlock[0][1]).Data()), "C");
l_meson_MassResolution_Eta_B->SetBorderSize(0);
l_meson_MassResolution_Eta_B->SetFillStyle(0);
l_meson_MassResolution_Eta_B->SetTextSize(TextSize);
l_meson_MassResolution_Eta_B->AddEntry(hInvMassGG_B_SmearedP,"Invariant Mass","p");
l_meson_MassResolution_Eta_B->AddEntry(hInvMassGGEta_B_SmearedP,"#splitline{Invariant Mass with}{smeared Momentum}","p");
l_meson_MassResolution_Eta_B->AddEntry(gs_meson_MassResolution_Eta_B,"Gaussian Fit","l");
l_meson_MassResolution_Eta_B->Draw("SAME");


TLatex *ltl_meson_MassResolution_Mass_Eta_B = new TLatex(0.7,0.75,ltl_meson_mu_MassResolution_Eta_B.Data());
SetStyleTLatex( ltl_meson_MassResolution_Mass_Eta_B, TextSize,4);
ltl_meson_MassResolution_Mass_Eta_B->Draw("SAME");


TLatex *ltl_meson_MassResolution_Sigma_Eta_B = new TLatex(0.7,0.7,ltl_meson_sigma_MassResolution_Eta_B.Data());
SetStyleTLatex( ltl_meson_MassResolution_Sigma_Eta_B, TextSize,4);
ltl_meson_MassResolution_Sigma_Eta_B->Draw("SAME");

SetStyleTLatex( ltb_Eta_B, TextSize,4);
ltb_Eta_B->Draw("SAME");

SetStyleTLatex( ltb_Eta_B_Additional_text, TextSize,4);
ltb_Eta_B_Additional_text->Draw("SAME");

c_meson_MassResolution_Eta_B.SaveAs(Form("meson_MassResolution_%s_%s.png",LightMeson[1][0].Data(),(RapidityBlock[0][1]).Data()));



/////  Eta  Forward /////

TCanvas c_meson_MassResolution_Eta_F(Form("meson_MassResolution_%s_%s",LightMeson[1][0].Data(),(RapidityBlock[1][0]).Data()), Form("meson_MassResolution_%s_%s",LightMeson[1][0].Data(),(RapidityBlock[1][0]).Data()), 800, 800);

SetStyleHistoTH1ForGraphs(hInvMassGG_F_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGG_F_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGEta_F_SmearedP,20,0.8, kRed+2 , kRed+2);


hInvMassGGEta_F_SmearedP->Scale(ScaleFactor_Eta_F);
TF1 *gs_meson_MassResolution_Eta_F = new TF1("gs_meson_MassResolution_Eta_F", "gaus(0)", Eta_fit_xmin, Eta_fit_xmax);
gs_meson_MassResolution_Eta_F->SetParameters(Eta_Gaussian_param0_start, Eta_Gaussian_param1_start, Eta_Gaussian_param2_start);
hInvMassGGEta_F_SmearedP->Fit(gs_meson_MassResolution_Eta_F,"QRME+");
gs_meson_MassResolution_Eta_F->SetLineColor(kAzure+2);
gs_meson_MassResolution_Eta_F->SetLineWidth(2);

double Eta_F_mean = gs_meson_MassResolution_Eta_F->GetParameter(1);
double Eta_F_sigma = gs_meson_MassResolution_Eta_F->GetParameter(2);

ltb_Eta_F_Additional_text = new TLatex(0.2,0.5,Form("Scale factor = %d",ScaleFactor_Eta_F));

TString ltl_meson_mu_MassResolution_Eta_F = Form("#mu: %f MeV/c^{2}", Eta_F_mean);
TString ltl_meson_sigma_MassResolution_Eta_F = Form("#sigma: %f MeV/c^{2}", Eta_F_sigma);

hInvMassGG_F_SmearedP->GetXaxis()->SetRangeUser(Eta_plot_xmin,Eta_plot_xmax); 
hInvMassGG_F_SmearedP->SetMinimum(0); 
hInvMassGG_F_SmearedP->DrawCopy();
hInvMassGGEta_F_SmearedP->Draw("E1,SAME");
gs_meson_MassResolution_Eta_F->Draw("SAME");


auto l_meson_MassResolution_Eta_F = new TLegend(0.7, 0.3, 0.8, 0.5);
l_meson_MassResolution_Eta_F->SetHeader(Form("%s %s",(LightMeson[1][1]).Data(), (RapidityBlock[1][1]).Data()),"c");
l_meson_MassResolution_Eta_F->SetBorderSize(0);
l_meson_MassResolution_Eta_F->SetFillStyle(0);
l_meson_MassResolution_Eta_F->SetTextSize(TextSize);
l_meson_MassResolution_Eta_F->AddEntry(hInvMassGG_F_SmearedP,"Invariant Mass","p");
l_meson_MassResolution_Eta_F->AddEntry(hInvMassGGEta_F_SmearedP,"#splitline{Invariant Mass with}{smeared Momentum}","p");
l_meson_MassResolution_Eta_F->AddEntry(gs_meson_MassResolution_Eta_F,"Gaussian Fit","l");
l_meson_MassResolution_Eta_F->Draw("SAME");


TLatex *ltl_meson_MassResolution_Mass_Eta_F = new TLatex(0.7,0.75,ltl_meson_mu_MassResolution_Eta_F.Data());
SetStyleTLatex( ltl_meson_MassResolution_Mass_Eta_F, TextSize,4);
ltl_meson_MassResolution_Mass_Eta_F->Draw("SAME");


TLatex *ltl_meson_MassResolution_Sigma_Eta_F = new TLatex(0.7,0.7,ltl_meson_sigma_MassResolution_Eta_F.Data());
SetStyleTLatex( ltl_meson_MassResolution_Sigma_Eta_F, TextSize,4);
ltl_meson_MassResolution_Sigma_Eta_F->Draw("SAME");

SetStyleTLatex( ltb_Eta_F, TextSize,4);
ltb_Eta_F->Draw("SAME");

SetStyleTLatex( ltb_Eta_F_Additional_text, TextSize,4);
ltb_Eta_F_Additional_text->Draw("SAME");

c_meson_MassResolution_Eta_F.SaveAs(Form("meson_MassResolution_%s_%s.png",LightMeson[1][0].Data(),(RapidityBlock[1][1]).Data()));







}