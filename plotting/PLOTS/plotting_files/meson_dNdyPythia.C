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

void meson_dNdyPythia(){


//SET THESE VARIABLES: 

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
gSystem->Exec("mkdir ./meson_dNdyPythia");
gSystem->cd("./meson_dNdyPythia");


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
plot_minY = 0.01;
plot_maxY = 100000.0;

//Pi0:
TH2D * histRapPt_ALL_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * histRapPt_ALL_Pi0_F          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
histRapPt_ALL_Pi0_B->Sumw2();
histRapPt_ALL_Pi0_F->Sumw2();

//Eta:
TH2D * histRapPt_ALL_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");
TH2D * histRapPt_ALL_Eta_F          = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");
histRapPt_ALL_Eta_B->Sumw2();
histRapPt_ALL_Eta_F->Sumw2();

TH1D * hNPrimChPiP = (TH1D*) fileRec->Get("hNPrimChPiP");
int NEvents = hNPrimChPiP->GetEntries();




TCanvas* meson_dNdyPythia = new TCanvas("meson_dNdyPythia","meson_dNdyPythia",600,600);  // gives the page size
DrawGammaCanvasSettings( meson_dNdyPythia, 0.1, 0.02, 0.02, 0.1);
meson_dNdyPythia->SetLogy();  
//meson_dNdyPythia->SetLogx();  


////////////////////////     Forward       //////////////////////////

    ///////////      Dividing in rapidity     ///////////

TAxis *xaxis_Pi0_F = histRapPt_ALL_Pi0_F->GetXaxis();
Int_t bin_Rap_F_Pi0_all1 = xaxis_Pi0_F->FindBin(Rap_F_all1 + epsilon);
Int_t bin_Rap_F_Pi0_all2 = xaxis_Pi0_F->FindBin(Rap_F_all2 - epsilon);

TH1 * histPt_ALL_rap_F_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Pi0",bin_Rap_F_Pi0_all1,bin_Rap_F_Pi0_all2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Eta",bin_Rap_F_Pi0_all1,bin_Rap_F_Pi0_all2); 


histPt_ALL_rap_F_mid1_to_mid2_Pi0->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta->Sumw2();



//REBINNING
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Sumw2();

//SCALING

DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin);


// Labelling //
SetStyleHistoTH1ForGraphs(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin, p_T.Data(), "1/(Bin_width*N_{ev})#frac{dN}{dy}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title,LabelOffsetY,LabelOffsetX);

// CHECKER LABELING //
DrawGammaSetMarker(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin,marker_F,1.0, Pi0_marker_color , Pi0_marker_color);
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Scale(1./NEvents);
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Scale(1./(Rap_F_all2-Rap_F_all1));
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Draw("E1");
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetXaxis()->SetRangeUser(plot_minPt,plot_maxPt);
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetYaxis()->SetRangeUser(plot_minY,plot_maxY);

DrawGammaSetMarker(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin,marker_F,1.0, Eta_marker_color , Eta_marker_color);
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Scale(1./NEvents);
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Scale(1./(Rap_F_all2-Rap_F_all1));
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Draw("SAME,E1");



////////////////////////     Barrel       //////////////////////////

    ///////////      Dividing in rapidity     ///////////
TAxis *xaxis_Pi0_B = histRapPt_ALL_Pi0_B->GetXaxis();
Int_t bin_Rap_B_Pi0_all1 = xaxis_Pi0_B->FindBin(Rap_B_all1 + epsilon);
Int_t bin_Rap_B_Pi0_all2 = xaxis_Pi0_B->FindBin(Rap_B_all2 - epsilon);

TH1 * histPt_ALL_rap_B_all1_to_all2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap_B_all1_to_all2_Pi0",bin_Rap_B_Pi0_all1,bin_Rap_B_Pi0_all2); 
TH1 * histPt_ALL_rap_B_all1_to_all2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap_B_all1_to_all2_Eta",bin_Rap_B_Pi0_all1,bin_Rap_B_Pi0_all2); 


histPt_ALL_rap_B_all1_to_all2_Pi0->Sumw2();
histPt_ALL_rap_B_all1_to_all2_Eta->Sumw2();



//REBINNING
TH1F* histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_B_all1_to_all2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_all1_to_all2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_B_all1_to_all2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_all1_to_all2_Eta_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->Sumw2();

//SCALING

DivideTH1ByBinWidth(histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_all1_to_all2_Eta_Rebin);

// CHECKER LABELING //
DrawGammaSetMarker(histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin,8,1.0, Pi0_marker_color , Pi0_marker_color);
histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->Scale(1./NEvents);
histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->Scale(1./(Rap_B_all2-Rap_B_all1));
histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->Draw("SAME,E1");
DrawGammaSetMarker(histPt_ALL_rap_B_all1_to_all2_Eta_Rebin,8,1.0, Eta_marker_color , Eta_marker_color);
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->Scale(1./NEvents);
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->Scale(1./(Rap_B_all2-Rap_B_all1));
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->Draw("SAME,E1");


auto l_dNdy_Pythia = new TLegend(0.6, 0.65, 0.9, 0.85);
l_dNdy_Pythia->SetHeader("");
l_dNdy_Pythia->SetBorderSize(0);
l_dNdy_Pythia->SetFillStyle(0);
l_dNdy_Pythia->SetTextSize(TextSize);
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");  
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");    
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_B_all1_to_all2_Eta_Rebin,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");  
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_F_all1,Rap_F_all2),"p");    
l_dNdy_Pythia->Draw("SAME");

SetStyleTLatex( ltb_general_Additional_text, 0.03,4);
ltb_general_Additional_text->Draw("SAME");

meson_dNdyPythia->SaveAs("./meson_dNdyPythia.png");
meson_dNdyPythia->Close();

const char *outputFile = "../ALICE3_significance_input.root"; // merge output files after analysis was run to keep file size moderate
auto fout = TFile::Open(outputFile, "UPDATE");
//TFile *outputfile = TFile::Open("../../ALICE3_significance_input.root","UPDATE");
fout->cd();
fout->mkdir(fcollisionSystem.Data());
fout->cd(fcollisionSystem.Data());

histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetXaxis()->SetTitle(p_T.Data());
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->SetName(Form("histPt_Signal_dNdy_rap_F_%0.2f_to_%0.2f_Pi0_Rebin",Rap_F_all1,Rap_F_all2));
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Write();

histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->GetXaxis()->SetTitle(p_T.Data());
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->SetName(Form("histPt_Signal_dNdy_rap_F_%0.2f_to_%0.2f_Eta_Rebin",Rap_F_all1,Rap_F_all2));
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Write();

histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->GetXaxis()->SetTitle(p_T.Data());
histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->SetName(Form("histPt_Signal_dNdy_rap_B_%0.2f_to_%0.2f_Pi0_Rebin",Rap_B_all1,Rap_B_all2));
histPt_ALL_rap_B_all1_to_all2_Pi0_Rebin->Write();

histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->GetXaxis()->SetTitle(p_T.Data());
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->SetName(Form("histPt_Signal_dNdy_rap_B_%0.2f_to_%0.2f_Eta_Rebin",Rap_B_all1,Rap_B_all2));
histPt_ALL_rap_B_all1_to_all2_Eta_Rebin->Write();

fout->Close();


}