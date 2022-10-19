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
void meson_significance(){
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms o


Int_t collisionSystem = 1 ;//  pp = 0 || PbPb = 1; 

bool SWITCH_meson_RelUncertainity_ALL      = true;
bool SWITCH_yield_with_fit                 = true;
bool SWITCH_background_with_fit            = true;
bool SWITCH_significance_with_fit          = true;


Double_t pion_mass = 0.134;
Double_t eta_mass = 0.547;

Double_t* fMesonMassPlotRange_Alice3    = nullptr;

fMesonMassPlotRange_Alice3      = new Double_t[2];
fMesonMassPlotRange_Alice3[0]   = 0.00; 
fMesonMassPlotRange_Alice3[1]   = 10.00; 


TFile * fileRec;
TLatex *lt_meson_significance_F_b;
TLatex *lt_meson_significance_B_b;
double_t Nevent_run5_and_run6;
const double_t Crosssection = 7.8;

//fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/plots/plotting_files/ALICE3_significance_input.root");


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
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ALICE3_significance_input.root");
    lt_meson_significance_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{minimum bias Pb-Pb: 5.5 TeV}");
    lt_meson_significance_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{minimum bias Pb-Pb: 5.5 TeV}");
    gSystem->Exec("mkdir meson_significance/PbPb");
    gSystem->cd("./meson_significance/PbPb");
    Nevent_run5_and_run6 = 35*1e9;

        break;
    }
}


