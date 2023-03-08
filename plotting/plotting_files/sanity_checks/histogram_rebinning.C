#include <iostream>
#include <TRandom.h>
#include <TH1F.h>
#include <TCanvas.h>
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"

void ScalingAfterRebin(TH1F *hist, TH1F *hist_r, Double_t binVals[])
{

    for (int i = 0; i < hist_r->GetNbinsX(); i++)
    {
        Int_t bin_before = hist->FindBin(binVals[i]);
        Int_t bin_after = hist->FindBin(binVals[i + 1]);
        Float_t scalefactor = bin_after - bin_before;
        Float_t bin_content = hist_r->GetBinContent(i);
        hist_r->SetBinContent(i, bin_content / scalefactor);
        cout << bin_before << " " << binVals[i] << " " << scalefactor << " " << bin_content << endl;
    }
}

void histogram_rebinning()
{

    // Create a histogram with a Gaussian distribution
    TH1F *h1 = new TH1F("h1", "Histogram with Gaussian Distribution", 100, -5, 5);
    for (int i = 0; i < 10000; i++)
    {
        h1->Fill(gRandom->Gaus(0, 1));
    }

    // Create a second histogram by rebinnning the first histogram
    const int nBins = 10;
    Double_t binEdges[nBins + 1] = {-5, -3, -2, -1, -0.5, 0, 0.5, 1, 2, 3, 5};
    TH1F *h2 = (TH1F *)(h1->Rebin(nBins, "h2", binEdges)); // Rebining

    // Create a histogram with a Gaussian distribution same binning as 2nd
    TH1F *h3 = new TH1F("h3", "Histogram with Gaussian Distribution", nBins, binEdges);
    for (int i = 0; i < 10000; i++)
    {
        h3->Fill(gRandom->Gaus(0, 1));
    }
    // DivideTH1ByBinWidth(h3);

    // Create a histogram with rebinning adjacent bins
    TH1F *h4 = (TH1F *)(h1->Rebin(2, "h4")); // Rebining
    DivideTH1ByBinWidth(h4);

    // Create a second histogram by rebinnning the first histogram and dividing by bin width
    TH1F *h5 = (TH1F *)(h1->Rebin(nBins, "h5", binEdges)); // Rebining
    DivideTH1ByBinWidth(h5);
    cout << h5->GetXaxis()->GetBinWidth(5) << endl;
    cout << h1->GetXaxis()->GetBinWidth(5) << endl;

    // Create a histogram with rebinning adjacent bins
    TH1F *h6 = (TH1F *)(h1->Rebin(nBins, "h6", binEdges)); // Rebining
    ScalingAfterRebin(h1, h6, binEdges);

    // Create a histogram with rebinning adjacent bins
    TH1F *h7 = (TH1F *)(h1->Rebin(4, "h7")); // Rebining
    Float_t scaling_factor = h1->GetBinWidth(0) / h7->GetBinWidth(0);
    h7->Scale(scaling_factor);

    // Create a histogram with rebinning adjacent bins
    TH1F *h8 = (TH1F *)(h1->Rebin(2, "h8")); // Rebining

    // Draw the histograms on a canvas
    TCanvas *c1 = new TCanvas("c1", "Histograms with Gaussian Distribution", 800, 600);
    // c1->SetLogy();
    h1->GetYaxis()->SetRangeUser(0.1, 6000);

    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h3->SetLineColor(kGreen);
    h4->SetLineColor(kYellow + 1);
    h5->SetLineColor(kBlack);
    h6->SetLineColor(kCyan);
    h7->SetLineColor(kMagenta);
    h8->SetLineColor(kOrange);

    h1->Draw();
    h2->Draw("same");
    h3->Draw("same");
    h4->Draw("same");
    h5->Draw("same");
    h6->Draw("E,same");
    h7->Draw("E, same");
    h8->Draw("L, same");

    // Add a legend to the canvas
    TLegend *legend = new TLegend(0.1, 0.7, 0.75, 0.9);
    legend->SetTextSize(0.02);
    legend->SetFillStyle(0);
    legend->AddEntry(h1, "H1 = Histogram with Gaussian Distribution & small uniform bin", "l");
    legend->AddEntry(h2, "H2 = Histogram with arbitrary bins Rebinning H1", "l");
    legend->AddEntry(h3, "H3 = Histogram with Gaussian Distribution given array bin", "l");
    legend->AddEntry(h4, "H4 = Histogram with Rebinning 2 adjacent bins of H1 and divide by bin width", "l");
    legend->AddEntry(h5, "H5 = Histogram with arbitrary bins Rebinning H1  and dividing by bin width", "l");
    legend->AddEntry(h6, "H6 = H5 without Bin width division but individual scaling", "l");
    legend->AddEntry(h7, "H7 = H4 without Bin width division but individual scaling", "l");
    legend->AddEntry(h8, "H8 = Histogram with Rebinning 2 adjacent bins of H1", "l");
    legend->Draw();

    // Save the canvas as a PDF file
    c1->SaveAs("histograms.png");
}
