#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include "TRandom.h"
#include "TMath.h"
#include "TTree.h"
#include <vector>
#include "TH1.h"
#include "TAxis.h"
#include "TString.h"
#include "Riostream.h"
#include "TFile.h"
#include "TF1.h"
#include "TList.h"
#include "TObjString.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TColor.h"
#include "TMatrixTSym.h"
#include "TMatrixDfwd.h"
#include "TFitResult.h"
#include "Fit/FitResult.h"

Double_t exponential (Double_t *var, Double_t *par)
{
  // Simple exponential (not normalized):
  Double_t N = par[0]; // value of the exponential at x=0
  Double_t s = par[1]; // slope of the exponential
  Double_t A = par[2];
  Double_t x = var[0]; // variable
  return N*exp(-x/s)+A;
}

Double_t doubleexponential (Double_t *var, Double_t *par)
{
  // Simple exponential (not normalized):
  Double_t N1 = par[0];
  Double_t tau1 = par[1]; 
  Double_t N2 = par[2];
  Double_t tau2 = par[3];
  Double_t A = par[4];
  Double_t x = var[0]; // variable
  return N1*exp(-x/tau1)*N2*exp(-x/tau2)+A;
}

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include "TRandom.h"
#include "TMath.h"
#include "TTree.h"

// pour executer la macro: root -l 'PlotHisto.C("FileName")'

void PlotHisto(char* filename){
    
  gROOT->Reset();

     gStyle->SetOptTitle(0) ;
    gStyle->SetOptStat(10) ;
    gStyle->SetPalette(1) ;
    gStyle->SetCanvasColor(10) ;
    gStyle->SetFrameFillColor(10) ;
    gStyle->SetOptFit(1) ;
  TCanvas *c1 = new TCanvas("c1","Simulation",0,10,700,700);

  FILE *fp1;
  
  double time;
  TH1F *h2 = 0, *besth2=0;
  TF1 *fit = 0, *bestfit=0;
  Double_t bestchi2=10000000000;
  int bestbinning=0;
  Double_t min=1e30,max=0;
  
  fp1 = fopen(filename,"r");
  while(fscanf(fp1,"%lf",&time)!=EOF)
    {
      if(time<min){min=time;}
      if(time>max){max=time;}
    }
  fclose(fp1);

  for (int binning=100;binning<150;binning++){

    h2 = new TH1F("h2","Fit of the data",binning,min,max) ;
    h2->Sumw2();
    fp1 = fopen(filename,"r");
    while(fscanf(fp1,"%lf",&time)!=EOF)
      {
	h2->Fill(time);
      }
    fclose(fp1);
    ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit");
    fit = new TF1("fit",exponential,0,1000,3);
    fit->SetLineColor(4);
    fit->SetLineStyle(1);
    fit->SetLineWidth(3);

    fit->SetParameter(0,500);
    fit->SetParameter(1,2);
    fit->SetParameter(2,20);

    TFitResultPtr MyFit = h2->Fit(fit,"LS","E",min+(max-min)/binning,max-(max-min)/binning);
    h2->GetYaxis()->SetTitle("Number of events");
    h2->GetXaxis()->SetTitle("Time (#mus)");
    Int_t fit_status_value = MyFit->Status();
    Int_t fit_covmat_value = MyFit->CovMatrixStatus();
    Double_t chi2_Background = fit->GetChisquare();
    Double_t ndf_Background = fit->GetNDF();
    Double_t chi2ndf_Background = chi2_Background/ndf_Background;
  
    if(chi2ndf_Background<bestchi2 && fit_status_value==0 && fit_covmat_value==3){
      bestchi2=chi2ndf_Background;
      bestbinning=binning;
      if(besth2!=0)delete besth2;
      besth2=h2;
      if(bestfit!=0)delete bestfit;
      bestfit=fit;
    }
    else {
      delete h2;
      delete fit;
    }
  }
  
  besth2->SetLineColor(2);
  besth2->Draw("Same");

  cout << "bestchi2 " << bestchi2 << "\nbest binning " << bestbinning << endl;

}
