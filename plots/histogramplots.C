#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"

void histogramplots(){
StyleSettings();
SetPlotStyle();
/*
gStyle->SetOptTitle(0);
//gStyle->SetOptStat(0);
gStyle->SetLineWidth(2);
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetPadTopMargin(0.05);
gStyle->SetPadRightMargin(0.05);
gStyle->SetTitleSize(0.06);
gStyle->SetTitleSize(0.06,"Y");
gStyle->SetTitleOffset(1,"Y");
gStyle->SetTitleOffset(1,"X");
gStyle->SetLabelSize(0.05);
gStyle->SetLabelSize(0.05,"Y");
gStyle->SetFrameLineWidth(2);
gStyle->SetNdivisions(505,"X");
gStyle->SetNdivisions(505,"Y");
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);
*/
//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);

//   TO VANISH STAT BOX 
                                                ////////////////FORWARD///////////////

//TFile * fileRec = new TFile("./ana_withft3.root");
TFile * fileRec = new TFile("./ana_pTcut_withft3.root");
//TFile * fileRec = new TFile("./output/pp/pcut_0.1/ana_pTcut_withft3.root");

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.02;
Double_t TextSize_lable=0.03;
Double_t TextSize_title=0.04;
Double_t TextSize_latex=20;
Double_t LabelOffsetLog=-0.015;
//const int nBinsPt=100;

Double_t pt_bin_proj[]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
Int_t nbinspt_proj  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;

Double_t pt_bin_proj_fine[]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0, 7.0,10.0};
Int_t nbinspt_proj_fine  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;

/*
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 10) pt_bin_proj[i]            = *i;
      else if(i<20) pt_bin_proj[i]          = 1.0 + 0.2*(i-10);
      else if(i<22) pt_bin_proj[i]          = 3.0 + 0.5*(i-20);
      else pt_bin_proj[i]                   = fMaxPt;
}
*/


///////////////   INVARIANT MASS PLOT    ///////////////

TH1D * hInvMassGGF = (TH1D*) fileRec->Get("hInvMassGGF");
TH1D * hInvMassGGF_SmearedP = (TH1D*) fileRec->Get("hInvMassGGF_SmearedP");
TH1D * hInvMassGGF_rec = (TH1D*) fileRec->Get("hInvMassGGF_rec");
TH1D * hInvMassGGF_rec_SmearedP = (TH1D*) fileRec->Get("hInvMassGGF_rec_SmearedP");
TH1D * hInvMassGGF_conv = (TH1D*) fileRec->Get("hInvMassGGF_conv");
TH1D * hInvMassGGF_conv_SmearedP = (TH1D*) fileRec->Get("hInvMassGGF_conv_SmearedP");

TCanvas c1("c1", "c1", 1600, 1600);
c1.Divide(3,1);

c1.cd(1);
c1.cd(1)->SetLogy();  
hInvMassGGF->Draw();
hInvMassGGF->SetLineColor(kBlue);  
hInvMassGGF_SmearedP->Draw("SAME");
hInvMassGGF_SmearedP->SetLineColor(kRed);

c1.cd(3);
c1.cd(3)->SetLogy();  
hInvMassGGF_rec->Draw("SAME");
hInvMassGGF_rec->SetLineColor(kMagenta);  
hInvMassGGF_rec_SmearedP->Draw("SAME");
hInvMassGGF_rec_SmearedP->SetLineColor(kGreen+4); 

c1.cd(2);
c1.cd(2)->SetLogy();  
hInvMassGGF_conv->Draw("SAME");
hInvMassGGF_conv->SetLineColor(kMagenta);  
hInvMassGGF_conv_SmearedP->Draw("SAME");
hInvMassGGF_conv_SmearedP->SetLineColor(kCyan);  


hInvMassGGF->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGF_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGF_rec->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGF_rec_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGF_conv->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGF_conv_SmearedP->GetYaxis()->SetTitle("N_{ev}");

hInvMassGGF->GetXaxis()->SetTitle("Invariant Mass #gamma#gamma (GeV/c^{2})");
hInvMassGGF_SmearedP->GetXaxis()->SetTitle("Invariant Mass #gamma#gamma (GeV/c^{2})");
hInvMassGGF_rec->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGF_rec_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGF_conv->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGF_conv_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");

auto l1 = new TLegend(0.4, 0.6, 0.7, 0.8);
l1->SetHeader("ALICE 3 Study");
l1->SetBorderSize(0);
l1->SetFillStyle(0);
l1->SetTextSize(0.03);
l1->AddEntry(hInvMassGGF,"hInvMassGGF","l");
l1->AddEntry(hInvMassGGF_SmearedP,"hInvMassGGF_SmearedP","l");
l1->AddEntry(hInvMassGGF_rec,"hInvMassGGF_rec","l");
l1->AddEntry(hInvMassGGF_rec_SmearedP,"hInvMassGGF_rec_SmearedP","l");
l1->AddEntry(hInvMassGGF_conv,"hInvMassGGF_conv","l");
l1->AddEntry(hInvMassGGF_conv_SmearedP,"hInvMassGGF_conv_SmearedP","l");

l1->Draw("SAME");
c1.SaveAs("plots/hInvMassGGF.png");


///////////////   Pi0 INVMASS PLOT    ///////////////

TH1D * hInvMassGGPi0F = (TH1D*) fileRec->Get("hInvMassGGPi0F");
TH1D * hInvMassGGPi0F_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0F_SmearedP");
TH1D * hInvMassGGPi0F_rec = (TH1D*) fileRec->Get("hInvMassGGPi0F_rec");
TH1D * hInvMassGGPi0F_rec_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0F_rec_SmearedP");
TH1D * hInvMassGGPi0F_conv = (TH1D*) fileRec->Get("hInvMassGGPi0F_conv");
TH1D * hInvMassGGPi0F_conv_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0F_conv_SmearedP");

TCanvas c2("c2", "c2", 1600, 1600);
c2.Divide(3,1);

hInvMassGGPi0F->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F_rec->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F_rec_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F_conv->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F_conv_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0F_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0F_rec->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0F_rec_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0F_conv->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0F_conv_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");

c2.cd(1);
c2.cd(1)->SetLogy();  
hInvMassGGPi0F->Draw();
hInvMassGGPi0F->SetLineColor(kBlue);  
hInvMassGGPi0F_SmearedP->Draw("SAME");
hInvMassGGPi0F_SmearedP->SetLineColor(kRed);

c2.cd(2);
c2.cd(2)->SetLogy();  
hInvMassGGPi0F_conv->Draw("SAME");
hInvMassGGPi0F_conv->SetLineColor(kOrange+4);  
hInvMassGGPi0F_conv_SmearedP->Draw("SAME");
hInvMassGGPi0F_conv_SmearedP->SetLineColor(kCyan);  

c2.cd(3); 
c2.cd(3)->SetLogy();  
hInvMassGGPi0F_rec->Draw("SAME");
hInvMassGGPi0F_rec->SetLineColor(kMagenta);  
hInvMassGGPi0F_rec_SmearedP->Draw("SAME");
hInvMassGGPi0F_rec_SmearedP->SetLineColor(kGreen+4); 

auto l2 = new TLegend(0.4, 0.6, 0.7, 0.8);
l2->SetHeader("ALICE 3 Study");
l2->SetBorderSize(0);
l2->SetFillStyle(0);
l2->SetTextSize(0.03);
l2->AddEntry(hInvMassGGPi0F,"hInvMassGGPi0F","l");
l2->AddEntry(hInvMassGGPi0F_SmearedP,"hInvMassGGPi0F_SmearedP","l");
l2->AddEntry(hInvMassGGPi0F_conv,"hInvMassGGPi0F_conv","l");
l2->AddEntry(hInvMassGGPi0F_conv_SmearedP,"hInvMassGGPi0F_conv_SmearedP","l");
l2->AddEntry(hInvMassGGPi0F_rec,"hInvMassGGPi0F_rec","l");
l2->AddEntry(hInvMassGGPi0F_rec_SmearedP,"hInvMassGGPi0F_rec_SmearedP","l");

l2->Draw("SAME");
c2.SaveAs("plots/hInvMassGGF_Pi0.png");


///////////////   Eta INVMASS PLOT    ///////////////

TH1D * hInvMassGGEtaF = (TH1D*) fileRec->Get("hInvMassGGEtaF");
TH1D * hInvMassGGEtaF_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaF_SmearedP");
TH1D * hInvMassGGEtaF_rec = (TH1D*) fileRec->Get("hInvMassGGEtaF_rec");
TH1D * hInvMassGGEtaF_rec_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaF_rec_SmearedP");
TH1D * hInvMassGGEtaF_conv = (TH1D*) fileRec->Get("hInvMassGGEtaF_conv");
TH1D * hInvMassGGEtaF_conv_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaF_conv_SmearedP");

TCanvas c3("c3", "c3", 1600, 1600);
c3.Divide(3,1);

hInvMassGGEtaF->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF_rec->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF_rec_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF_conv->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF_conv_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF->GetXaxis()->SetTitle("Invaeiant Mass (GeV/c^{2})");
hInvMassGGEtaF_SmearedP->GetXaxis()->SetTitle("Invaeiant Mass (GeV/c^{2})");
hInvMassGGEtaF_rec->GetXaxis()->SetTitle("Invaeiant Mass (GeV/c^{2})");
hInvMassGGEtaF_rec_SmearedP->GetXaxis()->SetTitle("Invaeiant Mass (GeV/c^{2})");
hInvMassGGEtaF_conv->GetXaxis()->SetTitle("Invaeiant Mass (GeV/c^{2})");
hInvMassGGEtaF_conv_SmearedP->GetXaxis()->SetTitle("Invaeiant Mass (GeV/c^{2})");

c3.cd(1);
c3.cd(1)->SetLogy();  
hInvMassGGEtaF->Draw();
hInvMassGGEtaF->SetLineColor(kBlue);  
hInvMassGGEtaF_SmearedP->Draw("SAME");
hInvMassGGEtaF_SmearedP->SetLineColor(kRed);

c3.cd(2);
c3.cd(2)->SetLogy();  
hInvMassGGEtaF_conv->Draw("SAME");
hInvMassGGEtaF_conv->SetLineColor(kOrange+4);  
hInvMassGGEtaF_conv_SmearedP->Draw("SAME");
hInvMassGGEtaF_conv_SmearedP->SetLineColor(kCyan);  

c3.cd(3); 
c3.cd(3)->SetLogy();  
hInvMassGGEtaF_rec->Draw("SAME");
hInvMassGGEtaF_rec->SetLineColor(kMagenta);  
hInvMassGGEtaF_rec_SmearedP->Draw("SAME");
hInvMassGGEtaF_rec_SmearedP->SetLineColor(kGreen+4); 

auto l3 = new TLegend(0.4, 0.6, 0.7, 0.8);
l3->SetHeader("ALICE 3 Study");
l3->SetBorderSize(0);
l3->SetFillStyle(0);
l3->SetTextSize(0.03);
l3->AddEntry(hInvMassGGEtaF,"hInvMassGGEtaF","l");
l3->AddEntry(hInvMassGGEtaF_SmearedP,"hInvMassGGEtaF_SmearedP","l");
l3->AddEntry(hInvMassGGEtaF_conv,"hInvMassGGEtaF_conv","l");
l3->AddEntry(hInvMassGGEtaF_conv_SmearedP,"hInvMassGGEtaF_conv_SmearedP","l");
l3->AddEntry(hInvMassGGEtaF_rec,"hInvMassGGEtaF_rec","l");
l3->AddEntry(hInvMassGGEtaF_rec_SmearedP,"hInvMassGGEtaF_rec_SmearedP","l");
//
l3->Draw("SAME");
c3.SaveAs("plots/hInvMassGGF_Eta.png");




///////////////   Pi0 pT PLOT    ///////////////

TH1D * hPtGGPi0F = (TH1D*) fileRec->Get("hPtGGPi0F");
TH1D * hPtGGPi0F_SmearedP = (TH1D*) fileRec->Get("hPtGGPi0F_SmearedP");
TH1D * hPtGGPi0F_rec = (TH1D*) fileRec->Get("hPtGGPi0F_rec");
TH1D * hPtGGPi0F_rec_SmearedP = (TH1D*) fileRec->Get("hPtGGPi0F_rec_SmearedP");
TH1D * hPtGGPi0F_conv = (TH1D*) fileRec->Get("hPtGGPi0F_conv");
TH1D * hPtGGPi0F_conv_SmearedP = (TH1D*) fileRec->Get("hPtGGPi0F_conv_SmearedP");