double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.025;
Double_t TextSize_title=0.025;
Double_t TextSize_latex=20;
Double_t LabelOffsetX=1.1;
Double_t LabelOffsetY=1.7;



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
TH1F* hist_RelativeUncertainity_Pi0_F                    = new TH1F("hist_RelativeUncertainity_Pi0_F","hist_RelativeUncertainity_Pi0_F",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Pi0_F->Add(hist_meson_yield_Pi0_F,hist_BackgroundPerEvent_Pi0_F,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Pi0_F->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Pi0_F->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Pi0_F->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Pi0_F->SetBinError(bin, 0);
}
   hist_Significance_PerEvent_Pi0_F->Divide(hist_meson_yield_Pi0_F,hist_Background_AND_SignalPerEvent_Pi0_F,1,1 );
   hist_RelativeUncertainity_Pi0_F->Divide(hist_Background_AND_SignalPerEvent_Pi0_F,hist_meson_yield_Pi0_F);

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
TH1F* hist_RelativeUncertainity_Pi0_B                    = new TH1F("hist_RelativeUncertainity_Pi0_B","hist_RelativeUncertainity_Pi0_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Pi0_B->Add(hist_meson_yield_Pi0_B,hist_BackgroundPerEvent_Pi0_B,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Pi0_B->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Pi0_B->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Pi0_B->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Pi0_B->SetBinError(bin, 0);

}
   hist_Significance_PerEvent_Pi0_B->Divide(hist_meson_yield_Pi0_B,hist_Background_AND_SignalPerEvent_Pi0_B,1,1 );
   hist_RelativeUncertainity_Pi0_B->Divide(hist_Background_AND_SignalPerEvent_Pi0_B,hist_meson_yield_Pi0_B);
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
TH1F* hist_RelativeUncertainity_Eta_F                    = new TH1F("hist_RelativeUncertainity_Eta_F","hist_RelativeUncertainity_Eta_F",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Eta_F->Add(hist_meson_yield_Eta_F,hist_BackgroundPerEvent_Eta_F,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Eta_F->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Eta_F->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Eta_F->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Eta_F->SetBinError(bin, 0);

}
   hist_Significance_PerEvent_Eta_F->Divide(hist_meson_yield_Eta_F,hist_Background_AND_SignalPerEvent_Eta_F,1,1 );
   hist_RelativeUncertainity_Eta_F->Divide(hist_Background_AND_SignalPerEvent_Eta_F,hist_meson_yield_Eta_F);

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
SetStyleHistoTH1ForGraphs(hist_meson_yield_Eta_B, "p_{T} (GeV/c)", "meson yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);

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
TH1F* hist_RelativeUncertainity_Eta_B                    = new TH1F("hist_RelativeUncertainity_Eta_B","hist_RelativeUncertainity_Eta_B",nbinspt_proj_fine,pt_bin_proj_fine);

hist_Background_AND_SignalPerEvent_Eta_B->Add(hist_meson_yield_Eta_B,hist_BackgroundPerEvent_Eta_B,1,1);

for (int bin=0;bin<=hist_Background_AND_SignalPerEvent_Eta_B->GetNcells();++bin) {
   hist_Background_AND_SignalPerEvent_Eta_B->SetBinContent(bin, sqrt(hist_Background_AND_SignalPerEvent_Eta_B->GetBinContent(bin)));
   hist_Background_AND_SignalPerEvent_Eta_B->SetBinError(bin, 0);
}
   hist_Significance_PerEvent_Eta_B->Divide(hist_meson_yield_Eta_B,hist_Background_AND_SignalPerEvent_Eta_B,1,1 );
   hist_RelativeUncertainity_Eta_B->Divide(hist_Background_AND_SignalPerEvent_Eta_B,hist_meson_yield_Eta_B);
c_meson_significance_Eta_B->cd(2)->SetLogy();  
SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Eta_B, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);

hist_Significance_PerEvent_Eta_B->Draw("E1");























                        ////////////////////            Combined significance plot     ///////////////////////////


TCanvas* c_meson_significance_ALL = new TCanvas("c_meson_significance_ALL","c_meson_significance_ALL",0,0,600,600);  // gives the page size
c_meson_significance_ALL->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_Significance_PerEvent_Pi0_F, "p_{T} (GeV/c)", "Significance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_Significance_PerEvent_Pi0_F,24,1.0, kRed , kRed);
DrawGammaSetMarker(hist_Significance_PerEvent_Pi0_B,8,1.0, kRed , kRed);
DrawGammaSetMarker(hist_Significance_PerEvent_Eta_F,24,1.0, kGreen+3 , kGreen+3);
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
hist_Significance_PerEvent_Pi0_F->GetXaxis()->SetRangeUser(0.2, 10.);
hist_Significance_PerEvent_Pi0_F->Draw("E1");
hist_Significance_PerEvent_Pi0_B->Draw("E1,SAME");
hist_Significance_PerEvent_Eta_F->Draw("E1,SAME");
hist_Significance_PerEvent_Eta_B->Draw("E1,SAME");

SetStyleTLatex( lt_meson_significance_F_b, 0.03,4);
lt_meson_significance_F_b->Draw("SAME");

l_meson_significance_meson_ALL->Draw("SAME");








TCanvas* c_meson_significance_Yield_ALL = new TCanvas("c_meson_significance_Yield_ALL","c_meson_significance_Yield_ALL",0,0,1600,1600);  // gives the page size
c_meson_significance_Yield_ALL->Divide(2,1);
c_meson_significance_Yield_ALL->cd(1);
c_meson_significance_Yield_ALL->cd(1)->SetLogy();  
//c_meson_significance_Yield_ALL->SetLogx();  

SetStyleHistoTH1ForGraphs(hist_meson_yield_Pi0_F, "p_{T} (GeV/c)", "meson yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);

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


hist_meson_yield_Pi0_F->GetYaxis()->SetRangeUser(1e5, 1e14);

hist_meson_yield_Pi0_F->Draw("E1");
hist_meson_yield_Pi0_B->Draw("E1,SAME");
hist_meson_yield_Eta_F->Draw("E1,SAME");
hist_meson_yield_Eta_B->Draw("E1,SAME");

l_meson_significance_meson_Yield_ALL->Draw("SAME");




                        ///    SIGNAL TO BACKGROUND   /////

c_meson_significance_Yield_ALL->cd(2);
c_meson_significance_Yield_ALL->cd(2)->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_BackgroundPerEvent_Pi0_F, "p_{T} (GeV/c)", "Background yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);


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

hist_BackgroundPerEvent_Pi0_F->GetYaxis()->SetRangeUser(1e5, 1e14);

hist_BackgroundPerEvent_Pi0_F->Draw("E1");
hist_BackgroundPerEvent_Pi0_B->Draw("E1,SAME");
hist_BackgroundPerEvent_Eta_F->Draw("E1,SAME");
hist_BackgroundPerEvent_Eta_B->Draw("E1,SAME");

l_meson_significance_meson_Yield_Ratio->Draw("SAME");







                        ////////////////////            Combined relative error plot comparison     ///////////////////////////


if (SWITCH_meson_RelUncertainity_ALL){

TCanvas* c_meson_RelUncertainity_ALL = new TCanvas("c_meson_RelUncertainity_ALL","c_meson_RelUncertainity_ALL",0,0,600,600);  // gives the page size
c_meson_RelUncertainity_ALL->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_RelativeUncertainity_Pi0_F, "p_{T} (GeV/c)", "Relative Uncertainity (%)", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_RelativeUncertainity_Pi0_F,24,1.0, kRed , kRed);
DrawGammaSetMarker(hist_RelativeUncertainity_Pi0_B,8,1.0, kRed+2 , kRed+2);
DrawGammaSetMarker(hist_RelativeUncertainity_Eta_F,24,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_RelativeUncertainity_Eta_B,8,1.0, kGreen+3 , kGreen+3);

hist_RelativeUncertainity_Pi0_F->Scale(100.);
hist_RelativeUncertainity_Pi0_B->Scale(100.);
hist_RelativeUncertainity_Eta_F->Scale(100.);
hist_RelativeUncertainity_Eta_B->Scale(100.);

auto l_meson_RelUncertainity_ALL = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_RelUncertainity_ALL->SetHeader("");
l_meson_RelUncertainity_ALL->SetBorderSize(0);
l_meson_RelUncertainity_ALL->SetFillStyle(0);
l_meson_RelUncertainity_ALL->SetTextSize(TextSize);

l_meson_RelUncertainity_ALL->AddEntry(hist_RelativeUncertainity_Pi0_F,"#pi^{0} Forward ");
l_meson_RelUncertainity_ALL->AddEntry(hist_RelativeUncertainity_Pi0_B,"#pi^{0} Barrel ");
l_meson_RelUncertainity_ALL->AddEntry(hist_RelativeUncertainity_Eta_F,"#eta Forward ");
l_meson_RelUncertainity_ALL->AddEntry(hist_RelativeUncertainity_Eta_B,"#eta Barrel");

hist_RelativeUncertainity_Pi0_F->GetYaxis()->SetRangeUser(1e-4,1e-2);
hist_RelativeUncertainity_Pi0_F->Draw("E1");
hist_RelativeUncertainity_Pi0_B->Draw("E1,SAME");
hist_RelativeUncertainity_Eta_F->Draw("E1,SAME");
hist_RelativeUncertainity_Eta_B->Draw("E1,SAME");

SetStyleTLatex( lt_meson_significance_F_b, 0.03,4);
lt_meson_significance_F_b->Draw("SAME");

l_meson_RelUncertainity_ALL->Draw("SAME");
c_meson_RelUncertainity_ALL->SaveAs("./c_meson_RelUncertainity_ALL.png");

}




TF1  *  fFitReco_Pi0_F = nullptr;
fFitReco_Pi0_F         = new TF1("fFitReco_Pi0_F",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",pion_mass,pion_mass,pion_mass,pion_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);


TF1  *  fFitReco_Pi0_B = nullptr;
fFitReco_Pi0_B         = new TF1("fFitReco_Pi0_B",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",pion_mass,pion_mass,pion_mass,pion_mass), fMesonMassPlotRange_Alice3[0]+0.2, fMesonMassPlotRange_Alice3[1]);

TF1  *  fFitReco_Eta_F = nullptr;
fFitReco_Eta_F         = new TF1("fFitReco_Eta_F",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",eta_mass,eta_mass,eta_mass,eta_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);

TF1  *  fFitReco_Eta_B = nullptr;
fFitReco_Eta_B         = new TF1("fFitReco_Eta_B",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",eta_mass,eta_mass,eta_mass,eta_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);




                        ////////////////////            Combined relative error plot comparison FIT TSALLIS     ///////////////////////////


if (SWITCH_yield_with_fit){
TH1F* hist_meson_yield_Pi0_F_Fit = (TH1F*) hist_meson_yield_Pi0_F->Clone("Pi0 Forward Yield fit with Tsallis");
TH1F* hist_meson_yield_Eta_F_Fit = (TH1F*) hist_meson_yield_Eta_F->Clone("Eta Forward Yield fit with Tsallis");
TH1F* hist_meson_yield_Pi0_B_Fit = (TH1F*) hist_meson_yield_Pi0_B->Clone("Pi0 Barrel Yield fit with Tsallis");
TH1F* hist_meson_yield_Eta_B_Fit = (TH1F*) hist_meson_yield_Eta_B->Clone("Eta Barrel Yield fit with Tsallis");


//fFitReco->SetParameter(0,mesonAmplitude);
//fFitReco->SetParameter(1,fMesonMassExpect);
fFitReco_Pi0_F->SetNpx(10000);
fFitReco_Pi0_F->SetParameter(2,pion_mass);
fFitReco_Pi0_F->SetParLimits(0,1e5,1e15);
fFitReco_Pi0_F->SetParLimits(1,0.01,1e3);
fFitReco_Pi0_F->SetParLimits(2,pion_mass-.1,pion_mass+.1);
hist_meson_yield_Pi0_F_Fit->Fit(fFitReco_Pi0_F,"QRME");
fFitReco_Pi0_F->SetLineColor(kRed);
fFitReco_Pi0_F->SetLineWidth(1);
fFitReco_Pi0_F->SetLineStyle(2);
//cout << fFitReco_Pi0_F->GetParameter(0)<<"  "<<fFitReco_Pi0_F->GetParameter(1)<<"  "<< fFitReco_Pi0_F->GetParameter(2)<<endl; 


fFitReco_Pi0_B->SetNpx(10000);
fFitReco_Pi0_B->SetParameter(2,eta_mass+.7);// different mass only for better raw yield fit 
fFitReco_Pi0_B->SetParLimits(0,1e5,1e15);
fFitReco_Pi0_B->SetParLimits(1,0.01,1e9);
fFitReco_Pi0_B->SetParLimits(2,eta_mass-.1,eta_mass+.8);
hist_meson_yield_Pi0_B_Fit->Fit(fFitReco_Pi0_B,"QRME");
fFitReco_Pi0_B->SetLineColor(kRed);
fFitReco_Pi0_B->SetLineWidth(1);
fFitReco_Pi0_B->SetLineStyle(1);
//cout << fFitReco_Pi0_B->GetParameter(0)<<"  "<<fFitReco_Pi0_B->GetParameter(1)<<"  "<< fFitReco_Pi0_B->GetParameter(2)<<endl; 


fFitReco_Eta_F->SetNpx(10000);
fFitReco_Eta_F->SetParameter(2,pion_mass);
fFitReco_Eta_F->SetParLimits(0,1e5,1e15);
fFitReco_Eta_F->SetParLimits(1,0.01,1e3);
fFitReco_Eta_F->SetParLimits(2,pion_mass-.1,pion_mass+.1);
hist_meson_yield_Eta_F_Fit->Fit(fFitReco_Eta_F,"QRME");
fFitReco_Eta_F->SetLineColor(kGreen+3);
fFitReco_Eta_F->SetLineWidth(1);
fFitReco_Eta_F->SetLineStyle(2);

fFitReco_Eta_B->SetNpx(10000);
fFitReco_Eta_B->SetParameter(2,eta_mass);
fFitReco_Eta_B->SetParLimits(0,1e5,1e15);
fFitReco_Eta_B->SetParLimits(1,0.01,1e5);
fFitReco_Eta_B->SetParLimits(2,eta_mass-.1,eta_mass+.1);
hist_meson_yield_Eta_B_Fit->Fit(fFitReco_Eta_B,"QRME");
fFitReco_Eta_B->SetLineColor(kGreen+3);
fFitReco_Eta_B->SetLineWidth(1);
fFitReco_Eta_B->SetLineStyle(1);

  cout<< "It breaks after this " <<__LINE__<<endl;

TCanvas* c_meson_yield_fit = new TCanvas("c_meson_yield_fit","c_meson_yield_fit",0,0,600,600);  // gives the page size

c_meson_yield_fit->SetLogy();
fFitReco_Pi0_F->GetYaxis()->SetRangeUser(1e5, 1e15);

fFitReco_Pi0_F->Draw();
fFitReco_Pi0_B->Draw("SAME");
fFitReco_Eta_F->Draw("SAME");
fFitReco_Eta_B->Draw("SAME");
hist_meson_yield_Pi0_F->Draw("E1,SAME");
hist_meson_yield_Pi0_B->Draw("E1,SAME");
hist_meson_yield_Eta_F->Draw("E1,SAME");
hist_meson_yield_Eta_B->Draw("E1,SAME");
l_meson_significance_meson_Yield_ALL->Draw("SAME");

c_meson_yield_fit->SaveAs("./c_meson_yield_fit.png");
c_meson_yield_fit->Close();
}

TH1F* hist_meson_background_Pi0_F_Fit = (TH1F*) hist_BackgroundPerEvent_Pi0_F->Clone("Pi0 Forward Background fit with Tsallis");
TH1F* hist_meson_background_Eta_F_Fit = (TH1F*) hist_BackgroundPerEvent_Eta_F->Clone("Eta Forward Background fit with Tsallis");
TH1F* hist_meson_background_Pi0_B_Fit = (TH1F*) hist_BackgroundPerEvent_Pi0_B->Clone("Pi0 Barrel Background fit with Tsallis");
TH1F* hist_meson_background_Eta_B_Fit = (TH1F*) hist_BackgroundPerEvent_Eta_B->Clone("Eta Barrel Background fit with Tsallis");

TF1  *  fFitReco_Pi0_F_background = nullptr;
fFitReco_Pi0_F_background         = new TF1("fFitReco_Pi0_F_background",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",pion_mass,pion_mass,pion_mass,pion_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);
//fFitReco_Pi0_F_background         = new TF1("fFitReco_Pi0_F_background","[0]+[1]*TMath::Power(x,1)+[2]*TMath::Power(x,2)+[3]*TMath::Power(x,3)", fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);

TF1  *  fFitReco_Pi0_B_background = nullptr;
fFitReco_Pi0_B_background         = new TF1("fFitReco_Pi0_B_background",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x*x*x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",eta_mass,eta_mass,eta_mass,eta_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);

TF1  *  fFitReco_Eta_F_background = nullptr;
fFitReco_Eta_F_background         = new TF1("fFitReco_Eta_F_background",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",eta_mass,eta_mass,eta_mass,eta_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);

TF1  *  fFitReco_Eta_B_background = nullptr;
fFitReco_Eta_B_background         = new TF1("fFitReco_Eta_B_background",Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",eta_mass,eta_mass,eta_mass,eta_mass), fMesonMassPlotRange_Alice3[0], fMesonMassPlotRange_Alice3[1]);


if (SWITCH_background_with_fit){


//fFitReco->SetParameter(0,mesonAmplitude);
//fFitReco->SetParameter(1,fMesonMassExpect);
fFitReco_Pi0_F_background->SetNpx(10000);
fFitReco_Pi0_F_background->SetParameter(2,pion_mass);
fFitReco_Pi0_F_background->SetParLimits(0,1e5,1e15);
fFitReco_Pi0_F_background->SetParLimits(1,0.01,1e3);
fFitReco_Pi0_F_background->SetParLimits(2,pion_mass-.1,pion_mass+.1);
hist_meson_background_Pi0_F_Fit->Fit(fFitReco_Pi0_F_background,"QRME");
fFitReco_Pi0_F_background->SetLineColor(kRed);
fFitReco_Pi0_F_background->SetLineWidth(1);
fFitReco_Pi0_F_background->SetLineStyle(2);
//cout << fFitReco_Pi0_F_background->GetParameter(0)<<"  "<<fFitReco_Pi0_F_background->GetParameter(1)<<"  "<< fFitReco_Pi0_F_background->GetParameter(2)<<endl; 


fFitReco_Pi0_B_background->SetNpx(10000);
fFitReco_Pi0_B_background->SetParameter(2,pion_mass+.1);// different mass only for better raw yield fit 
fFitReco_Pi0_B_background->SetParLimits(0,1e5,1e15);
fFitReco_Pi0_B_background->SetParLimits(1,500,1e4);//fFitReco_Pi0_B_background->SetParLimits(1,0.01,1e3);
fFitReco_Pi0_B_background->SetParLimits(2,pion_mass-.1,pion_mass+.3);
hist_meson_background_Pi0_B_Fit->Fit(fFitReco_Pi0_B_background,"QRME");
fFitReco_Pi0_B_background->SetLineColor(kRed);
fFitReco_Pi0_B_background->SetLineWidth(1);
fFitReco_Pi0_B_background->SetLineStyle(1);
cout << fFitReco_Pi0_B_background->GetParameter(0)<<"  "<<fFitReco_Pi0_B_background->GetParameter(1)<<"  "<< fFitReco_Pi0_B_background->GetParameter(2)<<endl; 


fFitReco_Eta_F_background->SetNpx(10000);
fFitReco_Eta_F_background->SetParameter(2,pion_mass);
fFitReco_Eta_F_background->SetParLimits(0,1e5,1e15);
fFitReco_Eta_F_background->SetParLimits(1,0.01,1e3);
fFitReco_Eta_F_background->SetParLimits(2,pion_mass-.1,pion_mass+.1);
hist_meson_background_Eta_F_Fit->Fit(fFitReco_Eta_F_background,"QRME");
fFitReco_Eta_F_background->SetLineColor(kGreen+3);
fFitReco_Eta_F_background->SetLineWidth(1);
fFitReco_Eta_F_background->SetLineStyle(2);

fFitReco_Eta_B_background->SetNpx(10000);
fFitReco_Eta_B_background->SetParameter(2,eta_mass);
fFitReco_Eta_B_background->SetParLimits(0,1e5,1e15);
fFitReco_Eta_B_background->SetParLimits(1,0.01,1e5);
fFitReco_Eta_B_background->SetParLimits(2,eta_mass-.1,eta_mass+.1);
hist_meson_background_Eta_B_Fit->Fit(fFitReco_Eta_B_background,"QRME");
fFitReco_Eta_B_background->SetLineColor(kGreen+3);
fFitReco_Eta_B_background->SetLineWidth(1);
fFitReco_Eta_B_background->SetLineStyle(1);
cout << fFitReco_Eta_B_background->GetParameter(0)<<"  "<<fFitReco_Eta_B_background->GetParameter(1)<<"  "<< fFitReco_Eta_B_background->GetParameter(2)<<endl; 

  cout<< "It breaks after this " <<__LINE__<<endl;

TCanvas* c_meson_background_fit = new TCanvas("c_meson_background_fit","c_meson_background_fit",0,0,600,600);  // gives the page size

c_meson_background_fit->SetLogy();
fFitReco_Pi0_F_background->GetYaxis()->SetRangeUser(1e7, 2e15);

fFitReco_Pi0_F_background->Draw();
fFitReco_Pi0_B_background->Draw("SAME");
fFitReco_Eta_F_background->Draw("SAME");
fFitReco_Eta_B_background->Draw("SAME");
hist_BackgroundPerEvent_Pi0_F->Draw("E1,SAME");
hist_BackgroundPerEvent_Eta_F->Draw("E1,SAME");
hist_BackgroundPerEvent_Pi0_B->Draw("E1,SAME");
hist_BackgroundPerEvent_Eta_B->Draw("E1,SAME");

auto l_meson_background_fit = new TLegend(0.6, 0.65, 0.8, 0.85);
l_meson_background_fit->SetHeader("");
l_meson_background_fit->SetBorderSize(0);
l_meson_background_fit->SetFillStyle(0);
l_meson_background_fit->SetTextSize(TextSize);
l_meson_background_fit->AddEntry(fFitReco_Pi0_F_background,"#pi^{0} Forward ");
l_meson_background_fit->AddEntry(fFitReco_Pi0_B_background,"#pi^{0} Barrel ");
l_meson_background_fit->AddEntry(fFitReco_Eta_F_background,"#eta Forward  ");
l_meson_background_fit->AddEntry(fFitReco_Eta_B_background,"#eta Barrel  ");
l_meson_background_fit->Draw("SAME");

c_meson_background_fit->SaveAs("./c_meson_background_fit.png");
//c_meson_background_fit->Close();
}



if (SWITCH_significance_with_fit){

TCanvas* c_meson_significance_fit = new TCanvas("c_meson_significance_fit","c_meson_significance_fit",0,0,600,600);  // gives the page size
c_meson_significance_fit->SetLogy();

TString Pi0_F_background_TSallis = Form("[0] / ( 2 * TMath::Pi())*([1]-1.)*([1]-2.) / ([1]*[2]*([1]*[2]+%.10f*([1]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([1]*[2]), -[1])",pion_mass,pion_mass,pion_mass,pion_mass); 
TString Pi0_F_yield_TSallis = Form("[3] / ( 2 * TMath::Pi())*([4]-1.)*([4]-2.) / ([4]*[5]*([4]*[5]+%.10f*([4]-2.)))  * x* TMath::Power(1.+(TMath::Sqrt(x*x+%.10f*%.10f)-%.10f)/([4]*[5]), -[4])",pion_mass,pion_mass,pion_mass,pion_mass);

TString Pi0_F_yield_TSallis_sig = Form("TMath::Sqrt(%s+%s)/%s",Pi0_F_background_TSallis.Data(),Pi0_F_yield_TSallis.Data(),Pi0_F_yield_TSallis.Data());
//TString Pi0_F_yield_TSallis_sig = Form("TMath::Sqrt(%s+%s)/%s",Pi0_F_background_TSallis.Data(),Pi0_F_yield_TSallis.Data(),Pi0_F_yield_TSallis.Data());

//cout << Pi0_F_yield_TSallis_sig.Data()<< endl;

TF1  *  fFitReco_Pi0_F_relerr = nullptr;
fFitReco_Pi0_F_relerr         = new TF1("fFitReco_Pi0_F_relerr",Pi0_F_yield_TSallis_sig.Data(), 0, 10.);
fFitReco_Pi0_F_relerr->SetNpx(10000);
//fFitReco_Pi0_F_relerr->GetYaxis()->SetRangeUser(1e7, 2e13);
fFitReco_Pi0_F_relerr->SetParameter(0,fFitReco_Pi0_F_background->GetParameter(0));
fFitReco_Pi0_F_relerr->SetParameter(1,fFitReco_Pi0_F_background->GetParameter(1));
fFitReco_Pi0_F_relerr->SetParameter(2,fFitReco_Pi0_F_background->GetParameter(2));
fFitReco_Pi0_F_relerr->SetParameter(3,fFitReco_Pi0_F->GetParameter(0));
fFitReco_Pi0_F_relerr->SetParameter(4,fFitReco_Pi0_F->GetParameter(1));
fFitReco_Pi0_F_relerr->SetParameter(5,fFitReco_Pi0_F->GetParameter(2));

//fFitReco_Pi0_F_relerr->SetParLimits(0,1e5,1e15);
//fFitReco_Pi0_F_relerr->SetParLimits(1,0.01,1e3);
//fFitReco_Pi0_F_relerr->SetParLimits(5,pion_mass-.1,pion_mass+.1);
//fFitReco_Pi0_F_relerr->SetParLimits(3,1e5,1e15);
//fFitReco_Pi0_F_relerr->SetParLimits(4,0.01,1e3);
//fFitReco_Pi0_F_relerr->SetParLimits(5,pion_mass-.1,pion_mass+.1);

//hist_RelativeUncertainity_Pi0_B->Fit(fFitReco_Pi0_F_relerr,"QRME");
//fFitReco_Pi0_F_relerr->SetLineColor(kRed);
//fFitReco_Pi0_F_relerr->SetLineWidth(1);
//fFitReco_Pi0_F_relerr->SetLineStyle(2);
//cout << fFitReco_Pi0_F->GetParameter(0)<<"  "<<fFitReco_Pi0_F->GetParameter(1)<<"  "<< fFitReco_Pi0_F->GetParameter(2)<<endl; 

//
//hist_BackgroundPerEvent_Pi0_F->Draw("");
//hist_meson_yield_Pi0_F->Draw("SAME");

fFitReco_Pi0_F_relerr->Draw("");
hist_RelativeUncertainity_Pi0_F->Draw("SAME");
hist_RelativeUncertainity_Pi0_B->Draw("SAME");
hist_RelativeUncertainity_Eta_F->Draw("SAME");
hist_RelativeUncertainity_Eta_B->Draw("SAME");
/*      TF1 *fcos = new TF1 ("fcos", "[0]*cos(x)", 0., 10.);
      fcos->SetParNames( "cos");
      fcos->SetParameter( 0, 1.1);
 
      TF1 *fsin = new TF1 ("fsin", "[0]*sin(x)", 0., 10.);
      fsin->SetParNames( "sin");
      fsin->SetParameter( 0, 2.1);
 
      TF1 *fsincos = new TF1 ("fsc", "fcos+fsin",1,10);
 
      TF1 *fs2 = new TF1 ("fs2", "fsc+fsc",1,10);
      fsincos->Draw("");
      fs2->Draw("SAME");
      */
c_meson_significance_fit->SaveAs("./c_meson_significance_fit.png");

}
TCanvas* c_test = new TCanvas("c_test","c_test",0,0,600,600);  // gives the page size
c_test->SetLogy();
float_t x_val;
float_t y_val_back_Pi0_F, y_val_sig_Pi0_F, y_err_Pi0_F;
float_t y_val_back_Pi0_B, y_val_sig_Pi0_B, y_err_Pi0_B;
float_t y_val_back_Eta_F, y_val_sig_Eta_F, y_err_Eta_F;
float_t y_val_back_Eta_B, y_val_sig_Eta_B, y_err_Eta_B;

TH1F* hist_test_Pi0_F            = new TH1F("hist_test_Pi0_F","hist_test_Pi0_F",1000,0.,10.);
TH1F* hist_test_Pi0_B            = new TH1F("hist_test_Pi0_B","hist_test_Pi0_B",1000,0.,10.);
TH1F* hist_test_Eta_F            = new TH1F("hist_test_Eta_F","hist_test_Eta_F",1000,0.,10.);
TH1F* hist_test_Eta_B            = new TH1F("hist_test_Eta_B","hist_test_Eta_B",1000,0.,10.);

for(int i=1; i<1000; i++){
   x_val = hist_test_Pi0_F->GetBinCenter(i);

   y_val_back_Pi0_F = fFitReco_Pi0_F_background->Eval(x_val);
   y_val_back_Pi0_B = fFitReco_Pi0_B_background->Eval(x_val);
   y_val_back_Eta_F = fFitReco_Eta_F_background->Eval(x_val);
   y_val_back_Eta_B = fFitReco_Eta_B_background->Eval(x_val);

   y_val_sig_Pi0_F = fFitReco_Pi0_F->Eval(x_val);
   y_val_sig_Pi0_B = fFitReco_Pi0_B->Eval(x_val);
   y_val_sig_Eta_F = fFitReco_Eta_F->Eval(x_val);
   y_val_sig_Eta_B = fFitReco_Eta_B->Eval(x_val);

   if (y_val_sig_Pi0_F !=0) y_err_Pi0_F = TMath::Sqrt(y_val_sig_Pi0_F+y_val_back_Pi0_F)/y_val_sig_Pi0_F;
   if (y_val_sig_Pi0_B !=0) y_err_Pi0_B = TMath::Sqrt(y_val_sig_Pi0_B+y_val_back_Pi0_B)/y_val_sig_Pi0_B;
   if (y_val_sig_Eta_F !=0) y_err_Eta_F = TMath::Sqrt(y_val_sig_Eta_F+y_val_back_Eta_F)/y_val_sig_Eta_F;
   if (y_val_sig_Eta_B !=0) y_err_Eta_B = TMath::Sqrt(y_val_sig_Eta_B+y_val_back_Eta_B)/y_val_sig_Eta_B;

   hist_test_Pi0_F->SetBinContent(i,100*y_err_Pi0_F);
   hist_test_Pi0_B->SetBinContent(i,100*y_err_Pi0_B);
   hist_test_Eta_F->SetBinContent(i,100*y_err_Eta_F);
   hist_test_Eta_B->SetBinContent(i,100*y_err_Eta_B);
}



SetStyleHistoTH1ForGraphs(hist_RelativeUncertainity_Pi0_F, "p_{T} (GeV/c)", "Statistical uncertainity (%)", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_test_Pi0_F,24,1.0, kRed , kRed);
DrawGammaSetMarker(hist_test_Pi0_B,8,1.0, kRed+2 , kRed+2);
DrawGammaSetMarker(hist_test_Eta_F,24,1.0, kGreen+2 , kGreen+2);
DrawGammaSetMarker(hist_test_Eta_B,8,1.0, kGreen+3 , kGreen+3);

auto l_meson_RelUncertainity_FIT = new TLegend(0.6, 0.15, 0.8, 0.35);
l_meson_RelUncertainity_FIT->SetHeader("");
l_meson_RelUncertainity_FIT->SetBorderSize(0);
l_meson_RelUncertainity_FIT->SetFillStyle(0);
l_meson_RelUncertainity_FIT->SetTextSize(TextSize);

l_meson_RelUncertainity_FIT->AddEntry(hist_test_Pi0_F,"#pi^{0} Forward ");
l_meson_RelUncertainity_FIT->AddEntry(hist_test_Pi0_B,"#pi^{0} Barrel ");
l_meson_RelUncertainity_FIT->AddEntry(hist_test_Eta_F,"#eta Forward ");
l_meson_RelUncertainity_FIT->AddEntry(hist_test_Eta_B,"#eta Barrel");


 hist_RelativeUncertainity_Pi0_F->GetYaxis()->SetRangeUser(1e-4, 100.);
 
//hist_test_Pi0_F->Draw("");
hist_RelativeUncertainity_Pi0_F->Draw("");
hist_RelativeUncertainity_Pi0_B->Draw("SAME");
hist_RelativeUncertainity_Eta_F->Draw("SAME");
hist_RelativeUncertainity_Eta_B->Draw("SAME");
 //hist_test_Pi0_B->Draw("SAME");
 //hist_test_Eta_F->Draw("SAME");
 //hist_test_Eta_B->Draw("SAME");

 l_meson_RelUncertainity_FIT->Draw("SAME");
 lt_meson_significance_F_b->Draw("SAME");
 }