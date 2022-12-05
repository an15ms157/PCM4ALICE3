#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"

#include "./headers/ALICE3_setup.h"

void meson_NetEfficiency(){

gSystem->Exec("mkdir meson_NetEffeciency");
gSystem->Exec("cd meson_NetEffeciency");



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

bool SWITCH_write_to_file = TRUE ;

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/PbPb/PbPb_100event_perfile/ana_pTcut_withft3_check.root";
gSystem->Exec("mkdir ./meson_NetEffeciency");
gSystem->cd("./meson_NetEffeciency");


switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{

    fcollisionSystem = "PbPb";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
}

// INPUT CONDITIONS:
plot_minPt = 0.01;
plot_maxPt = 5.0;
plot_minY = 0.0000001;
plot_maxY = 0.45;



///////////////  Acceptance*BR*efficiency at different rapidity PLOT    ///////////////

/*


///////////////  Pi0 Effiiency at different Forward rapidity PLOT    ///////////////

TCanvas* c_eff_Pi0 = new TCanvas("c_eff_Pi0","c_eff_Pi0",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c_eff_Pi0, 0.3, 0.02, 0.02, 0.16);
c_eff_Pi0->Divide(2,1);
c_eff_Pi0->cd(1)->SetLogy();  
c_eff_Pi0->cd(1);


//WITH MOMENTUM SMEARING

TH2D * histRapPt_ALL_Pi0_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_SmearedP");
TH2D * histRapPt_REC_Pi0_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec_SmearedP");

TH2D * histRapPt_ALL_Eta_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_SmearedP");
TH2D * histRapPt_REC_Eta_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");

histRapPt_ALL_Pi0_F_SmearedP->Sumw2();
histRapPt_REC_Pi0_F_SmearedP->Sumw2();
histRapPt_ALL_Eta_F_SmearedP->Sumw2();
histRapPt_REC_Eta_F_SmearedP->Sumw2();

TAxis *xaxis_F_Pi0 = histRapPt_ALL_Pi0_F_SmearedP->GetXaxis();
Int_t bin_eta_F_low1 = xaxis_F_Pi0->FindBin(eta_F_low1 + 0.0001);
Int_t bin_eta_F_low2 = xaxis_F_Pi0->FindBin(eta_F_low2 - 0.0001);
Int_t bin_eta_F_high1 = xaxis_F_Pi0->FindBin(eta_F_high1 + 0.0001);
Int_t bin_eta_F_high2 = xaxis_F_Pi0->FindBin(eta_F_high2 - 0.0001);
Int_t bin_eta_F_mid1 = xaxis_F_Pi0->FindBin(eta_F_mid1 + 0.0001);
Int_t bin_eta_F_mid2 = xaxis_F_Pi0->FindBin(eta_F_mid2 - 0.0001);

TH1 * histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP",bin_eta_F_low1,bin_eta_F_low2); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP",bin_eta_F_high1,bin_eta_F_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP",bin_eta_F_mid1,bin_eta_F_mid2); 

TH1 * histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP",bin_eta_F_low1,bin_eta_F_low2); 
TH1 * histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP",bin_eta_F_high1,bin_eta_F_high2); 
TH1 * histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP",bin_eta_F_mid1,bin_eta_F_mid2); 

TH1 * histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP",bin_eta_F_low1,bin_eta_F_low2); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP",bin_eta_F_high1,bin_eta_F_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP",bin_eta_F_mid1,bin_eta_F_mid2); 

TH1 * histPt_REC_rap_F_low1_to_low2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_low1_to_low2_Eta_SmearedP",bin_eta_F_low1,bin_eta_F_low2); 
TH1 * histPt_REC_rap_F_high1_to_high2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_high1_to_high2_Eta_SmearedP",bin_eta_F_high1,bin_eta_F_high2); 
TH1 * histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP",bin_eta_F_mid1,bin_eta_F_mid2); 

histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_F_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin);

DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin);
//RATIO
TH1F* histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP");
histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP->Divide(histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP");
histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP->Divide(histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP");
histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->Divide(histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin, 1,1,"B");

TH1F* histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP");
histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP->Divide(histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP");
histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP->Divide(histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP");
histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->Divide(histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin, 1,1,"B");

histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->Sumw2();

// Labelling //
SetStyleHistoTH1ForGraphs(histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP, "pT (GeV)", "Efficiency*BR*Acceptance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP->GetYaxis()->SetRangeUser(0.0001,.01);
histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP->GetXaxis()->SetRangeUser(0.0,5.0);

// CHECKER LABELING //
//DrawGammaSetMarker(histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP,25,1.0, kRed+3 , kRed+3);
histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->Draw("E1");
DrawGammaSetMarker(histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP,26,1.0, kRed , kRed);
histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP,20,1.0, kRed , kRed);
histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP->Draw("SAME,P"); 

//DrawGammaSetMarker(histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP,25,1.0, kGreen+3 , kGreen+3);
histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->Draw("SAME,E1");
DrawGammaSetMarker(histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP,26,1.0, kGreen+3 , kGreen+3);
histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP,20,1.0, kGreen+3 , kGreen+3);
histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP->Draw("SAME,P"); 


auto mesonRec_BR_Acc_F = new TLegend(0.6, 0.15, 0.8, 0.35);
mesonRec_BR_Acc_F->SetHeader("");
mesonRec_BR_Acc_F->SetBorderSize(0);
mesonRec_BR_Acc_F->SetFillStyle(0);
mesonRec_BR_Acc_F->SetTextSize(TextSize);
mesonRec_BR_Acc_F->AddEntry(histPt_AccBrREC_rap_F_low1_to_low2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",eta_F_low1,eta_F_low2));
mesonRec_BR_Acc_F->AddEntry(histPt_AccBrREC_rap_F_high1_to_high2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",eta_F_high1,eta_F_high2));
mesonRec_BR_Acc_F->AddEntry(histPt_AccBrREC_rap_F_low1_to_low2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",eta_F_low1,eta_F_low2));
mesonRec_BR_Acc_F->AddEntry(histPt_AccBrREC_rap_F_high1_to_high2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",eta_F_high1,eta_F_high2));
mesonRec_BR_Acc_F->AddEntry(histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",eta_F_mid1,eta_F_mid2));
mesonRec_BR_Acc_F->AddEntry(histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",eta_F_mid1,eta_F_mid2));
//mesonRec_BR_Acc_F->AddEntry(histPt_Acceptance_rap_F_low_plus_high_Pi0,Form("#pi^{0} : %.2f < |y| < %.2f",eta_F_high1,eta_F_high2));
//mesonRec_BR_Acc_F->AddEntry(histPt_Acceptance_rap_F_low_plus_high_Eta,Form("#eta : %.2f < |y| < %.2f",eta_F_high1,eta_F_high2));
mesonRec_BR_Acc_F->Draw("SAME");

TLatex *lt_mesonAcc_F_a = new TLatex(0.65,0.35,"Forward region");
SetStyleTLatex( lt_mesonAcc_F_a, 0.03,4);
lt_mesonAcc_F_a->Draw("SAME");

SetStyleTLatex( lt_mesonAcc_F_b, 0.03,4);
lt_mesonAcc_F_b->Draw("SAME");





c_eff_Pi0->cd(2)->SetLogy();  
c_eff_Pi0->cd(2);

//WITH MOMENTUM SMEARING

TH2D * histRapPt_ALL_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_SmearedP");
TH2D * histRapPt_REC_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");

TH2D * histRapPt_ALL_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_SmearedP");
TH2D * histRapPt_REC_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");

histRapPt_ALL_Pi0_B_SmearedP->Sumw2();
histRapPt_REC_Pi0_B_SmearedP->Sumw2();
histRapPt_ALL_Eta_B_SmearedP->Sumw2();
histRapPt_REC_Eta_B_SmearedP->Sumw2();

TAxis *xaxis_B_Pi0 = histRapPt_ALL_Pi0_B_SmearedP->GetXaxis();
Int_t bin_eta_B_low1 = xaxis_B_Pi0->FindBin(eta_B_low1 + 0.0001);
Int_t bin_eta_B_low2 = xaxis_B_Pi0->FindBin(eta_B_low2 - 0.0001);
Int_t bin_eta_B_high1 = xaxis_B_Pi0->FindBin(eta_B_high1 + 0.0001);
Int_t bin_eta_B_high2 = xaxis_B_Pi0->FindBin(eta_B_high2 - 0.0001);
Int_t bin_eta_B_mid1 = xaxis_B_Pi0->FindBin(eta_B_mid1 + 0.0001);
Int_t bin_eta_B_mid2 = xaxis_B_Pi0->FindBin(eta_B_mid2 - 0.0001);


TH1 * histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP",bin_eta_B_low1,bin_eta_B_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP",bin_eta_B_high1,bin_eta_B_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP",bin_eta_B_mid1,bin_eta_B_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP",bin_eta_B_low1,bin_eta_B_low2); 
TH1 * histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP",bin_eta_B_high1,bin_eta_B_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP",bin_eta_B_mid1,bin_eta_B_mid2); 

TH1 * histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP",bin_eta_B_low1,bin_eta_B_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP",bin_eta_B_high1,bin_eta_B_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP",bin_eta_B_mid1,bin_eta_B_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_low1_to_low2_Eta_SmearedP",bin_eta_B_low1,bin_eta_B_low2); 
TH1 * histPt_REC_rap_B_high1_to_high2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_high1_to_high2_Eta_SmearedP",bin_eta_B_high1,bin_eta_B_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP",bin_eta_B_mid1,bin_eta_B_mid2); 

histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin);

DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin);

//RATIO
TH1F* histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP");
histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP->Divide(histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP");
histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->Divide(histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP");
histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP->Divide(histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin, 1,1,"B");

TH1F* histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP");
histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP->Divide(histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP");
histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->Divide(histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Clone("histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP");
histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP->Divide(histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin, 1,1,"B");

histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP->Sumw2();

// Labelling //
SetStyleHistoTH1ForGraphs(histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP, "pT (GeV)", "Efficiency*BR*Acceptance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP->GetYaxis()->SetRangeUser(0.00001,.001);
histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP->GetXaxis()->SetRangeUser(0.0,5.0);

// CHECKER LABELING //
//DrawGammaSetMarker(histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP,25,1.0, kRed+3 , kRed+3);
//histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP->Draw("E1");
DrawGammaSetMarker(histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP,26,1.0, kRed , kRed);
histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP,20,1.0, kRed , kRed);
histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->Draw("SAME,P"); 

//DrawGammaSetMarker(histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP,25,1.0, kGreen+3 , kGreen+3);
//histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP->Draw("SAME,E1");
DrawGammaSetMarker(histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP,26,1.0, kGreen+3 , kGreen+3);
histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP,20,1.0, kGreen+3 , kGreen+3);
histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->Draw("SAME,P"); 


auto mesonRec_BR_Acc_B = new TLegend(0.6, 0.15, 0.8, 0.35);
mesonRec_BR_Acc_B->SetHeader("");
mesonRec_BR_Acc_B->SetBorderSize(0);
mesonRec_BR_Acc_B->SetFillStyle(0);
mesonRec_BR_Acc_B->SetTextSize(TextSize);
mesonRec_BR_Acc_B->AddEntry(histPt_AccBrREC_rap_B_low1_to_low2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",eta_B_low1,eta_B_low2));
mesonRec_BR_Acc_B->AddEntry(histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",eta_B_high1,eta_B_high2));
mesonRec_BR_Acc_B->AddEntry(histPt_AccBrREC_rap_B_low1_to_low2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",eta_B_low1,eta_B_low2));
mesonRec_BR_Acc_B->AddEntry(histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",eta_B_high1,eta_B_high2));
//mesonRec_BR_Acc_B->AddEntry(histPt_AccBrREC_rap_B_mid1_to_mid2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",eta_B_mid1,eta_B_mid2));
//mesonRec_BR_Acc_B->AddEntry(histPt_AccBrREC_rap_B_mid1_to_mid2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",eta_B_mid1,eta_B_mid2));
//mesonRec_BR_Acc_B->AddEntry(histPt_Acceptance_rap_B_low_plus_high_Pi0,Form("#pi^{0} : %.2f < |y| < %.2f",eta_B_high1,eta_B_high2));
//mesonRec_BR_Acc_B->AddEntry(histPt_Acceptance_rap_B_low_plus_high_Eta,Form("#eta : %.2f < |y| < %.2f",eta_B_high1,eta_B_high2));
mesonRec_BR_Acc_B->Draw("SAME");

TLatex *lt_mesonAcc_B_a = new TLatex(0.65,0.35,"Barrel region");
SetStyleTLatex( lt_mesonAcc_B_a, 0.03,4);
lt_mesonAcc_B_a->Draw("SAME");

SetStyleTLatex( lt_mesonAcc_B_b, 0.03,4);
lt_mesonAcc_B_b->Draw("SAME");

c_eff_Pi0->Update();

c_eff_Pi0->SaveAs("./hAccBR_REC.png");

c_eff_Pi0->Close();

const char *outputFile = "../../ALICE3_significance_input.root"; // merge output files after analysis was run to keep file size moderate
auto fout = TFile::Open(outputFile, "UPDATE");
//TFile *outputfile = TFile::Open("../../ALICE3_significance_input.root","UPDATE");
fout->cd();
fout->mkdir(colli_Sys);
fout->cd(colli_Sys);

histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->GetXaxis()->SetTitle("pT (GeV/c)");
histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->GetYaxis()->SetTitle("Acc*BR*RecEff");
histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->SetName(Form("histPt_AccBrREC_rap_F_%0.2f_to_%0.2f_Pi0_SmearedP",eta_F_mid1,eta_F_mid2));
histPt_AccBrREC_rap_F_mid1_to_mid2_Pi0_SmearedP->Write();

histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->GetXaxis()->SetTitle("pT (GeV/c)");
histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->GetYaxis()->SetTitle("Acc*BR*RecEff");
histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->SetName(Form("histPt_AccBrREC_rap_F_%0.2f_to_%0.2f_Eta_SmearedP",eta_F_mid1,eta_F_mid2));
histPt_AccBrREC_rap_F_mid1_to_mid2_Eta_SmearedP->Write();

histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->GetXaxis()->SetTitle("pT (GeV/c)");
histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->GetYaxis()->SetTitle("Acc*BR*RecEff");
histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->SetName(Form("histPt_AccBrREC_rap_B_%0.2f_to_%0.2f_Pi0_SmearedP",eta_B_high1,eta_B_high2));
histPt_AccBrREC_rap_B_high1_to_high2_Pi0_SmearedP->Write();

histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->GetXaxis()->SetTitle("pT (GeV/c)");
histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->GetYaxis()->SetTitle("Acc*BR*RecEff");
histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->SetName(Form("histPt_AccBrREC_rap_B_%0.2f_to_%0.2f_Eta_SmearedP",eta_B_high1,eta_B_high2));
histPt_AccBrREC_rap_B_high1_to_high2_Eta_SmearedP->Write();

fout->Close();



*/


///////////////  Acceptance*BR*efficiency combined PLOT    ///////////////

TCanvas* c_meson_NetEffeciency = new TCanvas("c_meson_NetEffeciency","c_meson_NetEffeciency",600,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_NetEffeciency, 0.1, 0.05, 0.1, 0.1);
//c_meson_NetEffeciency->Divide(2,1);
c_meson_NetEffeciency->SetLogy();  

//Barrel
TH2D * histRapPt_All_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * histRapPt_All_Pi0_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH2D * histRapPt_REC_Pi0_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");

TH1 * histPt_All_Pi0_B    = histRapPt_All_Pi0_B->ProjectionY("histPt_ALL_Pi0_B"); 
TH1 * histPt_All_Pi0_B_GG    = histRapPt_All_Pi0_B_GG->ProjectionY("histPt_ALL_Pi0_B_GG"); 
TH1 * histPt_REC_Pi0_B_GG    = histRapPt_REC_Pi0_B_GG->ProjectionY("histPt_REC_Pi0_B_GG"); 

TH2D * histRapPt_All_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");
TH2D * histRapPt_All_Eta_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH2D * histRapPt_REC_Eta_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");

TH1 * histPt_All_Eta_B    = histRapPt_All_Eta_B->ProjectionY("histPt_ALL_Eta_B"); 
TH1 * histPt_All_Eta_B_GG = histRapPt_All_Eta_B_GG->ProjectionY("histPt_ALL_Eta_B_GG");
TH1 * histPt_REC_Eta_B_GG    = histRapPt_REC_Eta_B_GG->ProjectionY("histPt_REC_Eta_B_GG"); 

//Forward
TH2D * histRapPt_All_Pi0_F          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH2D * histRapPt_All_Pi0_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * histRapPt_REC_Pi0_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");

TH1 * histPt_All_Pi0_F    = histRapPt_All_Pi0_F->ProjectionY("histPt_ALL_Pi0_F"); 
TH1 * histPt_All_Pi0_F_GG = histRapPt_All_Pi0_F_GG->ProjectionY("histPt_ALL_Pi0_F_GG"); 
TH1 * histPt_REC_Pi0_F_GG = histRapPt_REC_Pi0_F_GG->ProjectionY("histPt_REC_Pi0_F_GG"); 

TH2D * histRapPt_All_Eta_F          = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");
TH2D * histRapPt_All_Eta_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH2D * histRapPt_REC_Eta_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");

TH1 * histPt_All_Eta_F    = histRapPt_All_Eta_F->ProjectionY("histPt_ALL_Eta_F"); 
TH1 * histPt_All_Eta_F_GG = histRapPt_All_Eta_F_GG->ProjectionY("histPt_ALL_Eta_F_GG");
TH1 * histPt_REC_Eta_F_GG = histRapPt_REC_Eta_F_GG->ProjectionY("histPt_REC_Eta_F_GG"); 



TH1F* histPt_All_Pi0_B_Rebin     = (TH1F*) histPt_All_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_All_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_Pi0_B_GG_Rebin     = (TH1F*) histPt_All_Pi0_B_GG->Rebin(nbinspt_proj_fine,"histPt_All_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_Pi0_B_GG_Rebin     = (TH1F*) histPt_REC_Pi0_B_GG->Rebin(nbinspt_proj_fine,"histPt_REC_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_All_Pi0_B_GG_Rebin);
DivideTH1ByBinWidth(histPt_REC_Pi0_B_GG_Rebin);

TH1F* histPt_All_Eta_B_Rebin     = (TH1F*) histPt_All_Eta_B->Rebin(nbinspt_proj_fine,"histPt_All_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_Eta_B_GG_Rebin     = (TH1F*) histPt_All_Eta_B_GG->Rebin(nbinspt_proj_fine,"histPt_All_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_Eta_B_GG_Rebin     = (TH1F*) histPt_REC_Eta_B_GG->Rebin(nbinspt_proj_fine,"histPt_REC_Eta_B_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_All_Eta_B_GG_Rebin);
DivideTH1ByBinWidth(histPt_REC_Eta_B_GG_Rebin);


TH1F* histPt_All_Pi0_F_Rebin     = (TH1F*) histPt_All_Pi0_F->Rebin(nbinspt_proj_fine,"histPt_All_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_Pi0_F_GG_Rebin     = (TH1F*) histPt_All_Pi0_F_GG->Rebin(nbinspt_proj_fine,"histPt_All_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_Pi0_F_GG_Rebin     = (TH1F*) histPt_REC_Pi0_F_GG->Rebin(nbinspt_proj_fine,"histPt_REC_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_Pi0_F_Rebin);
DivideTH1ByBinWidth(histPt_All_Pi0_F_GG_Rebin);
DivideTH1ByBinWidth(histPt_REC_Pi0_F_GG_Rebin);

TH1F* histPt_All_Eta_F_Rebin     = (TH1F*) histPt_All_Eta_F->Rebin(nbinspt_proj_fine,"histPt_All_Eta_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_Eta_F_GG_Rebin  = (TH1F*) histPt_All_Eta_F_GG->Rebin(nbinspt_proj_fine,"histPt_All_Eta_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_Eta_F_GG_Rebin  = (TH1F*) histPt_REC_Eta_F_GG->Rebin(nbinspt_proj_fine,"histPt_REC_Eta_F_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_Eta_F_Rebin);
DivideTH1ByBinWidth(histPt_All_Eta_F_GG_Rebin);
DivideTH1ByBinWidth(histPt_REC_Eta_F_GG_Rebin);



//RATIO
TH1F* histPt_Acceptance_Pi0_B  = (TH1F*) histPt_All_Pi0_B_Rebin->Clone("histPt_Acceptance_Pi0_B");
histPt_Acceptance_Pi0_B->Divide(histPt_All_Pi0_B_GG_Rebin, histPt_All_Pi0_B_Rebin, 1,1,"B");
TH1F* histPt_Efficiency_Pi0_B  = (TH1F*) histPt_All_Pi0_B_Rebin->Clone("histPt_Efficiency_Pi0_B");
histPt_Efficiency_Pi0_B->Divide(histPt_REC_Pi0_B_GG_Rebin, histPt_All_Pi0_B_GG_Rebin, 1,1,"B");
TH1F* histPt_Eff_BR_Acc_Pi0_B  = (TH1F*) histPt_All_Pi0_B_Rebin->Clone("histPt_Eff_BR_Acc_Pi0_B");
histPt_Eff_BR_Acc_Pi0_B->Divide(histPt_REC_Pi0_B_GG_Rebin, histPt_All_Pi0_B_Rebin, 1,1,"B");

TH1F* histPt_Acceptance_Eta_B  = (TH1F*) histPt_All_Eta_B_Rebin->Clone("histPt_Acceptance_Eta_B");
histPt_Acceptance_Eta_B->Divide(histPt_All_Eta_B_GG_Rebin, histPt_All_Eta_B_Rebin, 1,1,"B");
TH1F* histPt_Efficiency_Eta_B  = (TH1F*) histPt_All_Eta_B_Rebin->Clone("histPt_Efficiency_Eta_B");
histPt_Efficiency_Eta_B->Divide(histPt_REC_Eta_B_GG_Rebin, histPt_All_Eta_B_GG_Rebin, 1,1,"B");
TH1F* histPt_Eff_BR_Acc_Eta_B  = (TH1F*) histPt_All_Eta_B_Rebin->Clone("histPt_Eff_BR_Acc_Eta_B");
histPt_Eff_BR_Acc_Eta_B->Divide(histPt_REC_Eta_B_GG_Rebin, histPt_All_Eta_B_Rebin, 1,1,"B");

TH1F* histPt_Acceptance_Pi0_F  = (TH1F*) histPt_All_Pi0_F_Rebin->Clone("histPt_Acceptance_Pi0_F");
histPt_Acceptance_Pi0_F->Divide(histPt_All_Pi0_F_GG_Rebin, histPt_All_Pi0_F_Rebin, 1,1,"B");
TH1F* histPt_Efficiency_Pi0_F  = (TH1F*) histPt_All_Pi0_F_Rebin->Clone("histPt_Efficiency_Pi0_F");
histPt_Efficiency_Pi0_F->Divide(histPt_REC_Pi0_F_GG_Rebin, histPt_All_Pi0_F_GG_Rebin, 1,1,"B");
TH1F* histPt_Eff_BR_Acc_Pi0_F  = (TH1F*) histPt_All_Pi0_F_Rebin->Clone("histPt_Eff_BR_Acc_Pi0_F");
histPt_Eff_BR_Acc_Pi0_F->Divide(histPt_REC_Pi0_F_GG_Rebin, histPt_All_Pi0_F_Rebin, 1,1,"B");

TH1F* histPt_Acceptance_Eta_F  = (TH1F*) histPt_All_Eta_F_Rebin->Clone("histPt_Acceptance_Eta_F");
histPt_Acceptance_Eta_F->Divide(histPt_All_Eta_F_GG_Rebin, histPt_All_Eta_F_Rebin, 1,1,"B");
TH1F* histPt_Efficiency_Eta_F  = (TH1F*) histPt_All_Eta_F_Rebin->Clone("histPt_Efficiency_Eta_F");
histPt_Efficiency_Eta_F->Divide(histPt_REC_Eta_F_GG_Rebin, histPt_All_Eta_F_GG_Rebin, 1,1,"B");
TH1F* histPt_Eff_BR_Acc_Eta_F  = (TH1F*) histPt_All_Eta_F_Rebin->Clone("histPt_Eff_BR_Acc_Eta_F");
histPt_Eff_BR_Acc_Eta_F->Divide(histPt_REC_Eta_F_GG_Rebin, histPt_All_Eta_F_Rebin, 1,1,"B");

SetStyleHistoTH1ForGraphs(histPt_Eff_BR_Acc_Pi0_F, p_T.Data(), "acc. #times BR #times p_{conv} #times #varepsilon_{reco} ", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title,LabelOffsetX,LabelOffsetY);
DrawGammaSetMarker(histPt_Eff_BR_Acc_Pi0_B,marker_B,1.0,  Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(histPt_Eff_BR_Acc_Pi0_F,marker_F,1.0,Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(histPt_Eff_BR_Acc_Eta_B,marker_B,1.0, Eta_marker_color , Eta_marker_color);
DrawGammaSetMarker(histPt_Eff_BR_Acc_Eta_F,marker_F,1.0,Eta_marker_color , Eta_marker_color);

//LABELING
histPt_Eff_BR_Acc_Pi0_F->GetYaxis()->SetRangeUser(plot_minY,plot_maxY);
histPt_Eff_BR_Acc_Pi0_F->GetXaxis()->SetRangeUser(plot_minPt,plot_maxPt);
histPt_Eff_BR_Acc_Pi0_F->Draw(" E1");
histPt_Eff_BR_Acc_Pi0_B->Draw("SAME E1");
histPt_Eff_BR_Acc_Eta_B->Draw("SAME E1");
histPt_Eff_BR_Acc_Eta_F->Draw("SAME E1");

auto l_mesonRec_BR_Acc = new TLegend(0.5,0.2, 0.7, 0.4);
l_mesonRec_BR_Acc->SetHeader("");
l_mesonRec_BR_Acc->SetBorderSize(0);
l_mesonRec_BR_Acc->SetFillStyle(0);
l_mesonRec_BR_Acc->SetTextSize(TextSize);
l_mesonRec_BR_Acc->AddEntry(histPt_Eff_BR_Acc_Pi0_B,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_mesonRec_BR_Acc->AddEntry(histPt_Eff_BR_Acc_Pi0_F,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_mesonRec_BR_Acc->AddEntry(histPt_Eff_BR_Acc_Eta_B,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_mesonRec_BR_Acc->AddEntry(histPt_Eff_BR_Acc_Eta_F,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_mesonRec_BR_Acc->Draw("SAME");


SetStyleTLatex( ltb_general_Additional_text, 0.03,4);
ltb_general_Additional_text->Draw("SAME");
c_meson_NetEffeciency->SaveAs("./meson_NetEffeciency.png");
c_meson_NetEffeciency->Close();


if (SWITCH_write_to_file){

    const char *outputFile = "../ALICE3_significance_input.root"; // merge output files after analysis was run to keep file size moderate
    auto fout = TFile::Open(outputFile, "UPDATE");

    fout->cd();
    fout->mkdir(fcollisionSystem.Data());
    fout->cd(fcollisionSystem.Data());

    histPt_Eff_BR_Acc_Pi0_F->GetXaxis()->SetTitle(p_T.Data());
    histPt_Eff_BR_Acc_Pi0_F->GetYaxis()->SetTitle("Acc*BR*RecEff");
    histPt_Eff_BR_Acc_Pi0_F->SetName(Form("histPt_AccBrREC_rap_F_%0.2f_to_%0.2f_Pi0_SmearedP",Rap_F_all1,Rap_F_all2));
    histPt_Eff_BR_Acc_Pi0_F->Write();

    histPt_Eff_BR_Acc_Eta_F->GetXaxis()->SetTitle(p_T.Data());
    histPt_Eff_BR_Acc_Eta_F->GetYaxis()->SetTitle("Acc*BR*RecEff");
    histPt_Eff_BR_Acc_Eta_F->SetName(Form("histPt_AccBrREC_rap_F_%0.2f_to_%0.2f_Eta_SmearedP",Rap_F_all1,Rap_F_all2));
    histPt_Eff_BR_Acc_Eta_F->Write();

    histPt_Eff_BR_Acc_Pi0_B->GetXaxis()->SetTitle(p_T.Data());
    histPt_Eff_BR_Acc_Pi0_B->GetYaxis()->SetTitle("Acc*BR*RecEff");
    histPt_Eff_BR_Acc_Pi0_B->SetName(Form("histPt_AccBrREC_rap_B_%0.2f_to_%0.2f_Pi0_SmearedP",Rap_B_all1,Rap_B_all2));
    histPt_Eff_BR_Acc_Pi0_B->Write();

    histPt_Eff_BR_Acc_Eta_B->GetXaxis()->SetTitle(p_T.Data());
    histPt_Eff_BR_Acc_Eta_B->GetYaxis()->SetTitle("Acc*BR*RecEff");
    histPt_Eff_BR_Acc_Eta_B->SetName(Form("histPt_AccBrREC_rap_B_%0.2f_to_%0.2f_Eta_SmearedP",Rap_B_all1,Rap_B_all2));
    histPt_Eff_BR_Acc_Eta_B->Write();
    fout->Close();
    }

}