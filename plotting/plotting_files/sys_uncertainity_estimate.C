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
#include "TFitResultPtr.h"

#include "./headers/ALICE3_setup.h"


void sys_uncertainity_estimate(){
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

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/directphotonsPbPb5020GeV/abhishek/Gamma_Pi0_data_GammaConvV1_InclusiveRatio_0020.root";
gSystem->Exec("mkdir ./sys_uncertainity_estimate");
gSystem->cd("./sys_uncertainity_estimate");


switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.85,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    // INPUT CONDITIONS:
    plot_minPt = 0.1;
    plot_maxPt = 5.0;
    plot_minY = 0.5;
    plot_maxY = 2.0;

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
    plot_minPt = 0.1;
    plot_maxPt = 5.0;
    plot_minY = 0.8;
    plot_maxY = 2.0;
        break;
    }
}



SetStyleTLatex( ltb_general_Additional_text, 0.03,4);

TH1F * hist_DoubleRatio_run2                 = (TH1F*) fileRec->Get(Form("DoubleRatioTrueEffPurity"));
TH1F * hist_InclusivePhoton_Yield_run2       = (TH1F*) fileRec->Get(Form("histoGammaSpecCorrPurity"));

TH1F* hist_DoubleRatio_ALICE3             = (TH1F*) hist_DoubleRatio_run2->Clone("hist_DoubleRatio_ALICE3");
TH1F* hist_InclusivePhoton_Yield_ALICE3   = (TH1F*) hist_InclusivePhoton_Yield_run2->Clone("hist_InclusivePhoton_Yield_run2");

TH1F* hist_DirectPhoton_Yield_ALICE3      = (TH1F*) hist_DoubleRatio_run2->Clone("hist_DirectPhoton_Yield_ALICE3");
hist_DirectPhoton_Yield_ALICE3->Divide(hist_InclusivePhoton_Yield_ALICE3, hist_DoubleRatio_ALICE3, 1,1,"B");
hist_DirectPhoton_Yield_ALICE3->Add(hist_InclusivePhoton_Yield_ALICE3,-1);
hist_DirectPhoton_Yield_ALICE3->Scale(-1);

//graphDirGammaSpectrumStatErr


double_t Thermal_gamma_yield[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/Thermal_photon_theory_yield.dat"
};

double_t Prompt_gamma_yield[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/Prompt_photon_theory_yield.dat"
};

double_t pT_Theory[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/pT.dat"
   //-1 add another number because the txt file ends with a comma
};





///////////////////////////////////    Double Ratio: Previous run comparison    //////////////////////////////////////////

for (int bin=0;bin<=hist_DoubleRatio_ALICE3->GetNcells();++bin) {
      hist_DoubleRatio_ALICE3->SetBinError(bin, 0.035*(hist_DoubleRatio_ALICE3->GetBinContent(bin)));
}


///////////////////////////////////    Double Ratio: Theory comparison    //////////////////////////////////////////

TH1F * hist_DecayPhoton_Yield_ALICE3_fit       = (TH1F*) fileRec->Get(Form("Gamma_Pt"));

TF1  *  fFitReco = nullptr;
fFitReco         = new TF1("QCD_Tsallis","(x<=[5])*[0]*TMath::Power(x,-1*([1]+[2]/(TMath::Power(x,[3])+[4])))+(x>[5])*[6]*TMath::Power(x,-1*([7]+[8]/(TMath::Power(x,[9])+[10])))", .6, plot_maxPt);
fFitReco->SetParameter(0,5);
fFitReco->SetParameter(1,6.7);
fFitReco->SetParameter(2,-6.5);
fFitReco->SetParameter(3,1.);
fFitReco->SetParameter(4,10);
fFitReco->SetParameter(5,24);
fFitReco->SetParameter(6,2);
fFitReco->SetParameter(7,6.7);
fFitReco->SetParameter(8,-6.5);
fFitReco->SetParameter(9,1.);
fFitReco->SetParameter(10,1);


TFitResultPtr theFitResult;
theFitResult = hist_DecayPhoton_Yield_ALICE3_fit->Fit(fFitReco,"SQRME");

