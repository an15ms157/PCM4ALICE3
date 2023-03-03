#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TH1F.h>

void plot_histogram()
{
    TH1F *hist = new TH1F("hist", "Example Histogram", 50, -10, 10);

    // Fill the histogram with random numbers
    hist->FillRandom("gaus", 100000);

    // Calculate the bin contents and errors for the TGraphAsymmErrors object
    int nbins = hist->GetNbinsX();
    double x[nbins], y[nbins], exl[nbins], exh[nbins], eyl[nbins], eyh[nbins];
    for (int i = 1; i <= nbins; i++) {
        x[i-1] = hist->GetBinCenter(i);
        y[i-1] = hist->GetBinContent(i);
        exl[i-1] = hist->GetBinWidth(i) / 2.0;
        exh[i-1] = hist->GetBinWidth(i) / 2.0;
        eyl[i-1] = hist->GetBinErrorLow(i);
        eyh[i-1] = hist->GetBinErrorUp(i);
    }

    // Create a TGraphAsymmErrors object to represent the error band
    TGraphAsymmErrors *gr = new TGraphAsymmErrors(nbins, x, y, exl, exh, eyl, eyh);

    // Create a canvas to display the histogram and error band
    TCanvas *canvas = new TCanvas("canvas", "Histogram Canvas", 800, 600);

    // Draw the histogram and error band on the canvas
    hist->Draw();
    gr->Draw("3 SAME");

    // Update the canvas to display the histogram and error band
    canvas->Update();
    
    // Set the color of the error band to orange
    gr->SetFillColor(kOrange);
}
