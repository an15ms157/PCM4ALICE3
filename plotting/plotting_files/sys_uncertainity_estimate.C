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
#include "TLine.h"

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



void sys_uncertainity_estimate(){

//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);



// INPUT SETUP 

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/directphotonsPbPb5020GeV/abhishek/Gamma_Pi0_data_GammaConvV1_InclusiveRatio_0020.root";
gSystem->Exec("mkdir ./sys_uncertainity_estimate");
gSystem->cd("./sys_uncertainity_estimate");

cout << collisionSystem<< endl;
switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.2,0.75,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    // INPUT CONDITIONS:
    plot_minPt = 0.2;
    plot_maxPt = 10.0;
    plot_minY = 0.0;
    plot_maxY = 2.0;

    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{

    fcollisionSystem = "PbPb";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.15,0.75,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;
    plot_minPt = 0.2;
    plot_maxPt = 14.0;
    plot_minY = 0.8;
    plot_maxY = 2.0;
        break;
    }
}



SetStyleTLatex( ltb_general_Additional_text, TextSize,4);



///////////////////////////////////    Double Ratio: Previous run comparison    //////////////////////////////////////////

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

double_t Total_gamma_yield[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/Total_photon_theory_yield.dat"
};

double_t pT_Theory[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/pT.dat"
   //-1 add another number because the txt file ends with a comma
};




for (int bin=0;bin<=hist_DoubleRatio_ALICE3->GetNcells();++bin) {
      hist_DoubleRatio_ALICE3->SetBinError(bin, 0.035*(hist_DoubleRatio_ALICE3->GetBinContent(bin)));
}


///////////////////////////////////    Double Ratio: Theory comparison    //////////////////////////////////////////

TH1F * hist_DecayPhoton_Yield_ALICE3_fit       = (TH1F*) fileRec->Get(Form("Gamma_Pt"));

TF1  *  fFitReco = nullptr;
fFitReco         = new TF1("QCD_Tsallis","(x<=[5])*[0]*TMath::Power(x,-1*([1]+[2]/(TMath::Power(x,[3])+[4])))+(x>[5])*[6]*TMath::Power(x,-1*([7]+[8]/(TMath::Power(x,[9])+[10])))", 0.5, 14);
fFitReco->SetParameter(0,15);
fFitReco->SetParameter(1,6.7);
fFitReco->SetParameter(2,-6.5);
fFitReco->SetParameter(3,100.);
fFitReco->SetParameter(4,10);
fFitReco->SetParameter(5,240);
fFitReco->SetParameter(6,2);
fFitReco->SetParameter(7,60.7);
fFitReco->SetParameter(8,-6.5);
fFitReco->SetParameter(9,10.);
fFitReco->SetParameter(10,10);


TFitResultPtr theFitResult;
theFitResult = hist_DecayPhoton_Yield_ALICE3_fit->Fit(fFitReco,"SQRME");

double_t Decay_gamma_yield[99];
for( Int_t i = 0; i < 99 ; i++){
   Decay_gamma_yield[i]=fFitReco->Eval(pT_Theory[i]);
}

double_t DoubleRatio_Theory[99];
for( Int_t i = 0; i < 99 ; i++){
   DoubleRatio_Theory[i]=(Total_gamma_yield[i]+Decay_gamma_yield[i])/Decay_gamma_yield[i];
}


double_t DoubleRatio_Theory_reduced[97];
double_t pT_Theory_reduced[97];
for( Int_t i = 2; i < 99 ; i++){
   DoubleRatio_Theory_reduced[i-2]=DoubleRatio_Theory[i];
   pT_Theory_reduced[i-2]=pT_Theory[i];


}
TH1F* hist_DoubleRatio_Theory = new TH1F("hist_DoubleRatio_Theory","hist_DoubleRatio_Theory",nbinspt_proj_rebin,pt_bin_proj_rebin);
TAxis *DoubleRatio_hist_axis = hist_DoubleRatio_Theory->GetXaxis();

