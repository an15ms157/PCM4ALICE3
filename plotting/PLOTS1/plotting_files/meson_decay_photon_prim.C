#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TF1.h"
#include "TPad.h"
#include "TLegend.h"
//#include "TMath.h"
#include "TLatex.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"

#include "./headers/ALICE3_setup.h"





void SetStyle(Bool_t graypalette) {
  //cout << "Setting style!" << endl;
  gStyle->Reset("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  if(graypalette) gStyle->SetPalette(8,0);
  else gStyle->SetPalette(1);
  gStyle->SetCanvasColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameLineWidth(9);
  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetPadColor(10);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetHistLineWidth(1);
  gStyle->SetHistLineColor(kRed);
  gStyle->SetFuncWidth(9);
  gStyle->SetFuncColor(kBlack);
  gStyle->SetLineWidth(9);
  gStyle->SetLabelSize(0.045,"xyz");
  gStyle->SetLabelOffset(0.015,"y");
  gStyle->SetLabelOffset(0.01,"x");
  gStyle->SetLabelColor(kBlack,"xyz");
  gStyle->SetTitleSize(0.05,"xyz");
  gStyle->SetTitleOffset(1.5,"y");
  gStyle->SetTitleOffset(1.25,"x");
  gStyle->SetTitleFillColor(kWhite);
  gStyle->SetTextSizePixels(26);
  gStyle->SetTextFont(42);
  gStyle->SetTickLength(0.03,"X");
  gStyle->SetTickLength(0.03,"Y"); 
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);
  gStyle->SetLegendFont(42);
}




void meson_decay_photon_prim(){
//SET THIS VARIABLES: 

//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);
void SetStyle(Bool_t graypalette=kFALSE);



// INPUT SETUP 

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/latest/pp/ana_pTcut_withft3.root";
//TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/latest/PbPb/ana_pTcut_withft3.root";
gSystem->Exec("mkdir ./meson_decay_photon_prim");
gSystem->cd("./meson_decay_photon_prim");
gStyle->SetOptStat(0);

collisionSystem = 0;
switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.25,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    // INPUT CONDITIONS:
    plot_minPt = 3e-1;
    plot_maxPt = 10;
    plot_minY = 1e-7;
    plot_maxY = 1e2;

    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{

    fcollisionSystem = "PbPb";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.85,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;
    plot_minPt = 1e-1;
    plot_maxPt = 10;
    plot_minY = 1e-4;
    plot_maxY = 10.;
        break;
    }
}

SetStyleTLatex( ltb_general_Additional_text, 0.03,4);






///////////////////////////////////          Barrel             //////////////////////////////////////////

TH1F * hist_PrimPhotonPt_B                  = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_B_Pt"));
TH1F * hist_PrimPhotonPt_Pi0_B              = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Pi0_B_Pt"));
TH1F * hist_PrimPhotonPt_Eta_B              = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Eta_B_Pt"));
TH1F * hist_PrimPhotonPt_Omega_B            = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Omega_B_Pt"));
TH1F * hist_PrimPhotonPt_EtaPrime_B         = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_EtaPrime_B_Pt"));
TH1F * hist_PrimPhotonPt_Rho0_B             = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Rho0_B_Pt"));
TH1F * hist_PrimPhotonPt_RhoPlus_B          = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_RhoPlus_B_Pt"));
TH1F * hist_PrimPhotonPt_RhoMinus_B         = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_RhoMinus_B_Pt"));
TH1F * hist_PrimPhotonPt_Phi_B              = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Phi_B_Pt"));
TH1F * hist_PrimPhotonPt_Delta0_B           = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Delta0_B_Pt"));
TH1F * hist_PrimPhotonPt_DeltaPlus_B        = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_DeltaPlus_B_Pt"));
TH1F * hist_PrimPhotonPt_Sigma0_B           = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Sigma0_B_Pt"));
TH1F * hist_PrimPhotonPt_KZeroShort_B       = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_KZeroShort_B_Pt"));
TH1F * hist_PrimPhotonPt_KZeroLong_B        = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_KZeroLong_B_Pt"));
TH1F * hist_PrimPhotonPt_Lambda_B           = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Lambda_B_Pt"));