TH1F* hPtGGPi0F_Rebin               = (TH1F*) hPtGGPi0F->Rebin(4);
TH1F* hPtGGPi0F_SmearedP_Rebin      = (TH1F*) hPtGGPi0F_SmearedP->Rebin(4);
TH1F* hPtGGPi0F_rec_Rebin           = (TH1F*) hPtGGPi0F_rec->Rebin(4);
TH1F* hPtGGPi0F_rec_SmearedP_Rebin  = (TH1F*) hPtGGPi0F_rec_SmearedP->Rebin(4);
TH1F* hPtGGPi0F_conv_Rebin          = (TH1F*) hPtGGPi0F_conv->Rebin(4);
TH1F* hPtGGPi0F_conv_SmearedP_Rebin = (TH1F*) hPtGGPi0F_conv_SmearedP->Rebin(4);


TCanvas c4("c4", "c4", 1600, 1600);
c4.Divide(3,1 );
hPtGGPi0F_Rebin->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0F_SmearedP_Rebin->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0F_rec_Rebin->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0F_rec_SmearedP_Rebin->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0F_conv_Rebin->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0F_conv_SmearedP_Rebin->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");

c4.cd(1);
c4.cd(1)->SetLogy();
c4.cd(1)-> SetLeftMargin(0.2);
hPtGGPi0F_Rebin->GetYaxis()->SetTitleOffset(2.5);   
hPtGGPi0F_Rebin->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0F_Rebin->Draw("E1");
hPtGGPi0F_Rebin->SetLineColor(kBlue);  
hPtGGPi0F_SmearedP_Rebin->Draw("SAME,E1");
hPtGGPi0F_SmearedP_Rebin->SetLineColor(kRed);

c4.cd(2);
c4.cd(2)->SetLogy(); 
c4.cd(2)-> SetLeftMargin(0.2);
hPtGGPi0F_conv_Rebin->GetYaxis()->SetTitleOffset(2.5);   
hPtGGPi0F_conv_Rebin->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0F_conv_Rebin->Draw("SAME,E1");
hPtGGPi0F_conv_Rebin->SetLineColor(kOrange+4);  
hPtGGPi0F_conv_SmearedP_Rebin->Draw("SAME,E1");
hPtGGPi0F_conv_SmearedP_Rebin->SetLineColor(kCyan);  

c4.cd(3); 
c4.cd(3)->SetLogy();  
c4.cd(3)-> SetLeftMargin(0.2);   
hPtGGPi0F_rec_Rebin->GetYaxis()->SetTitleOffset(2.5);   
hPtGGPi0F_rec_Rebin->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0F_rec_Rebin->Draw("SAME,E1");
hPtGGPi0F_rec_Rebin->SetLineColor(kMagenta);  
//hPtGGPi0F_rec_SmearedP->Fit("gaus","V","E1");
hPtGGPi0F_rec_SmearedP_Rebin->Draw("SAME,E1");
hPtGGPi0F_rec_SmearedP_Rebin->SetLineColor(kGreen+4); 

c4.cd(1);

auto l4 = new TLegend(0.25, 0.2, 0.4, 0.5);
l4->SetHeader("ALICE 3 Study");
l4->SetBorderSize(0);
l4->SetFillStyle(0);
l4->SetTextSize(0.03);
l4->AddEntry(hPtGGPi0F_Rebin,"hPtGGPi0F","l");
l4->AddEntry(hPtGGPi0F_SmearedP_Rebin,"hPtGGPi0F_SmearedP","l");
l4->AddEntry(hPtGGPi0F_rec_Rebin,"hPtGGPi0F_rec","l");
l4->AddEntry(hPtGGPi0F_rec_SmearedP_Rebin,"hPtGGPi0F_rec_SmearedPc_SmearedP","l");
l4->AddEntry(hPtGGPi0F_conv_Rebin,"hPtGGPi0F_conv","l");
l4->AddEntry(hPtGGPi0F_conv_SmearedP_Rebin,"hPtGGPi0F_conv_SmearedP","l");
//
l4->Draw("SAME");
c4.SaveAs("plots/hPtGGPi0F.png");


///////////////   Eta pT PLOT    ///////////////

TH1D * hPtGGEtaF = (TH1D*) fileRec->Get("hPtGGEtaF");
TH1D * hPtGGEtaF_SmearedP = (TH1D*) fileRec->Get("hPtGGEtaF_SmearedP");
TH1D * hPtGGEtaF_rec = (TH1D*) fileRec->Get("hPtGGEtaF_rec");
TH1D * hPtGGEtaF_rec_SmearedP = (TH1D*) fileRec->Get("hPtGGEtaF_rec_SmearedP");
TH1D * hPtGGEtaF_conv = (TH1D*) fileRec->Get("hPtGGEtaF_conv");
TH1D * hPtGGEtaF_conv_SmearedP = (TH1D*) fileRec->Get("hPtGGEtaF_conv_SmearedP");

hPtGGEtaF->Rebin(4);
hPtGGEtaF_SmearedP->Rebin(4);
hPtGGEtaF_rec->Rebin(4);
hPtGGEtaF_rec_SmearedP->Rebin(4);
hPtGGEtaF_conv->Rebin(4);
hPtGGEtaF_conv_SmearedP->Rebin(4);

hPtGGEtaF->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaF_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaF_rec->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaF_rec_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaF_conv->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaF_conv_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");

TCanvas c5("c5", "c5", 1600, 1600);
c5.Divide(3,1);

c5.cd(1);
c5.cd(1)->SetLogy();  
c5.cd(1)-> SetLeftMargin(0.2);
hPtGGEtaF->GetYaxis()->SetTitleOffset(2.5);   
hPtGGEtaF->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaF->Draw("E!");
hPtGGEtaF->SetLineColor(kBlue);  
hPtGGEtaF_SmearedP->Draw("SAME,E1");
hPtGGEtaF_SmearedP->SetLineColor(kRed);

c5.cd(2);
c5.cd(2)->SetLogy();
c5.cd(2)-> SetLeftMargin(0.2);
hPtGGEtaF_conv->GetYaxis()->SetTitleOffset(2.5);    
hPtGGEtaF_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaF_conv->Draw("SAME,E1");
hPtGGEtaF_conv->SetLineColor(kOrange+4);  
hPtGGEtaF_conv_SmearedP->Draw("SAME,E1");
hPtGGEtaF_conv_SmearedP->SetLineColor(kCyan);  

c5.cd(3);
c5.cd(3)->SetLogy(); 
c5.cd(3)-> SetLeftMargin(0.2);
hPtGGEtaF_rec->GetYaxis()->SetTitleOffset(2.5);  
hPtGGEtaF_rec->GetXaxis()->SetRangeUser(0,5.0); 
hPtGGEtaF_rec->Draw("SAME,E1");
hPtGGEtaF_rec->SetLineColor(kMagenta);  
hPtGGEtaF_rec_SmearedP->Draw("SAME,E1");
hPtGGEtaF_rec_SmearedP->SetLineColor(kGreen+4); 
//TH1D* hPtGGEtaF_rec_SmearedP_FIT   = (TH1D*) hPtGGEtaF_rec_SmearedP->Clone("Fit");
//hPtGGEtaF_rec_SmearedP_FIT->Fit("gaus");
//hPtGGEtaF_rec_SmearedP_FIT->Draw("SAME,E1");
c5.cd(1);

auto l5 = new TLegend(0.25, 0.2, 0.4, 0.5);
l5->SetHeader("ALICE 3 Study");
l5->SetBorderSize(0);
l5->SetFillStyle(0);
l5->SetTextSize(0.03);
l5->AddEntry(hPtGGEtaF,"hPtGGEtaF","l");
l5->AddEntry(hPtGGEtaF_SmearedP,"hPtGGEtaF_SmearedP","l");
l5->AddEntry(hPtGGEtaF_rec,"hPtGGEtaF_rec","l");
l5->AddEntry(hPtGGEtaF_rec_SmearedP,"hPtGGEtaF_rec_SmearedP","l");
l5->AddEntry(hPtGGEtaF_conv,"hPtGGEtaF_conv","l");
l5->AddEntry(hPtGGEtaF_conv_SmearedP,"hPtGGEtaF_conv_SmearedP","l");
//
l5->Draw("SAME");
c5.SaveAs("plots/hPtGGEtaF.png");


///////////////  Pi0 Effiiency at different rapidity PLOT    ///////////////

TCanvas* c14 = new TCanvas("c14","c14",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c14, 0.3, 0.02, 0.02, 0.16);
c14->Divide(2,1);
c14->SetLogy();  
c14->cd(1);


TH2D * histRapPt_ALL_Pi0 = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH1 * histPt_ALL_rap1_75to3_Pi0 = histRapPt_ALL_Pi0->ProjectionY("histPt_MC_rap1_75to3",676,800); 
TH1 * histPt_ALL_rap3to4_Pi0 = histRapPt_ALL_Pi0->ProjectionY("histPt_MC_rap3to4",800,900); 
TH1 * histPt_ALL_rap1_75to4_Pi0 = histRapPt_ALL_Pi0->ProjectionY("histPt_MC_rap1_75to4",676,900); 

TH2D * histRapPt_REC_Pi0 = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
TH1 * histPt_REC_rap1_75to3_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap1_75to3_Pi0",676,800); 
TH1 * histPt_REC_rap3to4_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap3to4_Pi0",800,900); 
TH1 * histPt_REC_rap1_75to4_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap1_75to4_Pi0",676,900); 

//REBINNING
TH1F* histPt_ALL_rap1_75to3_Pi0_Rebin     = (TH1F*) histPt_ALL_rap1_75to3_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to3_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap3to4_Pi0_Rebin        = (TH1F*) histPt_ALL_rap3to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap3to4_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap1_75to4_Pi0_Rebin     = (TH1F*) histPt_ALL_rap1_75to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to4_Pi0_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap1_75to3_Pi0_Rebin     = (TH1F*) histPt_REC_rap1_75to3_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to3_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap3to4_Pi0_Rebin        = (TH1F*) histPt_REC_rap3to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap3to4_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap1_75to4_Pi0_Rebin     = (TH1F*) histPt_REC_rap1_75to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to4_Pi0_Rebin",&pt_bin_proj_fine[0]);


//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap1_75to3_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap3to4_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap1_75to4_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to3_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap3to4_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to4_Pi0_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Pi0  = (TH1F*) histPt_REC_rap1_75to3_Pi0_Rebin->Clone("histPt_RATIO_rap1_75to3_Pi0");
histPt_RATIO_rap1_75to3_Pi0->Divide(histPt_REC_rap1_75to3_Pi0_Rebin, histPt_ALL_rap1_75to3_Pi0_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap3to4_Pi0  = (TH1F*) histPt_REC_rap3to4_Pi0_Rebin->Clone("histPt_RATIO_rap3to4_Pi0");
histPt_RATIO_rap3to4_Pi0->Divide(histPt_REC_rap3to4_Pi0_Rebin, histPt_ALL_rap3to4_Pi0_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap1_75to4_Pi0  = (TH1F*) histPt_REC_rap1_75to4_Pi0_Rebin->Clone("histPt_RATIO_rap1_75to4_Pi0");
histPt_RATIO_rap1_75to4_Pi0->Divide(histPt_REC_rap1_75to4_Pi0_Rebin, histPt_ALL_rap1_75to4_Pi0_Rebin, 1,1,"B");


//histPt_RATIO_rap1_75to3_Pi0->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap1_75to3_Pi0->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Pi0,25,0.5, kBlue , kBlue);
histPt_RATIO_rap3to4_Pi0->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap3to4_Pi0,25,0.5, kRed , kRed);
histPt_RATIO_rap1_75to4_Pi0->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to4_Pi0,25,0.5, kBlack , kBlack);

//CHECKER
//TH1F* histPt_RATIO_CheckerF_Pi0  = (TH1F*) hPtGGPi0F_rec->Clone("histPt_RATIO_CheckerF_Pi0");
//histPt_RATIO_CheckerF_Pi0->Divide(hPtGGPi0F_rec, hPtGGPi0F, 1,1,"B");
//histPt_RATIO_CheckerF_Pi0->Draw("SAME");

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Pi0, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Pi0->GetXaxis()->SetRangeUser(0.0,10.0);
histPt_RATIO_rap1_75to3_Pi0->GetYaxis()->SetRangeUser(.0001,0.005);