double_t Decay_gamma_yield[99];
for( Int_t i = pT_Theory[0]; i < 99 ; i++){
   Decay_gamma_yield[i]=fFitReco->Eval(pT_Theory[i]);
   //cout << Decay_gamma_yield[i]<<endl;
}

double_t DoubleRatio_Theory[99];
for( Int_t i = pT_Theory[0]; i < 99 ; i++){
   DoubleRatio_Theory[i]=(Decay_gamma_yield[i]+Thermal_gamma_yield[i]+Prompt_gamma_yield[i])/Decay_gamma_yield[i];
   cout << DoubleRatio_Theory[i]<<endl;
}


double_t DoubleRatio_Theory_reduced[97];
double_t pT_Theory_reduced[97];
for( Int_t i = pT_Theory[0]; i < 97 ; i++){
   DoubleRatio_Theory_reduced[i]=DoubleRatio_Theory[i+2];
   pT_Theory_reduced[i]=pT_Theory[i+2];

}
TH1F* hist_DoubleRatio_Theory = new TH1F("hist_DoubleRatio_Theory","hist_DoubleRatio_Theory",nbinspt_proj_fine,pt_bin_proj_fine);
for( Int_t i = pT_Theory[0]; i < 97 ; i++){
   hist_DoubleRatio_Theory->SetBinContent(pT_Theory_reduced[i],DoubleRatio_Theory_reduced[i] ); 
   hist_DoubleRatio_Theory->SetBinError(pT_Theory_reduced[i], 0.03*(hist_DoubleRatio_Theory->GetBinContent(pT_Theory_reduced[i])));

}

TCanvas* c_sys_uncertainity_estimate_DoubleRatio = new TCanvas("c_sys_uncertainity_estimate_DoubleRatio","c_sys_uncertainity_estimate_DoubleRatio",0,0,600,600);  // gives the page size


c_sys_uncertainity_estimate_DoubleRatio->SetLogx();  


SetStyleHistoTH1ForGraphs(hist_DoubleRatio_run2, p_T.Data() , "Double ratio", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_DoubleRatio_run2,marker_F,1.0, kRed , kRed);
DrawGammaSetMarker(hist_DoubleRatio_ALICE3,marker_F,1.0, kRed , kRed+3);

auto l_sys_uncertainity_estimate_meson_DoubleRatio = new TLegend(0.5, 0.75, 0.85, 0.9);
l_sys_uncertainity_estimate_meson_DoubleRatio->SetHeader("Systematic errors; 0-20%");
l_sys_uncertainity_estimate_meson_DoubleRatio->SetBorderSize(0);
l_sys_uncertainity_estimate_meson_DoubleRatio->SetFillStyle(0);
l_sys_uncertainity_estimate_meson_DoubleRatio->SetTextSize(TextSize);
l_sys_uncertainity_estimate_meson_DoubleRatio->AddEntry(hist_DoubleRatio_run2,Form("Meike: run2"),"p");
l_sys_uncertainity_estimate_meson_DoubleRatio->AddEntry(hist_DoubleRatio_ALICE3,Form("ALICE3"),"l");
l_sys_uncertainity_estimate_meson_DoubleRatio->AddEntry(hist_DoubleRatio_Theory,Form("ALICE3 Theory: arXiv_2106.11216"),"l");

//hist_DoubleRatio_run2->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
hist_DoubleRatio_run2->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);

hist_DoubleRatio_run2->Draw("E1");
hist_DoubleRatio_ALICE3->Draw("E1,SAME");
hist_DoubleRatio_Theory->Draw("E1,SAME");

ltb_general_Additional_text->Draw("SAME");

l_sys_uncertainity_estimate_meson_DoubleRatio->Draw("SAME");

c_sys_uncertainity_estimate_DoubleRatio->SaveAs("./sys_uncertainity_estimate_DoubleRatio.png");
c_sys_uncertainity_estimate_DoubleRatio->Close();



//auto gr = new TGraph (97, pT_Theory_reduced, DoubleRatio_Theory_reduced);
//   gr->Draw("AL*");  

//cout<<endl<<fFitReco->Eval(1);
//cout<<endl<<fFitReco->GetX(0.89,1,2.5);