for( Int_t i = 0; i < 97 ; i++){
   Int_t bin_number =  DoubleRatio_hist_axis->FindBin(pT_Theory_reduced[i]+0.00001);
   hist_DoubleRatio_Theory->SetBinContent(bin_number,DoubleRatio_Theory_reduced[i] ); 
   hist_DoubleRatio_Theory->SetBinError(bin_number, 0.03*(hist_DoubleRatio_Theory->GetBinContent(bin_number)));
}

TCanvas* c_sys_uncertainity_estimate_DoubleRatio = new TCanvas("c_sys_uncertainity_estimate_DoubleRatio","c_sys_uncertainity_estimate_DoubleRatio",0,0,1000,500);  // gives the page size
DrawGammaCanvasSettings( c_sys_uncertainity_estimate_DoubleRatio, 0.12, 0.01, 0.03, 0.15);
c_sys_uncertainity_estimate_DoubleRatio;
c_sys_uncertainity_estimate_DoubleRatio->SetLogx();  

void SetStyle(Bool_t graypalette=kFALSE);

SetStyleHistoTH1ForGraphs(hist_DoubleRatio_run2, p_T.Data() , "Double ratio", TextSize_lable+.01, TextSize_title+00.01, TextSize_lable+.01,TextSize_title+0.01, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_DoubleRatio_run2,marker_B,1.0, kRed , kRed);
DrawGammaSetMarker(hist_DoubleRatio_ALICE3,marker_F,0.5, kBlue+3 , kBlue+3);
DrawGammaSetMarker(hist_DoubleRatio_Theory,marker_F,0.5, kRed+3 , kRed+3);

auto l_sys_uncertainity_estimate_meson_DoubleRatio = new TLegend(0.35, 0.65, 0.85, 0.9);
l_sys_uncertainity_estimate_meson_DoubleRatio->SetHeader("Systematic errors; 0-20%");
l_sys_uncertainity_estimate_meson_DoubleRatio->SetBorderSize(0);
l_sys_uncertainity_estimate_meson_DoubleRatio->SetFillStyle(0);
l_sys_uncertainity_estimate_meson_DoubleRatio->SetTextSize(TextSize);
l_sys_uncertainity_estimate_meson_DoubleRatio->AddEntry(hist_DoubleRatio_run2,Form("Run 2"),"p");
l_sys_uncertainity_estimate_meson_DoubleRatio->AddEntry(hist_DoubleRatio_ALICE3,Form("ALICE 3"),"p");
l_sys_uncertainity_estimate_meson_DoubleRatio->AddEntry(hist_DoubleRatio_Theory,Form("ALICE 3 + Theory: arXiv_2106.11216"),"p");

hist_DoubleRatio_run2->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
hist_DoubleRatio_run2->GetYaxis()->SetRangeUser(plot_minY, plot_maxY);

hist_DoubleRatio_run2->Draw("E1 ");
hist_DoubleRatio_Theory->SetFillColor(kOrange-9);
hist_DoubleRatio_Theory->SetLineColor(kOrange);
hist_DoubleRatio_Theory->Draw("E2, SAME");
hist_DoubleRatio_ALICE3->SetLineColor(kBlue);
hist_DoubleRatio_ALICE3->Draw("E0, SAME");
TLine *line_y1 = new TLine(0.4,1.0,plot_maxPt,1.0);
line_y1->Draw("SAME");
ltb_general_Additional_text->Draw("SAME");

l_sys_uncertainity_estimate_meson_DoubleRatio->Draw("SAME");


c_sys_uncertainity_estimate_DoubleRatio->SaveAs("./sys_uncertainity_estimate_DoubleRatio.png");
c_sys_uncertainity_estimate_DoubleRatio->Close();




















///////////////////////////////////    Double Ratio: Centrality comparison    //////////////////////////////////////////


TCanvas* c_sys_uncertainity_estimate_DoubleRatio_THeory = new TCanvas("c_sys_uncertainity_estimate_DoubleRatio_THeory","c_sys_uncertainity_estimate_DoubleRatio_THeory",0,0,1000,500);  // gives the page size
DrawGammaCanvasSettings( c_sys_uncertainity_estimate_DoubleRatio_THeory, 0.12, 0.01, 0.03, 0.15);
c_sys_uncertainity_estimate_DoubleRatio_THeory;
c_sys_uncertainity_estimate_DoubleRatio_THeory->SetLogx();  