auto l14 = new TLegend(0.4, 0.2, 0.9, 0.35);
l14->SetHeader("");
l14->SetBorderSize(0);
l14->SetFillStyle(0);
l14->SetTextSize(TextSize);
l14->AddEntry(histPt_RATIO_rap1_75to3_Pi0,"Pi0 efficiency: rapidity: 1.75-3 ","p");
l14->AddEntry(histPt_RATIO_rap3to4_Pi0,"Pi0 efficiency: rapidity: 3-4","p");
l14->AddEntry(histPt_RATIO_rap1_75to4_Pi0,"Pi0 efficiency: rapidity: 1.75-4","p");
//l14->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
l14->Draw("SAME");

TLatex *lt14a = new TLatex(0.2,0.8,"Pi0 Effiiency at different rapidity ");
SetStyleTLatex( lt14a, 0.03,4);
lt14a->Draw("SAME");

TLatex *lt14b = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt14b, 0.03,4);
lt14b->Draw("SAME");




//WITH MOMENTUM SMEARING
c14->cd(2);

TH2D * histRapPt_ALL_Pi0_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_SmearedP");
TH1 * histPt_ALL_rap3to4_Pi0_SmearedP = histRapPt_ALL_Pi0_SmearedP->ProjectionY("histPt_MC_rap3to4",800,900); 
TH1 * histPt_ALL_rap1_75to3_Pi0_SmearedP = histRapPt_ALL_Pi0_SmearedP->ProjectionY("histPt_MC_rap1_75to3",676,800); 
TH1 * histPt_ALL_rap1_75to4_Pi0_SmearedP = histRapPt_ALL_Pi0_SmearedP->ProjectionY("histPt_MC_rap1_75to4",676,900); 

TH2D * histRapPt_REC_Pi0_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec_SmearedP");
TH1 * histPt_REC_rap3to4_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap3to4_Pi0_SmearedP",800,900); 
TH1 * histPt_REC_rap1_75to3_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap1_75to3_Pi0_SmearedP",676,800); 
TH1 * histPt_REC_rap1_75to4_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap1_75to4_Pi0_SmearedP",676,900); 

//REBINNING
TH1F* histPt_ALL_rap1_75to3_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap1_75to3_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to3_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap3to4_Pi0_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap3to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap3to4_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap1_75to4_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap1_75to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to4_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap1_75to3_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap1_75to3_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to3_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap3to4_Pi0_SmearedP_Rebin        = (TH1F*) histPt_REC_rap3to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap3to4_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap1_75to4_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap1_75to4_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to4_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap1_75to3_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap3to4_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap1_75to4_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to3_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap3to4_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to4_Pi0_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Pi0_SmearedP  = (TH1F*) histPt_REC_rap1_75to3_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to3_Pi0_SmearedP");
histPt_RATIO_rap1_75to3_Pi0_SmearedP->Divide(histPt_REC_rap1_75to3_Pi0_SmearedP_Rebin, histPt_ALL_rap1_75to3_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap3to4_Pi0_SmearedP  = (TH1F*) histPt_REC_rap3to4_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap3to4_Pi0_SmearedP");
histPt_RATIO_rap3to4_Pi0_SmearedP->Divide(histPt_REC_rap3to4_Pi0_SmearedP_Rebin, histPt_ALL_rap3to4_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap1_75to4_Pi0_SmearedP  = (TH1F*) histPt_REC_rap1_75to4_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to4_Pi0_SmearedP");
histPt_RATIO_rap1_75to4_Pi0_SmearedP->Divide(histPt_REC_rap1_75to4_Pi0_SmearedP_Rebin, histPt_ALL_rap1_75to4_Pi0_SmearedP_Rebin, 1,1,"B");

//histPt_RATIO_rap1_75to3_Pi0->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap1_75to3_Pi0_SmearedP->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Pi0_SmearedP,21,0.5, kBlue , kBlue);
histPt_RATIO_rap3to4_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap3to4_Pi0_SmearedP,21,0.5, kRed , kRed);
histPt_RATIO_rap1_75to4_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to4_Pi0_SmearedP,21,0.5, kBlack , kBlack);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Pi0_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Pi0_SmearedP->GetXaxis()->SetRangeUser(0.0,10.0);
histPt_RATIO_rap1_75to3_Pi0_SmearedP->GetYaxis()->SetRangeUser(.0001,0.005);

auto l14_SmearedP = new TLegend(0.4, 0.2, 0.9, 0.35);
l14_SmearedP->SetHeader("Pi0 Effiiency at different rapidity \n with momentum smearing");
l14_SmearedP->SetBorderSize(0);
l14_SmearedP->SetFillStyle(0);
l14_SmearedP->SetTextSize(TextSize);
l14_SmearedP->AddEntry(histPt_RATIO_rap1_75to3_Pi0_SmearedP,"Pi0 efficiency: rapidity: 1.75-3 ","p");
l14_SmearedP->AddEntry(histPt_RATIO_rap3to4_Pi0_SmearedP,"Pi0 efficiency: rapidity: 3-4","p");
l14_SmearedP->AddEntry(histPt_RATIO_rap1_75to4_Pi0_SmearedP,"Pi0 efficiency: rapidity: 1.75-4","p");
//l14_SmearedP->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
l14_SmearedP->Draw("SAME");

TLatex *lt14a_SmearedP = new TLatex(0.2,0.8,"#splitline{Pi0 Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lt14a_SmearedP, 0.03,4);
lt14a_SmearedP->Draw("SAME");

TLatex *lt14b_SmearedP = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt14b_SmearedP, 0.03,4);
lt14b_SmearedP->Draw("SAME");


c14->Update();

c14->SaveAs("plots/hDiffRap_ratio_Pi0_F.png");

c14->Close();






///////////////  Eta Effiiency at different rapidity PLOT    ///////////////

TCanvas* c15 = new TCanvas("c15","c15",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c15, 0.3, 0.02, 0.02, 0.16);
c15->Divide(2,1);
c15->SetLogy();  
c15->cd(1);


TH2D * histRapPt_ALL_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH1 * histPt_ALL_rap1_75to3_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap1_75to3",676,800); 
TH1 * histPt_ALL_rap3to4_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap3to4",800,900); 
TH1 * histPt_ALL_rap1_75to4_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap1_75to4",676,900); 

TH2D * histRapPt_REC_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");
TH1 * histPt_REC_rap1_75to3_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap1_75to3_Eta",676,800); 
TH1 * histPt_REC_rap3to4_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap3to4_Eta",800,900); 
TH1 * histPt_REC_rap1_75to4_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap1_75to4_Eta",676,900); 

//REBINNING
TH1F* histPt_ALL_rap1_75to3_Eta_Rebin     = (TH1F*) histPt_ALL_rap1_75to3_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to3_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap3to4_Eta_Rebin        = (TH1F*) histPt_ALL_rap3to4_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap3to4_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap1_75to4_Eta_Rebin     = (TH1F*) histPt_ALL_rap1_75to4_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to4_Eta_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap1_75to3_Eta_Rebin     = (TH1F*) histPt_REC_rap1_75to3_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to3_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap3to4_Eta_Rebin        = (TH1F*) histPt_REC_rap3to4_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap3to4_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap1_75to4_Eta_Rebin     = (TH1F*) histPt_REC_rap1_75to4_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to4_Eta_Rebin",&pt_bin_proj_fine[0]);


//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap1_75to3_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap3to4_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap1_75to4_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to3_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap3to4_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to4_Eta_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Eta  = (TH1F*) histPt_REC_rap1_75to3_Eta_Rebin->Clone("histPt_RATIO_rap1_75to3_Eta");
histPt_RATIO_rap1_75to3_Eta->Divide(histPt_REC_rap1_75to3_Eta_Rebin, histPt_ALL_rap1_75to3_Eta_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap3to4_Eta  = (TH1F*) histPt_REC_rap3to4_Eta_Rebin->Clone("histPt_RATIO_rap3to4_Eta");
histPt_RATIO_rap3to4_Eta->Divide(histPt_REC_rap3to4_Eta_Rebin, histPt_ALL_rap3to4_Eta_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap1_75to4_Eta  = (TH1F*) histPt_REC_rap1_75to4_Eta_Rebin->Clone("histPt_RATIO_rap1_75to4_Eta");
histPt_RATIO_rap1_75to4_Eta->Divide(histPt_REC_rap1_75to4_Eta_Rebin, histPt_ALL_rap1_75to4_Eta_Rebin, 1,1,"B");


//histPt_RATIO_rap1_75to3_Eta->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap1_75to3_Eta->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Eta,25,0.5, kBlue , kBlue);
histPt_RATIO_rap3to4_Eta->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap3to4_Eta,25,0.5, kRed , kRed);
histPt_RATIO_rap1_75to4_Eta->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to4_Eta,25,0.5, kBlack , kBlack);

//CHECKER
//TH1F* histPt_RATIO_CheckerF_Eta  = (TH1F*) hPtGGEtaF_rec->Clone("histPt_RATIO_CheckerF_Eta");
//histPt_RATIO_CheckerF_Eta->Divide(hPtGGEtaF_rec, hPtGGEtaF, 1,1,"B");
//histPt_RATIO_CheckerF_Eta->Draw("SAME");

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Eta, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Eta->GetXaxis()->SetRangeUser(0.0,10.0);
histPt_RATIO_rap1_75to3_Eta->GetYaxis()->SetRangeUser(.0001,0.005);

auto l15 = new TLegend(0.4, 0.2, 0.9, 0.35);
l15->SetHeader("");
l15->SetBorderSize(0);
l15->SetFillStyle(0);
l15->SetTextSize(TextSize);
l15->AddEntry(histPt_RATIO_rap1_75to3_Eta,"Eta efficiency: rapidity: 1.75-3 ","p");
l15->AddEntry(histPt_RATIO_rap3to4_Eta,"Eta efficiency: rapidity: 3-4","p");
l15->AddEntry(histPt_RATIO_rap1_75to4_Eta,"Eta efficiency: rapidity: 1.75-4","p");
//l15->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
l15->Draw("SAME");

TLatex *lt15a = new TLatex(0.2,0.8,"Eta Effiiency at different rapidity ");
SetStyleTLatex( lt15a, 0.03,4);
lt15a->Draw("SAME");

TLatex *lt15b = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt15b, 0.03,4);
lt15b->Draw("SAME");




//WITH MOMENTUM SMEARING
c15->cd(2);

TH2D * histRapPt_ALL_Eta_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_SmearedP");
TH1 * histPt_ALL_rap3to4_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap3to4",800,900); 
TH1 * histPt_ALL_rap1_75to3_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap1_75to3",676,800); 
TH1 * histPt_ALL_rap1_75to4_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap1_75to4",676,900); 

TH2D * histRapPt_REC_Eta_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");
TH1 * histPt_REC_rap3to4_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap3to4_Eta_SmearedP",800,900); 
TH1 * histPt_REC_rap1_75to3_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap1_75to3_Eta_SmearedP",676,800); 
TH1 * histPt_REC_rap1_75to4_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap1_75to4_Eta_SmearedP",676,900); 

