// Include the string library
#include <string>

TFile * fileRec;

Int_t collisionSystem = 1;
TString fcollisionSystem ;

TLatex *ltb_system_Eta_B;
TLatex *ltb_system_Pi0_F;
TLatex *ltb_system_Pi0_B;
TLatex *ltb_system_Eta_F;

TLatex *ltb_Eta_B,*ltb_Pi0_F,*ltb_Pi0_B,*ltb_Eta_F;
TLatex *ltb_Eta_B_Additional_text,*ltb_Pi0_F_Additional_text,*ltb_Pi0_B_Additional_text,*ltb_Eta_F_Additional_text;
TLatex *ltb_general_Additional_text;

TString LightMeson[2][2]       = {{"Pi0","#pi^{0}"},{"Eta","#eta"}};
TString RapidityBlock[2][2]   = {{"B", "Barrel"},{"F", "Forward"}};

Double_t epsilon = 0.00001;
Double_t Rap_F_low1 = 1.75;
Double_t Rap_F_low2 = 3;
Double_t Rap_F_high1 = 3.0;
Double_t Rap_F_high2 = 4.0;
Double_t Rap_F_all1 = 1.75;
Double_t Rap_F_all2 = 4.0;


Double_t Rap_B_low1   = 0.0;
Double_t Rap_B_low2   = 0.8;
Double_t Rap_B_high1  = 0.8;
Double_t Rap_B_high2  = 1.3;
Double_t Rap_B_all1  = 0.0;
Double_t Rap_B_all2  = 1.3;



TString p_T = "p_{T} (GeV/c)";
TString momentum = "p (GeV/c)";

Float_t plot_minPt, plot_maxPt;
Float_t plot_minY, plot_maxY;
Float_t plot_minPt_log, plot_maxPt_log;

Int_t marker_size = 1;

Int_t marker_B = 24;
Int_t marker_F = 8;
Int_t Pi0_marker_color = 632 ;  //kRed
Int_t Eta_marker_color = 416+3; //kGreen+3

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.025;
Double_t TextSize_title=0.025;
Double_t TextSize_latex=20;
Double_t LabelOffsetX=1.5;
Double_t LabelOffsetY=1.5;

// BIN SETUP
Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;