// 0-5%
double_t Total_gamma_yield_0_5[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/Total_photon_theory_yield_0-5.dat"
};

double_t DoubleRatio_Theory_0_5[99];
for( Int_t i = 0; i < 99 ; i++){
   DoubleRatio_Theory_0_5[i]=(Total_gamma_yield_0_5[i]+Decay_gamma_yield[i])/Decay_gamma_yield[i];
}

double_t DoubleRatio_Theory_reduced_0_5[97];
for( Int_t i = 2; i < 99 ; i++){
   DoubleRatio_Theory_reduced_0_5[i-2]=DoubleRatio_Theory_0_5[i];
}

TH1F* hist_DoubleRatio_Theory_0_5 = new TH1F("hist_DoubleRatio_Theory_0_5","hist_DoubleRatio_Theory_0_5",nbinspt_proj_rebin,pt_bin_proj_rebin);
TAxis *DoubleRatio_hist_axis_0_5 = hist_DoubleRatio_Theory_0_5->GetXaxis();

for( Int_t i = 0; i < 97 ; i++){
   Int_t bin_number =  DoubleRatio_hist_axis_0_5->FindBin(pT_Theory_reduced[i]+0.00001);
   hist_DoubleRatio_Theory_0_5->SetBinContent(bin_number,DoubleRatio_Theory_reduced_0_5[i] ); 
   hist_DoubleRatio_Theory_0_5->SetBinError(bin_number, 0.03*(hist_DoubleRatio_Theory_0_5->GetBinContent(bin_number)));
}





// 5-10%
double_t Total_gamma_yield_5_10[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/Total_photon_theory_yield_5-10.dat"
};

double_t DoubleRatio_Theory_5_10[99];
for( Int_t i = 0; i < 99 ; i++){
   DoubleRatio_Theory_5_10[i]=(Total_gamma_yield_5_10[i]+Decay_gamma_yield[i])/Decay_gamma_yield[i];
}

double_t DoubleRatio_Theory_reduced_5_10[97];
for( Int_t i = 2; i < 99 ; i++){
   DoubleRatio_Theory_reduced_5_10[i-2]=DoubleRatio_Theory_5_10[i];
}

TH1F* hist_DoubleRatio_Theory_5_10 = new TH1F("hist_DoubleRatio_Theory_5_10","hist_DoubleRatio_Theory_5_10",nbinspt_proj_rebin,pt_bin_proj_rebin);
TAxis *DoubleRatio_hist_axis_5_10 = hist_DoubleRatio_Theory_5_10->GetXaxis();

for( Int_t i = 0; i < 97 ; i++){
   Int_t bin_number =  DoubleRatio_hist_axis_5_10->FindBin(pT_Theory_reduced[i]+0.00001);
   hist_DoubleRatio_Theory_5_10->SetBinContent(bin_number,DoubleRatio_Theory_reduced_5_10[i] ); 
   hist_DoubleRatio_Theory_5_10->SetBinError(bin_number, 0.03*(hist_DoubleRatio_Theory_5_10->GetBinContent(bin_number)));
}






// 0-10%
double_t Total_gamma_yield_10_20[99] = {
   #include "/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/photon_calculations_arXiv_2106.11216/Total_photon_theory_yield_10-20.dat"
};

double_t DoubleRatio_Theory_10_20[99];
for( Int_t i = 0; i < 99 ; i++){
   DoubleRatio_Theory_10_20[i]=(Total_gamma_yield_10_20[i]+Decay_gamma_yield[i])/Decay_gamma_yield[i];
}

double_t DoubleRatio_Theory_reduced_10_20[97];
for( Int_t i = 2; i < 99 ; i++){
   DoubleRatio_Theory_reduced_10_20[i-2]=DoubleRatio_Theory_10_20[i];
   cout << Total_gamma_yield[i]<<'\t' << Total_gamma_yield_0_5[i]<<'\t' << Total_gamma_yield_10_20[i]<<'\t' << Decay_gamma_yield[i]<<'\t' << DoubleRatio_Theory[i] <<'\t' << DoubleRatio_Theory_0_5[i] <<'\t' << DoubleRatio_Theory_10_20[i]<<endl;

}

