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
void meson_significance(){
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms o


Int_t collisionSystem = 1 ;//  pp = 0 || PbPb = 1; 

TFile * fileRec;
TLatex *lt_meson_significance_F_b;
TLatex *lt_meson_significance_B_b;
double_t Nevent_run5_and_run6;
const double_t Crosssection = 7.8;

fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/plots/plotting_files/ALICE3_significance_input.root");


switch(collisionSystem){
    case 0:{
    cout << "pp system"<< endl;    
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/plots/plotting_files/ALICE3_significance_input.root");
    lt_meson_significance_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    lt_meson_significance_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec("mkdir meson_significance/pp");
    gSystem->cd("./meson_significance/pp");
    Nevent_run5_and_run6 = 18*1e15;


        break;
    }
    case 1:{
    cout << "PbPb system"<< endl;
        //TFile * fileRec = new TFile("./ana_withft3.root");
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/plots/plotting_files/ALICE3_significance_input.root");
    lt_meson_significance_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    lt_meson_significance_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec("mkdir meson_significance/PbPb");
    gSystem->cd("./meson_significance/PbPb");
    Nevent_run5_and_run6 = 35*1e9;

        break;
    }
}

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.03;
Double_t TextSize_title=0.04;
Double_t TextSize_latex=20;
Double_t LabelOffsetLog=-0.015;


Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;


Double_t etaF_low1 = 1.75;
Double_t etaF_low2 = 3;
Double_t etaF_high1 = 3.0;
Double_t etaF_high2 = 4.0;
Double_t etaF_mid1 = 1.75;
Double_t etaF_mid2 = 4.0;


Double_t etaB_low1   = 0.0;
Double_t etaB_low2   = 0.8;
Double_t etaB_high1  = 0.;
Double_t etaB_high2  = 1.3;
Double_t etaB_mid1  = 0.8;
Double_t etaB_mid2  = 1.3;


///////////////////////////////////          Pi0             //////////////////////////////////////////

TH1F * hist_dNdy_Pi0_F                  = (TH1F*) fileRec->Get("PbPb/histPt_Signal_dNdy_rap_F_1.75_to_4.00_Pi0_Rebin");
TH1F * hist_AccBrRec_Pi0_F              = (TH1F*) fileRec->Get("pp/histPt_AccBrREC_rap_F_1.75_to_4.00_Pi0_SmearedP");
TH1F * hist_BackgroundPerEvent_Pi0_F    = (TH1F*) fileRec->Get("PbPb/BackgroundPerEvent_Pi0_F");
TH1F * hist_SignalToBackground_Pi0_F    = (TH1F*) fileRec->Get("PbPb/Ratio_signalToBackgroundround_Pi0_F");

TH1F*  hist_meson_yield_Pi0_F            = new TH1F("hist_meson_yield_Pi0_F","hist_meson_yield_Pi0_F",nbinspt_proj_fine,pt_bin_proj_fine);

TH1F * hist_dNdy_Pi0_B                  = (TH1F*) fileRec->Get("PbPb/histPt_Signal_dNdy_rap_B_0.00_to_1.30_Pi0_Rebin");
TH1F * hist_AccBrRec_Pi0_B              = (TH1F*) fileRec->Get("pp/histPt_AccBrREC_rap_B_0.00_to_1.30_Pi0_SmearedP");
TH1F * hist_BackgroundPerEvent_Pi0_B    = (TH1F*) fileRec->Get("PbPb/BackgroundPerEvent_Pi0_B");
TH1F * hist_SignalToBackground_Pi0_B    = (TH1F*) fileRec->Get("PbPb/Ratio_signalToBackgroundround_Pi0_B");

TH1F*  hist_meson_yield_Pi0_B            = new TH1F("hist_meson_yield_Pi0_B","hist_meson_yield_Pi0_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_dNdy_Pi0_F->Sumw2();
hist_AccBrRec_Pi0_F->Sumw2();
hist_BackgroundPerEvent_Pi0_F->Sumw2();
hist_meson_yield_Pi0_F->Sumw2();

hist_dNdy_Pi0_B->Sumw2();
hist_AccBrRec_Pi0_B->Sumw2();
hist_BackgroundPerEvent_Pi0_B->Sumw2();
hist_meson_yield_Pi0_B->Sumw2();



hist_BackgroundPerEvent_Pi0_F->Scale(Crosssection*Nevent_run5_and_run6);
hist_BackgroundPerEvent_Pi0_B->Scale(Crosssection*Nevent_run5_and_run6);
*hist_meson_yield_Pi0_F                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Pi0_F)*(*hist_dNdy_Pi0_F);
*hist_meson_yield_Pi0_B                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Pi0_B)*(*hist_dNdy_Pi0_B);



