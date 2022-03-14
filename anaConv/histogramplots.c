#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"


void histogramplots(){

//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);

//   TO VANISH STAT BOX 
                                                ////////////////FORWARD///////////////

//TFile * fileRec = new TFile("./ana_withft3.root");
//TFile * fileRec = new TFile("./ana_211229_withft3.root");
TFile * fileRec = new TFile("./ana_pTcut_withft3.root");


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
hInvMassGGPi0F->GetYaxis()->SetTitle("N_{ev}");

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
hInvMassGGEtaF->GetYaxis()->SetTitle("N_{ev}");

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

TCanvas c4("c4", "c4", 1600, 1600);
c4.Divide(3,1);

c4.cd(1);
c4.cd(1)->SetLogy();  
hPtGGPi0F->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0F->Draw();
hPtGGPi0F->SetLineColor(kBlue);  
hPtGGPi0F_SmearedP->Draw("SAME");
hPtGGPi0F_SmearedP->SetLineColor(kRed);

c4.cd(2);
c4.cd(2)->SetLogy();  
hPtGGPi0F_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0F_conv->Draw("SAME");
hPtGGPi0F_conv->SetLineColor(kOrange+4);  
hPtGGPi0F_conv_SmearedP->Draw("SAME");
hPtGGPi0F_conv_SmearedP->SetLineColor(kCyan);  

c4.cd(3); 
c4.cd(3)->SetLogy();  
hPtGGPi0F_rec->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0F_rec->Draw("SAME");
hPtGGPi0F_rec->SetLineColor(kMagenta);  
//hPtGGPi0F_rec_SmearedP->Fit("gaus","V","E1");
hPtGGPi0F_rec_SmearedP->Draw("SAME");
hPtGGPi0F_rec_SmearedP->SetLineColor(kGreen+4); 
hPtGGPi0F->GetYaxis()->SetTitle("N_{ev}");

auto l4 = new TLegend(0.4, 0.6, 0.7, 0.8);
l4->SetHeader("ALICE 3 Study");
l4->SetBorderSize(0);
l4->SetFillStyle(0);
l4->SetTextSize(0.03);
l4->AddEntry(hPtGGPi0F,"hPtGGPi0F","l");
l4->AddEntry(hPtGGPi0F_SmearedP,"hPtGGPi0F_SmearedP","l");
l4->AddEntry(hPtGGPi0F_rec,"hPtGGPi0F_rec","l");
l4->AddEntry(hPtGGPi0F_rec_SmearedP,"hPtGGPi0F_rec_SmearedPc_SmearedP","l");
l4->AddEntry(hPtGGPi0F_conv,"hPtGGPi0F_conv","l");
l4->AddEntry(hPtGGPi0F_conv_SmearedP,"hPtGGPi0F_conv_SmearedP","l");
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

TCanvas c5("c5", "c5", 1600, 1600);
c5.Divide(3,1);

c5.cd(1);
c5.cd(1)->SetLogy();  
hPtGGEtaF->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaF->Draw();
hPtGGEtaF->SetLineColor(kBlue);  
hPtGGEtaF_SmearedP->Draw("SAME");
hPtGGEtaF_SmearedP->SetLineColor(kRed);

c5.cd(2);
c5.cd(2)->SetLogy();  
hPtGGEtaF_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaF_conv->Draw("SAME");
hPtGGEtaF_conv->SetLineColor(kOrange+4);  
hPtGGEtaF_conv_SmearedP->Draw("SAME");
hPtGGEtaF_conv_SmearedP->SetLineColor(kCyan);  

c5.cd(3);
c5.cd(3)->SetLogy();  
hPtGGEtaF_rec->GetXaxis()->SetRangeUser(0,5.0); 
hPtGGEtaF_rec->Draw("SAME");
hPtGGEtaF_rec->SetLineColor(kMagenta);  
hPtGGEtaF_rec_SmearedP->Draw("SAME");
hPtGGEtaF_rec_SmearedP->SetLineColor(kGreen+4); 
//TH1D* hPtGGEtaF_rec_SmearedP_FIT   = (TH1D*) hPtGGEtaF_rec_SmearedP->Clone("Fit");
//hPtGGEtaF_rec_SmearedP_FIT->Fit("gaus");
//hPtGGEtaF_rec_SmearedP_FIT->Draw("SAME");
hPtGGEtaF->GetYaxis()->SetTitle("N_{ev}");
c5.Update();

auto l5 = new TLegend(0.4, 0.6, 0.7, 0.8);
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


TCanvas c6("c6", "c6", 1600, 1600);
c6.Divide(2,2);
c6.cd(1);
hRapidityPt_Pi0_F->Draw("Colz");
hRapidityPt_Pi0_F->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F->GetYaxis()->SetTitle("pT");

c6.cd(2);
hRapidityPt_Pi0_F_GG->Draw("ColZ");
hRapidityPt_Pi0_F_GG->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG->GetYaxis()->SetTitle("pT");

c6.cd(3);
hRapidityPt_Pi0_F_GG_conv->Draw("ColZ");
hRapidityPt_Pi0_F_GG_conv->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_conv->GetYaxis()->SetTitle("pT");

c6.cd(4);
hRapidityPt_Pi0_F_GG_rec->Draw("ColZ");
hRapidityPt_Pi0_F_GG_rec->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_rec->GetYaxis()->SetTitle("pT");

c6.SaveAs("plots/hRapidityPt_Pi0_F.png");




TCanvas c7("c7", "c7", 1600, 1600);
c7.Divide(2,2);
c7.cd(1);
hRapidityPt_Pi0_F_SmearedP->Draw("Colz");
hRapidityPt_Pi0_F_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_SmearedP->GetYaxis()->SetTitle("pT");

c7.cd(2);
hRapidityPt_Pi0_F_GG_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_F_GG_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_SmearedP->GetYaxis()->SetTitle("pT");

c7.cd(3);
hRapidityPt_Pi0_F_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_conv_SmearedP->GetYaxis()->SetTitle("pT");

c7.cd(4);
hRapidityPt_Pi0_F_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_F_GG_rec_SmearedP->GetYaxis()->SetTitle("pT");

c7.SaveAs("plots/hRapidityPt_Pi0_F_SmearedP.png");


TCanvas c8("c8", "c8", 1600, 1600);
c8.Divide(2,2);
c8.cd(1);
hRapidityPt_Eta_F->Draw("Colz");
hRapidityPt_Eta_F->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F->GetYaxis()->SetTitle("pT");

c8.cd(2);
hRapidityPt_Eta_F_GG->Draw("ColZ");
hRapidityPt_Eta_F_GG->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG->GetYaxis()->SetTitle("pT");

c8.cd(3);
hRapidityPt_Eta_F_GG_conv->Draw("ColZ");
hRapidityPt_Eta_F_GG_conv->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_conv->GetYaxis()->SetTitle("pT");

c8.cd(4);
hRapidityPt_Eta_F_GG_rec->Draw("ColZ");
hRapidityPt_Eta_F_GG_rec->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_rec->GetYaxis()->SetTitle("pT");

c8.SaveAs("plots/hRapidityPt_Eta_F.png");




TCanvas c9("c9", "c9", 1600, 1600);
c9.Divide(2,2);
c9.cd(1);
hRapidityPt_Eta_F_SmearedP->Draw("Colz");
hRapidityPt_Eta_F_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_SmearedP->GetYaxis()->SetTitle("pT");

c9.cd(2);
hRapidityPt_Eta_F_GG_SmearedP->Draw("ColZ");
hRapidityPt_Eta_F_GG_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_SmearedP->GetYaxis()->SetTitle("pT");

c9.cd(3);
hRapidityPt_Eta_F_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Eta_F_GG_conv_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_conv_SmearedP->GetYaxis()->SetTitle("pT");

c9.cd(4);
hRapidityPt_Eta_F_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Eta_F_GG_rec_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hRapidityPt_Eta_F_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_F_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_F_GG_rec_SmearedP->GetYaxis()->SetTitle("pT");

c9.SaveAs("plots/hRapidityPt_Eta_F_SmearedP.png");





///////////////  Pi0 Rapidity-pT RATIO PLOT    ///////////////

TCanvas c10("c10", "c10", 1600, 1600);
c10.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_Pi0   = (TH2D*) hRapidityPt_Pi0_F->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Rec_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG->Clone("ReC vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Rec_Pi0->Divide(hRapidityPt_Pi0_F_GG_rec , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Rec_Pi0->Divide(hRapidityPt_Pi0_F_GG_rec ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Rec_Pi0->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Pi0->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_Pi0->GetXaxis()->SetTitle("Rapidity");

c10.cd(1);
RapPt_ratio_ALL_Rec_Pi0->Draw("colz");
c10.cd(3);
RapPt_ratio_MC_Rec_Pi0->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Pi0   = (TH2D*) hRapidityPt_Pi0_F->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Conv_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Pi0->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Pi0->GetYaxis()->SetTitle("pT");
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

RapPt_ratio_ALL_Rec_SmearedP_Pi0->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Pi0->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

c11.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Pi0->Draw("colz");
c11.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Pi0->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Pi0   = (TH2D*) hRapidityPt_Pi0_F_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Pi0    = (TH2D*) hRapidityPt_Pi0_F_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_SmearedP_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv , hRapidityPt_Pi0_F,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Pi0->Divide(hRapidityPt_Pi0_F_GG_conv ,  hRapidityPt_Pi0_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Pi0->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_SmearedP_Pi0->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Pi0->GetYaxis()->SetTitle("pT");
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

RapPt_ratio_ALL_Rec_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_Eta->GetXaxis()->SetTitle("Rapidity");

c12.cd(1);
RapPt_ratio_ALL_Rec_Eta->Draw("colz");
c12.cd(3);
RapPt_ratio_MC_Rec_Eta->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Eta   = (TH2D*) hRapidityPt_Eta_F->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_Eta    = (TH2D*) hRapidityPt_Eta_F_GG->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_Eta->Divide(hRapidityPt_Eta_F_GG_conv , hRapidityPt_Eta_F,1,1,"B");
RapPt_ratio_MC_Conv_Eta->Divide(hRapidityPt_Eta_F_GG_conv ,  hRapidityPt_Eta_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Eta->GetYaxis()->SetTitle("pT");
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

RapPt_ratio_ALL_Rec_SmearedP_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

c13.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Eta->Draw("colz");
c13.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Eta->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Eta   = (TH2D*) hRapidityPt_Eta_F_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Eta    = (TH2D*) hRapidityPt_Eta_F_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_SmearedP_Eta->Divide(hRapidityPt_Eta_F_GG_conv , hRapidityPt_Eta_F,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Eta->Divide(hRapidityPt_Eta_F_GG_conv ,  hRapidityPt_Eta_F_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Eta->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Conv_SmearedP_Eta->GetXaxis()->SetTitle("Rapidity");

c13.cd(1);
RapPt_ratio_ALL_Conv_SmearedP_Eta->Draw("colz");
c13.cd(3);
RapPt_ratio_MC_Conv_SmearedP_Eta->Draw("colz");


c13.SaveAs("plots/hRapPt_ratio_Eta_F_SmearedP.png");






///////////////  Pi0 Effiiency at different rapidity PLOT    ///////////////

TCanvas c14("c14", "c14", 1600, 1600);
c14.Divide(2,1);

c14.cd(1);
TH2D * histRapPt_ALL_Pi0 = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH1 * histPt_ALL_rap1_75to4_Pi0 = histRapPt_ALL_Pi0->ProjectionY("histPt_MC_rap1_75to4",1,1000); 
TH1 * histPt_ALL_rap3to4_Pi0 = histRapPt_ALL_Pi0->ProjectionY("histPt_MC_rap3to4",300,400); 
TH1 * histPt_ALL_rap1_75to3_Pi0 = histRapPt_ALL_Pi0->ProjectionY("histPt_MC_rap1_75to3",175,300); 

TH2D * histRapPt_REC_Pi0 = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
TH1 * histPt_REC_rap1_75to4_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap1_75to3_Pi0",1,1000); 
TH1 * histPt_REC_rap3to4_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap3to4_Pi0",300,400); 
TH1 * histPt_REC_rap1_75to3_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap1_75to3_Pi0",175,300); 

TH1F* histPt_RATIO_rap3to4_Pi0  = (TH1F*) histPt_REC_rap3to4_Pi0->Clone("histPt_RATIO_rap3to4_Pi0");
histPt_RATIO_rap3to4_Pi0->Divide(histPt_REC_rap3to4_Pi0, histPt_ALL_rap3to4_Pi0, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Pi0  = (TH1F*) histPt_REC_rap1_75to3_Pi0->Clone("histPt_RATIO_rap1_75to3_Pi0");
histPt_RATIO_rap1_75to3_Pi0->Divide(histPt_REC_rap1_75to3_Pi0, histPt_ALL_rap1_75to3_Pi0, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to4_Pi0  = (TH1F*) histPt_REC_rap1_75to4_Pi0->Clone("histPt_RATIO_rap1_75to4_Pi0");
histPt_RATIO_rap1_75to4_Pi0->Divide(histPt_REC_rap1_75to4_Pi0, histPt_ALL_rap1_75to4_Pi0, 1,1,"B");

histPt_RATIO_rap3to4_Pi0->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4_Pi0->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap3to4_Pi0->GetXaxis()->SetLogy();
histPt_RATIO_rap3to4_Pi0->SetMarkerStyle(3);
histPt_RATIO_rap3to4_Pi0->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3_Pi0->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3_Pi0->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Pi0->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Pi0->SetMarkerStyle(8);
c14.cd(1)->SetLogy();  
histPt_RATIO_rap3to4_Pi0->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4_Pi0->GetYaxis()->SetRangeUser(.0001,1.1);

histPt_RATIO_rap3to4_Pi0->Draw();
histPt_RATIO_rap1_75to3_Pi0->Draw("SAME");
histPt_RATIO_rap1_75to4_Pi0->Draw("SAME");

auto leg_Pi0_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Pi0_eff->SetHeader("ALICE 3 Study");
leg_Pi0_eff->SetBorderSize(0);
leg_Pi0_eff->SetFillStyle(0);
leg_Pi0_eff->SetTextSize(0.03);
leg_Pi0_eff->AddEntry(histPt_RATIO_rap1_75to3_Pi0,"Pi0 efficiency: rapidity: 1.75-3 ","p");
leg_Pi0_eff->AddEntry(histPt_RATIO_rap3to4_Pi0,"Pi0 efficiency: rapidity: 3-4","p");
leg_Pi0_eff->AddEntry(histPt_RATIO_rap1_75to4_Pi0,"Pi0 efficiency: rapidity: 1.75-4","p");
//leg_Pi0_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Pi0_eff->Draw("SAME");



c14.cd(2);
TH2D * histRapPt_ALL_Pi0_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_SmearedP");
TH1 * histPt_ALL_rap3to4_Pi0_SmearedP = histRapPt_ALL_Pi0_SmearedP->ProjectionY("histPt_MC_rap3to4",300,400); 
TH1 * histPt_ALL_rap1_75to3_Pi0_SmearedP = histRapPt_ALL_Pi0_SmearedP->ProjectionY("histPt_MC_rap1_75to3",175,300); 
TH1 * histPt_ALL_rap1_75to4_Pi0_SmearedP = histRapPt_ALL_Pi0_SmearedP->ProjectionY("histPt_MC_rap1_75to4",1,1000); 

TH2D * histRapPt_REC_Pi0_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec_SmearedP");
TH1 * histPt_REC_rap3to4_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap3to4_Pi0_SmearedP",300,400); 
TH1 * histPt_REC_rap1_75to3_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap1_75to3_Pi0_SmearedP",175,300); 
TH1 * histPt_REC_rap1_75to4_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap1_75to4_Pi0_SmearedP",1,1000); 

TH1F* histPt_RATIO_rap3to4_Pi0_SmearedP  = (TH1F*) histPt_REC_rap3to4_Pi0_SmearedP->Clone("histPt_RATIO_rap3to4_Pi0_SmearedP");
histPt_RATIO_rap3to4_Pi0_SmearedP->Divide(histPt_REC_rap3to4_Pi0_SmearedP, histPt_ALL_rap3to4_Pi0_SmearedP, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Pi0_SmearedP  = (TH1F*) histPt_REC_rap1_75to3_Pi0_SmearedP->Clone("histPt_RATIO_rap1_75to3_Pi0_SmearedP");
histPt_RATIO_rap1_75to3_Pi0_SmearedP->Divide(histPt_REC_rap1_75to3_Pi0_SmearedP, histPt_ALL_rap1_75to3_Pi0_SmearedP, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to4_Pi0_SmearedP  = (TH1F*) histPt_REC_rap1_75to4_Pi0_SmearedP->Clone("histPt_RATIO_rap1_75to4_Pi0_SmearedP");
histPt_RATIO_rap1_75to4_Pi0_SmearedP->Divide(histPt_REC_rap1_75to4_Pi0_SmearedP, histPt_ALL_rap1_75to4_Pi0_SmearedP, 1,1,"B");

c14.cd(2)->SetLogy();  
/*
histPt_REC_rap1_75to3_Pi0_SmearedP->Draw();
histPt_ALL_rap1_75to3_Pi0_SmearedP->Draw("SAME");
*/
histPt_RATIO_rap3to4_Pi0_SmearedP->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4_Pi0_SmearedP->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap3to4_Pi0_SmearedP->GetXaxis()->SetLogy();
histPt_RATIO_rap3to4_Pi0_SmearedP->SetMarkerStyle(3);
histPt_RATIO_rap3to4_Pi0_SmearedP->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3_Pi0_SmearedP->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3_Pi0_SmearedP->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Pi0_SmearedP->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Pi0_SmearedP->SetMarkerStyle(8);

c14.cd(2)->SetLogy();  
histPt_RATIO_rap3to4_Pi0_SmearedP->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4_Pi0_SmearedP->GetYaxis()->SetRangeUser(.0001,1.1);

histPt_RATIO_rap3to4_Pi0_SmearedP->Draw();
histPt_RATIO_rap1_75to3_Pi0_SmearedP->Draw("SAME");
histPt_RATIO_rap1_75to4_Pi0_SmearedP->Draw("SAME");

auto leg_Pi0_SmearedP_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Pi0_SmearedP_eff->SetHeader("ALICE 3 Study");
leg_Pi0_SmearedP_eff->SetBorderSize(0);
leg_Pi0_SmearedP_eff->SetFillStyle(0);
leg_Pi0_SmearedP_eff->SetTextSize(0.03);
leg_Pi0_SmearedP_eff->AddEntry(histPt_RATIO_rap1_75to3_Pi0_SmearedP,"Pi0 efficiency: rapidity: 1.75-3 ","p");
leg_Pi0_SmearedP_eff->AddEntry(histPt_RATIO_rap3to4_Pi0_SmearedP,"Pi0 efficiency: rapidity: 3-4","p");
leg_Pi0_SmearedP_eff->AddEntry(histPt_RATIO_rap1_75to4_Pi0_SmearedP,"Pi0 efficiency: rapidity: 1.75-4","p");
//leg_Pi0_SmearedP_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Pi0_SmearedP_eff->Draw("SAME");


c14.SaveAs("plots/hDiffRap_ratio_Pi0_F.png");






///////////////  Eta Effiiency at different rapidity PLOT    ///////////////
double fMaxPt=5.0;
const int nBinsPt=1001;
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 50) pt_bin_proj[i]            =  0.1*i;
      else if(i<60) pt_bin_proj[i]          = 0.5 + 0.2*(i-50);
      else if(i<70) pt_bin_proj[i]          = 2.0 + 0.5*(i-60);
      else if(i<78) pt_bin_proj[i]          = 3.0 + 1.0*(i-70);
      else pt_bin_proj[i]                   = fMaxPt;
}
Int_t nbinspt_proj  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;


TCanvas c15("c15", "c15", 1600, 1600);
c15.Divide(2,1);

c15.cd(1);
TH2D * histRapPt_ALL_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH1 * histPt_ALL_rap1_75to4_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap1_75to4",1,1000); 
TH1 * histPt_ALL_rap3to4_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap3to4",300,400); 
TH1 * histPt_ALL_rap1_75to3_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap1_75to3",175,300); 

TH2D * histRapPt_REC_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");
TH1 * histPt_REC_rap1_75to4_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap1_75to3_Eta",1,1000); 
TH1 * histPt_REC_rap3to4_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap3to4_Eta",300,400); 
TH1 * histPt_REC_rap1_75to3_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap1_75to3_Eta",175,300); 

TH1F* histPt_RATIO_rap3to4_Eta  = (TH1F*) histPt_REC_rap3to4_Eta->Clone("histPt_RATIO_rap3to4_Eta");
histPt_RATIO_rap3to4_Eta->Divide(histPt_REC_rap3to4_Eta, histPt_ALL_rap3to4_Eta, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Eta  = (TH1F*) histPt_REC_rap1_75to3_Eta->Clone("histPt_RATIO_rap1_75to3_Eta");
histPt_RATIO_rap1_75to3_Eta->Divide(histPt_REC_rap1_75to3_Eta, histPt_ALL_rap1_75to3_Eta, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to4_Eta  = (TH1F*) histPt_REC_rap1_75to4_Eta->Clone("histPt_RATIO_rap1_75to4_Eta");
histPt_RATIO_rap1_75to4_Eta->Divide(histPt_REC_rap1_75to4_Eta, histPt_ALL_rap1_75to4_Eta, 1,1,"B");

histPt_RATIO_rap3to4_Eta->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4_Eta->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap3to4_Eta->GetXaxis()->SetLogy();
histPt_RATIO_rap3to4_Eta->SetMarkerStyle(3);
histPt_RATIO_rap3to4_Eta->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3_Eta->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3_Eta->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Eta->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Eta->SetMarkerStyle(8);
c15.cd(1)->SetLogy();  
histPt_RATIO_rap3to4_Eta->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4_Eta->GetYaxis()->SetRangeUser(.0001,1.1);

TH1F* histPt_RATIO_rap3to4_Eta_Rebin      = (TH1F*) histPt_RATIO_rap3to4_Eta->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to3_Eta_Rebin   = (TH1F*) histPt_RATIO_rap1_75to3_Eta->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to4_Eta_Rebin   = (TH1F*) histPt_RATIO_rap1_75to4_Eta->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
//histPt_RATIO_rap3to4_Eta_Rebin->Draw();
//histPt_RATIO_rap1_75to3_Eta_Rebin->Draw("SAME");
//histPt_RATIO_rap1_75to4_Eta_Rebin->Draw("SAME");
histPt_RATIO_rap3to4_Eta->Draw();
histPt_RATIO_rap1_75to3_Eta->Draw("SAME");
histPt_RATIO_rap1_75to4_Eta->Draw("SAME");

auto leg_Eta_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Eta_eff->SetHeader("ALICE 3 Study");
leg_Eta_eff->SetBorderSize(0);
leg_Eta_eff->SetFillStyle(0);
leg_Eta_eff->SetTextSize(0.03);
leg_Eta_eff->AddEntry(histPt_RATIO_rap3to4_Eta_Rebin,"Eta efficiency: rapidity: 1.75-3 ","p");
leg_Eta_eff->AddEntry(histPt_RATIO_rap1_75to3_Eta_Rebin,"Eta efficiency: rapidity: 3-4","p");
leg_Eta_eff->AddEntry(histPt_RATIO_rap1_75to4_Eta_Rebin,"Eta efficiency: rapidity: 1.75-4","p");
//leg_Eta_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Eta_eff->Draw("SAME");



c15.cd(2);
TH2D * histRapPt_ALL_Eta_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_SmearedP");
TH1 * histPt_ALL_rap3to4_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap3to4",300,400); 
TH1 * histPt_ALL_rap1_75to3_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap1_75to3",180,300); 
TH1 * histPt_ALL_rap1_75to4_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap1_75to4",1,1000); 

TH2D * histRapPt_REC_Eta_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");
TH1 * histPt_REC_rap3to4_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap3to4_Eta_SmearedP",300,400); 
TH1 * histPt_REC_rap1_75to3_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap1_75to3_Eta_SmearedP",180,300); 
TH1 * histPt_REC_rap1_75to4_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap1_75to4_Eta_SmearedP",1,1000); 

TH1F* histPt_RATIO_rap3to4_Eta_SmearedP  = (TH1F*) histPt_REC_rap3to4_Eta_SmearedP->Clone("histPt_RATIO_rap3to4_Eta_SmearedP");
histPt_RATIO_rap3to4_Eta_SmearedP->Divide(histPt_REC_rap3to4_Eta_SmearedP, histPt_ALL_rap3to4_Eta_SmearedP, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Eta_SmearedP  = (TH1F*) histPt_REC_rap1_75to3_Eta_SmearedP->Clone("histPt_RATIO_rap1_75to3_Eta_SmearedP");
histPt_RATIO_rap1_75to3_Eta_SmearedP->Divide(histPt_REC_rap1_75to3_Eta_SmearedP, histPt_ALL_rap1_75to3_Eta_SmearedP, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to4_Eta_SmearedP  = (TH1F*) histPt_REC_rap1_75to4_Eta_SmearedP->Clone("histPt_RATIO_rap1_75to4_Eta_SmearedP");
histPt_RATIO_rap1_75to4_Eta_SmearedP->Divide(histPt_REC_rap1_75to4_Eta_SmearedP, histPt_ALL_rap1_75to4_Eta_SmearedP, 1,1,"B");

c15.cd(2)->SetLogy();  
/*
histPt_REC_rap1_75to3_Eta_SmearedP->Draw();
histPt_ALL_rap1_75to3_Eta_SmearedP->Draw("SAME");
*/
histPt_RATIO_rap3to4_Eta_SmearedP->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4_Eta_SmearedP->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap3to4_Eta_SmearedP->GetXaxis()->SetLogy();
histPt_RATIO_rap3to4_Eta_SmearedP->SetMarkerStyle(3);
histPt_RATIO_rap3to4_Eta_SmearedP->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3_Eta_SmearedP->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3_Eta_SmearedP->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Eta_SmearedP->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Eta_SmearedP->SetMarkerStyle(8);

c15.cd(2)->SetLogy();  
histPt_RATIO_rap3to4_Eta_SmearedP->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4_Eta_SmearedP->GetYaxis()->SetRangeUser(.0001,1.1);

TH1F* histPt_RATIO_rap3to4_Eta_SmearedP_Rebin      = (TH1F*) histPt_RATIO_rap3to4_Eta_SmearedP->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to3_Eta_SmearedP_Rebin   = (TH1F*) histPt_RATIO_rap1_75to3_Eta_SmearedP->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to4_Eta_SmearedP_Rebin   = (TH1F*) histPt_RATIO_rap1_75to4_Eta_SmearedP->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);

//histPt_RATIO_rap3to4_Eta_SmearedP_Rebin->Draw();
//histPt_RATIO_rap1_75to3_Eta_SmearedP_Rebin->Draw("SAME");
//histPt_RATIO_rap1_75to4_Eta_SmearedP_Rebin->Draw("SAME");
histPt_RATIO_rap3to4_Eta_SmearedP->Draw();
histPt_RATIO_rap1_75to3_Eta_SmearedP->Draw("SAME");
histPt_RATIO_rap1_75to4_Eta_SmearedP->Draw("SAME");

auto leg_Eta_SmearedP_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Eta_SmearedP_eff->SetHeader("ALICE 3 Study");
leg_Eta_SmearedP_eff->SetBorderSize(0);
leg_Eta_SmearedP_eff->SetFillStyle(0);
leg_Eta_SmearedP_eff->SetTextSize(0.03);
leg_Eta_SmearedP_eff->AddEntry(histPt_RATIO_rap1_75to3_Eta_SmearedP,"Eta efficiency: rapidity: 1.75-3 ","p");
leg_Eta_SmearedP_eff->AddEntry(histPt_RATIO_rap3to4_Eta_SmearedP,"Eta efficiency: rapidity: 3-4","p");
leg_Eta_SmearedP_eff->AddEntry(histPt_RATIO_rap1_75to4_Eta_SmearedP,"Eta efficiency: rapidity: 1.75-4","p");
//leg_Eta_SmearedP_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Eta_SmearedP_eff->Draw("SAME");


c15.SaveAs("plots/hDiffRap_ratio_Eta_F.png");




///////////////   InVmass FIT PLOT    ///////////////

TCanvas c16("c16", "c16", 1600, 1600);
c16.Divide(2,1);

c16.cd(1);
c16.cd(1)->SetLogy();  
TH1D* hInvMassGGPi0F_SmearedP_FIT   = (TH1D*) hInvMassGGPi0F_SmearedP->Clone("Fit");
hInvMassGGPi0F_SmearedP_FIT->Fit("gaus");
hInvMassGGPi0F_SmearedP_FIT->Draw("SAME");
hInvMassGGPi0F_SmearedP_FIT->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0F_SmearedP->SetLineColor(kBlue);
hInvMassGGPi0F_SmearedP_FIT->GetXaxis()->SetRangeUser(0,0.3); 

hInvMassGGPi0F_SmearedP->Draw("SAME");

c16.cd(2);
c16.cd(2)->SetLogy();  

//TH1D* hPtGGPi0F_rec_SmearedP_FIT   = (TH1D*) hPtGGPi0F_rec_SmearedP->Clone("Fit");

TH1D* hInvMassGGEtaF_SmearedP_FIT   = (TH1D*) hInvMassGGEtaF_SmearedP->Clone("Fit");
hInvMassGGEtaF_SmearedP_FIT->Fit("gaus");
hInvMassGGEtaF_SmearedP_FIT->Draw("SAME");
hInvMassGGEtaF_SmearedP_FIT->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaF_SmearedP->Draw("SAME");
hInvMassGGEtaF_SmearedP->SetLineColor(kBlue);
hInvMassGGEtaF_SmearedP_FIT->GetXaxis()->SetRangeUser(0.3,0.8); 

hInvMassGGEtaF_SmearedP->Draw("SAME");

auto l16 = new TLegend(0.2, 0.8, 0.5, 0.9);
l16->SetHeader("ALICE 3 Study: \n Gaussian fit for Smeared Momentum");
l16->SetBorderSize(0);
l16->SetFillStyle(0);
l16->SetTextSize(0.025);
//l16->AddEntry(hInvMassGGEtaF_SmearedP_FIT,"hInvMassGGEtaF_SmearedP_FIT","l");
//l16->AddEntry(hInvMassGGEtaF_SmearedP_FIT,"hInvMassGGEtaF_SmearedP_FIT","l");
l16->Draw("SAME");

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


TCanvas c17("c17", "c17", 1600, 1600);
c17.Divide(2,2);
c17.cd(1);
hInvMassPt_F->Draw("Colz");
hInvMassPt_F->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F->GetYaxis()->SetTitle("pT");

c17.cd(2);
hInvMassPt_F_GG->Draw("ColZ");
hInvMassPt_F_GG->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_GG->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_GG->GetYaxis()->SetTitle("pT");

c17.cd(3);
hInvMassPt_F_GG_conv->Draw("ColZ");
hInvMassPt_F_GG_conv->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_GG_conv->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_GG_conv->GetYaxis()->SetTitle("pT");

c17.cd(4);
hInvMassPt_F_GG_rec->Draw("ColZ");
hInvMassPt_F_GG_rec->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_GG_rec->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_GG_rec->GetYaxis()->SetTitle("pT");

c17.SaveAs("plots/hInvMassPt_F.png");




TCanvas c18("c18", "c18", 1600, 1600);
c18.Divide(2,2);
c18.cd(1);
hInvMassPt_F_SmearedP->Draw("Colz");
hInvMassPt_F_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_SmearedP->GetYaxis()->SetTitle("pT");

c18.cd(2);
hInvMassPt_F_GG_SmearedP->Draw("ColZ");
hInvMassPt_F_GG_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_GG_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_GG_SmearedP->GetYaxis()->SetTitle("pT");

c18.cd(3);
hInvMassPt_F_GG_conv_SmearedP->Draw("ColZ");
hInvMassPt_F_GG_conv_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_GG_conv_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_GG_conv_SmearedP->GetYaxis()->SetTitle("pT");

c18.cd(4);
hInvMassPt_F_GG_rec_SmearedP->Draw("ColZ");
hInvMassPt_F_GG_rec_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_F_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_F_GG_rec_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_F_GG_rec_SmearedP->GetYaxis()->SetTitle("pT");

c18.SaveAs("plots/hInvMassPt_F_SmearedP.png");










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




hInvMassGGB->GetYaxis()->SetTitle("N_{ev}");

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
hInvMassGGPi0B->GetYaxis()->SetTitle("N_{ev}");
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
hInvMassGGEtaB->GetYaxis()->SetTitle("N_{ev}");
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

TCanvas c104("c104", "c104", 1600, 1600);
c104.Divide(3,1);

c104.cd(1);
c104.cd(1)->SetLogy();  
hPtGGPi0B->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0B->Draw();
hPtGGPi0B->SetLineColor(kBlue);  
hPtGGPi0B_SmearedP->Draw("SAME");
hPtGGPi0B_SmearedP->SetLineColor(kRed);

c104.cd(2);
c104.cd(2)->SetLogy();  
hPtGGPi0B_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0B_conv->Draw("SAME");
hPtGGPi0B_conv->SetLineColor(kOrange+4);  
hPtGGPi0B_conv_SmearedP->Draw("SAME");
hPtGGPi0B_conv_SmearedP->SetLineColor(kCyan);  

c104.cd(3); 
c104.cd(3)->SetLogy();  
hPtGGPi0B_rec->GetXaxis()->SetRangeUser(0,5.0);
hPtGGPi0B_rec->Draw("SAME");
hPtGGPi0B_rec->SetLineColor(kMagenta);  
//hPtGGPi0B_rec_SmearedP->Fit("gaus","V","E1");
hPtGGPi0B_rec_SmearedP->Draw("SAME");
hPtGGPi0B_rec_SmearedP->SetLineColor(kGreen+4); 
hPtGGPi0B->GetYaxis()->SetTitle("N_{ev}");

auto l104 = new TLegend(0.4, 0.6, 0.7, 0.8);
l104->SetHeader("ALICE 3 Study");
l104->SetBorderSize(0);
l104->SetFillStyle(0);
l104->SetTextSize(0.03);
l104->AddEntry(hPtGGPi0B,"hPtGGPi0B","l");
l104->AddEntry(hPtGGPi0B_SmearedP,"hPtGGPi0B_SmearedP","l");
l104->AddEntry(hPtGGPi0B_rec,"hPtGGPi0B_rec","l");
l104->AddEntry(hPtGGPi0B_rec_SmearedP,"hPtGGPi0B_rec_SmearedPc_SmearedP","l");
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

TCanvas c105("c105", "c105", 1600, 1600);
c105.Divide(3,1);

c105.cd(1);
c105.cd(1)->SetLogy();  
hPtGGEtaB->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaB->Draw();
hPtGGEtaB->SetLineColor(kBlue);  
hPtGGEtaB_SmearedP->Draw("SAME");
hPtGGEtaB_SmearedP->SetLineColor(kRed);

c105.cd(2);
c105.cd(2)->SetLogy();  
hPtGGEtaB_conv->GetXaxis()->SetRangeUser(0,5.0);
hPtGGEtaB_conv->Draw("SAME");
hPtGGEtaB_conv->SetLineColor(kOrange+4);  
hPtGGEtaB_conv_SmearedP->Draw("SAME");
hPtGGEtaB_conv_SmearedP->SetLineColor(kCyan);  

c105.cd(3);
c105.cd(3)->SetLogy();  
hPtGGEtaB_rec->GetXaxis()->SetRangeUser(0,5.0); 
hPtGGEtaB_rec->Draw("SAME");
hPtGGEtaB_rec->SetLineColor(kMagenta);  
hPtGGEtaB_rec_SmearedP->Draw("SAME");
hPtGGEtaB_rec_SmearedP->SetLineColor(kGreen+4); 
//TH1D* hPtGGEtaB_rec_SmearedP_FIT   = (TH1D*) hPtGGEtaB_rec_SmearedP->Clone("Fit");
//hPtGGEtaB_rec_SmearedP_FIT->Fit("gaus");
//hPtGGEtaB_rec_SmearedP_FIT->Draw("SAME");
hPtGGEtaB->GetYaxis()->SetTitle("N_{ev}");
c105.Update();

auto l105 = new TLegend(0.4, 0.6, 0.7, 0.8);
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


TCanvas c106("c106", "c106", 1600, 1600);
c106.Divide(2,2);
c106.cd(1);
hRapidityPt_Pi0_B->Draw("Colz");
hRapidityPt_Pi0_B->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B->GetYaxis()->SetTitle("pT");

c106.cd(2);
hRapidityPt_Pi0_B_GG->Draw("ColZ");
hRapidityPt_Pi0_B_GG->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG->GetYaxis()->SetTitle("pT");

c106.cd(3);
hRapidityPt_Pi0_B_GG_conv->Draw("ColZ");
hRapidityPt_Pi0_B_GG_conv->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_conv->GetYaxis()->SetTitle("pT");

c106.cd(4);
hRapidityPt_Pi0_B_GG_rec->Draw("ColZ");
hRapidityPt_Pi0_B_GG_rec->GetXaxis()->SetRangeUser(-1.0,1.5);
hRapidityPt_Pi0_B_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_rec->GetYaxis()->SetTitle("pT");

c106.SaveAs("plots/hRapidityPt_Pi0_B.png");




TCanvas c107("c107", "c107", 1600, 1600);
c107.Divide(2,2);
c107.cd(1);
hRapidityPt_Pi0_B_SmearedP->Draw("Colz");
hRapidityPt_Pi0_B_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_SmearedP->GetYaxis()->SetTitle("pT");

c107.cd(2);
hRapidityPt_Pi0_B_GG_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_B_GG_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_SmearedP->GetYaxis()->SetTitle("pT");

c107.cd(3);
hRapidityPt_Pi0_B_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_conv_SmearedP->GetYaxis()->SetTitle("pT");

c107.cd(4);
hRapidityPt_Pi0_B_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Pi0_B_GG_rec_SmearedP->GetYaxis()->SetTitle("pT");

c107.SaveAs("plots/hRapidityPt_Pi0_B_SmearedP.png");


TCanvas c108("c108", "c108", 1600, 1600);
c108.Divide(2,2);
c108.cd(1);
hRapidityPt_Eta_B->Draw("Colz");
hRapidityPt_Eta_B->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B->GetYaxis()->SetTitle("pT");

c108.cd(2);
hRapidityPt_Eta_B_GG->Draw("ColZ");
hRapidityPt_Eta_B_GG->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG->GetYaxis()->SetTitle("pT");

c108.cd(3);
hRapidityPt_Eta_B_GG_conv->Draw("ColZ");
hRapidityPt_Eta_B_GG_conv->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_conv->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_conv->GetYaxis()->SetTitle("pT");

c108.cd(4);
hRapidityPt_Eta_B_GG_rec->Draw("ColZ");
hRapidityPt_Eta_B_GG_rec->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_rec->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_rec->GetYaxis()->SetTitle("pT");

c108.SaveAs("plots/hRapidityPt_Eta_B.png");




TCanvas c109("c109", "c109", 1600, 1600);
c109.Divide(2,2);
c109.cd(1);
hRapidityPt_Eta_B_SmearedP->Draw("Colz");
hRapidityPt_Eta_B_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_SmearedP->GetYaxis()->SetTitle("pT");

c109.cd(2);
hRapidityPt_Eta_B_GG_SmearedP->Draw("ColZ");
hRapidityPt_Eta_B_GG_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_SmearedP->GetYaxis()->SetTitle("pT");

c109.cd(3);
hRapidityPt_Eta_B_GG_conv_SmearedP->Draw("ColZ");
hRapidityPt_Eta_B_GG_conv_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_conv_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_conv_SmearedP->GetYaxis()->SetTitle("pT");

c109.cd(4);
hRapidityPt_Eta_B_GG_rec_SmearedP->Draw("ColZ");
hRapidityPt_Eta_B_GG_rec_SmearedP->GetXaxis()->SetRangeUser(-2.0,1.5);
hRapidityPt_Eta_B_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hRapidityPt_Eta_B_GG_rec_SmearedP->GetXaxis()->SetTitle("Rapidity");
hRapidityPt_Eta_B_GG_rec_SmearedP->GetYaxis()->SetTitle("pT");

c109.SaveAs("plots/hRapidityPt_Eta_B_SmearedP.png");



///////////////  Pi0 Rapidity-pT RATIO PLOT    ///////////////

TCanvas c110("c110", "c110", 1600, 1600);
c110.Divide(2,2);

TH2D* RapPt_ratio_ALL_Rec_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Rec_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG->Clone("ReC vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Rec_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_rec , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Rec_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_rec ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Rec_Pi0_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Pi0_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_Pi0_B->GetXaxis()->SetTitle("Rapidity");

c110.cd(1);
RapPt_ratio_ALL_Rec_Pi0_B->Draw("colz");
c110.cd(3);
RapPt_ratio_MC_Rec_Pi0_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Conv_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Pi0_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Pi0_B->GetYaxis()->SetTitle("pT");
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

RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

c111.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Pi0_B->Draw("colz");
c111.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Pi0_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Pi0_B   = (TH2D*) hRapidityPt_Pi0_B_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Pi0_B    = (TH2D*) hRapidityPt_Pi0_B_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Pi0");
RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv , hRapidityPt_Pi0_B,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Pi0_B->Divide(hRapidityPt_Pi0_B_GG_conv ,  hRapidityPt_Pi0_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_SmearedP_Pi0_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Pi0_B->GetYaxis()->SetTitle("pT");
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

RapPt_ratio_ALL_Rec_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_Eta_B->GetXaxis()->SetTitle("Rapidity");

c112.cd(1);
RapPt_ratio_ALL_Rec_Eta_B->Draw("colz");
c112.cd(3);
RapPt_ratio_MC_Rec_Eta_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_Eta_B   = (TH2D*) hRapidityPt_Eta_B->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_Eta_B    = (TH2D*) hRapidityPt_Eta_B_GG->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv , hRapidityPt_Eta_B,1,1,"B");
RapPt_ratio_MC_Conv_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv ,  hRapidityPt_Eta_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_Eta_B->GetYaxis()->SetTitle("pT");
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

RapPt_ratio_ALL_Rec_SmearedP_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Rec_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Rec_SmearedP_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Rec_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

c113.cd(2);
RapPt_ratio_ALL_Rec_SmearedP_Eta_B->Draw("colz");
c113.cd(4);
RapPt_ratio_MC_Rec_SmearedP_Eta_B->Draw("colz");


TH2D* RapPt_ratio_ALL_Conv_SmearedP_Eta_B   = (TH2D*) hRapidityPt_Eta_B_SmearedP->Clone("Conv vs ALL rapidity and pT distribution on Eta");
TH2D* RapPt_ratio_MC_Conv_SmearedP_Eta_B    = (TH2D*) hRapidityPt_Eta_B_GG_SmearedP->Clone("Conv vs MC rapidity and pT distribution on Eta");
RapPt_ratio_ALL_Conv_SmearedP_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv , hRapidityPt_Eta_B,1,1,"B");
RapPt_ratio_MC_Conv_SmearedP_Eta_B->Divide(hRapidityPt_Eta_B_GG_conv ,  hRapidityPt_Eta_B_GG,1,1,"B");

RapPt_ratio_ALL_Conv_SmearedP_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL_Conv_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

RapPt_ratio_MC_Conv_SmearedP_Eta_B->GetYaxis()->SetTitle("pT");
RapPt_ratio_MC_Conv_SmearedP_Eta_B->GetXaxis()->SetTitle("Rapidity");

c113.cd(1);
RapPt_ratio_ALL_Conv_SmearedP_Eta_B->Draw("colz");
c113.cd(3);
RapPt_ratio_MC_Conv_SmearedP_Eta_B->Draw("colz");


c113.SaveAs("plots/hRapPt_ratio_Eta_B_SmearedP.png");





///////////////  Meson Effiiency at different rapidity PLOT    ///////////////

TCanvas c114("c114", "c114", 1600, 1600);
c114.Divide(2,1);

c114.cd(1);
TH2D * histRapPt_ALL_Pi0_B = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH1 * histPt_ALL_rap0to1_3_Pi0_B = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B",1,1000); 

TH2D * histRapPt_REC_Pi0_B = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");
TH1 * histPt_REC_rap0to1_3_Pi0_B  = histRapPt_REC_Pi0_B->ProjectionY("histPt_REC_rap0to1_3_Pi0_B",1,1000); 

TH1F* histPt_RATIO_rap0to1_3_Pi0_B  = (TH1F*) histPt_REC_rap0to1_3_Pi0_B->Clone("histPt_RATIO_rap0to1_3_Pi0_B");
histPt_RATIO_rap0to1_3_Pi0_B->Divide(histPt_REC_rap0to1_3_Pi0_B, histPt_ALL_rap0to1_3_Pi0_B, 1,1,"B");

histPt_RATIO_rap0to1_3_Pi0_B->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap0to1_3_Pi0_B->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap0to1_3_Pi0_B->GetXaxis()->SetLogy();
histPt_RATIO_rap0to1_3_Pi0_B->SetMarkerStyle(3);
histPt_RATIO_rap0to1_3_Pi0_B->SetLineColor(kRed);  

TH2D * histRapPt_ALL_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Pi0_B_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B_SmearedP",1,1000); 
TH2D * histRapPt_REC_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Pi0_B_SmearedP  = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Pi0_B_SmearedP",1,1000); 
TH1F* histPt_RATIO_rap0to1_3_Pi0_B_SmearedP  = (TH1F*) histPt_REC_rap0to1_3_Pi0_B_SmearedP->Clone("histPt_RATIO_rap0to1_3_Pi0_B_SmearedP");
histPt_RATIO_rap0to1_3_Pi0_B_SmearedP->Divide(histPt_REC_rap0to1_3_Pi0_B_SmearedP, histPt_ALL_rap0to1_3_Pi0_B_SmearedP, 1,1,"B");
histPt_RATIO_rap0to1_3_Pi0_B_SmearedP->SetMarkerStyle(4);
histPt_RATIO_rap0to1_3_Pi0_B_SmearedP->SetLineColor(kBlue);  

c114.cd(1)->SetLogy();  
histPt_RATIO_rap0to1_3_Pi0_B->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap0to1_3_Pi0_B->GetYaxis()->SetRangeUser(.0001,1.1);

histPt_RATIO_rap0to1_3_Pi0_B->Draw();
histPt_RATIO_rap0to1_3_Pi0_B_SmearedP->Draw("SAME");

auto leg_Pi0_eff_B = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Pi0_eff_B->SetHeader("ALICE 3 Study");
leg_Pi0_eff_B->SetBorderSize(0);
leg_Pi0_eff_B->SetFillStyle(0);
leg_Pi0_eff_B->SetTextSize(0.03);
leg_Pi0_eff_B->AddEntry(histPt_RATIO_rap0to1_3_Pi0_B,"Pi0 efficiency: rapidity: 0-1.3","p");
leg_Pi0_eff_B->AddEntry(histPt_RATIO_rap0to1_3_Pi0_B_SmearedP,"Pi0 efficiency Smeared P: rapidity: 0-1.3","p");
//leg_Pi0_eff_B->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Pi0_eff_B->Draw("SAME");


c114.cd(2);
TH2D * histRapPt_ALL_Eta_B = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH1 * histPt_ALL_rap0to1_3_Eta_B = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap0to1_3_Eta_B",1,1000); 

TH2D * histRapPt_REC_Eta_B = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");
TH1 * histPt_REC_rap0to1_3_Eta_B  = histRapPt_REC_Eta_B->ProjectionY("histPt_REC_rap0to1_3_Eta_B",1,1000); 

TH1F* histPt_RATIO_rap0to1_3_Eta_B  = (TH1F*) histPt_REC_rap0to1_3_Eta_B->Clone("histPt_RATIO_rap0to1_3_Eta_B");
histPt_RATIO_rap0to1_3_Eta_B->Divide(histPt_REC_rap0to1_3_Eta_B, histPt_ALL_rap0to1_3_Eta_B, 1,1,"B");

histPt_RATIO_rap0to1_3_Eta_B->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap0to1_3_Eta_B->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap0to1_3_Eta_B->GetXaxis()->SetLogy();
histPt_RATIO_rap0to1_3_Eta_B->SetMarkerStyle(3);
histPt_RATIO_rap0to1_3_Eta_B->SetLineColor(kRed);  

TH2D * histRapPt_ALL_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Eta_B_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Eta_B_SmearedP",1,1000); 
TH2D * histRapPt_REC_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Eta_B_SmearedP  = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Eta_B_SmearedP",1,1000); 
TH1F* histPt_RATIO_rap0to1_3_Eta_B_SmearedP  = (TH1F*) histPt_REC_rap0to1_3_Eta_B_SmearedP->Clone("histPt_RATIO_rap0to1_3_Eta_B_SmearedP");
histPt_RATIO_rap0to1_3_Eta_B_SmearedP->Divide(histPt_REC_rap0to1_3_Eta_B_SmearedP, histPt_ALL_rap0to1_3_Eta_B_SmearedP, 1,1,"B");
histPt_RATIO_rap0to1_3_Eta_B_SmearedP->SetMarkerStyle(4);
histPt_RATIO_rap0to1_3_Eta_B_SmearedP->SetLineColor(kBlue);  

c114.cd(2)->SetLogy();  
histPt_RATIO_rap0to1_3_Eta_B->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap0to1_3_Eta_B->GetYaxis()->SetRangeUser(.0001,1.1);

histPt_RATIO_rap0to1_3_Eta_B->Draw();
histPt_RATIO_rap0to1_3_Eta_B_SmearedP->Draw("SAME");

auto leg_Eta_eff_B = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Eta_eff_B->SetHeader("ALICE 3 Study");
leg_Eta_eff_B->SetBorderSize(0);
leg_Eta_eff_B->SetFillStyle(0);
leg_Eta_eff_B->SetTextSize(0.03);
leg_Eta_eff_B->AddEntry(histPt_RATIO_rap0to1_3_Eta_B,"Eta efficiency: rapidity: 0-1.3","p");
leg_Eta_eff_B->AddEntry(histPt_RATIO_rap0to1_3_Eta_B_SmearedP,"Eta efficiency Smeared P: rapidity: 0-1.3","p");
//leg_Eta_eff_B->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Eta_eff_B->Draw("SAME");

c114.SaveAs("plots/hDiffRap_ratio_B.png");




///////////////   InVmass FIT PLOT    ///////////////

TCanvas c116("c116", "c116", 1600, 1600);
c116.Divide(2,1);

c116.cd(1);
c116.cd(1)->SetLogy();  
TH1D* hInvMassGGPi0B_SmearedP_FIT   = (TH1D*) hInvMassGGPi0B_SmearedP->Clone("Fit");
hInvMassGGPi0B_SmearedP_FIT->Fit("gaus");
hInvMassGGPi0B_SmearedP_FIT->Draw("SAME");
hInvMassGGPi0B_SmearedP_FIT->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGPi0B_SmearedP->SetLineColor(kBlue);
hInvMassGGPi0B_SmearedP_FIT->GetXaxis()->SetRangeUser(0,0.3); 

hInvMassGGPi0B_SmearedP->Draw("SAME");

c116.cd(2);
c116.cd(2)->SetLogy();  

//TH1D* hPtGGPi0B_rec_SmearedP_FIT   = (TH1D*) hPtGGPi0B_rec_SmearedP->Clone("Fit");

TH1D* hInvMassGGEtaB_SmearedP_FIT   = (TH1D*) hInvMassGGEtaB_SmearedP->Clone("Fit");
hInvMassGGEtaB_SmearedP_FIT->Fit("gaus");
hInvMassGGEtaB_SmearedP_FIT->Draw("SAME");
hInvMassGGEtaB_SmearedP_FIT->GetYaxis()->SetTitle("N_{ev}");
hInvMassGGEtaB_SmearedP->Draw("SAME");
hInvMassGGEtaB_SmearedP->SetLineColor(kBlue);
hInvMassGGEtaB_SmearedP_FIT->GetXaxis()->SetRangeUser(0.3,0.8); 

hInvMassGGEtaB_SmearedP->Draw("SAME");

auto l116 = new TLegend(0.2, 0.8, 0.5, 0.9);
l116->SetHeader("ALICE 3 Study: \n Gaussian fit for Smeared Momentum");
l116->SetBorderSize(0);
l116->SetFillStyle(0);
l116->SetTextSize(0.025);
//l116->AddEntry(hInvMassGGEtaB_SmearedP_FIT,"hInvMassGGEtaB_SmearedP_FIT","l");
//l116->AddEntry(hInvMassGGEtaB_SmearedP_FIT,"hInvMassGGEtaB_SmearedP_FIT","l");
l116->Draw("SAME");

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


TCanvas c117("c117", "c117", 1600, 1600);
c117.Divide(2,2);
c117.cd(1);
hInvMassPt_B->Draw("Colz");
hInvMassPt_B->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B->GetYaxis()->SetTitle("pT");

c117.cd(2);
hInvMassPt_B_GG->Draw("ColZ");
hInvMassPt_B_GG->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_GG->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_GG->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_GG->GetYaxis()->SetTitle("pT");

c117.cd(3);
hInvMassPt_B_GG_conv->Draw("ColZ");
hInvMassPt_B_GG_conv->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_GG_conv->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_GG_conv->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_GG_conv->GetYaxis()->SetTitle("pT");

c117.cd(4);
hInvMassPt_B_GG_rec->Draw("ColZ");
hInvMassPt_B_GG_rec->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_GG_rec->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_GG_rec->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_GG_rec->GetYaxis()->SetTitle("pT");

c117.SaveAs("plots/hInvMassPt_B.png");




TCanvas c118("c118", "c118", 1600, 1600);
c118.Divide(2,2);
c118.cd(1);
hInvMassPt_B_SmearedP->Draw("Colz");
hInvMassPt_B_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_SmearedP->GetYaxis()->SetTitle("pT");

c118.cd(2);
hInvMassPt_B_GG_SmearedP->Draw("ColZ");
hInvMassPt_B_GG_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_GG_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_GG_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_GG_SmearedP->GetYaxis()->SetTitle("pT");

c118.cd(3);
hInvMassPt_B_GG_conv_SmearedP->Draw("ColZ");
hInvMassPt_B_GG_conv_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_GG_conv_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_GG_conv_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_GG_conv_SmearedP->GetYaxis()->SetTitle("pT");

c118.cd(4);
hInvMassPt_B_GG_rec_SmearedP->Draw("ColZ");
hInvMassPt_B_GG_rec_SmearedP->GetXaxis()->SetRangeUser(1.5,4.5);
hInvMassPt_B_GG_rec_SmearedP->GetYaxis()->SetRangeUser(-0.5,10.0);
hInvMassPt_B_GG_rec_SmearedP->GetXaxis()->SetTitle("nvasshInvMass");
hInvMassPt_B_GG_rec_SmearedP->GetYaxis()->SetTitle("pT");

c118.SaveAs("plots/hInvMassPt_B_SmearedP.png");




}

