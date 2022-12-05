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


void meson_signal_AND_background(){
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

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/plotting/plotting_files/ALICE3_significance_input.root";
gSystem->Exec("mkdir ./meson_signal_AND_background");
gSystem->cd("./meson_signal_AND_background");


switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    Nevent_run5_and_run6 = 18*1e15;
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.85,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();

    // INPUT CONDITIONS:
    plot_minPt = 0.0;
    plot_maxPt = 5.0;
    plot_minY = 10e11;
    plot_maxY = 10e18;
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{

    fcollisionSystem = "PbPb";
    Nevent_run5_and_run6 = 35*1e9;
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.85,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
}




SetStyleTLatex( ltb_general_Additional_text, 0.03,4);

///////////////////////////////////          Pi0             //////////////////////////////////////////

TH1F * hist_dNdy_Pi0_F                  = (TH1F*) fileRec->Get(Form("%s/histPt_Signal_dNdy_rap_F_1.75_to_4.00_Pi0_Rebin",fcollisionSystem.Data()));
TH1F * hist_AccBrRec_Pi0_F              = (TH1F*) fileRec->Get(Form("%s/histPt_AccBrREC_rap_F_1.75_to_4.00_Pi0_SmearedP",fcollisionSystem.Data()));
TH1F * hist_BackgroundPerEvent_Pi0_F    = (TH1F*) fileRec->Get(Form("%s/BackgroundPerEvent_Pi0_F",fcollisionSystem.Data()));
TH1F * hist_SignalToBackground_Pi0_F    = (TH1F*) fileRec->Get(Form("%s/Ratio_signalToBackgroundround_Pi0_F",fcollisionSystem.Data()));

TH1F*  hist_meson_yield_Pi0_F            = new TH1F("hist_meson_yield_Pi0_F","hist_meson_yield_Pi0_F",nbinspt_proj_fine,pt_bin_proj_fine);

TH1F * hist_dNdy_Pi0_B                  = (TH1F*) fileRec->Get(Form("%s/histPt_Signal_dNdy_rap_B_0.00_to_1.30_Pi0_Rebin",fcollisionSystem.Data()));
TH1F * hist_AccBrRec_Pi0_B              = (TH1F*) fileRec->Get(Form("%s/histPt_AccBrREC_rap_B_0.00_to_1.30_Pi0_SmearedP",fcollisionSystem.Data()));
TH1F * hist_BackgroundPerEvent_Pi0_B    = (TH1F*) fileRec->Get(Form("%s/BackgroundPerEvent_Pi0_B",fcollisionSystem.Data()));
TH1F * hist_SignalToBackground_Pi0_B    = (TH1F*) fileRec->Get(Form("%s/Ratio_signalToBackgroundround_Pi0_B",fcollisionSystem.Data()));

TH1F*  hist_meson_yield_Pi0_B            = new TH1F("hist_meson_yield_Pi0_B","hist_meson_yield_Pi0_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_dNdy_Pi0_F->Sumw2();
hist_AccBrRec_Pi0_F->Sumw2();
hist_BackgroundPerEvent_Pi0_F->Sumw2();

hist_dNdy_Pi0_B->Sumw2();
hist_AccBrRec_Pi0_B->Sumw2();
hist_BackgroundPerEvent_Pi0_B->Sumw2();

Float_t parameters =  (Crosssection*Nevent_run5_and_run6);

hist_BackgroundPerEvent_Pi0_F->Scale(parameters);
hist_BackgroundPerEvent_Pi0_B->Scale(parameters);

*hist_meson_yield_Pi0_B                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Pi0_B)*(*hist_dNdy_Pi0_B);
*hist_meson_yield_Pi0_F                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Pi0_F)*(*hist_dNdy_Pi0_F);

hist_meson_yield_Pi0_B->Sumw2();
hist_meson_yield_Pi0_F->Sumw2();





///////////////////////////////////          Eta             //////////////////////////////////////////

TH1F * hist_dNdy_Eta_F                  = (TH1F*) fileRec->Get(Form("%s/histPt_Signal_dNdy_rap_F_1.75_to_4.00_Eta_Rebin",fcollisionSystem.Data()));
TH1F * hist_AccBrRec_Eta_F              = (TH1F*) fileRec->Get(Form("%s/histPt_AccBrREC_rap_F_1.75_to_4.00_Eta_SmearedP",fcollisionSystem.Data()));
TH1F * hist_BackgroundPerEvent_Eta_F    = (TH1F*) fileRec->Get(Form("%s/BackgroundPerEvent_Eta_F",fcollisionSystem.Data()));
TH1F * hist_SignalToBackground_Eta_F    = (TH1F*) fileRec->Get(Form("%s/Ratio_signalToBackgroundround_Eta_F",fcollisionSystem.Data()));

TH1F*  hist_meson_yield_Eta_F            = new TH1F("hist_meson_yield_Eta_F","hist_meson_yield_Eta_F",nbinspt_proj_fine,pt_bin_proj_fine);


TH1F * hist_dNdy_Eta_B                  = (TH1F*) fileRec->Get(Form("%s/histPt_Signal_dNdy_rap_B_0.00_to_1.30_Eta_Rebin",fcollisionSystem.Data()));
TH1F * hist_AccBrRec_Eta_B              = (TH1F*) fileRec->Get(Form("%s/histPt_AccBrREC_rap_B_0.00_to_1.30_Eta_SmearedP",fcollisionSystem.Data()));
TH1F * hist_BackgroundPerEvent_Eta_B    = (TH1F*) fileRec->Get(Form("%s/BackgroundPerEvent_Eta_B",fcollisionSystem.Data()));
TH1F * hist_SignalToBackground_Eta_B    = (TH1F*) fileRec->Get(Form("%s/Ratio_signalToBackgroundround_Eta_B",fcollisionSystem.Data()));

