Int_t collisionSystem = 1;
TFile * fileRec;

TLatex *ltb_system_Eta_B;
TLatex *ltb_system_Pi0_F;
TLatex *ltb_system_Pi0_B;
TLatex *ltb_system_Eta_F;

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.03;
Double_t TextSize_title=0.04;
Double_t TextSize_latex=20;
Double_t LabelOffsetLog=-0.015;

// BIN SETUP
Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;
