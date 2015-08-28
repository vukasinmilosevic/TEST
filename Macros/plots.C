#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TCut.h"
#include <iostream>
#include "TColor.h"
#include "setTDRStyle.C"
#include "THStack.h"
#include "TLegend.h"
#include "TPaveText.h"


TFile *fp[10];
TTree *events[10];

TH1F *histo[5][20];
THStack * hstack[20];

enum samples{data,mc1,mc2};
enum plots{Z_mass};

TCut myWeight[3];
int maxEvents[3];
bool goFast=false;
float frac = 0.1;

TCanvas *can[100];
TLegend *leg[100];
int canCounter =0 ;

TPaveText *pt1;
TPaveText *pt2;
TPaveText *pt3;

void Plot()
{




}
void LEPETA_ee()
{
  setTDRStyle();

  gStyle->SetOptTitle(0);
  fp[mc1] = TFile::Open("/afs/cern.ch/work/t/theofil/public/ntuples/data_v1/dileptonSkim/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8___RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2.root");
  events[mc1] = (TTree*)fp[mc1]->Get("demo/events");
  //myWeight[mc1] = TCut("0.010419652");
  
  
  maxEvents[mc1] = events[mc1]->GetEntries();
  if(goFast) maxEvents[mc1] = int(frac*maxEvents[mc1]);
  cout << "maxEvents[mc1] = " << maxEvents[mc1] << endl; 
  myWeight[mc1] = TCut("xsection*totEveW*40.02");
  
  fp[mc2] = TFile::Open("/afs/cern.ch/work/t/theofil/public/ntuples/data_v1/dileptonSkim/TT_TuneCUETP8M1_13TeV-powheg-pythia8___RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v4.root");
  events[mc2] = (TTree*)fp[mc2]->Get("demo/events");
  myWeight[mc2] = TCut("xsection*totEveW*40.02");
  maxEvents[mc2] = events[mc2]->GetEntries();
  if(goFast) maxEvents[mc2] = int(frac*maxEvents[mc2]);
  cout << "maxEvents[mc2] = " << maxEvents[mc2] << endl; 
  
   fp[data] = TFile::Open("/afs/cern.ch/work/t/theofil/public/ntuples/data_v1/v1d/DoubleEG_v1d.root");
  //fp[data] = TFile::Open("/afs/cern.ch/work/t/theofil/public/ntuples/data_v1/dileptonSkim/alldata_40.24pb-1_golden_v1d.root");
 
  events[data] = (TTree*)fp[data]->Get("demo/events");
  maxEvents[data] = events[data]->GetEntries();
  if(goFast) maxEvents[data] = int(frac*maxEvents[data]);
  cout << "maxEvents[data] = " << maxEvents[data] << endl; 
  
  //TCut presel_ee("lepPt[1]>20 && goodVtx && HLT_e1e2 == 1 && lepID[0]*lepID[1]==-11*11 && l1l2M>55");
  TCut presel_mumu("lepPt[1]>20 && goodVtx && HLT_mu1mu2 == 1 && lepID[0]*lepID[1]==-13*13 && l1l2M>55");
  TCut presel_ee_data("lepPt[1]>20 && goodVtx && HLT_e1e2 == 1 && lepID[0]*lepID[1]==-11*11 && l1l2M>55 && lepEta[0]>0 && lepEta[1]>0");
  TCut presel_ee(" lepPt[1]>20 && goodVtx && HLT_e1e2 == 1 && lepID[0]*lepID[1]==-11*11 && l1l2M>55 && lepEta[0]>0 && lepEta[1]>0");
  
  //Double_t lumi1=2.13+0.86+2.6+1.75;
  //Double_t lumi2=11.41+14.19+0.46+6.63;
  //  Bool_t runs1=((runNum == 251244)||(runNum == 251251)||(runNum == 251252)||(runNum == 251561));
 // Bool_t runs2=((runNum == 251562)||(runNum == 251643)||(runNum == 251721)||(runNum == 251883));
  
 // TCut presel();
  
  // --- create and fill histograms
  histo[mc1][Z_mass] = new TH1F("mc1_lep_pt_0",";lepIso (ee) ;Events / 0.01",20,0,0.2);
  histo[mc1][Z_mass]->Sumw2();
  histo[mc1][Z_mass]->SetFillColor(kWhite) ;
  histo[mc1][Z_mass]->SetLineColor(12);
  events[mc1]->Draw("lepIso[0]>>mc1_lep_pt_0",presel_ee*myWeight[mc1],"goff",maxEvents[mc1]);
 events[mc1]->Draw("lepIso[1]>>+mc1_lep_pt_0",presel_ee*myWeight[mc1],"goff",maxEvents[mc1]);
  //events[mc1]->Draw("mjj>>mc1_Z_mass",presel*myWeight[mc1],"goff",maxEvents[mc1]);
  
  histo[mc2][Z_mass] = new TH1F("mc2_lep_pt_0",";lepIso (ee)  ;Events / 0.01",20,0,0.2);
  histo[mc2][Z_mass]->Sumw2();
  histo[mc2][Z_mass]->SetFillColor(11);
  histo[mc2][Z_mass]->SetLineColor(11);
  
  events[mc2]->Draw("lepIso[0]>>mc2_lep_pt_0",presel_ee*myWeight[mc2],"goff",maxEvents[mc2]);
  events[mc2]->Draw("lepIso[1]>>+mc2_lep_pt_0",presel_ee*myWeight[mc2],"goff",maxEvents[mc2]);
  //events[mc2]->Draw("mjj>>mc2_Z_mass",presel*myWeight[mc2],"goff",maxEvents[mc2]);
 
  histo[data][Z_mass] = new TH1F("data_lep_pt_0",";lepIso (ee)  ;Events / 0.01",20,0,0.2);
  histo[data][Z_mass]->Sumw2();
  histo[data][Z_mass]->SetFillColor(kWhite);
  histo[data][Z_mass]->SetLineColor(kBlack);
  events[data]->Draw("lepIso[0]>>data_lep_pt_0",presel_ee_data,"goff",maxEvents[data]);
  events[data]->Draw("lepIso[1]>>+data_lep_pt_0",presel_ee_data,"goff",maxEvents[data]);
  //events[data]->Draw("mjj>>data_Z_mass",presel*myWeight[data],"goff",maxEvents[data]);
  
   // --- decorations
  
  pt1 = new TPaveText(0.13,0.925,0.23,0.98,"blNDC");
  pt1->SetBorderSize(0);
  pt1->SetFillColor(0);
  pt1->SetFillStyle(0);
  pt1->SetTextFont(63);
  pt1->SetTextSize(25);
  pt1->AddText("CMS");

  pt2 = new TPaveText(0.21,0.91,0.475,0.98,"blNDC");
  pt2->SetBorderSize(0);
  pt2->SetFillColor(0);
  pt2->SetFillStyle(0);
  pt2->SetTextFont(53);
  pt2->SetTextSize(23);
  pt2->AddText("Preliminary");

  pt3 = new TPaveText(0.65,0.925,0.95,0.97,"blNDC");
  pt3->SetBorderSize(0);
  pt3->SetFillColor(0);
  pt3->SetFillStyle(0);
  pt3->SetTextFont(43);
  pt3->SetTextSize(20);
  pt3->AddText("40.2 pb^{-1} (13 TeV)");
  
  
  // --- start plotting
  can[canCounter] = new TCanvas("lep_pt_1_mumu","lep_pt_1_mumu"); 
  can[canCounter]->cd(); 
  can[canCounter]->SetLogy();
  hstack[canCounter] = new THStack("lep_pt_1_mumu","lep_pt_1_mumu");
  hstack[canCounter]->Add(histo[mc2][Z_mass]);
  hstack[canCounter]->Add(histo[mc1][Z_mass]);
  

   TCanvas *c1 = new TCanvas("c1","example", 500,650);
   TPad *pad1 = new TPad("pad1","pad1",0., 0.35, 1., 1.);
     pad1->SetTopMargin(0.08);
   pad1->SetBottomMargin(0.015);

   pad1->Draw();
   pad1->cd();
  
  histo[data][Z_mass]->Draw();
  histo[data][Z_mass]->GetXaxis()->SetLabelSize(0);
  histo[data][Z_mass]->GetYaxis()->SetLabelSize(0.04);
  hstack[canCounter]->Draw("hist same");
  histo[data][Z_mass]->Draw("same e1");
  histo[data][Z_mass]->Draw("same axis");


  
  
  

  leg[canCounter] = new TLegend(0.72,0.71,1.0,0.91);
  leg[canCounter]->SetTextSize(23);
  leg[canCounter]->SetTextFont(43);
  leg[canCounter]->SetFillColor(kWhite);
  leg[canCounter]->SetFillStyle(0);
  leg[canCounter]->SetBorderSize(0);
  leg[canCounter]->AddEntry(histo[data][Z_mass],"Data","PL");
  leg[canCounter]->AddEntry(histo[mc1][Z_mass],"DY","F");
  leg[canCounter]->AddEntry(histo[mc2][Z_mass],"t#bar{t}","F");
  leg[canCounter]->Draw("same");
  pt1->Draw("same");
  pt2->Draw("same");
  pt3->Draw("same");

  Int_t validation1=histo[data][Z_mass]->Integral(29,42);
  cout<< validation1<<endl;
  validation1=histo[data][Z_mass]->Integral(1,26)+histo[data][Z_mass]->Integral(45,70);
  cout<< validation1<<endl;
  validation1=histo[data][Z_mass]->Integral();
  cout<< validation1<<endl;
  
  TH1F* h_data=(TH1F*)histo[data][Z_mass]->Clone();
  TH1F* h_mc1=(TH1F*)histo[mc1][Z_mass]->Clone();
  TH1F* h_mc2=(TH1F*)histo[mc2][Z_mass]->Clone();
  h_mc1->Add(h_mc2);
  
   c1->cd();
   TPad *pad2 = new TPad("pad2","pad2",0., 0., 1., 0.35);
   pad2->SetTopMargin(0.1);
   pad2->Draw();
   pad2->cd();
   h_data->Sumw2();
   h_data->SetStats(0);
   h_data->Divide(h_mc1);
   h_data->SetMarkerStyle(21);
   pad2->SetBottomMargin(0.3);
   pad2->SetGridy();
   h_data->Draw("ep");
   h_data->GetYaxis()->SetRangeUser(0.7,1.3);
   h_data->GetYaxis()->SetLabelSize(0.07);
   h_data->GetYaxis()->SetTitleSize(0);
   h_data->GetXaxis()->SetLabelSize(0.07);
   h_data->GetXaxis()->SetTitleSize(0.1);
   h_data->GetXaxis()->SetTitleOffset(1.);
   









}
