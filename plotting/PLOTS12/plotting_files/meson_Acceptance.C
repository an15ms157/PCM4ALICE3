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

void meson_Acceptance(){

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

bool SWITCH_write_to_file = TRUE ;

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/PbPb/PbPb_100event_perfile/ana_pTcut_withft3_check.root";
gSystem->Exec("mkdir ./meson_Acceptance");
gSystem->cd("./meson_Acceptance");

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
plot_minPt = 0.05;
plot_maxPt = 5.0;
plot_minY = 0.1;
plot_maxY = 5.0;

//Pi0

TH2D * histRapPt_ALL_Pi0_F          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH2D * histRapPt_ALL_Pi0_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * histRapPt_ALL_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * histRapPt_ALL_Pi0_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");

histRapPt_ALL_Pi0_F->Sumw2();
histRapPt_ALL_Pi0_F_GG->Sumw2();
histRapPt_ALL_Pi0_B->Sumw2();
histRapPt_ALL_Pi0_B_GG->Sumw2();



// Eta: 
TH2D * histRapPt_ALL_Eta_F          = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");
TH2D * histRapPt_ALL_Eta_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH2D * histRapPt_ALL_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");
TH2D * histRapPt_ALL_Eta_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");

histRapPt_ALL_Eta_F->Sumw2();
histRapPt_ALL_Eta_F_GG->Sumw2();
histRapPt_ALL_Eta_B->Sumw2();
histRapPt_ALL_Eta_B_GG->Sumw2();





/////////////////      Meson Acceptance Combined plot    ///////////

TCanvas* c_meson_Acceptance_combined = new TCanvas("c_meson_Acceptance_combined","c_meson_Acceptance_combined",0,0,600,600);
DrawGammaCanvasSettings( c_meson_Acceptance_combined, 0.1, 0.05, 0.1, 0.1);

c_meson_Acceptance_combined->SetLogy();  

                                    // ProjectionY("histPt_ALL_rap_B_low1_to_low2_Eta",bin_etaB_low1,bin_etaB_low2); 

// PROJECTION Y:
TH1 * histPt_ALL_Pi0_B    = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_Pi0_B"); 
TH1 * histPt_ALL_Pi0_B_GG    = histRapPt_ALL_Pi0_B_GG->ProjectionY("histPt_ALL_Pi0_B_GG"); 
TH1 * histPt_ALL_Pi0_F    = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_Pi0_F"); 
TH1 * histPt_ALL_Pi0_F_GG = histRapPt_ALL_Pi0_F_GG->ProjectionY("histPt_ALL_Pi0_F_GG"); 

TH1 * histPt_ALL_Eta_B    = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_Eta_B"); 
TH1 * histPt_ALL_Eta_B_GG = histRapPt_ALL_Eta_B_GG->ProjectionY("histPt_ALL_Eta_B_GG");
TH1 * histPt_ALL_Eta_F    = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_Eta_F"); 
TH1 * histPt_ALL_Eta_F_GG = histRapPt_ALL_Eta_F_GG->ProjectionY("histPt_ALL_Eta_F_GG");



// REBINNING 
TH1F* histPt_ALL_Pi0_B_Rebin     = (TH1F*) histPt_ALL_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Pi0_B_GG_Rebin     = (TH1F*) histPt_ALL_Pi0_B_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Pi0_F_Rebin     = (TH1F*) histPt_ALL_Pi0_F->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Pi0_F_GG_Rebin     = (TH1F*) histPt_ALL_Pi0_F_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_F_Rebin",&pt_bin_proj_fine[0]);


TH1F* histPt_ALL_Eta_B_Rebin     = (TH1F*) histPt_ALL_Eta_B->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Eta_B_GG_Rebin     = (TH1F*) histPt_ALL_Eta_B_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Eta_F_Rebin     = (TH1F*) histPt_ALL_Eta_F->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Eta_F_GG_Rebin  = (TH1F*) histPt_ALL_Eta_F_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_F_Rebin",&pt_bin_proj_fine[0]);


// DIVIDE BY BIN WIDTH 
DivideTH1ByBinWidth(histPt_ALL_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Pi0_B_GG_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Pi0_F_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Pi0_F_GG_Rebin);

DivideTH1ByBinWidth(histPt_ALL_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Eta_B_GG_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Eta_F_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Eta_F_GG_Rebin);


//CLONE FOR RATIO
TH1F* histPt_Acceptance_Pi0_B  = (TH1F*) histPt_ALL_Pi0_B_Rebin->Clone("histPt_Acceptance_Pi0_B");
TH1F* histPt_Acceptance_Pi0_F  = (TH1F*) histPt_ALL_Pi0_F_Rebin->Clone("histPt_Acceptance_Pi0_F");
TH1F* histPt_Acceptance_Eta_B  = (TH1F*) histPt_ALL_Eta_B_Rebin->Clone("histPt_Acceptance_Eta_B");
TH1F* histPt_Acceptance_Eta_F  = (TH1F*) histPt_ALL_Eta_F_Rebin->Clone("histPt_Acceptance_Eta_F");

//RATIO
histPt_Acceptance_Pi0_B->Divide(histPt_ALL_Pi0_B_GG_Rebin, histPt_ALL_Pi0_B_Rebin, 1,1,"B");
histPt_Acceptance_Eta_B->Divide(histPt_ALL_Eta_B_GG_Rebin, histPt_ALL_Eta_B_Rebin, 1,1,"B");
histPt_Acceptance_Pi0_F->Divide(histPt_ALL_Pi0_F_GG_Rebin, histPt_ALL_Pi0_F_Rebin, 1,1,"B");
histPt_Acceptance_Eta_F->Divide(histPt_ALL_Eta_F_GG_Rebin, histPt_ALL_Eta_F_Rebin, 1,1,"B");


// STYLE
SetStyleHistoTH1ForGraphs(histPt_Acceptance_Pi0_B, p_T.Data(), "Acceptance * BR (counts)", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

DrawGammaSetMarker(histPt_Acceptance_Pi0_B,marker_B,marker_size, Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(histPt_Acceptance_Pi0_F,marker_F,marker_size, Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(histPt_Acceptance_Eta_B,marker_B,marker_size, Eta_marker_color , Eta_marker_color);
DrawGammaSetMarker(histPt_Acceptance_Eta_F,marker_F,marker_size, Eta_marker_color , Eta_marker_color);


// DRAW:
histPt_Acceptance_Pi0_B->Draw("E1"); 
histPt_Acceptance_Pi0_F->Draw("E1, SAME"); 
histPt_Acceptance_Eta_B->Draw("E1, SAME"); 
histPt_Acceptance_Eta_F->Draw("E1, SAME"); 

//LABELING
histPt_Acceptance_Pi0_B->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
histPt_Acceptance_Pi0_B->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);
/*
auto l_mesonAcc = new TLegend(0.7, 0.65, 0.9, 0.8);
l_mesonAcc->SetHeader("");
l_mesonAcc->SetBorderSize(0);
l_mesonAcc->SetFillStyle(0);
l_mesonAcc->SetTextSize(TextSize);
l_mesonAcc->AddEntry(histPt_Acceptance_Pi0_B,"#pi^{0} :  0<|y|<1.3 ","p");
l_mesonAcc->AddEntry(histPt_Acceptance_Pi0_F,"#pi^{0} :  1.75<|y|<4.0 ","p");
l_mesonAcc->AddEntry(histPt_Acceptance_Eta_B,"#eta  :  0<|y|<1.3 ","p");
l_mesonAcc->AddEntry(histPt_Acceptance_Eta_F,"#eta  :  1.75<|y|<4.0 ","p");
l_mesonAcc->Draw("SAME");
*/
auto l_meson_Acceptance_combined = new TLegend(0.6, 0.65, 0.9, 0.85);
l_meson_Acceptance_combined->SetHeader("Accptance across rapidities");
l_meson_Acceptance_combined->SetBorderSize(0);
l_meson_Acceptance_combined->SetFillStyle(0);
l_meson_Acceptance_combined->SetTextSize(TextSize);
l_meson_Acceptance_combined->AddEntry(histPt_Acceptance_Pi0_B,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_Acceptance_combined->AddEntry(histPt_Acceptance_Pi0_F,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_meson_Acceptance_combined->AddEntry(histPt_Acceptance_Eta_B,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_Acceptance_combined->AddEntry(histPt_Acceptance_Eta_F,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_meson_Acceptance_combined->Draw("SAME");

SetStyleTLatex( ltb_general_Additional_text, 0.03,4);
ltb_general_Additional_text->Draw("SAME");

c_meson_Acceptance_combined->SaveAs("./Acceptance_meson_ALL.png");
c_meson_Acceptance_combined->Close();





if (SWITCH_write_to_file){
const char *outputFile = "../ALICE3_significance_input.root"; // merge output files after analysis was run to keep file size moderate
auto fout = TFile::Open(outputFile, "UPDATE");
//TFile *outputfile = TFile::Open("../../ALICE3_significance_input.root","UPDATE");
fout->cd();
fout->mkdir(Form("%s",fcollisionSystem.Data()));
fout->cd(Form("%s",fcollisionSystem.Data()));

histPt_Acceptance_Pi0_B->SetName("histPt_Acceptance_Pi0_B");
histPt_Acceptance_Pi0_B->Write();

histPt_Acceptance_Pi0_B->GetXaxis()->SetTitle(p_T.Data());
histPt_Acceptance_Pi0_B->GetYaxis()->SetTitle("#Acceptance");
histPt_Acceptance_Pi0_B->GetXaxis()->SetRangeUser(0, plot_maxPt);
//histPt_Acceptance_Pi0_B->GetYaxis()->SetRangeUser(1e-5, 1e5);

histPt_Acceptance_Pi0_F->SetName("histPt_Acceptance_Pi0_F");
histPt_Acceptance_Pi0_F->Write();

histPt_Acceptance_Eta_B->SetName("histPt_Acceptance_Eta_B");
histPt_Acceptance_Eta_B->Write();

histPt_Acceptance_Eta_F->SetName("histPt_Acceptance_Eta_F");
histPt_Acceptance_Eta_F->Write();

fout->Close();
}

//gSystem->cd("../../");

}