cout<< hist_PrimPhotonPt_B->GetNdivisions();

TH1F* hist_PrimPhotonPt_B_Rebin              = (TH1F*) hist_PrimPhotonPt_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Pi0_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Pi0_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Eta_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Eta_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Omega_B_Rebin        = (TH1F*) hist_PrimPhotonPt_Omega_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Omega_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_EtaPrime_B_Rebin     = (TH1F*) hist_PrimPhotonPt_EtaPrime_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_EtaPrime_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Rho0_B_Rebin         = (TH1F*) hist_PrimPhotonPt_Rho0_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Rho0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_RhoPlus_B_Rebin      = (TH1F*) hist_PrimPhotonPt_RhoPlus_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_RhoPlus_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_RhoMinus_B_Rebin     = (TH1F*) hist_PrimPhotonPt_RhoMinus_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_RhoMinus_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Phi_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Phi_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Phi_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Delta0_B_Rebin       = (TH1F*) hist_PrimPhotonPt_Delta0_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Delta0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_DeltaPlus_B_Rebin    = (TH1F*) hist_PrimPhotonPt_DeltaPlus_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_DeltaPlus_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Sigma0_B_Rebin       = (TH1F*) hist_PrimPhotonPt_Sigma0_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Sigma0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_KZeroShort_B_Rebin   = (TH1F*) hist_PrimPhotonPt_KZeroShort_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_KZeroShort_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_KZeroLong_B_Rebin    = (TH1F*) hist_PrimPhotonPt_KZeroLong_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_KZeroLong_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Lambda_B_Rebin       = (TH1F*) hist_PrimPhotonPt_Lambda_B->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Lambda_B_Rebin",&pt_bin_proj_fine[0]);


TH1F* hist_PrimPhotonFraction_Pt_B_Pi0             = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Pi0");
TH1F* hist_PrimPhotonFraction_Pt_B_Eta             = (TH1F*) hist_PrimPhotonPt_Eta_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Eta");
TH1F* hist_PrimPhotonFraction_Pt_B_Omega           = (TH1F*) hist_PrimPhotonPt_Omega_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Omega");
TH1F* hist_PrimPhotonFraction_Pt_B_EtaPrime        = (TH1F*) hist_PrimPhotonPt_EtaPrime_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_EtaPrime");
TH1F* hist_PrimPhotonFraction_Pt_B_Rho0            = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Rho0");
TH1F* hist_PrimPhotonFraction_Pt_B_RhoPlus         = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_RhoPlus");
TH1F* hist_PrimPhotonFraction_Pt_B_RhoMinus        = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_RhoMinus");
TH1F* hist_PrimPhotonFraction_Pt_B_Phi             = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Phi");
TH1F* hist_PrimPhotonFraction_Pt_B_Delta0          = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Delta0");
TH1F* hist_PrimPhotonFraction_Pt_B_DeltaPlus       = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_DeltaPlus");
TH1F* hist_PrimPhotonFraction_Pt_B_Sigma0          = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Sigma0");
TH1F* hist_PrimPhotonFraction_Pt_B_KZeroShort      = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_KZeroShort");
TH1F* hist_PrimPhotonFraction_Pt_B_KZeroLong       = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_KZeroLong");
TH1F* hist_PrimPhotonFraction_Pt_B_Lambda          = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Lambda");


TH1F* hist_PrimPhotonFraction_Pt_B_All_Rebin = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_All_Rebin");
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Eta_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Omega_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_EtaPrime_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Rho0_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_RhoPlus_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_RhoMinus_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Phi_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Delta0_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_DeltaPlus_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Sigma0_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_KZeroShort_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_KZeroLong_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Lambda_B_Rebin,1);