TH1F*  hist_meson_yield_Eta_B            = new TH1F("hist_meson_yield_Eta_B","hist_meson_yield_Eta_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_dNdy_Eta_F->Sumw2();
hist_AccBrRec_Eta_F->Sumw2();
hist_BackgroundPerEvent_Eta_F->Sumw2();

hist_dNdy_Eta_B->Sumw2();
hist_AccBrRec_Eta_B->Sumw2();
hist_BackgroundPerEvent_Eta_B->Sumw2();


hist_BackgroundPerEvent_Eta_B->Scale(Crosssection*Nevent_run5_and_run6);
hist_BackgroundPerEvent_Eta_F->Scale(Crosssection*Nevent_run5_and_run6);
*hist_meson_yield_Eta_B                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Eta_B)*(*hist_dNdy_Eta_B);
*hist_meson_yield_Eta_F                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Eta_F)*(*hist_dNdy_Eta_F);

hist_meson_yield_Eta_B->Sumw2();
hist_meson_yield_Eta_F->Sumw2();




                           //////////             BACKGROUND               //////////////

TCanvas* c_meson_background = new TCanvas("c_meson_background","c_meson_background",600,600);  // gives the page size
c_meson_background->SetLogy();  



SetStyleHistoTH1ForGraphs(hist_BackgroundPerEvent_Pi0_B, p_T.Data(), "Background yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);

DrawGammaSetMarker(hist_BackgroundPerEvent_Pi0_B,marker_B,1.0, Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(hist_BackgroundPerEvent_Pi0_F,marker_F,1.0, Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(hist_BackgroundPerEvent_Eta_B,marker_B,1.0, Eta_marker_color , Eta_marker_color);
DrawGammaSetMarker(hist_BackgroundPerEvent_Eta_F,marker_F,1.0, Eta_marker_color , Eta_marker_color);


auto l_meson_background = new TLegend(0.7, 0.65, 0.9, 0.85);
l_meson_background->SetHeader("");
l_meson_background->SetBorderSize(0);
l_meson_background->SetFillStyle(0);
l_meson_background->SetTextSize(TextSize);
l_meson_background->AddEntry(hist_BackgroundPerEvent_Pi0_B,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_background->AddEntry(hist_BackgroundPerEvent_Pi0_F,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_meson_background->AddEntry(hist_BackgroundPerEvent_Eta_B,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_background->AddEntry(hist_BackgroundPerEvent_Eta_F,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_F_all1,Rap_F_all2),"p");

hist_BackgroundPerEvent_Pi0_B->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
hist_BackgroundPerEvent_Pi0_B->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);
hist_BackgroundPerEvent_Pi0_B->Draw("E1");
hist_BackgroundPerEvent_Pi0_F->Draw("SAME,E1");
hist_BackgroundPerEvent_Eta_F->Draw("SAME,E1");
hist_BackgroundPerEvent_Eta_B->Draw("SAME,E1");

l_meson_background->Draw("SAME");
ltb_general_Additional_text->Draw("SAME");

c_meson_background->SaveAs("./meson_background.png");
c_meson_background->Close();  





                           //////////             SIGNAL               //////////////

TCanvas* c_meson_signal = new TCanvas("c_meson_signal","c_meson_signal",600,600);  // gives the page size
c_meson_signal->SetLogy();  
//c_meson_signal->SetLogx();  



SetStyleHistoTH1ForGraphs(hist_meson_yield_Pi0_B, p_T.Data(), "Signal yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);

DrawGammaSetMarker(hist_meson_yield_Pi0_B,marker_B,1.0, Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(hist_meson_yield_Pi0_F,marker_F,1.0, Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(hist_meson_yield_Eta_B,marker_B,1.0, Eta_marker_color , Eta_marker_color);
DrawGammaSetMarker(hist_meson_yield_Eta_F,marker_F,1.0, Eta_marker_color , Eta_marker_color);


auto l_meson_signal = new TLegend(0.7, 0.65, 0.9, 0.85);
l_meson_signal->SetHeader("");
l_meson_signal->SetBorderSize(0);
l_meson_signal->SetFillStyle(0);
l_meson_signal->SetTextSize(TextSize);
l_meson_signal->AddEntry(hist_meson_yield_Pi0_B,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_signal->AddEntry(hist_meson_yield_Pi0_F,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_meson_signal->AddEntry(hist_meson_yield_Eta_B,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_signal->AddEntry(hist_meson_yield_Eta_F,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_F_all1,Rap_F_all2),"p");

hist_meson_yield_Pi0_B->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
hist_meson_yield_Pi0_B->GetYaxis()->SetRangeUser(plot_minY*10e-3, plot_maxY*10e-3);
hist_meson_yield_Pi0_B->Draw("E1");
hist_meson_yield_Pi0_F->Draw("SAME,E1");
hist_meson_yield_Eta_B->Draw("SAME,E1");
hist_meson_yield_Eta_F->Draw("SAME,E1");

l_meson_signal->Draw("SAME");
ltb_general_Additional_text->Draw("SAME");

c_meson_signal->SaveAs("./meson_signal.png");
c_meson_signal->Close();  



}