////////////////////////     Forward       //////////////////////////
TCanvas* c_meson_significance_Pi0_F = new TCanvas("c_meson_significance_Pi0_F","c_meson_significance_Pi0_F",0,0,600,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_significance_Pi0_F, 0.1, 0.05, 0.1, 0.1);
c_meson_significance_Pi0_F->Divide(2,1);
c_meson_significance_Pi0_F->cd(1)->SetLogy();  
c_meson_significance_Pi0_F->cd(1);

// Labelling //
SetStyleHistoTH1ForGraphs(hist_meson_yield_Pi0_F, "p_{T} (GeV/c)", "meson yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

// CHECKER LABELING //

auto l_meson_significance_Pi0_F = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_Pi0_F->SetHeader("Forward");
l_meson_significance_Pi0_F->SetBorderSize(0);
l_meson_significance_Pi0_F->SetFillStyle(0);
l_meson_significance_Pi0_F->SetTextSize(TextSize);
l_meson_significance_Pi0_F->AddEntry(hist_meson_yield_Pi0_F,"Pi0 signal ");
l_meson_significance_Pi0_F->AddEntry(hist_BackgroundPerEvent_Pi0_F,"Background");

DrawGammaSetMarker(hist_meson_yield_Pi0_F,8,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_meson_yield_Pi0_F,27,1.0, kGreen+4 , kGreen+4);
hist_BackgroundPerEvent_Pi0_F->GetYaxis()->SetRangeUser(1e7, 2e13);

hist_BackgroundPerEvent_Pi0_F->Draw("E1");
hist_meson_yield_Pi0_F->Draw("E1,SAME");
l_meson_significance_Pi0_F->Draw("SAME");



c_meson_significance_Pi0_F->cd(2);
TH1F* hist_Background_AND_SignalPerEvent_Pi0_F            = new TH1F("hist_BackgroundPerEvent_Pi0_F","hist_BackgroundPerEvent_Pi0_F",nbinspt_proj_fine,pt_bin_proj_fine);
TH1F* hist_Significance_PerEvent_Pi0_F                    = new TH1F("hist_Significance_PerEvent_Pi0_F","hist_Significance_PerEvent_Pi0_F",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Pi0_F->Add(hist_meson_yield_Pi0_F,hist_BackgroundPerEvent_Pi0_F,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Pi0_F->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Pi0_F->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Pi0_F->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Pi0_F->SetBinError(bin, 0);
}
   hist_Significance_PerEvent_Pi0_F->Divide(hist_meson_yield_Pi0_F,hist_Background_AND_SignalPerEvent_Pi0_F,1,1 );

c_meson_significance_Pi0_F->cd(2)->SetLogy();  
SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Pi0_F, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

hist_Significance_PerEvent_Pi0_F->Draw("E1");



////////////////////////     Barrel       //////////////////////////
TCanvas* c_meson_significance_Pi0_B = new TCanvas("c_meson_significance_Pi0_B","c_meson_significance_Pi0_B",0,0,600,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_significance_Pi0_B, 0.1, 0.05, 0.1, 0.1);
c_meson_significance_Pi0_B->Divide(2,1);
c_meson_significance_Pi0_B->cd(1)->SetLogy();  
c_meson_significance_Pi0_B->cd(1);
//c_meson_significance_Pi0_F->SetLogx();  

// Labelling //
SetStyleHistoTH1ForGraphs(hist_meson_yield_Pi0_B, "p_{T} (GeV/c)", "meson yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

// CHECKER LABELING //

auto l_meson_significance_Pi0_B = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_Pi0_B->SetHeader("Forward");
l_meson_significance_Pi0_B->SetBorderSize(0);
l_meson_significance_Pi0_B->SetFillStyle(0);
l_meson_significance_Pi0_B->SetTextSize(TextSize);
l_meson_significance_Pi0_B->AddEntry(hist_meson_yield_Pi0_B,"Pi0 signal ");
l_meson_significance_Pi0_B->AddEntry(hist_BackgroundPerEvent_Pi0_B,"Background");

DrawGammaSetMarker(hist_meson_yield_Pi0_B,8,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_meson_yield_Pi0_B,27,1.0, kGreen+4 , kGreen+4);
hist_BackgroundPerEvent_Pi0_B->GetYaxis()->SetRangeUser(1e7, 2e13);

hist_BackgroundPerEvent_Pi0_B->Draw("E1");
hist_meson_yield_Pi0_B->Draw("E1,SAME");
l_meson_significance_Pi0_B->Draw("SAME");



c_meson_significance_Pi0_B->cd(2);
TH1F* hist_Background_AND_SignalPerEvent_Pi0_B            = new TH1F("hist_BackgroundPerEvent_Pi0_B","hist_BackgroundPerEvent_Pi0_B",nbinspt_proj_fine,pt_bin_proj_fine);
TH1F* hist_Significance_PerEvent_Pi0_B                    = new TH1F("hist_Significance_PerEvent_Pi0_B","hist_Significance_PerEvent_Pi0_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Pi0_B->Add(hist_meson_yield_Pi0_B,hist_BackgroundPerEvent_Pi0_B,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Pi0_B->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Pi0_B->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Pi0_B->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Pi0_B->SetBinError(bin, 0);

}
   hist_Significance_PerEvent_Pi0_B->Divide(hist_meson_yield_Pi0_B,hist_Background_AND_SignalPerEvent_Pi0_B,1,1 );

c_meson_significance_Pi0_B->cd(2)->SetLogy();  
SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Pi0_B, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

hist_Significance_PerEvent_Pi0_B->Draw("E1");










///////////////////////////////////          Eta             //////////////////////////////////////////

TH1F * hist_dNdy_Eta_F                  = (TH1F*) fileRec->Get("PbPb/histPt_Signal_dNdy_rap_F_1.75_to_4.00_Eta_Rebin");
TH1F * hist_AccBrRec_Eta_F              = (TH1F*) fileRec->Get("pp/histPt_AccBrREC_rap_F_1.75_to_4.00_Eta_SmearedP");
TH1F * hist_BackgroundPerEvent_Eta_F    = (TH1F*) fileRec->Get("PbPb/BackgroundPerEvent_Eta_F");
TH1F * hist_SignalToBackground_Eta_F    = (TH1F*) fileRec->Get("PbPb/Ratio_signalToBackgroundround_Eta_F");

TH1F*  hist_meson_yield_Eta_F            = new TH1F("hist_meson_yield_Eta_F","hist_meson_yield_Eta_F",nbinspt_proj_fine,pt_bin_proj_fine);


TH1F * hist_dNdy_Eta_B                  = (TH1F*) fileRec->Get("PbPb/histPt_Signal_dNdy_rap_B_0.00_to_1.30_Eta_Rebin");
TH1F * hist_AccBrRec_Eta_B              = (TH1F*) fileRec->Get("pp/histPt_AccBrREC_rap_B_0.00_to_1.30_Eta_SmearedP");
TH1F * hist_BackgroundPerEvent_Eta_B    = (TH1F*) fileRec->Get("PbPb/BackgroundPerEvent_Eta_B");
TH1F * hist_SignalToBackground_Eta_B    = (TH1F*) fileRec->Get("PbPb/Ratio_signalToBackgroundround_Eta_B");

TH1F*  hist_meson_yield_Eta_B            = new TH1F("hist_meson_yield_Eta_B","hist_meson_yield_Eta_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_dNdy_Eta_F->Sumw2();
hist_AccBrRec_Eta_F->Sumw2();
hist_BackgroundPerEvent_Eta_F->Sumw2();
hist_meson_yield_Eta_F->Sumw2();

hist_dNdy_Eta_B->Sumw2();
hist_AccBrRec_Eta_B->Sumw2();
hist_BackgroundPerEvent_Eta_B->Sumw2();
hist_meson_yield_Eta_B->Sumw2();



hist_BackgroundPerEvent_Eta_F->Scale(Crosssection*Nevent_run5_and_run6);
hist_BackgroundPerEvent_Eta_B->Scale(Crosssection*Nevent_run5_and_run6);
*hist_meson_yield_Eta_F                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Eta_F)*(*hist_dNdy_Eta_F);
*hist_meson_yield_Eta_B                 = (Crosssection)*(Nevent_run5_and_run6)*(*hist_AccBrRec_Eta_B)*(*hist_dNdy_Eta_B);



////////////////////////     Forward       //////////////////////////
TCanvas* c_meson_significance_Eta_F = new TCanvas("c_meson_significance_Eta_F","c_meson_significance_Eta_F",0,0,600,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_significance_Eta_F, 0.1, 0.05, 0.1, 0.1);
c_meson_significance_Eta_F->Divide(2,1);
c_meson_significance_Eta_F->cd(1)->SetLogy();  
c_meson_significance_Eta_F->cd(1);

// Labelling //
SetStyleHistoTH1ForGraphs(hist_meson_yield_Eta_F, "p_{T} (GeV/c)", "meson yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

// CHECKER LABELING //

auto l_meson_significance_Eta_F = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_Eta_F->SetHeader("Forward");
l_meson_significance_Eta_F->SetBorderSize(0);
l_meson_significance_Eta_F->SetFillStyle(0);
l_meson_significance_Eta_F->SetTextSize(TextSize);
l_meson_significance_Eta_F->AddEntry(hist_meson_yield_Eta_F,"Eta signal ");
l_meson_significance_Eta_F->AddEntry(hist_BackgroundPerEvent_Eta_F,"Background");

DrawGammaSetMarker(hist_meson_yield_Eta_F,8,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_meson_yield_Eta_F,27,1.0, kGreen+4 , kGreen+4);
hist_BackgroundPerEvent_Eta_F->GetYaxis()->SetRangeUser(1e7, 2e13);
hist_BackgroundPerEvent_Eta_F->Draw("E1");
hist_meson_yield_Eta_F->Draw("E1,SAME");
l_meson_significance_Eta_F->Draw("SAME");


c_meson_significance_Eta_F->cd(2);
TH1F* hist_Background_AND_SignalPerEvent_Eta_F            = new TH1F("hist_BackgroundPerEvent_Eta_F","hist_BackgroundPerEvent_Eta_F",nbinspt_proj_fine,pt_bin_proj_fine);
TH1F* hist_Significance_PerEvent_Eta_F                    = new TH1F("hist_Significance_PerEvent_Eta_F","hist_Significance_PerEvent_Eta_F",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Eta_F->Add(hist_meson_yield_Eta_F,hist_BackgroundPerEvent_Eta_F,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Eta_F->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Eta_F->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Eta_F->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Eta_F->SetBinError(bin, 0);

}
   hist_Significance_PerEvent_Eta_F->Divide(hist_meson_yield_Eta_F,hist_Background_AND_SignalPerEvent_Eta_F,1,1 );

c_meson_significance_Eta_F->cd(2)->SetLogy();  
SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Eta_F, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

hist_Significance_PerEvent_Eta_F->Draw("E1");



////////////////////////     Barrel       //////////////////////////
TCanvas* c_meson_significance_Eta_B = new TCanvas("c_meson_significance_Eta_B","c_meson_significance_Eta_B",0,0,600,600);  // gives the page size
DrawGammaCanvasSettings( c_meson_significance_Eta_B, 0.1, 0.05, 0.1, 0.1);
c_meson_significance_Eta_B->Divide(2,1);
c_meson_significance_Eta_B->cd(1)->SetLogy();  
c_meson_significance_Eta_B->cd(1);
//c_meson_significance_Eta_F->SetLogx();  

// Labelling //
SetStyleHistoTH1ForGraphs(hist_meson_yield_Eta_B, "p_{T} (GeV/c)", "meson yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

// CHECKER LABELING //

auto l_meson_significance_Eta_B = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_Eta_B->SetHeader("Forward");
l_meson_significance_Eta_B->SetBorderSize(0);
l_meson_significance_Eta_B->SetFillStyle(0);
l_meson_significance_Eta_B->SetTextSize(TextSize);
l_meson_significance_Eta_B->AddEntry(hist_meson_yield_Eta_B,"Eta signal ");
l_meson_significance_Eta_B->AddEntry(hist_BackgroundPerEvent_Eta_B,"Background");

DrawGammaSetMarker(hist_meson_yield_Eta_B,8,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_meson_yield_Eta_B,27,1.0, kGreen+4 , kGreen+4);
hist_BackgroundPerEvent_Eta_B->GetYaxis()->SetRangeUser(1e7, 2e13);
hist_BackgroundPerEvent_Eta_B->Draw("E1");
hist_meson_yield_Eta_B->Draw("E1,SAME");
l_meson_significance_Eta_B->Draw("SAME");



c_meson_significance_Eta_B->cd(2);
TH1F* hist_Background_AND_SignalPerEvent_Eta_B            = new TH1F("hist_BackgroundPerEvent_Eta_B","hist_BackgroundPerEvent_Eta_B",nbinspt_proj_fine,pt_bin_proj_fine);
TH1F* hist_Significance_PerEvent_Eta_B                    = new TH1F("hist_Significance_PerEvent_Eta_B","hist_Significance_PerEvent_Eta_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Eta_B->Add(hist_meson_yield_Eta_B,hist_BackgroundPerEvent_Eta_B,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Eta_B->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Eta_B->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Eta_B->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Eta_B->SetBinError(bin, 0);
}
   hist_Significance_PerEvent_Eta_B->Divide(hist_meson_yield_Eta_B,hist_Background_AND_SignalPerEvent_Eta_B,1,1 );

c_meson_significance_Eta_B->cd(2)->SetLogy();  
SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Eta_B, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

hist_Significance_PerEvent_Eta_B->Draw("E1");





                        ////////////////////            Combined significance plot     ///////////////////////////


TCanvas* c_meson_significance_ALL = new TCanvas("c_meson_significance_ALL","c_meson_significance_ALL",0,0,600,600);  // gives the page size
c_meson_significance_ALL->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Pi0_F, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hist_Significance_PerEvent_Pi0_F,24,1.0, kRed , kRed);
DrawGammaSetMarker(hist_Significance_PerEvent_Pi0_B,24,1.0, kGreen+3 , kGreen+3);
DrawGammaSetMarker(hist_Significance_PerEvent_Eta_F,8,1.0, kRed , kRed);
DrawGammaSetMarker(hist_Significance_PerEvent_Eta_B,8,1.0, kGreen+3 , kGreen+3);


auto l_meson_significance_meson_ALL = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_meson_ALL->SetHeader("");
l_meson_significance_meson_ALL->SetBorderSize(0);
l_meson_significance_meson_ALL->SetFillStyle(0);
l_meson_significance_meson_ALL->SetTextSize(TextSize);
l_meson_significance_meson_ALL->AddEntry(hist_Significance_PerEvent_Pi0_F,"#pi^{0} Forward ");
l_meson_significance_meson_ALL->AddEntry(hist_Significance_PerEvent_Pi0_B,"#pi^{0} Barrel");
l_meson_significance_meson_ALL->AddEntry(hist_Significance_PerEvent_Eta_F,"#eta Forward");
l_meson_significance_meson_ALL->AddEntry(hist_Significance_PerEvent_Eta_B,"#eta Barrel");

DrawGammaSetMarker(hist_meson_yield_Eta_B,8,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_meson_yield_Eta_B,27,1.0, kGreen+4 , kGreen+4);
hist_Significance_PerEvent_Pi0_F->GetYaxis()->SetRangeUser(1, 1e6);
hist_Significance_PerEvent_Pi0_F->Draw("E1");
hist_Significance_PerEvent_Pi0_B->Draw("E1,SAME");
hist_Significance_PerEvent_Eta_F->Draw("E1,SAME");
hist_Significance_PerEvent_Eta_B->Draw("E1,SAME");

l_meson_significance_meson_ALL->Draw("SAME");








TCanvas* c_meson_significance_Yield_ALL = new TCanvas("c_meson_significance_Yield_ALL","c_meson_significance_Yield_ALL",0,0,1600,1600);  // gives the page size
c_meson_significance_Yield_ALL->Divide(2,1);
c_meson_significance_Yield_ALL->cd(1);
c_meson_significance_Yield_ALL->cd(1)->SetLogy();  
//c_meson_significance_Yield_ALL->SetLogx();  

SetStyleHistoTH1ForGraphs(hist_BackgroundPerEvent_Pi0_F, "p_{T} (GeV/c)", "Signal Yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

DrawGammaSetMarker(hist_meson_yield_Pi0_F,24,1.0, kRed , kRed);
DrawGammaSetMarker(hist_meson_yield_Pi0_B,8,1.0, kRed , kRed);
DrawGammaSetMarker(hist_meson_yield_Eta_F,24,1.0, kGreen+3 , kGreen+3);
DrawGammaSetMarker(hist_meson_yield_Eta_B,8,1.0, kGreen+3 , kGreen+3);


auto l_meson_significance_meson_Yield_ALL = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_meson_Yield_ALL->SetHeader("");
l_meson_significance_meson_Yield_ALL->SetBorderSize(0);
l_meson_significance_meson_Yield_ALL->SetFillStyle(0);
l_meson_significance_meson_Yield_ALL->SetTextSize(TextSize);
l_meson_significance_meson_Yield_ALL->AddEntry(hist_meson_yield_Pi0_F,"#pi^{0} Forward");
l_meson_significance_meson_Yield_ALL->AddEntry(hist_meson_yield_Pi0_B,"#pi^{0} Barrel");
l_meson_significance_meson_Yield_ALL->AddEntry(hist_meson_yield_Eta_F,"#eta Forward");
l_meson_significance_meson_Yield_ALL->AddEntry(hist_meson_yield_Eta_B,"#eta Barrel");


hist_meson_yield_Pi0_F->GetYaxis()->SetRangeUser(1e6, 1e14);

hist_meson_yield_Pi0_F->Draw("E1");
hist_meson_yield_Pi0_B->Draw("E1,SAME");
hist_meson_yield_Eta_F->Draw("E1,SAME");
hist_meson_yield_Eta_B->Draw("E1,SAME");

l_meson_significance_meson_Yield_ALL->Draw("SAME");




                        ///    SIGNAL TO BACKGROUND   /////

c_meson_significance_Yield_ALL->cd(2);
c_meson_significance_Yield_ALL->cd(2)->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_BackgroundPerEvent_Pi0_F, "p_{T} (GeV/c)", "Background Yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);


DrawGammaSetMarker(hist_BackgroundPerEvent_Pi0_F,25,1.0, kRed , kRed);
DrawGammaSetMarker(hist_BackgroundPerEvent_Pi0_B,21,1.0, kRed , kRed);
DrawGammaSetMarker(hist_BackgroundPerEvent_Eta_F,25,1.0, kGreen+3 , kGreen+3);
DrawGammaSetMarker(hist_BackgroundPerEvent_Eta_B,21,1.0, kGreen+3 , kGreen+3);


auto l_meson_significance_meson_Yield_Ratio = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_significance_meson_Yield_Ratio->SetHeader("");
l_meson_significance_meson_Yield_Ratio->SetBorderSize(0);
l_meson_significance_meson_Yield_Ratio->SetFillStyle(0);
l_meson_significance_meson_Yield_Ratio->SetTextSize(TextSize);
l_meson_significance_meson_Yield_Ratio->AddEntry(hist_BackgroundPerEvent_Pi0_F,"#pi^{0} Forward ");
l_meson_significance_meson_Yield_Ratio->AddEntry(hist_BackgroundPerEvent_Pi0_B,"#pi^{0} Barrel ");
l_meson_significance_meson_Yield_Ratio->AddEntry(hist_BackgroundPerEvent_Eta_F,"#eta Forward  ");
l_meson_significance_meson_Yield_Ratio->AddEntry(hist_BackgroundPerEvent_Eta_B,"#eta Barrel  ");

hist_BackgroundPerEvent_Pi0_F->GetYaxis()->SetRangeUser(1e6, 1e14);

hist_BackgroundPerEvent_Pi0_F->Draw("E1");
hist_BackgroundPerEvent_Pi0_B->Draw("E1,SAME");
hist_BackgroundPerEvent_Eta_F->Draw("E1,SAME");
hist_BackgroundPerEvent_Eta_B->Draw("E1,SAME");

l_meson_significance_meson_Yield_Ratio->Draw("SAME");


}