TH1F* hist_DoubleRatio_Theory_10_20 = new TH1F("hist_DoubleRatio_Theory_10_20","hist_DoubleRatio_Theory_10_20",nbinspt_proj_rebin,pt_bin_proj_rebin);
TAxis *DoubleRatio_hist_axis_10_20 = hist_DoubleRatio_Theory_10_20->GetXaxis();

for( Int_t i = 0; i < 97 ; i++){
   Int_t bin_number =  DoubleRatio_hist_axis_10_20->FindBin(pT_Theory_reduced[i]+0.00001);
   hist_DoubleRatio_Theory_10_20->SetBinContent(bin_number,DoubleRatio_Theory_reduced_10_20[i] ); 
   hist_DoubleRatio_Theory_10_20->SetBinError(bin_number, 0.03*(hist_DoubleRatio_Theory_10_20->GetBinContent(bin_number)));
}



c_sys_uncertainity_estimate_DoubleRatio_THeory;
c_sys_uncertainity_estimate_DoubleRatio_THeory->SetLogx();  
//c_sys_uncertainity_estimate_DoubleRatio_THeory->cd(2)->SetLogy();  

void SetStyle(Bool_t graypalette=kFALSE);
gStyle->SetOptStat(0);


SetStyleHistoTH1ForGraphs(hist_DoubleRatio_Theory_0_5, p_T.Data() , "Double ratio", TextSize_lable+.01, TextSize_title+00.01, TextSize_lable+.01,TextSize_title+0.01, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(hist_DoubleRatio_Theory_0_5,marker_B,0.5, kRed , kRed);
hist_DoubleRatio_Theory->SetFillColor(kRed-9);
DrawGammaSetMarker(hist_DoubleRatio_Theory_5_10,marker_B,0.5, kGreen+3 , kGreen+3);
DrawGammaSetMarker(hist_DoubleRatio_Theory_10_20,marker_B,0.5, kBlue+3 , kBlue+3);
DrawGammaSetMarker(hist_DoubleRatio_Theory,marker_B,0.5, kRed+3 , kRed+3);
hist_DoubleRatio_Theory->SetFillColor(kOrange-9);


auto l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality = new TLegend(0.6, 0.65, 0.85, 0.9);
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->SetHeader("Centrality class");
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->SetBorderSize(0);
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->SetFillStyle(0);
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->SetTextSize(TextSize);
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->AddEntry(hist_DoubleRatio_Theory_0_5,"0-5%","p");
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->AddEntry(hist_DoubleRatio_Theory_5_10,"5-10%","p");
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->AddEntry(hist_DoubleRatio_Theory_10_20,"10-20%","p");
l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->AddEntry(hist_DoubleRatio_Theory,"0-20%","p");

hist_DoubleRatio_Theory_0_5->GetXaxis()->SetRangeUser(plot_minPt+.3, plot_maxPt);
hist_DoubleRatio_Theory_0_5->GetYaxis()->SetRangeUser(0.9, 1.6);
hist_DoubleRatio_Theory_0_5->Draw("E1 ");
hist_DoubleRatio_Theory_5_10->Draw("E1, SAME");
hist_DoubleRatio_Theory_10_20->Draw("E1, SAME");
hist_DoubleRatio_Theory->Draw("E1, SAME");

TLine *line_y2 = new TLine(plot_minPt+0.3,1.0,plot_maxPt-2,1.0);
line_y2->Draw("SAME");

ltb_general_Additional_text->Draw("SAME");

l_sys_uncertainity_estimate_meson_DoubleRatio_Centrality->Draw("SAME");

c_sys_uncertainity_estimate_DoubleRatio_THeory->SaveAs("./sys_uncertainity_estimate_DoubleRatio_Theory.png");
c_sys_uncertainity_estimate_DoubleRatio_THeory->Close();



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
