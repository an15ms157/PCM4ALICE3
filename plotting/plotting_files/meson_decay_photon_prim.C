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

void meson_decay_photon_prim(){
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

//TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/latest/pp/ana_pTcut_withft3.root";
TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/latest/PbPb/ana_pTcut_withft3.root";
gSystem->Exec("mkdir ./meson_decay_photon_prim");
gSystem->cd("./meson_decay_photon_prim");


switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.85,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    // INPUT CONDITIONS:
    plot_minPt = 1e-1;
    plot_maxPt = 10;
    plot_minY = 1e-4;
    plot_maxY = 10.;

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

cout<< hist_PrimPhotonPt_B->GetNdivisions();

TH1F* hist_PrimPhotonPt_B_Rebin              = (TH1F*) hist_PrimPhotonPt_B->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_B_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_Pi0_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Pi0_B->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_Pi0_B_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_Eta_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Eta_B->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_Eta_B_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_Omega_B_Rebin        = (TH1F*) hist_PrimPhotonPt_Omega_B->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_Omega_B_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_EtaPrime_B_Rebin     = (TH1F*) hist_PrimPhotonPt_EtaPrime_B->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_EtaPrime_B_Rebin",&pt_bin_proj_rebin[0]);

/*
TH1F* hist_PrimPhotonPt_B_Rebin              = (TH1F*) hist_PrimPhotonPt_B->Rebin(9);
TH1F* hist_PrimPhotonPt_Pi0_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Pi0_B->Rebin(9);
TH1F* hist_PrimPhotonPt_Eta_B_Rebin          = (TH1F*) hist_PrimPhotonPt_Eta_B->Rebin(9);
TH1F* hist_PrimPhotonPt_Omega_B_Rebin        = (TH1F*) hist_PrimPhotonPt_Omega_B->Rebin(9);
TH1F* hist_PrimPhotonPt_EtaPrime_B_Rebin     = (TH1F*) hist_PrimPhotonPt_EtaPrime_B->Rebin(9);
*/

TH1F* hist_PrimPhotonFraction_Pt_B_Pi0             = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Pi0");
TH1F* hist_PrimPhotonFraction_Pt_B_Eta             = (TH1F*) hist_PrimPhotonPt_Eta_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Eta");
TH1F* hist_PrimPhotonFraction_Pt_B_Omega           = (TH1F*) hist_PrimPhotonPt_Omega_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_Omega");
TH1F* hist_PrimPhotonFraction_Pt_B_EtaPrime        = (TH1F*) hist_PrimPhotonPt_EtaPrime_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_EtaPrime");


TH1F* hist_PrimPhotonFraction_Pt_B_All_Rebin = (TH1F*) hist_PrimPhotonPt_Pi0_B_Rebin->Clone("hist_PrimPhotonFraction_Pt_B_All_Rebin");
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Eta_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_Omega_B_Rebin,1);
hist_PrimPhotonFraction_Pt_B_All_Rebin->Add(hist_PrimPhotonPt_EtaPrime_B_Rebin,1);


