#include <fstream>
#include <memory>
#include <vector>
#include "TF1.h"
#include "TH2.h"
#include "TH1D.h"
#include "TString.h"
#include "TObjectTable.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionAdditional.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/FittingGammaConversion.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/ConversionFunctions.h"

TDatime     now;
std::fstream fFileErrLog;
std::fstream fFileDataLog;

TH1D**      fHistoBackgroundInvMassPtBin                         = nullptr;
TH1D**      fHistoSignalInvMassPtBin                = nullptr;

Double_t*   fMesonMass                                                  = nullptr;
Double_t*   fMesonIntDeltaRange                                         = nullptr;
Double_t*   fBGFitRange                                                 = nullptr;
Double_t*   fBGFitRangeLeft                                             = nullptr;
Double_t*   fMesonMassLeft                                              = nullptr;
Double_t*   fMesonTrueMass                                              = nullptr;
Double_t*   fMesonIntDeltaRangeWide                                     = nullptr;
Double_t*   fMesonIntDeltaRangeNarrow                                   = nullptr;
Double_t*   fMesonFitRange                                              = nullptr;

TF1 *       fFitReco                                                    = nullptr;


Double_t    fMesonMassExpect                                            = 0;   // expected meson mass
Double_t    fNEvents                                                    = 0;
Int_t       fMesonId                                                    = 0;
Int_t       fMode                                                       = -1;
Double_t     fMesonWidthExpect                                          = 0;


TString     fNameHistoTrue                                              = "";
TString     fEnergyFlag                                                 = "";
TString     fPrefix                                                     = "";
TString     fEventCutSelection                                          = "";

TH1D* FillProjectionX (TH2*, TString, Double_t, Double_t, Int_t);                                           // Fill Projection in according to Y bins
void FitSubtractedPureGaussianInvMassInPtBins(TH1D*, Int_t);                                                // Fits the invariant mass histos with a pure gaussian plus lin BG