//REBINNING
TH1F* histPt_ALL_rap1_75to3_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap1_75to3_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to3_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap3to4_Eta_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap3to4_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap3to4_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap1_75to4_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap1_75to4_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap1_75to4_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap1_75to3_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap1_75to3_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to3_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap3to4_Eta_SmearedP_Rebin        = (TH1F*) histPt_REC_rap3to4_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap3to4_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap1_75to4_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap1_75to4_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap1_75to4_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap1_75to3_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap3to4_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap1_75to4_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to3_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap3to4_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap1_75to4_Eta_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Eta_SmearedP  = (TH1F*) histPt_REC_rap1_75to3_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to3_Eta_SmearedP");
histPt_RATIO_rap1_75to3_Eta_SmearedP->Divide(histPt_REC_rap1_75to3_Eta_SmearedP_Rebin, histPt_ALL_rap1_75to3_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap3to4_Eta_SmearedP  = (TH1F*) histPt_REC_rap3to4_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap3to4_Eta_SmearedP");
histPt_RATIO_rap3to4_Eta_SmearedP->Divide(histPt_REC_rap3to4_Eta_SmearedP_Rebin, histPt_ALL_rap3to4_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap1_75to4_Eta_SmearedP  = (TH1F*) histPt_REC_rap1_75to4_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to4_Eta_SmearedP");
histPt_RATIO_rap1_75to4_Eta_SmearedP->Divide(histPt_REC_rap1_75to4_Eta_SmearedP_Rebin, histPt_ALL_rap1_75to4_Eta_SmearedP_Rebin, 1,1,"B");

//histPt_RATIO_rap1_75to3_Eta->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap1_75to3_Eta_SmearedP->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Eta_SmearedP,21,0.5, kBlue , kBlue);
histPt_RATIO_rap3to4_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap3to4_Eta_SmearedP,21,0.5, kRed , kRed);
histPt_RATIO_rap1_75to4_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to4_Eta_SmearedP,21,0.5, kBlack , kBlack);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Eta_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Eta_SmearedP->GetXaxis()->SetRangeUser(0.0,10.0);
histPt_RATIO_rap1_75to3_Eta_SmearedP->GetYaxis()->SetRangeUser(.0001,0.005);

auto l15_SmearedP = new TLegend(0.4, 0.2, 0.9, 0.35);
l15_SmearedP->SetHeader("Eta Effiiency at different rapidity \n with momentum smearing");
l15_SmearedP->SetBorderSize(0);
l15_SmearedP->SetFillStyle(0);
l15_SmearedP->SetTextSize(TextSize);
l15_SmearedP->AddEntry(histPt_RATIO_rap1_75to3_Eta_SmearedP,"Eta efficiency: rapidity: 1.75-3 ","p");
l15_SmearedP->AddEntry(histPt_RATIO_rap3to4_Eta_SmearedP,"Eta efficiency: rapidity: 3-4","p");
l15_SmearedP->AddEntry(histPt_RATIO_rap1_75to4_Eta_SmearedP,"Eta efficiency: rapidity: 1.75-4","p");
//l15_SmearedP->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
l15_SmearedP->Draw("SAME");

TLatex *lt15a_SmearedP = new TLatex(0.2,0.8,"#splitline{Eta Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lt15a_SmearedP, 0.03,4);
lt15a_SmearedP->Draw("SAME");

TLatex *lt15b_SmearedP = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt15b_SmearedP, 0.03,4);
lt15b_SmearedP->Draw("SAME");


c15->Update();

c15->SaveAs("plots/hDiffRap_ratio_Eta_F.png");

c15->Close();






///////////////   Rapidity-pT PLOT    ///////////////

TH2D * hRapidityPt_Pi0_F            = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH2D * hRapidityPt_Pi0_F_GG         = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * hRapidityPt_Pi0_F_GG_conv    = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_conv");
TH2D * hRapidityPt_Pi0_F_GG_rec     = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
TH2D * hRapidityPt_Eta_F            = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");
TH2D * hRapidityPt_Eta_F_GG         = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH2D * hRapidityPt_Eta_F_GG_conv    = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_conv");
TH2D * hRapidityPt_Eta_F_GG_rec     = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");

TH2D * hRapidityPt_Pi0_F_SmearedP           = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_SmearedP");
TH2D * hRapidityPt_Pi0_F_GG_SmearedP        = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_SmearedP");
TH2D * hRapidityPt_Pi0_F_GG_conv_SmearedP   = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_conv_SmearedP");
TH2D * hRapidityPt_Pi0_F_GG_rec_SmearedP    = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec_SmearedP");
TH2D * hRapidityPt_Eta_F_SmearedP           = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_SmearedP");
TH2D * hRapidityPt_Eta_F_GG_SmearedP        = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_SmearedP");
TH2D * hRapidityPt_Eta_F_GG_conv_SmearedP   = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_conv_SmearedP");
TH2D * hRapidityPt_Eta_F_GG_rec_SmearedP    = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");

hRapidityPt_Pi0_F->Rebin2D(4,2);
hRapidityPt_Pi0_F_GG->Rebin2D(4,2);
hRapidityPt_Pi0_F_GG_conv->Rebin2D(4,2);
hRapidityPt_Pi0_F_GG_rec->Rebin2D(4,2);
hRapidityPt_Eta_F->Rebin2D(4,2);
hRapidityPt_Eta_F_GG->Rebin2D(4,2);
hRapidityPt_Eta_F_GG_conv->Rebin2D(4,2);
hRapidityPt_Eta_F_GG_rec->Rebin2D(4,2);

hRapidityPt_Pi0_F_SmearedP->Rebin2D(4,2);
hRapidityPt_Pi0_F_GG_SmearedP->Rebin2D(4,2);
hRapidityPt_Pi0_F_GG_conv_SmearedP->Rebin2D(4,2);
hRapidityPt_Pi0_F_GG_rec_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_F_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_F_GG_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_F_GG_conv_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_F_GG_rec_SmearedP->Rebin2D(4,2);

TCanvas c6("c6", "c6", 1600, 1600);
c6.Divide(2,2);
c6.cd(1);
hRapidityPt_Pi0_F->Draw("Colz");
hRapidityPt_Pi0_F->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F->GetYaxis()->SetTitle("pT (GeV/c)");

c6.cd(2);
hRapidityPt_Pi0_F_GG->Draw("ColZ");
hRapidityPt_Pi0_F_GG->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG->GetYaxis()->SetTitle("pT (GeV/c)");

c6.cd(3);
hRapidityPt_Pi0_F_GG_conv->Draw("ColZ");
hRapidityPt_Pi0_F_GG_conv->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_conv->GetYaxis()->SetTitle("pT (GeV/c)");

c6.cd(4);
hRapidityPt_Pi0_F_GG_rec->Draw("ColZ");
hRapidityPt_Pi0_F_GG_rec->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_rec->GetYaxis()->SetTitle("pT (GeV/c)");

c6.SaveAs("plots/hRapidityPt_Pi0_F.png");




TCanvas c7("c7", "c7", 1600, 1600);
c7.Divide(2,2);
c7.cd(1);
hRapidityPt_Pi0_F_SmearedP->Draw("Colz");
hRapidityPt_Pi0_F_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c7.cd(2);
hRapidityPt_Pi0_F_GG_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_F_GG_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c7.cd(3);
hRapidityPt_Pi0_F_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c7.cd(4);
hRapidityPt_Pi0_F_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c7.SaveAs("plots/hRapidityPt_Pi0_F_SmearedP.png");


TCanvas c8("c8", "c8", 1600, 1600);
c8.Divide(2,2);
c8.cd(1);
hRapidityPt_Eta_F->Draw("Colz");
hRapidityPt_Eta_F->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F->GetYaxis()->SetTitle("pT (GeV/c)");

c8.cd(2);
hRapidityPt_Eta_F_GG->Draw("ColZ");
hRapidityPt_Eta_F_GG->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG->GetYaxis()->SetTitle("pT (GeV/c)");

c8.cd(3);
hRapidityPt_Eta_F_GG_conv->Draw("ColZ");
hRapidityPt_Eta_F_GG_conv->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_conv->GetYaxis()->SetTitle("pT (GeV/c)");

c8.cd(4);
hRapidityPt_Eta_F_GG_rec->Draw("ColZ");
hRapidityPt_Eta_F_GG_rec->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_rec->GetYaxis()->SetTitle("pT (GeV/c)");

c8.SaveAs("plots/hRapidityPt_Eta_F.png");




TCanvas c9("c9", "c9", 1600, 1600);
c9.Divide(2,2);
c9.cd(1);
hRapidityPt_Eta_F_SmearedP->Draw("Colz");
hRapidityPt_Eta_F_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c9.cd(2);
hRapidityPt_Eta_F_GG_SmearedP->Draw("ColZ");
hRapidityPt_Eta_F_GG_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c9.cd(3);
hRapidityPt_Eta_F_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Eta_F_GG_conv_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_conv_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c9.cd(4);
hRapidityPt_Eta_F_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Eta_F_GG_rec_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_rec_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c9.SaveAs("plots/hRapidityPt_Eta_F_SmearedP.png");





///////////////  Pi0 Rapidity-pT RATIO PLOT    ///////////////

