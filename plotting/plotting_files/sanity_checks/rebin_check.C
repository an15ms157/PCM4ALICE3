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

#include <TH1F.h>

void ScalingAfterRebin(TH1F* hist, TH1F* hist_r, Double_t binVals[]) {
    for (int i = 0; i < hist_r->GetNbinsX(); i++) {
            Int_t bin_before = hist->FindBin(binVals[i]);
            Int_t bin_after = hist->FindBin(binVals[i+1]);
            Float_t scalefactor = bin_after-bin_before; 
            Float_t bin_content = hist_r->GetBinContent(i);
            hist_r->SetBinContent(i, bin_content/scalefactor);
            cout<< bin_before<< " "<< binVals[i]<< " "<< scalefactor<<" "<<bin_content<<endl;
    }
}


void plot_hists()
{

 TH1F* hist_1overx = new TH1F("hist_1overx", "Gaussian Distribution", 100, 0, 10);

  // Create random number generator
  TRandom3* rand = new TRandom3();

  // Fill histogram with random numbers drawn from a Gaussian distribution
  for (int i = 0; i < 100000; ++i) {
    double val = rand->Exp(5.0); // Mean = 5.0, Sigma = 1.0
    hist_1overx->Fill(val);
  }
    // Define a fixed array for rebinning
    Double_t fixed_array[] = {0.0,0.5,1.0,2.0,3.0,5.0,7.0,10.0,15.0,20.0};
    const int nBinsFixed = sizeof(fixed_array)/sizeof(Double_t) - 1;

    // Create a new histogram by rebinning hist_1overx with respect to the fixed array
    //TH1F *hist_rebinned = new TH1F("hist_rebinned", "x Histogram", 50, 0, 5);
TH1F *hist_rebinned = (TH1F*)(hist_1overx->Rebin(nBinsFixed, "hist_rebinned", fixed_array)); //Rebining
    //TH1F* hist_rebinned  = (TH1F*) hist_1overx->Clone("hist_rebinned");
    //hist_rebinned->Rebin(nBinsFixed,"",fixed_array);
    //hist_rebinned->Rebin(3);
//Float_t scalefactor = (1.0*hist_rebinned->GetNbinsX())/hist_1overx->GetNbinsX();
//cout << hist_rebinned->GetNbinsX()<<" "<< scalefactor<< " "<<hist_1overx->GetNbinsX()<< endl;
//hist_rebinned->Scale(scalefactor);
//DivideTH1ByBinValue(hist_rebinned, fixed_array );
//DivideTH1ByBinWidth(hist_rebinned);

//DivideTH1ByBinWidth(hist_1overx);
ScalingAfterRebin(hist_1overx,hist_rebinned,fixed_array);

/*
int nbins = hist_1overx->GetNbinsX();
TH1F* hist_1overx_mul_pt  = (TH1F*) hist_1overx->Clone("hist_1overx_mul_pt");
for (int i = 0; i <= nbins; ++i) {
   Double_t binContent = hist_1overx->GetBinContent(i);
   Double_t midValue = hist_1overx->GetBinCenter(i);
   hist_1overx_mul_pt->SetBinContent(i, binContent * midValue);
}

TH1F *hist_1overx_mul_pt_rebin = (TH1F*)(hist_1overx_mul_pt->Rebin(nBinsFixed, "hist_1overx_mul_pt_rebin", fixed_array)); //Rebining
DivideTH1ByBinWidth(hist_1overx_mul_pt_rebin);
hist_1overx_mul_pt_rebin->Scale(scalefactor);

int nbins_rebinned = hist_1overx_mul_pt_rebin->GetNbinsX();
TH1F* hist_1overx_mul_pt_rebin_div_pt  = (TH1F*) hist_1overx_mul_pt_rebin->Clone("hist_1overx_mul_pt_rebin_div_pt");
for (int i = 1; i <= nbins_rebinned; ++i) {
   Double_t binContent = hist_1overx_mul_pt_rebin->GetBinContent(i);
   Double_t midValue = hist_1overx_mul_pt_rebin->GetBinCenter(i);
   hist_1overx_mul_pt_rebin_div_pt->SetBinContent(i, binContent / midValue);
}



*/
hist_1overx->SetLineColor(kBlue);
hist_rebinned->SetLineColor(kBlack);
//hist_1overx_mul_pt->SetLineColor(kViolet);
//hist_1overx_mul_pt_rebin->SetLineColor(kGreen);
//hist_1overx_mul_pt_rebin_div_pt->SetLineColor(kYellow+1);

auto l_plot_hist = new TLegend(0.15, 0.15, 0.55, 0.45);

l_plot_hist->AddEntry(hist_1overx,"hist = x*exp(1/x) ","l");
l_plot_hist->AddEntry(hist_rebinned,"hist: scaled rebinned","l");
//l_plot_hist->AddEntry(hist_1overx_mul_pt,"X * hist","l");
//l_plot_hist->AddEntry(hist_1overx_mul_pt_rebin,"hist * X: rebinned","l");
//l_plot_hist->AddEntry(hist_1overx_mul_pt_rebin_div_pt,"hist * X: rebinned *1/X","l");


//func->Draw("");  
//hist_1overx->Draw("E ");
hist_rebinned->Draw("E,SAME");
//hist_1overx_mul_pt->Draw("SAME");
//hist_1overx_mul_pt_rebin->Draw("SAME");
//hist_1overx_mul_pt_rebin_div_pt->Draw("SAME");
l_plot_hist->Draw();
}