hist_PrimPhotonFraction_Pt_B_Pi0->Divide(hist_PrimPhotonPt_Pi0_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Eta->Divide(hist_PrimPhotonPt_Eta_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Omega->Divide(hist_PrimPhotonPt_Omega_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_EtaPrime->Divide(hist_PrimPhotonPt_EtaPrime_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Rho0->Divide(hist_PrimPhotonPt_Rho0_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_RhoPlus->Divide(hist_PrimPhotonPt_RhoPlus_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_RhoMinus->Divide(hist_PrimPhotonPt_RhoMinus_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Phi->Divide(hist_PrimPhotonPt_Phi_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Delta0->Divide(hist_PrimPhotonPt_Delta0_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_DeltaPlus->Divide(hist_PrimPhotonPt_DeltaPlus_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Sigma0->Divide(hist_PrimPhotonPt_Sigma0_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_KZeroShort->Divide(hist_PrimPhotonPt_KZeroShort_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_KZeroLong->Divide(hist_PrimPhotonPt_KZeroLong_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Lambda->Divide(hist_PrimPhotonPt_Lambda_B_Rebin, hist_PrimPhotonFraction_Pt_B_All_Rebin, 1,1,"B");
//hist_PrimPhotonFraction_Pt_B_All_Rebin->Divide(hist_PrimPhotonFraction_Pt_B_All_Rebin, hist_PrimPhotonPt_B_Rebin, 1,1,"B");




TCanvas* c_meson_decay_photon_prim_B = new TCanvas("c_meson_decay_photon_prim_B","c_meson_decay_photon_prim_B",0,0,500,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_decay_photon_prim_B, 0.12, 0.03, 0.03, 0.12);
c_meson_decay_photon_prim_B->SetLogy();  
c_meson_decay_photon_prim_B->SetLogx();  

SetStyleHistoTH1ForGraphs(hist_PrimPhotonFraction_Pt_B_Pi0, p_T.Data() , "#gamma_{meson}/#gamma_{decay_sum}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Pi0,marker_B,0.5, kRed+2 , kRed+2);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_All_Rebin,marker_B,0.5, kBlack , kBlack);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Eta,marker_B,0.5, kBlue , kBlue);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Omega,marker_B,0.5, kYellow-3 , kYellow-3);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_EtaPrime,marker_B,0.5, kOrange , kOrange);
hist_PrimPhotonFraction_Pt_B_EtaPrime->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Rho0,marker_B,0.5, kAzure+1 , kAzure+1);
hist_PrimPhotonFraction_Pt_B_Rho0->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_RhoPlus,marker_B,0.5, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_RhoMinus,marker_B,0.5, kRed+3 , kRed+3);
hist_PrimPhotonFraction_Pt_B_RhoMinus->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Phi,marker_B,0.5, kMagenta , kMagenta);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Delta0,marker_B,0.5, kBlue-5 , kBlue-5);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_DeltaPlus,marker_B,0.5, kGreen , kGreen);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Sigma0,marker_B,0.5, kViolet-5 , kViolet-5);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_KZeroShort,marker_B,0.5, kGreen+4 , kGreen+4);
hist_PrimPhotonFraction_Pt_B_KZeroShort->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_KZeroLong,marker_B,0.5, kViolet-6 , kViolet-6);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Lambda,marker_B,0.5, kCyan , kCyan);
hist_PrimPhotonFraction_Pt_B_Lambda->SetLineStyle(9);

auto l_meson_decay_photon_prim_B = new TLegend(0.2, 0.8, 0.9, 0.9);
l_meson_decay_photon_prim_B->SetHeader(Form("#gamma from %s",RapidityBlock[0][2].Data()));
l_meson_decay_photon_prim_B->SetBorderSize(0);
l_meson_decay_photon_prim_B->SetFillStyle(0);
l_meson_decay_photon_prim_B->SetTextSize(TextSize);
l_meson_decay_photon_prim_B->SetNColumns(7);
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Pi0,Form("#pi^{0}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Eta,Form("#eta"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Omega,Form("#omega"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_EtaPrime,Form("#eta'"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Rho0,Form("#rho^{0}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_RhoPlus,Form("#rho^{+}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_RhoMinus,Form("#rho^{-}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Phi,Form("#phi"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Delta0,Form("#Delta^{0}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_DeltaPlus,Form("#Delta^{+}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Sigma0,Form("#Sigma^{0}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_KZeroShort,Form("K^{0}_{S}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_KZeroLong,Form("K^{0}_{L}"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Lambda,Form("#Lambda"),"l");


hist_PrimPhotonFraction_Pt_B_Pi0->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);
hist_PrimPhotonFraction_Pt_B_Pi0->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);

hist_PrimPhotonFraction_Pt_B_Pi0->Draw(" C HIST ");
hist_PrimPhotonFraction_Pt_B_All_Rebin->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Eta->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Omega->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_EtaPrime->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Rho0->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_RhoPlus->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_RhoMinus->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Phi->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Delta0->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_DeltaPlus->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Sigma0->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_KZeroShort->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_KZeroLong->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Lambda->Draw(" C HIST SAME ");

ltb_general_Additional_text->Draw("SAME");

l_meson_decay_photon_prim_B->Draw("SAME");

gPad->Modified();

c_meson_decay_photon_prim_B->SaveAs("./meson_decay_photon_prim_B.png");
c_meson_decay_photon_prim_B->Close();










///////////////////////////////////          Forward             //////////////////////////////////////////

TH1F * hist_PrimPhotonPt_F                  = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_F_Pt"));
TH1F * hist_PrimPhotonPt_Pi0_F              = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Pi0_F_Pt"));
TH1F * hist_PrimPhotonPt_Eta_F              = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Eta_F_Pt"));
TH1F * hist_PrimPhotonPt_Omega_F            = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Omega_F_Pt"));
TH1F * hist_PrimPhotonPt_EtaPrime_F         = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_EtaPrime_F_Pt"));
TH1F * hist_PrimPhotonPt_Rho0_F             = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Rho0_F_Pt"));
TH1F * hist_PrimPhotonPt_RhoPlus_F          = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_RhoPlus_F_Pt"));
TH1F * hist_PrimPhotonPt_RhoMinus_F         = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_RhoMinus_F_Pt"));
TH1F * hist_PrimPhotonPt_Phi_F              = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Phi_F_Pt"));
TH1F * hist_PrimPhotonPt_Delta0_F           = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Delta0_F_Pt"));
TH1F * hist_PrimPhotonPt_DeltaPlus_F        = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_DeltaPlus_F_Pt"));
TH1F * hist_PrimPhotonPt_Sigma0_F           = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Sigma0_F_Pt"));
TH1F * hist_PrimPhotonPt_KZeroShort_F       = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_KZeroShort_F_Pt"));
TH1F * hist_PrimPhotonPt_KZeroLong_F        = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_KZeroLong_F_Pt"));
TH1F * hist_PrimPhotonPt_Lambda_F           = (TH1F*) fileRec->Get(Form("hPrimPhoton_from_Lambda_F_Pt"));

cout<< hist_PrimPhotonPt_F->GetNdivisions();

TH1F* hist_PrimPhotonPt_F_Rebin              = (TH1F*) hist_PrimPhotonPt_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Pi0_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Pi0_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Eta_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Eta_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Eta_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Omega_F_Rebin        = (TH1F*) hist_PrimPhotonPt_Omega_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Omega_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_EtaPrime_F_Rebin     = (TH1F*) hist_PrimPhotonPt_EtaPrime_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_EtaPrime_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Rho0_F_Rebin         = (TH1F*) hist_PrimPhotonPt_Rho0_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Rho0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_RhoPlus_F_Rebin      = (TH1F*) hist_PrimPhotonPt_RhoPlus_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_RhoPlus_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_RhoMinus_F_Rebin     = (TH1F*) hist_PrimPhotonPt_RhoMinus_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_RhoMinus_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Phi_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Phi_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Phi_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Delta0_F_Rebin       = (TH1F*) hist_PrimPhotonPt_Delta0_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Delta0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_DeltaPlus_F_Rebin    = (TH1F*) hist_PrimPhotonPt_DeltaPlus_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_DeltaPlus_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Sigma0_F_Rebin       = (TH1F*) hist_PrimPhotonPt_Sigma0_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Sigma0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_KZeroShort_F_Rebin   = (TH1F*) hist_PrimPhotonPt_KZeroShort_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_KZeroShort_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_KZeroLong_F_Rebin    = (TH1F*) hist_PrimPhotonPt_KZeroLong_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_KZeroLong_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* hist_PrimPhotonPt_Lambda_F_Rebin       = (TH1F*) hist_PrimPhotonPt_Lambda_F->Rebin(nbinspt_proj_fine,"hist_PrimPhotonPt_Lambda_F_Rebin",&pt_bin_proj_fine[0]);


TH1F* hist_PrimPhotonFraction_Pt_F_Pi0             = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Pi0");
TH1F* hist_PrimPhotonFraction_Pt_F_Eta             = (TH1F*) hist_PrimPhotonPt_Eta_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Eta");
TH1F* hist_PrimPhotonFraction_Pt_F_Omega           = (TH1F*) hist_PrimPhotonPt_Omega_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Omega");
TH1F* hist_PrimPhotonFraction_Pt_F_EtaPrime        = (TH1F*) hist_PrimPhotonPt_EtaPrime_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_EtaPrime");
TH1F* hist_PrimPhotonFraction_Pt_F_Rho0            = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Rho0");
TH1F* hist_PrimPhotonFraction_Pt_F_RhoPlus         = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_RhoPlus");
TH1F* hist_PrimPhotonFraction_Pt_F_RhoMinus        = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_RhoMinus");
TH1F* hist_PrimPhotonFraction_Pt_F_Phi             = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Phi");
TH1F* hist_PrimPhotonFraction_Pt_F_Delta0          = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Delta0");
TH1F* hist_PrimPhotonFraction_Pt_F_DeltaPlus       = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_DeltaPlus");
TH1F* hist_PrimPhotonFraction_Pt_F_Sigma0          = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Sigma0");
TH1F* hist_PrimPhotonFraction_Pt_F_KZeroShort      = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_KZeroShort");
TH1F* hist_PrimPhotonFraction_Pt_F_KZeroLong       = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_KZeroLong");
TH1F* hist_PrimPhotonFraction_Pt_F_Lambda          = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Lambda");


TH1F* hist_PrimPhotonFraction_Pt_F_All_Rebin = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_All_Rebin");
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Eta_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Omega_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_EtaPrime_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Rho0_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_RhoPlus_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_RhoMinus_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Phi_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Delta0_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_DeltaPlus_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Sigma0_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_KZeroShort_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_KZeroLong_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Lambda_F_Rebin,1);


hist_PrimPhotonFraction_Pt_F_Pi0->Divide(hist_PrimPhotonPt_Pi0_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Eta->Divide(hist_PrimPhotonPt_Eta_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Omega->Divide(hist_PrimPhotonPt_Omega_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_EtaPrime->Divide(hist_PrimPhotonPt_EtaPrime_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Rho0->Divide(hist_PrimPhotonPt_Rho0_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_RhoPlus->Divide(hist_PrimPhotonPt_RhoPlus_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_RhoMinus->Divide(hist_PrimPhotonPt_RhoMinus_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Phi->Divide(hist_PrimPhotonPt_Phi_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Delta0->Divide(hist_PrimPhotonPt_Delta0_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_DeltaPlus->Divide(hist_PrimPhotonPt_DeltaPlus_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Sigma0->Divide(hist_PrimPhotonPt_Sigma0_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_KZeroShort->Divide(hist_PrimPhotonPt_KZeroShort_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_KZeroLong->Divide(hist_PrimPhotonPt_KZeroLong_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Lambda->Divide(hist_PrimPhotonPt_Lambda_F_Rebin, hist_PrimPhotonFraction_Pt_F_All_Rebin, 1,1,"B");
//hist_PrimPhotonFraction_Pt_F_All_Rebin->Divide(hist_PrimPhotonFraction_Pt_F_All_Rebin, hist_PrimPhotonPt_F_Rebin, 1,1,"B");




TCanvas* c_meson_decay_photon_prim_F = new TCanvas("c_meson_decay_photon_prim_F","c_meson_decay_photon_prim_F",0,0,500,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_decay_photon_prim_F, 0.12, 0.03, 0.03, 0.12);
c_meson_decay_photon_prim_F->SetLogy();  
c_meson_decay_photon_prim_F->SetLogx();  

SetStyleHistoTH1ForGraphs(hist_PrimPhotonFraction_Pt_F_Pi0, p_T.Data() , "#gamma_{meson}/#gamma_{decay_sum}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Pi0,marker_F,0.5, kRed+2 , kRed+2);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_All_Rebin,marker_F,0.5, kBlack , kBlack);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Eta,marker_F,0.5, kBlue , kBlue);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Omega,marker_F,0.5, kYellow-3 , kYellow-3);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_EtaPrime,marker_F,0.5, kOrange , kOrange);
hist_PrimPhotonFraction_Pt_F_EtaPrime->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Rho0,marker_F,0.5, kAzure+1 , kAzure+1);
hist_PrimPhotonFraction_Pt_F_Rho0->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_RhoPlus,marker_F,0.5, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_RhoMinus,marker_F,0.5, kRed+3 , kRed+3);
hist_PrimPhotonFraction_Pt_F_RhoMinus->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Phi,marker_F,0.5, kMagenta , kMagenta);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Delta0,marker_F,0.5, kBlue-5 , kBlue-5);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_DeltaPlus,marker_F,0.5, kGreen , kGreen);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Sigma0,marker_F,0.5, kViolet-5 , kViolet-5);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_KZeroShort,marker_F,0.5, kGreen+4 , kGreen+4);
hist_PrimPhotonFraction_Pt_F_KZeroShort->SetLineStyle(9);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_KZeroLong,marker_F,0.5,  kViolet-6 , kViolet-6);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Lambda,marker_F,0.5, kCyan , kCyan);
hist_PrimPhotonFraction_Pt_F_Lambda->SetLineStyle(9);

auto l_meson_decay_photon_prim_F = new TLegend(0.2, 0.8, 0.9, 0.9);
l_meson_decay_photon_prim_F->SetHeader(Form("#gamma from %s",RapidityBlock[1][2].Data()));
l_meson_decay_photon_prim_F->SetBorderSize(0);
l_meson_decay_photon_prim_F->SetFillStyle(0);
l_meson_decay_photon_prim_F->SetTextSize(TextSize);
l_meson_decay_photon_prim_F->SetNColumns(7);
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Pi0,Form("#pi^{0}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Eta,Form("#eta"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Omega,Form("#omega"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_EtaPrime,Form("#eta'"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Rho0,Form("#rho^{0}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_RhoPlus,Form("#rho^{+}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_RhoMinus,Form("#rho^{-}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Phi,Form("#phi"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Delta0,Form("#Delta^{0}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_DeltaPlus,Form("#Delta^{+}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Sigma0,Form("#Sigma^{0}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_KZeroShort,Form("K^{0}_{S}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_KZeroLong,Form("K^{0}_{L}"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Lambda,Form("#Lambda"),"l");


hist_PrimPhotonFraction_Pt_F_Pi0->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);
hist_PrimPhotonFraction_Pt_F_Pi0->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);

hist_PrimPhotonFraction_Pt_F_Pi0->Draw(" C HIST ");
hist_PrimPhotonFraction_Pt_F_All_Rebin->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Eta->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Omega->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_EtaPrime->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Rho0->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_RhoPlus->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_RhoMinus->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Phi->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Delta0->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_DeltaPlus->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Sigma0->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_KZeroShort->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_KZeroLong->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Lambda->Draw(" C HIST SAME ");

ltb_general_Additional_text->Draw("SAME");

l_meson_decay_photon_prim_F->Draw("SAME");

gPad->Modified();

c_meson_decay_photon_prim_F->SaveAs("./meson_decay_photon_prim_F.png");
c_meson_decay_photon_prim_F->Close();




}