TCanvas c10("c10", "c10", 1600, 1600);
c10.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_Pi0   = (TH2D*) hRapidityPt_Pi0_F->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Rec_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG->Clone("ReC vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Rec_Pi0->Divide(hRapidityPt_Pi0_F_GG_rec , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Rec_Pi0->Divide(hRapidityPt_Pi0_F_GG_rec ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Rec_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_Pi0->GetXaxis()->SetTitle("Rapidity");

c10.cd(1);
RapPt_ratio_ALL_Rec_Pi0->Draw("colz");
c10.cd(3);
RapPt_ratio_MC_Rec_Pi0->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Pi0   = (TH2D*) hRapidityPt_Pi0_F->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Conv_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_Pi0->GetXaxis()->SetTitle("Rapidity");

c10.cd(2);
RapPt_ratio_ALL_Conv_Pi0->Draw("colz");
c10.cd(4);
RapPt_ratio_MC_Conv_Pi0->Draw("colz");


c10.SaveAs("plots/hRapPt_ratio_Pi0_F.png");



TCanvas c11("c11", "c11", 1600, 1600);
c11.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_SmearedP_Pi0   = (TH2D*) hRapidityPt_Pi0_F->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Rec_SmearedP_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG->Clone("ReC vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Rec_SmearedP_Pi0->Divide(hRapidityPt_Pi0_F_GG_rec_SmearedP , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Rec_SmearedP_Pi0->Divide(hRapidityPt_Pi0_F_GG_rec_SmearedP ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Rec_SmearedP_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

c11.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Pi0->Draw("colz");
c11.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Pi0->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Pi0   = (TH2D*) hRapidityPt_Pi0_F_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_SmearedP_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Pi0->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

c11.cd(1);
RapPt_ratio_ALL_Conv_SmearedP_Pi0->Draw("colz");
c11.cd(3);
RapPt_ratio_MC_Conv_SmearedP_Pi0->Draw("colz");


c11.SaveAs("plots/hRapPt_ratio_Pi0_F_SmearedP.png");






///////////////  Eta Rapidity-pT RATIO PLOT    ///////////////

TCanvas c12("c12", "c12", 1600, 1600);
c12.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_Eta   = (TH2D*) hRapidityPt_Eta_F->Clone("ReC vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Rec_Eta    = (TH2D*) hRapidityPt_Eta_F_GG->Clone("ReC vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Rec_Eta->Divide(hRapidityPt_Eta_F_GG_rec , hRapidityPt_Eta_F,1,1,"B");
RapPt_ratio_MC_Rec_Eta->Divide(hRapidityPt_Eta_F_GG_rec ,  hRapidityPt_Eta_F_GG,1,1,"B");

RapPt_ratio_ALL_Rec_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_Eta->GetXaxis()->SetTitle("Rapidity");

c12.cd(1);
RapPt_ratio_ALL_Rec_Eta->Draw("colz");
c12.cd(3);
RapPt_ratio_MC_Rec_Eta->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Eta   = (TH2D*) hRapidityPt_Eta_F->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_Eta    = (TH2D*) hRapidityPt_Eta_F_GG->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_Eta->Divide(hRapidityPt_Eta_F_GG_conv , hRapidityPt_Eta_F,1,1,"B");
RapPt_ratio_MC_Conv_Eta->Divide(hRapidityPt_Eta_F_GG_conv ,  hRapidityPt_Eta_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_Eta->GetXaxis()->SetTitle("Rapidity");

c12.cd(2);
RapPt_ratio_ALL_Conv_Eta->Draw("colz");
c12.cd(4);
RapPt_ratio_MC_Conv_Eta->Draw("colz");


c12.SaveAs("plots/hRapPt_ratio_Eta_F.png");



TCanvas c13("c13", "c13", 1600, 1600);
c13.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_SmearedP_Eta   = (TH2D*) hRapidityPt_Eta_F->Clone("ReC vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Rec_SmearedP_Eta    = (TH2D*) hRapidityPt_Eta_F_GG->Clone("ReC vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Rec_SmearedP_Eta->Divide(hRapidityPt_Eta_F_GG_rec_SmearedP , hRapidityPt_Eta_F,1,1,"B");
RapPt_ratio_MC_Rec_SmearedP_Eta->Divide(hRapidityPt_Eta_F_GG_rec_SmearedP ,  hRapidityPt_Eta_F_GG,1,1,"B");

RapPt_ratio_ALL_Rec_SmearedP_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

c13.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Eta->Draw("colz");
c13.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Eta->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Eta   = (TH2D*) hRapidityPt_Eta_F_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Eta    = (TH2D*) hRapidityPt_Eta_F_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_SmearedP_Eta->Divide(hRapidityPt_Eta_F_GG_conv , hRapidityPt_Eta_F,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Eta->Divide(hRapidityPt_Eta_F_GG_conv ,  hRapidityPt_Eta_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Eta->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

c13.cd(1);
RapPt_ratio_ALL_Conv_SmearedP_Eta->Draw("colz");
c13.cd(3);
RapPt_ratio_MC_Conv_SmearedP_Eta->Draw("colz");


c13.SaveAs("plots/hRapPt_ratio_Eta_F_SmearedP.png");






///////////////   InVmass FIT PLOT    ///////////////

/////  Pi0   /////

TCanvas c16("c16", "c16", 1600, 1600);
c16.Divide(2,1);
c16.cd(1);
//c16.cd(1)->SetLogy();

SetStyleHistoTH1ForGraphs(hInvMassGGPi0F, "M_{#gamma#gamma} (GeV/c)^2)", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGPi0F , 0, 0, kBlack, kBlack);
DrawGammaSetMarker(hInvMassGGPi0F_SmearedP,20,0.8, kRed+2 , kRed+2);


TF1 *gs16_Pi0 = new TF1("gs16_Pi0", "gaus", 0.1, 0.2);
gs16_Pi0->SetParameters(.10, 0.547, 0.01);
hInvMassGGPi0F_SmearedP->Fit(gs16_Pi0,"LN");
gs16_Pi0->SetLineColor(kAzure+2);
gs16_Pi0->SetLineWidth(1);


hInvMassGGPi0F->GetXaxis()->SetRangeUser(0.1,0.2); 
hInvMassGGPi0F->Draw();
hInvMassGGPi0F_SmearedP->Draw("E1,SAME");
gs16_Pi0->Draw("SAME");


auto l16_Pi0 = new TLegend(0.55, 0.4, 0.7, 0.6);
l16_Pi0->SetHeader("");
l16_Pi0->SetBorderSize(0);
l16_Pi0->SetFillStyle(0);
l16_Pi0->SetTextSize(TextSize);
l16_Pi0->AddEntry(hInvMassGGPi0F,"Invariant Mass Histogram: #pi^0","l");
l16_Pi0->AddEntry(hInvMassGGPi0F_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l16_Pi0->AddEntry(gs16_Pi0,"Gaussian Fit","l");
l16_Pi0->Draw("SAME");

TLatex *lt16_Pi0_a = new TLatex(0.45,0.8,"#splitline{Effect of Momentum Smearing: #pi^0}{Mean: 1.34924e-01, Sigma: 3.90711e-03} ");
SetStyleTLatex( lt16_Pi0_a, 0.025,4);
lt16_Pi0_a->Draw("SAME");

TLatex *lt16_Pi0_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt16_Pi0_b, 0.025,4);
lt16_Pi0_b->Draw("SAME");



/////  Eta   /////

c16.cd(2);
//c16.cd(2)->SetLogy();


SetStyleHistoTH1ForGraphs(hInvMassGGEtaF, "M_{#gamma#gamma} (GeV/c)^2)", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGEtaF , 0, 0, kBlack, kBlack);
DrawGammaSetMarker(hInvMassGGEtaF_SmearedP,20,0.8, kRed+2 , kRed+2);


TF1 *gs16_Eta = new TF1("gs16_Eta", "gaus", 0.4, 07);
gs16_Eta->SetParameters(.10, 0.547, 0.01);
hInvMassGGEtaF_SmearedP->Fit(gs16_Eta,"LN");
gs16_Eta->SetLineColor(kAzure+2);
gs16_Eta->SetLineWidth(1);


hInvMassGGEtaF->GetXaxis()->SetRangeUser(0.48,0.65); 
hInvMassGGEtaF->Draw();
hInvMassGGEtaF_SmearedP->Draw("E1,SAME");
gs16_Eta->Draw("SAME");


auto l16_Eta = new TLegend(0.55, 0.45, 0.7, 0.65);
l16_Eta->SetHeader("");
l16_Eta->SetBorderSize(0);
l16_Eta->SetFillStyle(0);
l16_Eta->SetTextSize(TextSize);
l16_Eta->AddEntry(hInvMassGGEtaF,"Invariant Mass Histogram: #pi^0","l");
l16_Eta->AddEntry(hInvMassGGEtaF_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l16_Eta->AddEntry(gs16_Eta,"Gaussian Fit","l");
l16_Eta->Draw("SAME");

TLatex *lt16_Eta_a = new TLatex(0.45,0.8,"#splitline{Effect of Momentum Smearing: #eta}{{Mean: 5.47432e-01, Sigma: 1.76798e-02} ");
SetStyleTLatex( lt16_Eta_a, 0.025,4);
lt16_Eta_a->Draw("SAME");

TLatex *lt16_Eta_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt16_Eta_b, 0.025,4);
lt16_Eta_b->Draw("SAME");


c16.SaveAs("plots/hInvMassGGF_FIT.png");





///////////////  InvariantMass-pT PLOT    ///////////////


TH2D * hInvMassPt_F            = (TH2D*) fileRec->Get("hInvMassPt_F");
TH2D * hInvMassPt_F_GG         = (TH2D*) fileRec->Get("hInvMassPt_F_GG");
TH2D * hInvMassPt_F_GG_conv    = (TH2D*) fileRec->Get("hInvMassPt_F_GG_conv");
TH2D * hInvMassPt_F_GG_rec     = (TH2D*) fileRec->Get("hInvMassPt_F_GG_rec");

TH2D * hInvMassPt_F_SmearedP           = (TH2D*) fileRec->Get("hInvMassPt_F_SmearedP");
TH2D * hInvMassPt_F_GG_SmearedP        = (TH2D*) fileRec->Get("hInvMassPt_F_GG_SmearedP");
TH2D * hInvMassPt_F_GG_conv_SmearedP   = (TH2D*) fileRec->Get("hInvMassPt_F_GG_conv_SmearedP");
TH2D * hInvMassPt_F_GG_rec_SmearedP    = (TH2D*) fileRec->Get("hInvMassPt_F_GG_rec_SmearedP");


TCanvas* c17 = new TCanvas("c17","c17",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c17, 0.3, 0.02, 0.02, 0.16);
c17->cd(1);

c17->Divide(2,2);
c17->SetLogx();  
c17->SetLogy();  
//c17->SetLogz();  

c17->cd(1);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F,"M_{#gamma#gamma}-pT of all tracks with same mother particle ","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c17->cd(2);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_GG,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_GG,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c17->cd(3);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_GG_conv,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_GG_conv,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with Conversion Probability","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c17->cd(4);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_GG_rec,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_GG_rec,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with Conversion Probability and Reconstruction eficiency","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c17->SaveAs("hInvMassPt_F.png");
c17->Close();



TCanvas* c18 = new TCanvas("c18","c18",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c18, 0.3, 0.02, 0.02, 0.16);
c18->Divide(2,2);

c18->cd(1);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same mother particle with smeared momentum","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c18->cd(2);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_GG_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_GG_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with smeared momentum","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c18->cd(3);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_GG_conv_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_GG_conv_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with smeared momentum with Conversion Probability","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c18->cd(4);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_F_GG_rec_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_F_GG_rec_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with smeared momentum with Conversion Probability and Reconstruction eficiency","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);


c18->SaveAs("./hInvMassPt_F_SmearedP.png");
c18->Close();









///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                ////////////////   BARREL   ///////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





///////////////   INVARIANT MASS PLOT    ///////////////

TH1D * hInvMassGGB = (TH1D*) fileRec->Get("hInvMassGGB");
TH1D * hInvMassGGB_SmearedP = (TH1D*) fileRec->Get("hInvMassGGB_SmearedP");
TH1D * hInvMassGGB_rec = (TH1D*) fileRec->Get("hInvMassGGB_rec");
TH1D * hInvMassGGB_rec_SmearedP = (TH1D*) fileRec->Get("hInvMassGGB_rec_SmearedP");
TH1D * hInvMassGGB_conv = (TH1D*) fileRec->Get("hInvMassGGB_conv");
TH1D * hInvMassGGB_conv_SmearedP = (TH1D*) fileRec->Get("hInvMassGGB_conv_SmearedP");

TCanvas c101("c101", "c101", 1600, 1600);
c101.Divide(3,1);

hInvMassGGB->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGB_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGB_rec->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGB_rec_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGB_conv->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGB_conv_SmearedP->GetYaxis()->SetTitle("N_{ev}");

hInvMassGGB->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGB_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGB_rec->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGB_rec_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGB_conv->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGB_conv_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");

c101.cd(1);
c101.cd(1)->SetLogy();  
hInvMassGGB->Draw();
hInvMassGGB->SetLineColor(kBlue);  
hInvMassGGB_SmearedP->Draw("SAME");
hInvMassGGB_SmearedP->SetLineColor(kRed);

c101.cd(3);
c101.cd(3)->SetLogy();  
hInvMassGGB_rec->Draw("SAME");
hInvMassGGB_rec->SetLineColor(kMagenta);  
hInvMassGGB_rec_SmearedP->Draw("SAME");
hInvMassGGB_rec_SmearedP->SetLineColor(kGreen+4); 

c101.cd(2);
c101.cd(2)->SetLogy();  
hInvMassGGB_conv->Draw("SAME");
hInvMassGGB_conv->SetLineColor(kMagenta);  
hInvMassGGB_conv_SmearedP->Draw("SAME");
hInvMassGGB_conv_SmearedP->SetLineColor(kCyan);  


auto l101 = new TLegend(0.4, 0.6, 0.7, 0.8);
l101->SetHeader("ALICE 3 Study");
l101->SetBorderSize(0);
l101->SetFillStyle(0);
l101->SetTextSize(0.03);
l101->AddEntry(hInvMassGGB,"hInvMassGGB","l");
l101->AddEntry(hInvMassGGB_SmearedP,"hInvMassGGB_SmearedP","l");
l101->AddEntry(hInvMassGGB_rec,"hInvMassGGB_rec","l");
l101->AddEntry(hInvMassGGB_rec_SmearedP,"hInvMassGGB_rec_SmearedP","l");
l101->AddEntry(hInvMassGGB_conv,"hInvMassGGB_conv","l");
l101->AddEntry(hInvMassGGB_conv_SmearedP,"hInvMassGGB_conv_SmearedP","l");

l101->Draw("SAME");
c101.SaveAs("plots/hInvMassGGB.png");


///////////////   Pi0 INVMASS PLOT    ///////////////

TH1D * hInvMassGGPi0B = (TH1D*) fileRec->Get("hInvMassGGPi0B");
TH1D * hInvMassGGPi0B_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0B_SmearedP");
TH1D * hInvMassGGPi0B_rec = (TH1D*) fileRec->Get("hInvMassGGPi0B_rec");
TH1D * hInvMassGGPi0B_rec_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0B_rec_SmearedP");
TH1D * hInvMassGGPi0B_conv = (TH1D*) fileRec->Get("hInvMassGGPi0B_conv");
TH1D * hInvMassGGPi0B_conv_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0B_conv_SmearedP");

TCanvas c102("c102", "c102", 1600, 1600);
c102.Divide(3,1);

hInvMassGGPi0B->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B_rec->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B_rec_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B_conv->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B_conv_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0B_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0B_rec->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0B_rec_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0B_conv->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGPi0B_conv_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");

c102.cd(1);
c102.cd(1)->SetLogy();  
hInvMassGGPi0B->Draw();
hInvMassGGPi0B->SetLineColor(kBlue);  
hInvMassGGPi0B_SmearedP->Draw("SAME");
hInvMassGGPi0B_SmearedP->SetLineColor(kRed);
hInvMassGGPi0B->GetXaxis()->SetRangeUser(0,0.5);

c102.cd(2);
c102.cd(2)->SetLogy();  
hInvMassGGPi0B_conv->Draw("SAME");
hInvMassGGPi0B_conv->SetLineColor(kOrange+4);  
hInvMassGGPi0B_conv_SmearedP->Draw("SAME");
hInvMassGGPi0B_conv_SmearedP->SetLineColor(kCyan);  
hInvMassGGPi0B_conv->GetXaxis()->SetRangeUser(0,0.5);

c102.cd(3); 
c102.cd(3)->SetLogy();  
hInvMassGGPi0B_rec->Draw("SAME");
hInvMassGGPi0B_rec->SetLineColor(kMagenta);  
hInvMassGGPi0B_rec_SmearedP->Draw("SAME");
hInvMassGGPi0B_rec_SmearedP->SetLineColor(kGreen+4); 
hInvMassGGPi0B_rec->GetXaxis()->SetRangeUser(0,0.5);

auto l102 = new TLegend(0.4, 0.6, 0.7, 0.8);
l102->SetHeader("ALICE 3 Study");
l102->SetBorderSize(0);
l102->SetFillStyle(0);
l102->SetTextSize(0.03);
l102->AddEntry(hInvMassGGPi0B,"hInvMassGGPi0B","l");
l102->AddEntry(hInvMassGGPi0B_SmearedP,"hInvMassGGPi0B_SmearedP","l");
l102->AddEntry(hInvMassGGPi0B_conv,"hInvMassGGPi0B_conv","l");
l102->AddEntry(hInvMassGGPi0B_conv_SmearedP,"hInvMassGGPi0B_conv_SmearedP","l");
l102->AddEntry(hInvMassGGPi0B_rec,"hInvMassGGPi0B_rec","l");
l102->AddEntry(hInvMassGGPi0B_rec_SmearedP,"hInvMassGGPi0B_rec_SmearedP","l");

l102->Draw("SAME");
c102.SaveAs("plots/hInvMassGGB_Pi0.png");




///////////////   Eta INVMASS PLOT    ///////////////

TH1D * hInvMassGGEtaB = (TH1D*) fileRec->Get("hInvMassGGEtaB");
TH1D * hInvMassGGEtaB_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaB_SmearedP");
TH1D * hInvMassGGEtaB_rec = (TH1D*) fileRec->Get("hInvMassGGEtaB_rec");
TH1D * hInvMassGGEtaB_rec_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaB_rec_SmearedP");
TH1D * hInvMassGGEtaB_conv = (TH1D*) fileRec->Get("hInvMassGGEtaB_conv");
TH1D * hInvMassGGEtaB_conv_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaB_conv_SmearedP");

TCanvas c103("c103", "c103", 1600, 1600);
c103.Divide(3,1);

hInvMassGGEtaB->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB_rec->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB_rec_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB_conv->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB_conv_SmearedP->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGEtaB_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGEtaB_rec->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGEtaB_rec_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGEtaB_conv->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");
hInvMassGGEtaB_conv_SmearedP->GetXaxis()->SetTitle("Invariant Mass (GeV/c^{2})");

c103.cd(1);
c103.cd(1)->SetLogy();  
hInvMassGGEtaB->Draw();
hInvMassGGEtaB->SetLineColor(kBlue);  
hInvMassGGEtaB_SmearedP->Draw("SAME");
hInvMassGGEtaB_SmearedP->SetLineColor(kRed);
hInvMassGGEtaB->GetXaxis()->SetRangeUser(0,0.8);

c103.cd(2);
c103.cd(2)->SetLogy();  
hInvMassGGEtaB_conv->Draw("SAME");
hInvMassGGEtaB_conv->SetLineColor(kOrange+4);  
hInvMassGGEtaB_conv_SmearedP->Draw("SAME");
hInvMassGGEtaB_conv_SmearedP->SetLineColor(kCyan);  
hInvMassGGEtaB_conv->GetXaxis()->SetRangeUser(0,0.8);

c103.cd(3); 
c103.cd(3)->SetLogy();  
hInvMassGGEtaB_rec->SetLineColor(kMagenta);  
hInvMassGGEtaB_rec->Draw("SAME");
hInvMassGGEtaB_rec_SmearedP->SetLineColor(kGreen+4); 
hInvMassGGEtaB_rec_SmearedP->Draw("SAME");
hInvMassGGEtaB_rec->GetXaxis()->SetRangeUser(0,0.8);

auto l103 = new TLegend(0.15, 0.6, 0.35, 0.8);
l103->SetHeader("ALICE 3 Study");
l103->SetBorderSize(0);
l103->SetFillStyle(0);
l103->SetTextSize(0.03);
l103->AddEntry(hInvMassGGEtaB,"hInvMassGGEtaB","l");
l103->AddEntry(hInvMassGGEtaB_SmearedP,"hInvMassGGEtaB_SmearedP","l");
l103->AddEntry(hInvMassGGEtaB_conv,"hInvMassGGEtaB_conv","l");
l103->AddEntry(hInvMassGGEtaB_conv_SmearedP,"hInvMassGGEtaB_conv_SmearedP","l");
l103->AddEntry(hInvMassGGEtaB_rec,"hInvMassGGEtaB_rec","l");
l103->AddEntry(hInvMassGGEtaB_rec_SmearedP,"hInvMassGGEtaB_rec_SmearedP","l");
//
l103->Draw("SAME");
c103.SaveAs("plots/hInvMassGGB_Eta.png");




///////////////   Pi0 pT PLOT    ///////////////

TH1D * hPtGGPi0B = (TH1D*) fileRec->Get("hPtGGPi0B");
TH1D * hPtGGPi0B_SmearedP = (TH1D*) fileRec->Get("hPtGGPi0B_SmearedP");
TH1D * hPtGGPi0B_rec = (TH1D*) fileRec->Get("hPtGGPi0B_rec");
TH1D * hPtGGPi0B_rec_SmearedP = (TH1D*) fileRec->Get("hPtGGPi0B_rec_SmearedP");
TH1D * hPtGGPi0B_conv = (TH1D*) fileRec->Get("hPtGGPi0B_conv");
TH1D * hPtGGPi0B_conv_SmearedP = (TH1D*) fileRec->Get("hPtGGPi0B_conv_SmearedP");

hPtGGPi0B->Rebin(4);
hPtGGPi0B_SmearedP->Rebin(4);
hPtGGPi0B_rec->Rebin(4);
hPtGGPi0B_rec_SmearedP->Rebin(4);
hPtGGPi0B_conv->Rebin(4);
hPtGGPi0B_conv_SmearedP->Rebin(4);

TCanvas c104("c104", "c104", 1600, 1600);
c104.Divide(3,1);

hPtGGPi0B->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0B_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0B_rec->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0B_rec_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0B_conv->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGPi0B_conv_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");

c104.cd(1);
c104.cd(1)->SetLogy();
c104.cd(1)-> SetLeftMargin(0.2);
hPtGGPi0B->GetYaxis()->SetTitleOffset(2.5);   
hPtGGPi0B->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0B->Draw("E1");
hPtGGPi0B->SetLineColor(kBlue);  
hPtGGPi0B_SmearedP->Draw("SAME,E1");
hPtGGPi0B_SmearedP->SetLineColor(kRed);

c104.cd(2);
c104.cd(2)->SetLogy();
c104.cd(2)-> SetLeftMargin(0.2);
hPtGGPi0B_conv->GetYaxis()->SetTitleOffset(2.5);
hPtGGPi0B_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0B_conv->Draw("SAME,E1");
hPtGGPi0B_conv->SetLineColor(kOrange+4);  
hPtGGPi0B_conv_SmearedP->Draw("SAME,E1");
hPtGGPi0B_conv_SmearedP->SetLineColor(kCyan);  

c104.cd(3); 
c104.cd(3)->SetLogy();  
c104.cd(3)-> SetLeftMargin(0.2);
hPtGGPi0B_rec->GetYaxis()->SetTitleOffset(2.5);
hPtGGPi0B_rec->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0B_rec->Draw("SAME,E1");
hPtGGPi0B_rec->SetLineColor(kMagenta);  
//hPtGGPi0B_rec_SmearedP->Fit("gaus","V","E1");
hPtGGPi0B_rec_SmearedP->Draw("SAME,E1");
hPtGGPi0B_rec_SmearedP->SetLineColor(kGreen+4); 

c104.cd(1); 
auto l104 = new TLegend(0.25, 0.2, 0.4, 0.5);
l104->SetHeader("ALICE 3 Study");
l104->SetBorderSize(0);
l104->SetFillStyle(0);
l104->SetTextSize(0.03);
l104->AddEntry(hPtGGPi0B,"hPtGGPi0B","l");
l104->AddEntry(hPtGGPi0B_SmearedP,"hPtGGPi0B_SmearedP","l");
l104->AddEntry(hPtGGPi0B_rec,"hPtGGPi0B_rec","l");
l104->AddEntry(hPtGGPi0B_rec_SmearedP,"hPtGGPi0B_rec_SmearedP","l");
l104->AddEntry(hPtGGPi0B_conv,"hPtGGPi0B_conv","l");
l104->AddEntry(hPtGGPi0B_conv_SmearedP,"hPtGGPi0B_conv_SmearedP","l");
//
l104->Draw("SAME");
c104.SaveAs("plots/hPtGGPi0B.png");


///////////////   Eta pT PLOT    ///////////////

TH1D * hPtGGEtaB = (TH1D*) fileRec->Get("hPtGGEtaB");
TH1D * hPtGGEtaB_SmearedP = (TH1D*) fileRec->Get("hPtGGEtaB_SmearedP");
TH1D * hPtGGEtaB_rec = (TH1D*) fileRec->Get("hPtGGEtaB_rec");
TH1D * hPtGGEtaB_rec_SmearedP = (TH1D*) fileRec->Get("hPtGGEtaB_rec_SmearedP");
TH1D * hPtGGEtaB_conv = (TH1D*) fileRec->Get("hPtGGEtaB_conv");
TH1D * hPtGGEtaB_conv_SmearedP = (TH1D*) fileRec->Get("hPtGGEtaB_conv_SmearedP");

hPtGGEtaB->Rebin(5);
hPtGGEtaB_SmearedP->Rebin(5);
hPtGGEtaB_conv->Rebin(5);
hPtGGEtaB_conv_SmearedP->Rebin(5);
hPtGGEtaB_rec->Rebin(10);
hPtGGEtaB_rec_SmearedP->Rebin(10);

TCanvas c105("c105", "c105", 1600, 1600);
c105.Divide(3,1);

hPtGGEtaB->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaB_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaB_conv->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaB_conv_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaB_rec->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");
hPtGGEtaB_rec_SmearedP->GetYaxis()->SetTitle("#frac{d^{2} N_{#pi^{0}}}{2#pi N_{ev} p_{T} dp_{T} dy} (GeV/c)^{2}");

c105.cd(1);
c105.cd(1)->SetLogy();  
c105.cd(1)-> SetLeftMargin(0.2);
hPtGGEtaB->GetYaxis()->SetTitleOffset(2.5); 
hPtGGEtaB->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaB->Draw("E1");
hPtGGEtaB->SetLineColor(kBlue);  
hPtGGEtaB_SmearedP->Draw("SAME,E1");
hPtGGEtaB_SmearedP->SetLineColor(kRed);

c105.cd(2);
c105.cd(2)->SetLogy();  
c105.cd(2)-> SetLeftMargin(0.2);
hPtGGEtaB_conv->GetYaxis()->SetTitleOffset(2.5); 
hPtGGEtaB_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaB_conv->Draw("SAME,E1");
hPtGGEtaB_conv->SetLineColor(kOrange+4);  
hPtGGEtaB_conv_SmearedP->Draw("SAME,E1");
hPtGGEtaB_conv_SmearedP->SetLineColor(kCyan);  

c105.cd(3);
c105.cd(3)->SetLogy();  
c105.cd(3)-> SetLeftMargin(0.2);
hPtGGEtaB_rec->GetYaxis()->SetTitleOffset(2.5); 
hPtGGEtaB_rec->GetXaxis()->SetRangeUser(0,5.0); 
hPtGGEtaB_rec->Draw("SAME,E1");
hPtGGEtaB_rec->SetLineColor(kMagenta);  
hPtGGEtaB_rec_SmearedP->Draw("SAME,E1");
hPtGGEtaB_rec_SmearedP->SetLineColor(kGreen+4); 
//TH1D* hPtGGEtaB_rec_SmearedP_FIT   = (TH1D*) hPtGGEtaB_rec_SmearedP->Clone("Fit");
//hPtGGEtaB_rec_SmearedP_FIT->Fit("gaus");
//hPtGGEtaB_rec_SmearedP_FIT->Draw("SAME");
c105.cd(1); 

auto l105 = new TLegend(0.25, 0.2, 0.4, 0.5);
l105->SetHeader("ALICE 3 Study");
l105->SetBorderSize(0);
l105->SetFillStyle(0);
l105->SetTextSize(0.03);
l105->AddEntry(hPtGGEtaB,"hPtGGEtaB","l");
l105->AddEntry(hPtGGEtaB_SmearedP,"hPtGGEtaB_SmearedP","l");
l105->AddEntry(hPtGGEtaB_rec,"hPtGGEtaB_rec","l");
l105->AddEntry(hPtGGEtaB_rec_SmearedP,"hPtGGEtaB_rec_SmearedP","l");
l105->AddEntry(hPtGGEtaB_conv,"hPtGGEtaB_conv","l");
l105->AddEntry(hPtGGEtaB_conv_SmearedP,"hPtGGEtaB_conv_SmearedP","l");
//
l105->Draw("SAME");
c105.SaveAs("plots/hPtGGEtaB.png");







///////////////  Pi0 Effiiency at different rapidity PLOT    ///////////////

TCanvas* c114 = new TCanvas("c114","c114",200,10,700,700);  // gives the page size
DrawGammaCanvasSettings( c114, 0.1, 0.02, 0.02, 0.1);
//c114->Divide(2,1);
c114->SetLogy();  

c114->cd(1);
TH2D * histRapPt_ALL_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH1 * histPt_ALL_rap0to1_3_Pi0_B    = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B",501,630); 
TH2D * histRapPt_REC_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");
TH1 * histPt_REC_rap0to1_3_Pi0_B    = histRapPt_REC_Pi0_B->ProjectionY("histPt_REC_rap0to1_3_Pi0_B",501,630); 

//SMEARED P
TH2D * histRapPt_ALL_Pi0_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Pi0_B_SmearedP    = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B_SmearedP",501,630); 
TH2D * histRapPt_REC_Pi0_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Pi0_B_SmearedP    = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Pi0_B_SmearedP",501,630);

//REBINNING
TH1F* histPt_ALL_rap0to1_3_Pi0_B_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Pi0_B_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Pi0_B_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Pi0_B  = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B_Rebin->Clone("histPt_RATIO_rap1_75to3_Pi0_B");
histPt_RATIO_rap1_75to3_Pi0_B->Divide(histPt_REC_rap0to1_3_Pi0_B_Rebin, histPt_ALL_rap0to1_3_Pi0_B_Rebin, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Pi0_B_SmearedP  = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to3_Pi0_B_SmearedP");
histPt_RATIO_rap1_75to3_Pi0_B_SmearedP->Divide(histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin, histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap1_75to3_Pi0_B->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Pi0_B,25,0.5, kBlack , kBlack);
//histPt_RATIO_rap1_75to3_Pi0_B_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Pi0_B_SmearedP,20,0.5, kBlue , kBlue);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Pi0_B, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Pi0_B->GetXaxis()->SetRangeUser(0.0,10.0);
histPt_RATIO_rap1_75to3_Pi0_B->GetYaxis()->SetRangeUser(.0000001,0.01);

auto l114 = new TLegend(0.4, 0.2, 0.9, 0.35);
l114->SetHeader("");
l114->SetBorderSize(0);
l114->SetFillStyle(0);
l114->SetTextSize(TextSize);
l114->AddEntry(histPt_RATIO_rap1_75to3_Pi0_B,"Pi0 efficiency: rapidity: |0-1.3| ","p");
//l114->AddEntry(histPt_RATIO_rap1_75to3_Pi0_B_SmearedP,"Pi0 efficiency with smearing: rapidity: |0-1.3|","p");
l114->Draw("SAME");

TLatex *lt114a = new TLatex(0.2,0.9,"Pi0 Effiiency at Barrel region ");
SetStyleTLatex( lt114a, 0.03,4);
lt114a->Draw("SAME");

TLatex *lt114b = new TLatex(0.7,0.9,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt114b, 0.03,4);
lt114b->Draw("SAME");

c114->SaveAs("plots/hDiffRap_Pi0_ratio_B.png");

c114->Close();



///////////////  Eta Effiiency at different rapidity PLOT    ///////////////


TCanvas* c115 = new TCanvas("c115","c115",200,10,700,700);  // gives the page size
DrawGammaCanvasSettings( c115, 0.15, 0.02, 0.02, 0.16);
//c115->Divide(2,1);
c115->SetLogy();  

TH2D * histRapPt_ALL_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH1 * histPt_ALL_rap0to1_3_Eta_B    = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap0to1_3_Eta_B",501,630); 
TH2D * histRapPt_REC_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");
TH1 * histPt_REC_rap0to1_3_Eta_B    = histRapPt_REC_Eta_B->ProjectionY("histPt_REC_rap0to1_3_Eta_B",501,630); 

//SMEARED P
TH2D * histRapPt_ALL_Eta_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Eta_B_SmearedP    = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Eta_B_SmearedP",501,630); 
TH2D * histRapPt_REC_Eta_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Eta_B_SmearedP    = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Eta_B_SmearedP",501,630);

//REBINNING
TH1F* histPt_ALL_rap0to1_3_Eta_B_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Eta_B_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Eta_B_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Eta_B  = (TH1F*) histPt_ALL_rap0to1_3_Eta_B_Rebin->Clone("histPt_RATIO_rap1_75to3_Eta_B");
histPt_RATIO_rap1_75to3_Eta_B->Divide(histPt_REC_rap0to1_3_Eta_B_Rebin, histPt_ALL_rap0to1_3_Eta_B_Rebin, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Eta_B_SmearedP  = (TH1F*) histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to3_Eta_B_SmearedP");
histPt_RATIO_rap1_75to3_Eta_B_SmearedP->Divide(histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin, histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap1_75to3_Eta_B->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Eta_B,25,0.5, kBlack , kBlack);
histPt_RATIO_rap1_75to3_Eta_B_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Eta_B_SmearedP,20,0.5, kBlue , kBlue);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Eta_B, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Eta_B->GetXaxis()->SetRangeUser(0.0,10.0);
histPt_RATIO_rap1_75to3_Eta_B->GetYaxis()->SetRangeUser(.0000001,0.01);

auto l115 = new TLegend(0.4, 0.2, 0.9, 0.35);
l115->SetHeader("");
l115->SetBorderSize(0);
l115->SetFillStyle(0);
l115->SetTextSize(TextSize);
l115->AddEntry(histPt_RATIO_rap1_75to3_Eta_B,"Eta efficiency: rapidity: |0-1.3| ","p");
//l115->AddEntry(histPt_RATIO_rap1_75to3_Eta_B_SmearedP,"Eta efficiency with smearing: rapidity: |0-1.3|","p");
l115->Draw("SAME");

TLatex *lt115a = new TLatex(0.2,0.9,"Eta Effiiency at Barrel region ");
SetStyleTLatex( lt115a, 0.03,4);
lt115a->Draw("SAME");

TLatex *lt115b = new TLatex(0.7,0.9,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt115b, 0.03,4);
lt115b->Draw("SAME");


c115->SaveAs("plots/hDiffRap_Eta_ratio_B.png");

c115->Close();




///////////////   Rapidity-pT PLOT    ///////////////

TH2D * hRapidityPt_Pi0_B            = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * hRapidityPt_Pi0_B_GG         = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH2D * hRapidityPt_Pi0_B_GG_conv    = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_conv");
TH2D * hRapidityPt_Pi0_B_GG_rec     = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");
TH2D * hRapidityPt_Eta_B            = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");
TH2D * hRapidityPt_Eta_B_GG         = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH2D * hRapidityPt_Eta_B_GG_conv    = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_conv");
TH2D * hRapidityPt_Eta_B_GG_rec     = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");

TH2D * hRapidityPt_Pi0_B_SmearedP           = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_SmearedP");
TH2D * hRapidityPt_Pi0_B_GG_SmearedP        = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH2D * hRapidityPt_Pi0_B_GG_conv_SmearedP   = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_conv_SmearedP");
TH2D * hRapidityPt_Pi0_B_GG_rec_SmearedP    = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");
TH2D * hRapidityPt_Eta_B_SmearedP           = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_SmearedP");
TH2D * hRapidityPt_Eta_B_GG_SmearedP        = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH2D * hRapidityPt_Eta_B_GG_conv_SmearedP   = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_conv_SmearedP");
TH2D * hRapidityPt_Eta_B_GG_rec_SmearedP    = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");

hRapidityPt_Pi0_B->Rebin2D(4,2);
hRapidityPt_Pi0_B_GG->Rebin2D(4,2);
hRapidityPt_Pi0_B_GG_conv->Rebin2D(4,2);
hRapidityPt_Pi0_B_GG_rec->Rebin2D(4,2);
hRapidityPt_Eta_B->Rebin2D(4,2);
hRapidityPt_Eta_B_GG->Rebin2D(4,2);
hRapidityPt_Eta_B_GG_conv->Rebin2D(4,2);
hRapidityPt_Eta_B_GG_rec->Rebin2D(4,2);

hRapidityPt_Pi0_B_SmearedP->Rebin2D(4,2);
hRapidityPt_Pi0_B_GG_SmearedP->Rebin2D(4,2);
hRapidityPt_Pi0_B_GG_conv_SmearedP->Rebin2D(4,2);
hRapidityPt_Pi0_B_GG_rec_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_B_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_B_GG_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_B_GG_conv_SmearedP->Rebin2D(4,2);
hRapidityPt_Eta_B_GG_rec_SmearedP->Rebin2D(4,2);

TCanvas c106("c106", "c106", 1600, 1600);
c106.Divide(2,2);
c106.cd(1);
hRapidityPt_Pi0_B->Draw("Colz");
hRapidityPt_Pi0_B->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");

c106.cd(2);
hRapidityPt_Pi0_B_GG->Draw("ColZ");
hRapidityPt_Pi0_B_GG->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG->GetYaxis()->SetTitle("pT (GeV/c)");

c106.cd(3);
hRapidityPt_Pi0_B_GG_conv->Draw("ColZ");
hRapidityPt_Pi0_B_GG_conv->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_conv->GetYaxis()->SetTitle("pT (GeV/c)");

c106.cd(4);
hRapidityPt_Pi0_B_GG_rec->Draw("ColZ");
hRapidityPt_Pi0_B_GG_rec->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_rec->GetYaxis()->SetTitle("pT (GeV/c)");

c106.SaveAs("plots/hRapidityPt_Pi0_B.png");




TCanvas c107("c107", "c107", 1600, 1600);
c107.Divide(2,2);
c107.cd(1);
hRapidityPt_Pi0_B_SmearedP->Draw("Colz");
hRapidityPt_Pi0_B_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c107.cd(2);
hRapidityPt_Pi0_B_GG_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_B_GG_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c107.cd(3);
hRapidityPt_Pi0_B_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c107.cd(4);
hRapidityPt_Pi0_B_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c107.SaveAs("plots/hRapidityPt_Pi0_B_SmearedP.png");


TCanvas c108("c108", "c108", 1600, 1600);
c108.Divide(2,2);
c108.cd(1);
hRapidityPt_Eta_B->Draw("Colz");
hRapidityPt_Eta_B->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");

c108.cd(2);
hRapidityPt_Eta_B_GG->Draw("ColZ");
hRapidityPt_Eta_B_GG->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG->GetYaxis()->SetTitle("pT (GeV/c)");

c108.cd(3);
hRapidityPt_Eta_B_GG_conv->Draw("ColZ");
hRapidityPt_Eta_B_GG_conv->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_conv->GetYaxis()->SetTitle("pT (GeV/c)");

c108.cd(4);
hRapidityPt_Eta_B_GG_rec->Draw("ColZ");
hRapidityPt_Eta_B_GG_rec->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_rec->GetYaxis()->SetTitle("pT (GeV/c)");

c108.SaveAs("plots/hRapidityPt_Eta_B.png");




TCanvas c109("c109", "c109", 1600, 1600);
c109.Divide(2,2);
c109.cd(1);
hRapidityPt_Eta_B_SmearedP->Draw("Colz");
hRapidityPt_Eta_B_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c109.cd(2);
hRapidityPt_Eta_B_GG_SmearedP->Draw("ColZ");
hRapidityPt_Eta_B_GG_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c109.cd(3);
hRapidityPt_Eta_B_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Eta_B_GG_conv_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_conv_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c109.cd(4);
hRapidityPt_Eta_B_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Eta_B_GG_rec_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_rec_SmearedP->GetYaxis()->SetTitle("pT (GeV/c)");

c109.SaveAs("plots/hRapidityPt_Eta_B_SmearedP.png");



///////////////  Pi0 Rapidity-pT RATIO PLOT    ///////////////

TCanvas c110("c110", "c110", 1600, 1600);
c110.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Rec_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG->Clone("ReC vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Rec_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_rec , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Rec_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_rec ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Rec_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_Pi0_B->GetXaxis()->SetTitle("Rapidity");

c110.cd(1);
RapPt_ratio_ALL_Rec_Pi0_B->Draw("colz");
c110.cd(3);
RapPt_ratio_MC_Rec_Pi0_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Conv_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_Pi0_B->GetXaxis()->SetTitle("Rapidity");

c110.cd(2);
RapPt_ratio_ALL_Conv_Pi0_B->Draw("colz");
c110.cd(4);
RapPt_ratio_MC_Conv_Pi0_B->Draw("colz");


c110.SaveAs("plots/hRapPt_ratio_Pi0_B.png");



TCanvas c111("c111", "c111", 1600, 1600);
c111.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_SmearedP_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Rec_SmearedP_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG->Clone("ReC vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_rec_SmearedP , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Rec_SmearedP_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_rec_SmearedP ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

c111.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->Draw("colz");
c111.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Pi0_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

c111.cd(1);
RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->Draw("colz");
c111.cd(3);
RapPt_ratio_MC_Conv_SmearedP_Pi0_B->Draw("colz");


c111.SaveAs("plots/hRapPt_ratio_Pi0_B_SmearedP.png");





///////////////  Eta Rapidity-pT RATIO PLOT    ///////////////

TCanvas c112("c112", "c112", 1600, 1600);
c112.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_Eta_B   = (TH2D*) hRapidityPt_Eta_B->Clone("ReC vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Rec_Eta_B    = (TH2D*) hRapidityPt_Eta_B_GG->Clone("ReC vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Rec_Eta_B->Divide(hRapidityPt_Eta_B_GG_rec , hRapidityPt_Eta_B,1,1,"B");
RapPt_ratio_MC_Rec_Eta_B->Divide(hRapidityPt_Eta_B_GG_rec ,  hRapidityPt_Eta_B_GG,1,1,"B");

RapPt_ratio_ALL_Rec_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_Eta_B->GetXaxis()->SetTitle("Rapidity");

c112.cd(1);
RapPt_ratio_ALL_Rec_Eta_B->Draw("colz");
c112.cd(3);
RapPt_ratio_MC_Rec_Eta_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Eta_B   = (TH2D*) hRapidityPt_Eta_B->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_Eta_B    = (TH2D*) hRapidityPt_Eta_B_GG->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv , hRapidityPt_Eta_B,1,1,"B");
RapPt_ratio_MC_Conv_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv ,  hRapidityPt_Eta_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_Eta_B->GetXaxis()->SetTitle("Rapidity");

c112.cd(2);
RapPt_ratio_ALL_Conv_Eta_B->Draw("colz");
c112.cd(4);
RapPt_ratio_MC_Conv_Eta_B->Draw("colz");


c112.SaveAs("plots/hRapPt_ratio_Eta_B.png");



TCanvas c113("c113", "c113", 1600, 1600);
c113.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_SmearedP_Eta_B   = (TH2D*) hRapidityPt_Eta_B->Clone("ReC vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Rec_SmearedP_Eta_B    = (TH2D*) hRapidityPt_Eta_B_GG->Clone("ReC vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Rec_SmearedP_Eta_B->Divide(hRapidityPt_Eta_B_GG_rec_SmearedP , hRapidityPt_Eta_B,1,1,"B");
RapPt_ratio_MC_Rec_SmearedP_Eta_B->Divide(hRapidityPt_Eta_B_GG_rec_SmearedP ,  hRapidityPt_Eta_B_GG,1,1,"B");

RapPt_ratio_ALL_Rec_SmearedP_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Rec_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Rec_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

c113.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Eta_B->Draw("colz");
c113.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Eta_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Eta_B   = (TH2D*) hRapidityPt_Eta_B_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Eta_B    = (TH2D*) hRapidityPt_Eta_B_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_SmearedP_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv , hRapidityPt_Eta_B,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv ,  hRapidityPt_Eta_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_ALL_Conv_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Eta_B->GetYaxis()->SetTitle("pT (GeV/c)");
RapPt_ratio_MC_Conv_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

c113.cd(1);
RapPt_ratio_ALL_Conv_SmearedP_Eta_B->Draw("colz");
c113.cd(3);
RapPt_ratio_MC_Conv_SmearedP_Eta_B->Draw("colz");


c113.SaveAs("plots/hRapPt_ratio_Eta_B_SmearedP.png");






///////////////   InVmass FIT PLOT    ///////////////

/////  Pi0   /////

TCanvas c116("c116", "c116", 1600, 1600);
c116.Divide(2,1);
c116.cd(1);
//c116.cd(1)->SetLogy();

SetStyleHistoTH1ForGraphs(hInvMassGGPi0B, "M_{#gamma#gamma} (GeV/c)^2)", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGPi0B , 0, 0, kBlack, kBlack);
DrawGammaSetMarker(hInvMassGGPi0B_SmearedP,20,0.8, kRed+2 , kRed+2);


TF1 *gs116_Pi0 = new TF1("gs116_Pi0", "gaus", 0.1, 0.2);
gs116_Pi0->SetParameters(.10, 0.547, 0.01);
hInvMassGGPi0B_SmearedP->Fit(gs116_Pi0,"LN");
gs116_Pi0->SetLineColor(kAzure+2);
gs116_Pi0->SetLineWidth(1);


hInvMassGGPi0B->GetXaxis()->SetRangeUser(0.1,0.2); 
hInvMassGGPi0B->Draw();
hInvMassGGPi0B_SmearedP->Draw("E1,SAME");
gs116_Pi0->Draw("SAME");


auto l116_Pi0 = new TLegend(0.55, 0.4, 0.7, 0.6);
l116_Pi0->SetHeader("");
l116_Pi0->SetBorderSize(0);
l116_Pi0->SetFillStyle(0);
l116_Pi0->SetTextSize(TextSize);
l116_Pi0->AddEntry(hInvMassGGPi0B,"Invariant Mass Histogram: #pi^0","l");
l116_Pi0->AddEntry(hInvMassGGPi0B_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l116_Pi0->AddEntry(gs116_Pi0,"Gaussian Fit","l");
l116_Pi0->Draw("SAME");

TLatex *lt116_Pi0_a = new TLatex(0.45,0.8,"#splitline{Effect of Momentum Smearing: #pi^0}{Mean: 1.34924e-01, Sigma: 3.90711e-03} ");
SetStyleTLatex( lt116_Pi0_a, 0.025,4);
lt116_Pi0_a->Draw("SAME");

TLatex *lt116_Pi0_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt116_Pi0_b, 0.025,4);
lt116_Pi0_b->Draw("SAME");



/////  Eta   /////

c116.cd(2);
//c116.cd(2)->SetLogy();


SetStyleHistoTH1ForGraphs(hInvMassGGEtaB, "M_{#gamma#gamma} (GeV/c)^2)", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGEtaB , 0, 0, kBlack, kBlack);
DrawGammaSetMarker(hInvMassGGEtaB_SmearedP,20,0.8, kRed+2 , kRed+2);


TF1 *gs116_Eta = new TF1("gs116_Eta", "gaus", 0.4, 07);
gs116_Eta->SetParameters(.10, 0.547, 0.01);
hInvMassGGEtaB_SmearedP->Fit(gs116_Eta,"LN");
gs116_Eta->SetLineColor(kAzure+2);
gs116_Eta->SetLineWidth(1);


hInvMassGGEtaB->GetXaxis()->SetRangeUser(0.48,0.65); 
hInvMassGGEtaB->Draw();
hInvMassGGEtaB_SmearedP->Draw("E1,SAME");
gs116_Eta->Draw("SAME");


auto l116_Eta = new TLegend(0.55, 0.45, 0.7, 0.65);
l116_Eta->SetHeader("");
l116_Eta->SetBorderSize(0);
l116_Eta->SetFillStyle(0);
l116_Eta->SetTextSize(TextSize);
l116_Eta->AddEntry(hInvMassGGEtaB,"Invariant Mass Histogram: #pi^0","l");
l116_Eta->AddEntry(hInvMassGGEtaB_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l116_Eta->AddEntry(gs116_Eta,"Gaussian Fit","l");
l116_Eta->Draw("SAME");

TLatex *lt116_Eta_a = new TLatex(0.45,0.8,"#splitline{Effect of Momentum Smearing: #eta}{{Mean: 5.47432e-01, Sigma: 1.76798e-02} ");
SetStyleTLatex( lt116_Eta_a, 0.025,4);
lt116_Eta_a->Draw("SAME");

TLatex *lt116_Eta_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt116_Eta_b, 0.025,4);
lt116_Eta_b->Draw("SAME");


c116.SaveAs("plots/hInvMassGGB_FIT.png");







///////////////  InvariantMass-pT PLOT    ///////////////


TH2D * hInvMassPt_B            = (TH2D*) fileRec->Get("hInvMassPt_B");
TH2D * hInvMassPt_B_GG         = (TH2D*) fileRec->Get("hInvMassPt_B_GG");
TH2D * hInvMassPt_B_GG_conv    = (TH2D*) fileRec->Get("hInvMassPt_B_GG_conv");
TH2D * hInvMassPt_B_GG_rec     = (TH2D*) fileRec->Get("hInvMassPt_B_GG_rec");

TH2D * hInvMassPt_B_SmearedP           = (TH2D*) fileRec->Get("hInvMassPt_B_SmearedP");
TH2D * hInvMassPt_B_GG_SmearedP        = (TH2D*) fileRec->Get("hInvMassPt_B_GG_SmearedP");
TH2D * hInvMassPt_B_GG_conv_SmearedP   = (TH2D*) fileRec->Get("hInvMassPt_B_GG_conv_SmearedP");
TH2D * hInvMassPt_B_GG_rec_SmearedP    = (TH2D*) fileRec->Get("hInvMassPt_B_GG_rec_SmearedP");


TCanvas* c117 = new TCanvas("c117","c117",-200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c117, 0.3, 0.02, 0.02, 0.16);
c117->cd(1);

c117->Divide(2,2);
c117->SetLogx();  
c117->SetLogy();  
//c117->SetLogz();  

c117->cd(1);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B,"M_{#gamma#gamma}-pT of all tracks with same mother particle ","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c117->cd(2);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_GG,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_GG,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c117->cd(3);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_GG_conv,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_GG_conv,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with Conversion Probability","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c117->cd(4);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_GG_rec,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_GG_rec,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with Conversion Probability and Reconstruction eficiency","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c117->SaveAs("plots/hInvMassPt_B.png");
c117->Close();



TCanvas* c118 = new TCanvas("c118","c118",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c118, 0.3, 0.02, 0.02, 0.16);
c118->Divide(2,2);

c118->cd(1);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same mother particle with smeared momentum","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c118->cd(2);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_GG_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_GG_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with smeared momentum","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c118->cd(3);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_GG_conv_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_GG_conv_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with smeared momentum with Conversion Probability","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);

c118->cd(4);
ConvGammaRebinWithBinCorrection2D(hInvMassPt_B_GG_rec_SmearedP,4,4,3);
DrawAutoGammaHisto2D(hInvMassPt_B_GG_rec_SmearedP,"M_{#gamma#gamma}-pT of all tracks with same #pi^0 and #eta mother particle with smeared momentum with Conversion Probability and Reconstruction eficiency","Invariant Mass #gamma#gamma (GeV/c^{2})","pT (GeV/c)","",1,-0.1,5.0,1,0,1);


c118->SaveAs("plots/hInvMassPt_B_SmearedP.png");
c118->Close();

}

