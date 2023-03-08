#include <TH1F.h>
#include <TCanvas.h>

void plot_hists()
{
    // Construct a histogram for 1/x with 50 bins, ranging from 0 to 5
    TH1F *hist_1overx = new TH1F("hist_1overx", "1/x Histogram", 50, 0, 5);
    for (int i=1; i<=50; i++) {
        double x = hist_1overx->GetBinCenter(i);
        hist_1overx->SetBinContent(i, 1/x);
    }

    // Define a fixed array for rebinning
    Double_t fixed_array[] = {0, 0.2, 0.5, 0.8, 1.2, 1.6, 2.0, 2.5, 3.0, 4.0, 5.0};
    const int nBinsFixed = sizeof(fixed_array)/sizeof(Double_t) - 1;

    // Create a new histogram by rebinning hist_1overx with respect to the fixed array
    TH1F *hist_rebinned = new TH1F("hist_rebinned", "Rebinned Histogram", nBinsFixed, fixed_array);
    hist_rebinned->Rebin(nBinsFixed, "hist_rebinned", fixed_array);

  
hist_1overx->Draw();
hist_rebinned->Draw("Same");
}