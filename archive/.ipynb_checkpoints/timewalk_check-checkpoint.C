#include <TProfile.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TPaveText.h>
#include <TPaveLabel.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> 
#include <unistd.h>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TTree.h"
#include "TProfile.h"
#include "TH1F.h"
#include "TF1.h"
#include "TH2D.h"
#include "TFile.h"
#include "TPolyLine.h"
#include "TImage.h"
using namespace std;

void summary_run() 
{
    char infile[300], outfile[300], outfile1[300], outfile2[300];
    sprintf(outfile, "results/results_verify/timewalk_allruns.pdf");
    strcpy(outfile1, outfile);  
    strcpy(outfile2, outfile); 
    strcat(outfile1, "(");   
    strcat(outfile2, ")"); 
    
    TFile *f;
    TH2I *h_before, *h_after;
    string run_numb;
    TCanvas *c1 = new TCanvas("c1","c1", 1200, 600);
    c1->Divide(2,1);
    
    ifstream run_list("runs_calib.dat");
    
    while (getline(run_list, run_numb))
    {
        sprintf(infile,"results/root_verify/hists/%s/hd_root_%s_000.root", run_numb.c_str(), run_numb.c_str());
        f = new TFile(infile,"R");
        h_before = (TH2I*)f->Get(Form("TAGH_timewalk/Timewalk/TAGHRF_tdcTimeDiffVsPulseHeight_1"));
        h_before->SetTitle(run_numb.c_str());
        h_after = (TH2I*)f->Get(Form("TAGH_timewalk/Corrected_Timewalk/TAGHRF_correctedTdcTimeDiffVsPulseHeight_1"));
        h_after->SetTitle(run_numb.c_str());
     
        c1->cd(1);
        h_before->Draw("colz");
        h_before->SetMarkerSize(0.25);
        
        c1->cd(2);
        h_after->Draw("colz");
        h_after->SetMarkerSize(0.25);
        
        c1->Print(outfile1,"pdf");
        c1->Clear();
        c1->Divide(2,1);
    }
    
    c1->Print(outfile2,"pdf");
    run_list.close();    

}      