hist_PrimPhotonFraction_Pt_B_All_Rebin->Divide(hist_PrimPhotonFraction_Pt_B_All_Rebin, hist_PrimPhotonPt_B_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Pi0->Divide(hist_PrimPhotonPt_Pi0_B_Rebin, hist_PrimPhotonPt_B_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Eta->Divide(hist_PrimPhotonPt_Eta_B_Rebin, hist_PrimPhotonPt_B_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_Omega->Divide(hist_PrimPhotonPt_Omega_B_Rebin, hist_PrimPhotonPt_B_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_B_EtaPrime->Divide(hist_PrimPhotonPt_EtaPrime_B_Rebin, hist_PrimPhotonPt_B_Rebin, 1,1,"B");




TCanvas* c_meson_decay_photon_prim_B = new TCanvas("c_meson_decay_photon_prim_B","c_meson_decay_photon_prim_B",0,0,500,600);  // gives the page size
c_meson_decay_photon_prim_B->SetLogy();  
c_meson_decay_photon_prim_B->SetLogx();  

SetStyleHistoTH1ForGraphs(hist_PrimPhotonFraction_Pt_B_Pi0, p_T.Data() , "#gamma_{meson}/#gamma_{all primary gamma}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Pi0,marker_B,0.5, kRed , kRed);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_All_Rebin,marker_B,0.5, kBlack , kBlack);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Eta,marker_B,0.5, kBlue , kBlue);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_Omega,marker_B,0.5, kYellow-3 , kYellow-3);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_B_EtaPrime,marker_B,0.5, kOrange , kOrange);

auto l_meson_decay_photon_prim_B = new TLegend(0.65, 0.75, 0.85, 0.9);
l_meson_decay_photon_prim_B->SetHeader("Decay Photons from sources");
l_meson_decay_photon_prim_B->SetBorderSize(0);
l_meson_decay_photon_prim_B->SetFillStyle(0);
l_meson_decay_photon_prim_B->SetTextSize(TextSize);
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_All_Rebin,Form("Sum"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Pi0,Form("#pi^0"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Eta,Form("#eta"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_Omega,Form("#omega"),"l");
l_meson_decay_photon_prim_B->AddEntry(hist_PrimPhotonFraction_Pt_B_EtaPrime,Form("#eta'"),"l");


hist_PrimPhotonFraction_Pt_B_Pi0->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);
hist_PrimPhotonFraction_Pt_B_Pi0->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);

hist_PrimPhotonFraction_Pt_B_Pi0->Draw(" C HIST ");
hist_PrimPhotonFraction_Pt_B_All_Rebin->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Eta->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_Omega->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_B_EtaPrime->Draw(" C HIST SAME ");
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

cout<< hist_PrimPhotonPt_F->GetNdivisions();

TH1F* hist_PrimPhotonPt_F_Rebin              = (TH1F*) hist_PrimPhotonPt_F->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_F_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_Pi0_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Pi0_F->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_Pi0_F_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_Eta_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Eta_F->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_Eta_F_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_Omega_F_Rebin        = (TH1F*) hist_PrimPhotonPt_Omega_F->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_Omega_F_Rebin",&pt_bin_proj_rebin[0]);
TH1F* hist_PrimPhotonPt_EtaPrime_F_Rebin     = (TH1F*) hist_PrimPhotonPt_EtaPrime_F->Rebin(nbinspt_proj_rebin,"hist_PrimPhotonPt_EtaPrime_F_Rebin",&pt_bin_proj_rebin[0]);

/*
TH1F* hist_PrimPhotonPt_F_Rebin              = (TH1F*) hist_PrimPhotonPt_F->Rebin(9);
TH1F* hist_PrimPhotonPt_Pi0_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Pi0_F->Rebin(9);
TH1F* hist_PrimPhotonPt_Eta_F_Rebin          = (TH1F*) hist_PrimPhotonPt_Eta_F->Rebin(9);
TH1F* hist_PrimPhotonPt_Omega_F_Rebin        = (TH1F*) hist_PrimPhotonPt_Omega_F->Rebin(9);
TH1F* hist_PrimPhotonPt_EtaPrime_F_Rebin     = (TH1F*) hist_PrimPhotonPt_EtaPrime_F->Rebin(9);
*/

TH1F* hist_PrimPhotonFraction_Pt_F_Pi0             = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Pi0");
TH1F* hist_PrimPhotonFraction_Pt_F_Eta             = (TH1F*) hist_PrimPhotonPt_Eta_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Eta");
TH1F* hist_PrimPhotonFraction_Pt_F_Omega           = (TH1F*) hist_PrimPhotonPt_Omega_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_Omega");
TH1F* hist_PrimPhotonFraction_Pt_F_EtaPrime        = (TH1F*) hist_PrimPhotonPt_EtaPrime_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_EtaPrime");


TH1F* hist_PrimPhotonFraction_Pt_F_All_Rebin = (TH1F*) hist_PrimPhotonPt_Pi0_F_Rebin->Clone("hist_PrimPhotonFraction_Pt_F_All_Rebin");
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Eta_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_Omega_F_Rebin,1);
hist_PrimPhotonFraction_Pt_F_All_Rebin->Add(hist_PrimPhotonPt_EtaPrime_F_Rebin,1);


hist_PrimPhotonFraction_Pt_F_All_Rebin->Divide(hist_PrimPhotonFraction_Pt_F_All_Rebin, hist_PrimPhotonPt_F_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Pi0->Divide(hist_PrimPhotonPt_Pi0_F_Rebin, hist_PrimPhotonPt_F_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Eta->Divide(hist_PrimPhotonPt_Eta_F_Rebin, hist_PrimPhotonPt_F_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_Omega->Divide(hist_PrimPhotonPt_Omega_F_Rebin, hist_PrimPhotonPt_F_Rebin, 1,1,"B");
hist_PrimPhotonFraction_Pt_F_EtaPrime->Divide(hist_PrimPhotonPt_EtaPrime_F_Rebin, hist_PrimPhotonPt_F_Rebin, 1,1,"B");




TCanvas* c_meson_decay_photon_prim_F = new TCanvas("c_meson_decay_photon_prim_F","c_meson_decay_photon_prim_F",0,0,500,600);  // gives the page size
c_meson_decay_photon_prim_F->SetLogy();  
c_meson_decay_photon_prim_F->SetLogx();  

SetStyleHistoTH1ForGraphs(hist_PrimPhotonFraction_Pt_F_Pi0, p_T.Data() , "#gamma_{meson}/#gamma_{all primary gamma}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Pi0,marker_B,0.5, kRed , kRed);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_All_Rebin,marker_B,0.5, kBlack , kBlack);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Eta,marker_B,0.5, kBlue , kBlue);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_Omega,marker_B,0.5, kYellow-3 , kYellow-3);
DrawGammaSetMarker(hist_PrimPhotonFraction_Pt_F_EtaPrime,marker_B,0.5, kOrange , kOrange);

auto l_meson_decay_photon_prim_F = new TLegend(0.65, 0.75, 0.85, 0.9);
l_meson_decay_photon_prim_F->SetHeader("Decay Photons from sources");
l_meson_decay_photon_prim_F->SetBorderSize(0);
l_meson_decay_photon_prim_F->SetFillStyle(0);
l_meson_decay_photon_prim_F->SetTextSize(TextSize);
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_All_Rebin,Form("Sum"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Pi0,Form("#pi^0"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Eta,Form("#eta"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_Omega,Form("#omega"),"l");
l_meson_decay_photon_prim_F->AddEntry(hist_PrimPhotonFraction_Pt_F_EtaPrime,Form("#eta'"),"l");


hist_PrimPhotonFraction_Pt_F_Pi0->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);
hist_PrimPhotonFraction_Pt_F_Pi0->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);

hist_PrimPhotonFraction_Pt_F_Pi0->Draw(" C HIST ");
hist_PrimPhotonFraction_Pt_F_All_Rebin->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Eta->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_Omega->Draw(" C HIST SAME ");
hist_PrimPhotonFraction_Pt_F_EtaPrime->Draw(" C HIST SAME ");
ltb_general_Additional_text->Draw("SAME");

l_meson_decay_photon_prim_F->Draw("SAME");

gPad->Modified();

c_meson_decay_photon_prim_F->SaveAs("./meson_decay_photon_prim_F.png");
c_meson_decay_photon_prim_F->Close();





}