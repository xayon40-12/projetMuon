#include <iostream.h>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>
#include "TRandom.h"
#include "TMath.h"
#include "TTree.h"

void ana()
{
    gROOT->Reset();
    gStyle->SetOptFit(1111);
    c1 = new TCanvas("c1","CsI data",200,10,700,700);
    c1->SetLogy();

    Double_t Tot_depE_Pb;
    
    TH1F *h1 = new TH1F("h1","Comparison",1000,0.,2.);
    h1->SetStats(0);
    h1->SetLineColor(2);
    ifstream f1("CsIData1.dat");


    double bin = 0, count;
    do {
        f1 >> count;
	Tot_depE_Pb = bin*0.00220903 - 0.164306; //interpolation lineaire
        for(int j = 0;j<count;j++) h1->Fill(Tot_depE_Pb);
	bin++;
    } while(!f1.eof());
    f1.close();
   
    /*
    //On utilise des fit pour obtenir les energies des piques et les sigma
    TF1 *fn1 = new TF1("fn1","gaus",-.5,.5);
    h1->Fit("fn1","","",.45,.55);
    double p1[3];
    fn1->GetParameters(p1);
    
    TF1 *fn2 = new TF1("fn2","gaus",-.5,.5);
    h1->Fit("fn2","","",1.22,1.32);
    double p2[3];
    fn2->GetParameters(p2);
    
    //On calcul les coefficients par interpolation lineaire
    double a = (1.275-0.511)/(p2[1]-p1[1]);
    double b = 1.275-a*p2[1];
    std::cout << "a: " << a << "   b: " << b << std::endl;
    double K = p2[2]/sqrt(Tot_depE_Pb);// On sait que sigma = K*sqrt(E)
    std::cout << K << std::endl;*/
    
    TH1F *h2 = new TH1F("h2","simulation (MeV)",1000,0.,2.);
    h2->SetStats(0);
    h2->SetLineColor(3);
    TFile *f2 = new TFile("Results_no_shielding.root");
    
    TTree *mytree = (TTree*) f2->Get("tree"); 
    mytree->SetBranchAddress("Tot_depE_Pb",&Tot_depE_Pb);
    
    Int_t nevtree = mytree->GetEntries();
    for(int i=0;i<nevtree;i++){
        mytree->GetEntry(i);
        h2->Fill(gRandom->Gaus(Tot_depE_Pb, 0.0372771*sqrt(Tot_depE_Pb)));//ajout de la resolution en energie
    }
    delete f2;
    
    TH1F *h3 = new TH1F("h3","simulation shielding (MeV)",1000,0.,2.);
    h3->SetStats(0);
    h3->SetLineColor(4);
    TFile *f3 = new TFile("Results_shielding.root");
    
    TTree *mytree2 = (TTree*) f3->Get("tree"); 
    mytree2->SetBranchAddress("Tot_depE_Pb",&Tot_depE_Pb);
    
    Int_t nevtree2 = mytree2->GetEntries();
    for(int i=0;i<nevtree2;i++){
        mytree2->GetEntry(i);
        h3->Fill(gRandom->Gaus(Tot_depE_Pb, 0.0372771*sqrt(Tot_depE_Pb)));//ajout de la resolution en energie
    }
    delete f3;
    
    //h2->Rebin(4);
    h2->Draw();
    h3->Draw("Same");
    h1->Draw("Same");
    
   auto legend = new TLegend(0.1,0.1,0.5,0.35);
   legend->AddEntry(h1,"experimental (MeV)","l");
   legend->AddEntry(h2,"simulation without shielding (MeV)","l");
   legend->AddEntry(h3,"simulation with shielding (MeV)","l");
   legend->Draw("Same");
}