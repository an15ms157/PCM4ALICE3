#include <string>

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

void meson_Effeciency(){

gSystem->Exec("mkdir meson_Effeciency");
gSystem->Exec("cd meson_Effeciency");



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

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/all_events/pp/ana_pTcut_withft3.root";
gSystem->Exec("mkdir ./meson_Effeciency");
gSystem->cd("./meson_Effeciency");


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


/////////////////      Meson efficiency Combined plot    ///////////
TCanvas* c_meson_Effeciency = new TCanvas("c_meson_Effeciency","c_meson_Effeciency",0,0,600,600);
DrawGammaCanvasSettings( c_meson_Effeciency, 0.1, 0.05, 0.1, 0.1);

c_meson_Effeciency->SetLogy();  

auto l_eff_combined = new TLegend(0.6, 0.15, 0.85, 0.35);
l_eff_combined->SetHeader("#splitline{Effiiencies at different rapidity}{}");
l_eff_combined->SetBorderSize(0);
l_eff_combined->SetFillStyle(0);
l_eff_combined->SetTextSize(TextSize);



//Pi0 B:
TH2D * histRapPt_ALL_Pi0_B = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH2D * histRapPt_ALL_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH2D * histRapPt_REC_Pi0_B = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");
TH2D * histRapPt_REC_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");

histRapPt_ALL_Pi0_B->Sumw2();
histRapPt_ALL_Pi0_B_SmearedP->Sumw2();
histRapPt_REC_Pi0_B->Sumw2();
histRapPt_REC_Pi0_B_SmearedP->Sumw2();

TAxis *xaxis_Pi0_B = histRapPt_ALL_Pi0_B->GetXaxis();
Int_t bin_Rap_B_Pi0_all1 = xaxis_Pi0_B->FindBin(Rap_B_all1 + epsilon);
Int_t bin_Rap_B_Pi0_all2 = xaxis_Pi0_B->FindBin(Rap_B_all2 - epsilon);
 
TH1 * histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_MC_rap_B_all1_to_all2",bin_Rap_B_Pi0_all1,bin_Rap_B_Pi0_all2);  
TH1 * histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP",bin_Rap_B_Pi0_all1,bin_Rap_B_Pi0_all2); 

histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP->Sumw2();

TH1F* histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP_Rebin->Sumw2();

DivideTH1ByBinWidth(histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP_Rebin);

TH1F* histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP");
histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP->Divide(histPt_REC_rap_B_all1_to_all2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_all1_to_all2_Pi0_SmearedP_Rebin, 1,1,"B");
histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP->Sumw2();

SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP, p_T.Data(), "Efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title,LabelOffsetX,LabelOffsetY);
histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP->GetYaxis()->SetRangeUser(plot_minY,plot_maxY);
histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP->GetXaxis()->SetRangeUser(plot_minPt,plot_maxPt);
DrawGammaSetMarker(histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP,marker_B,0.9, Pi0_marker_color , Pi0_marker_color);
histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP->Draw("P");

l_eff_combined->AddEntry(histPt_RATIO_rap_B_all1_to_all2_Pi0_SmearedP,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");






//Pi0 F:
TH2D * histRapPt_ALL_Pi0_F = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * histRapPt_ALL_Pi0_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_SmearedP");
TH2D * histRapPt_REC_Pi0_F = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
TH2D * histRapPt_REC_Pi0_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec_SmearedP");

histRapPt_ALL_Pi0_F->Sumw2();
histRapPt_ALL_Pi0_F_SmearedP->Sumw2();
histRapPt_REC_Pi0_F->Sumw2();
histRapPt_REC_Pi0_F_SmearedP->Sumw2();

TAxis *xaxis_Pi0_F = histRapPt_ALL_Pi0_F->GetXaxis();
Int_t bin_Rap_F_Pi0_all1 = xaxis_Pi0_F->FindBin(Rap_F_all1 + epsilon);
Int_t bin_Rap_F_Pi0_all2 = xaxis_Pi0_F->FindBin(Rap_F_all2 - epsilon);
 
TH1 * histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_MC_rap_F_all1_to_all2",bin_Rap_F_Pi0_all1,bin_Rap_F_Pi0_all2);  
TH1 * histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP",bin_Rap_F_Pi0_all1,bin_Rap_F_Pi0_all2); 

histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP->Sumw2();

TH1F* histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP_Rebin->Sumw2();

DivideTH1ByBinWidth(histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP_Rebin);

TH1F* histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP");
histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP->Divide(histPt_REC_rap_F_all1_to_all2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_all1_to_all2_Pi0_SmearedP_Rebin, 1,1,"B");
histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP->Sumw2();

DrawGammaSetMarker(histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP,marker_F,0.9, Pi0_marker_color , Pi0_marker_color);
histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP->Draw("SAME,P");

l_eff_combined->AddEntry(histPt_RATIO_rap_F_all1_to_all2_Pi0_SmearedP,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");






//Eta B:
TH2D * histRapPt_ALL_Eta_B = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH2D * histRapPt_ALL_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH2D * histRapPt_REC_Eta_B = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");
TH2D * histRapPt_REC_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");

histRapPt_ALL_Eta_B->Sumw2();
histRapPt_ALL_Eta_B_SmearedP->Sumw2();
histRapPt_REC_Eta_B->Sumw2();
histRapPt_REC_Eta_B_SmearedP->Sumw2();

TAxis *xaxis_Eta_B = histRapPt_ALL_Eta_B->GetXaxis();
Int_t bin_Rap_B_Eta_all1 = xaxis_Eta_B->FindBin(Rap_B_all1 + epsilon);
Int_t bin_Rap_B_Eta_all2 = xaxis_Eta_B->FindBin(Rap_B_all2 - epsilon);
 
TH1 * histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_MC_rap_B_all1_to_all2",bin_Rap_B_Eta_all1,bin_Rap_B_Eta_all2);  
TH1 * histPt_REC_rap_B_all1_to_all2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_all1_to_all2_Eta_SmearedP",bin_Rap_B_Eta_all1,bin_Rap_B_Eta_all2); 

histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_all1_to_all2_Eta_SmearedP->Sumw2();

TH1F* histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_all1_to_all2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_all1_to_all2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_all1_to_all2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_all1_to_all2_Eta_SmearedP_Rebin->Sumw2();

DivideTH1ByBinWidth(histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_all1_to_all2_Eta_SmearedP_Rebin);

TH1F* histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_all1_to_all2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP");
histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP->Divide(histPt_REC_rap_B_all1_to_all2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_all1_to_all2_Eta_SmearedP_Rebin, 1,1,"B");
histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP->Sumw2();

DrawGammaSetMarker(histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP,marker_B,0.9, Eta_marker_color , Eta_marker_color);
histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP->Draw("SAME,P");

l_eff_combined->AddEntry(histPt_RATIO_rap_B_all1_to_all2_Eta_SmearedP,Form("%s : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");




//Eta F:
TH2D * histRapPt_ALL_Eta_F = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH2D * histRapPt_ALL_Eta_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_SmearedP");
TH2D * histRapPt_REC_Eta_F = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");
TH2D * histRapPt_REC_Eta_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");

histRapPt_ALL_Eta_F->Sumw2();
histRapPt_ALL_Eta_F_SmearedP->Sumw2();
histRapPt_REC_Eta_F->Sumw2();
histRapPt_REC_Eta_F_SmearedP->Sumw2();

TAxis *xaxis_Eta_F = histRapPt_ALL_Eta_F->GetXaxis();
Int_t bin_Rap_F_Eta_all1 = xaxis_Eta_F->FindBin(Rap_F_all1 + epsilon);
Int_t bin_Rap_F_Eta_all2 = xaxis_Eta_F->FindBin(Rap_F_all2 - epsilon);
 
TH1 * histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_MC_rap_F_all1_to_all2",bin_Rap_F_Eta_all1,bin_Rap_F_Eta_all2);  
TH1 * histPt_REC_rap_F_all1_to_all2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_all1_to_all2_Eta_SmearedP",bin_Rap_F_Eta_all1,bin_Rap_F_Eta_all2); 

histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_all1_to_all2_Eta_SmearedP->Sumw2();

TH1F* histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_all1_to_all2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_all1_to_all2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_all1_to_all2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_all1_to_all2_Eta_SmearedP_Rebin->Sumw2();

DivideTH1ByBinWidth(histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_all1_to_all2_Eta_SmearedP_Rebin);

TH1F* histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_all1_to_all2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP");
histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP->Divide(histPt_REC_rap_F_all1_to_all2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_all1_to_all2_Eta_SmearedP_Rebin, 1,1,"B");
histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP->Sumw2();

DrawGammaSetMarker(histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP,marker_F,0.9, Eta_marker_color , Eta_marker_color);
histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP->Draw("SAME,P");

l_eff_combined->AddEntry(histPt_RATIO_rap_F_all1_to_all2_Eta_SmearedP,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");





l_eff_combined->Draw("SAME");

SetStyleTLatex( ltb_general_Additional_text, 0.03,4);
ltb_general_Additional_text->Draw("SAME");

c_meson_Effeciency->SaveAs("./meson_Effeciency.png");

}