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
#include "../headers/ALICE3_setup.h"

using namespace std;


#include <TH1F.h>


void ScalingAfterRebin(TH1F* hist, TH1F* hist_r, Double_t binVals[],int N) {
    for (int i = 0; i < N; i++) {
            Int_t bin_before = hist->FindBin(binVals[i]);
            Int_t bin_after = hist->FindBin(binVals[i+1]);
            Float_t scalefactor = bin_after-bin_before; 
            Float_t bin_content = hist_r->GetBinContent(i);
            hist_r->SetBinContent(i, bin_content/scalefactor);
            cout<<  hist_r->GetNbinsX()<< " " <<bin_before<< " "<< binVals[i]<< " "<< scalefactor<<" "<<bin_content<<endl;
    }
}



void sys_uncertainity_estimate_REBIN_CHECK(){


///SET THIS VARIABLES: 

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

Double_t pt_bin_proj_modified[9]={0.0,0.4,0.8,1.2,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_modified  = 8;

// INPUT SETUP 

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/data/directphotonsPbPb5020GeV/abhishek/Gamma_Pi0_data_GammaConvV1_InclusiveRatio_0020.root";
TString cocktail_input_file_loc="/home/abhishek/PhD/Work/work_A/photons/Cocktail/GammaCocktail_0.80_10130e03_0d200009ab770c00amd0400000_0152101500000000.root";
TString Header_text="Sanity check: Cocktail Photon yield";

gSystem->Exec("mkdir ./sys_uncertainity_estimate");
gSystem->cd("./sys_uncertainity_estimate");

cout << collisionSystem<< endl;
switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    fileCocktail = new TFile(cocktail_input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.25,0.85,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
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
    fileCocktail = new TFile(cocktail_input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.6,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
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


TCanvas* c_sys_uncertainity_estimate_REBIN_CHECK = new TCanvas("c_sys_uncertainity_estimate_REBIN_CHECK","c_sys_uncertainity_estimate_REBIN_CHECK",0,0,800,800);  // gives the page size
DrawGammaCanvasSettings( c_sys_uncertainity_estimate_REBIN_CHECK, 0.13, 0.075, 0.075, 0.13);
//c_sys_uncertainity_estimate_REBIN_CHECK->SetLogx();  
c_sys_uncertainity_estimate_REBIN_CHECK->SetLogy();  

///   using cocktail decay photons

TH1F * Decay_gamma_yield_cocktail       = (TH1F*) fileCocktail->Get(Form("Gamma_Pt"));
//TH1F* Decay_gamma_yield_cocktail_rebin     = (TH1F*) Decay_gamma_yield_cocktail->Rebin(nbinspt_proj_rebin,"Decay_gamma_yield_cocktail_rebin",&pt_bin_proj_modified[0]);


//TH1F* Decay_gamma_yield_cocktail_rebin_scaled  = (TH1F*) Decay_gamma_yield_cocktail->Clone("Decay_gamma_yield_cocktail_rebin_scaled");
TH1F* Decay_gamma_yield_cocktail_rebin_scaled     = (TH1F*) Decay_gamma_yield_cocktail->Rebin(nbinspt_proj_modified,"Decay_gamma_yield_cocktail_rebin",&pt_bin_proj_modified[0]);
//Decay_gamma_yield_cocktail_rebin_scaled->Rebin(2);
DivideTH1ByBinWidth(Decay_gamma_yield_cocktail_rebin_scaled);
ScalingAfterRebin(Decay_gamma_yield_cocktail,Decay_gamma_yield_cocktail_rebin_scaled,pt_bin_proj_modified,nbinspt_proj_modified);

TH1F* Decay_gamma_yield_cocktail_rebin     = (TH1F*) Decay_gamma_yield_cocktail->Rebin(nbinspt_proj_modified,"Decay_gamma_yield_cocktail_rebin",&pt_bin_proj_modified[0]);
DivideTH1ByBinWidth(Decay_gamma_yield_cocktail_rebin);

/*
for (int i = 1; i < Decay_gamma_yield_cocktail->GetNbinsX(); i++) {
            Float_t bin_center = Decay_gamma_yield_cocktail->GetBinCenter(i);
            Float_t bin_content = Decay_gamma_yield_cocktail->GetBinContent(i);
            cout<< bin_center<< " " << bin_content<< endl;
    }
cout << "\n"<<endl;

for (int i = 1; i < Decay_gamma_yield_cocktail_rebin_scaled->GetNbinsX(); i++) {
            Float_t bin_center = Decay_gamma_yield_cocktail_rebin_scaled->GetBinCenter(i);
            Float_t bin_content = Decay_gamma_yield_cocktail_rebin_scaled->GetBinContent(i);
            cout<< bin_center<< " " << bin_content<< endl;
    }
cout << "\n"<<endl;
for (int i = 1; i < Decay_gamma_yield_cocktail_rebin->GetNbinsX(); i++) {
            Float_t bin_center = Decay_gamma_yield_cocktail_rebin->GetBinCenter(i);
            Float_t bin_content = Decay_gamma_yield_cocktail_rebin->GetBinContent(i);
            cout<< bin_center<< " " << bin_content<< endl;
    }

*/

int nbins = Decay_gamma_yield_cocktail->GetNbinsX();
TH1F* Decay_gamma_yield_cocktail_mul_pt  = (TH1F*) Decay_gamma_yield_cocktail->Clone("Decay_gamma_yield_cocktail_mul_pt");
for (int i = 1; i <= nbins; ++i) {
   Double_t binContent = Decay_gamma_yield_cocktail->GetBinContent(i);
   Double_t midValue = Decay_gamma_yield_cocktail->GetBinCenter(i);
   Decay_gamma_yield_cocktail_mul_pt->SetBinContent(i, binContent * midValue);
   cout << nbins <<" \t"<< binContent << "\t " << midValue << " \t"<< binContent * midValue<< " \t"<< Decay_gamma_yield_cocktail_mul_pt->GetBinContent(i)<<endl;
}

TH1F* Decay_gamma_yield_cocktail_mul_pt_rebin     = (TH1F*) Decay_gamma_yield_cocktail_mul_pt->Rebin(nbinspt_proj_modified,"Decay_gamma_yield_cocktail_mul_pt_rebin",&pt_bin_proj_modified[0]);
DivideTH1ByBinWidth(Decay_gamma_yield_cocktail_mul_pt_rebin);


int nbins_rebinned = Decay_gamma_yield_cocktail_mul_pt_rebin->GetNbinsX();
TH1F* Decay_gamma_yield_cocktail_mul_pt_rebin_div_pt  = (TH1F*) Decay_gamma_yield_cocktail_mul_pt_rebin->Clone("Decay_gamma_yield_cocktail_mul_pt_rebin_div_pt");
for (int i = 1; i <= nbins_rebinned; ++i) {
   Double_t binContent = Decay_gamma_yield_cocktail_mul_pt_rebin->GetBinContent(i);
   Double_t midValue = Decay_gamma_yield_cocktail_mul_pt_rebin->GetBinCenter(i);
   Decay_gamma_yield_cocktail_mul_pt_rebin_div_pt->SetBinContent(i, binContent / midValue);
}


SetStyleHistoTH1ForGraphs(Decay_gamma_yield_cocktail, p_T.Data() , "Invariant Yield",TextSize_lable, TextSize_title, TextSize_lable,TextSize_title, LabelOffsetX, LabelOffsetY);
DrawGammaSetMarker(Decay_gamma_yield_cocktail,marker_B,1.5, kRed , kRed);
DrawGammaSetMarker(Decay_gamma_yield_cocktail_rebin,marker_F,1.0, kRed+2 , kRed+2);
DrawGammaSetMarker(Decay_gamma_yield_cocktail_rebin_scaled,marker_F,1.0, kYellow+1 , kYellow+1);
DrawGammaSetMarker(Decay_gamma_yield_cocktail_mul_pt,marker_B,0.75, kCyan , kCyan);
DrawGammaSetMarker(Decay_gamma_yield_cocktail_mul_pt_rebin,marker_B,0.75, kBlue , kBlue);
DrawGammaSetMarker(Decay_gamma_yield_cocktail_mul_pt_rebin_div_pt,marker_F,0.75, kBlue+2 , kBlue+2);

auto l_sys_uncertainity_estimate_REBIN_CHECK = new TLegend(0.45, 0.55, 0.9, 0.85);
l_sys_uncertainity_estimate_REBIN_CHECK->SetHeader(Header_text.Data());
l_sys_uncertainity_estimate_REBIN_CHECK->SetTextSize(TextSize-.015);
l_sys_uncertainity_estimate_REBIN_CHECK->AddEntry(Decay_gamma_yield_cocktail,"Photon cocktail","p");
l_sys_uncertainity_estimate_REBIN_CHECK->AddEntry(Decay_gamma_yield_cocktail_rebin,"Photon cocktail rebinned","p");
l_sys_uncertainity_estimate_REBIN_CHECK->AddEntry(Decay_gamma_yield_cocktail_rebin_scaled,"Photon cocktail rebinned scaled","p");
l_sys_uncertainity_estimate_REBIN_CHECK->AddEntry(Decay_gamma_yield_cocktail_mul_pt,"Photon cocktail * p_T","p");
l_sys_uncertainity_estimate_REBIN_CHECK->AddEntry(Decay_gamma_yield_cocktail_mul_pt_rebin,"Photon cocktail * p_T rebinned and scaled","p");
l_sys_uncertainity_estimate_REBIN_CHECK->AddEntry(Decay_gamma_yield_cocktail_mul_pt_rebin_div_pt,"Photon cocktail * p_T rebinned *1/p_T","p");


Decay_gamma_yield_cocktail->GetXaxis()->SetRangeUser(plot_minPt, plot_maxPt);
Decay_gamma_yield_cocktail->GetYaxis()->SetRangeUser(10e-7, 10e4);



Decay_gamma_yield_cocktail->Draw("E0");
Decay_gamma_yield_cocktail_rebin->Draw("E0, SAME");
Decay_gamma_yield_cocktail_rebin_scaled->Draw("E0, SAME");
Decay_gamma_yield_cocktail_mul_pt->Draw("E0, SAME");
Decay_gamma_yield_cocktail_mul_pt_rebin->Draw("E0, SAME");
Decay_gamma_yield_cocktail_mul_pt_rebin_div_pt->Draw("E0, SAME");
ltb_general_Additional_text->Draw("E0 SAME");

l_sys_uncertainity_estimate_REBIN_CHECK->Draw("SAME");

c_sys_uncertainity_estimate_REBIN_CHECK->SaveAs("./c_sys_uncertainity_estimate_REBIN_CHECK.png");
//c_sys_uncertainity_estimate_REBIN_CHECK->Close();


}




int main() {

}
