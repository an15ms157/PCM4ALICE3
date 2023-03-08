#include <TH1F.h>
#include <TCanvas.h>
#include <TStyle.h>

void plot_histogram()
{
   // Create a histogram with 10 bins, ranging from 0 to 9
   TH1F *hist1 = new TH1F("hist1", "Histogram 1", 10, 0, 9);
   TH1F *hist2 = new TH1F("hist2", "Histogram 2", 10, 0, 9);
    hist1->Sumw2(); //
    hist2->Sumw2(); //
   // Fill the histograms with some data
   hist1->FillN(1, 10, 5);
   hist1->FillN(2, 20, 5);
   hist1->FillN(3, 30, 10);
   hist1->FillN(4, 40, 10);
   hist1->FillN(5, 50, 10);
   hist1->FillN(6, 60, 5);
   hist1->FillN(7, 70, 15);
   hist1->FillN(8, 80, 15);
   hist1->FillN(9, 90, 15);

   hist2->Fill(1, 15);
   hist2->Fill(2, 25);
   hist2->Fill(3, 35);
   hist2->Fill(4, 45);
   hist2->Fill(5, 55);
   hist2->Fill(6, 65);
   hist2->Fill(7, 75);
   hist2->Fill(8, 85);
   hist2->Fill(9, 95);

   // Set the style for the histograms
   hist1->SetLineColor(kBlue);
   hist2->SetLineColor(kRed);

   // Create a canvas to display the histograms
   TCanvas *canvas = new TCanvas("canvas", "Histograms with Error Boxes and Vertical Error Bars", 800, 600);

   // Draw the histograms with error boxes
   hist1->Draw("E1");
   hist2->Draw("E1 SAME");

   // Draw the vertical error bars
   //hist1->Draw("E1 SAME");
   //hist2->Draw("E1 SAME");

   // Update the canvas to display the histograms
   canvas->Update();
}