/*
///////////////////////////////////          Inclusive photons             //////////////////////////////////////////

for (int bin=0;bin<=hist_InclusivePhoton_Yield_ALICE3->GetNcells();++bin) {
      hist_InclusivePhoton_Yield_ALICE3->SetBinError(bin, 0.03*(hist_InclusivePhoton_Yield_ALICE3->GetBinContent(bin)));
}

TCanvas* c_sys_uncertainity_estimate_InclusivePhoton_Yield = new TCanvas("c_sys_uncertainity_estimate_InclusivePhoton_Yield","c_sys_uncertainity_estimate_InclusivePhoton_Yield",0,0,600,600);  // gives the page size
c_sys_uncertainity_estimate_InclusivePhoton_Yield->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_InclusivePhoton_Yield_run2, p_T.Data() , "Inclusive photons yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_InclusivePhoton_Yield_run2,marker_F,1.0, kRed , kRed);
DrawGammaSetMarker(hist_InclusivePhoton_Yield_ALICE3,marker_F,1.0, kRed , kRed+3);

auto l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield = new TLegend(0.65, 0.75, 0.85, 0.9);
l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->SetHeader("Systematic errors; 0-20%");
l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->SetBorderSize(0);
l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->SetFillStyle(0);
l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->SetTextSize(TextSize);
l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->AddEntry(hist_InclusivePhoton_Yield_run2,Form("Meike: run2"),"p");
l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->AddEntry(hist_InclusivePhoton_Yield_ALICE3,Form("ALICE3"),"l");

//hist_InclusivePhoton_Yield_run2->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
//hist_InclusivePhoton_Yield_run2->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);

hist_InclusivePhoton_Yield_run2->Draw("E1");
hist_InclusivePhoton_Yield_ALICE3->Draw("E1,SAME");

ltb_general_Additional_text->Draw("SAME");

l_sys_uncertainity_estimate_meson_InclusivePhoton_Yield->Draw("SAME");

c_sys_uncertainity_estimate_InclusivePhoton_Yield->SaveAs("./sys_uncertainity_estimate_InclusivePhoton_Yield.png");
c_sys_uncertainity_estimate_InclusivePhoton_Yield->Close();





///////////////////////////////////          Direct photons             //////////////////////////////////////////

for (int bin=0;bin<=hist_DirectPhoton_Yield_ALICE3->GetNcells();++bin) {
      hist_DirectPhoton_Yield_ALICE3->SetBinError(bin, 0.03*(hist_DirectPhoton_Yield_ALICE3->GetBinContent(bin)));
}

TCanvas* c_sys_uncertainity_estimate_DirectPhoton_Yield = new TCanvas("c_sys_uncertainity_estimate_DirectPhoton_Yield","c_sys_uncertainity_estimate_DirectPhoton_Yield",0,0,600,600);  // gives the page size
c_sys_uncertainity_estimate_DirectPhoton_Yield->SetLogy();  

SetStyleHistoTH1ForGraphs(hist_DirectPhoton_Yield_ALICE3, p_T.Data() , "Direct photons yield", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_DirectPhoton_Yield_ALICE3,marker_F,1.0, kRed , kRed);
DrawGammaSetMarker(hist_DirectPhoton_Yield_ALICE3,marker_F,1.0, kRed , kRed+3);

auto l_sys_uncertainity_estimate_meson_DirectPhoton_Yield = new TLegend(0.65, 0.75, 0.85, 0.9);
l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->SetHeader("Systematic errors; 0-20%");
l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->SetBorderSize(0);
l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->SetFillStyle(0);
l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->SetTextSize(TextSize);
//l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->AddEntry(hist_DirectPhoton_Yield_ALICE3,Form("Meike: run2"),"p");
l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->AddEntry(hist_DirectPhoton_Yield_ALICE3,Form("ALICE3"),"l");

//hist_DirectPhoton_Yield_ALICE3->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
//hist_DirectPhoton_Yield_ALICE3->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);

hist_DirectPhoton_Yield_ALICE3->Draw("E1");
ltb_general_Additional_text->Draw("SAME");

l_sys_uncertainity_estimate_meson_DirectPhoton_Yield->Draw("SAME");

c_sys_uncertainity_estimate_DirectPhoton_Yield->SaveAs("./sys_uncertainity_estimate_DirectPhoton_Yield.png");
//c_sys_uncertainity_estimate_DirectPhoton_Yield->Close();

*/
}
