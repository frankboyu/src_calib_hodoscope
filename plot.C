// Code to produce statistics and plots to verify the calibrations

// Import packages
#include <TProfile.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TPaveText.h>
#include <TPaveLabel.h>
#include <iostream>
#include <fstream>
#include <sstream>
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

// Declare variables
TFile *f;
TH2I *h_offsets[3];
TH2I *h_tdc[274];
TH2I *h_tw[274];

void plot(int run_numb) 
{
    // Get the input file
    char infile[300];
    sprintf(infile,"results/hists/hd_root_%d.root",run_numb);
    //sprintf(infile,"/work/halld/data_monitoring/RunPeriod-2021-11/mon_ver07/rootfiles/hd_root_0%d.root",run_numb);
    TFile *f = new TFile (infile,"R");
    
    // Set up the canvas
    TCanvas *c1 = new TCanvas("c1","c1", 10, 200, 960, 600);
    TLine *line = new TLine(0.0, 0.0, 4000.0, 0.0);
    line->SetLineColor(kRed);
    line->SetLineWidth(1);

    // Get the histograms
    h_offsets[0] = (TH2I*)f->Get(Form("TAGH_timewalk/Offsets/TAGH_tdcadcTimeDiffVsSlotID"));
    h_offsets[1] = (TH2I*)f->Get(Form("TAGH_timewalk/Offsets/TAGHRF_tdcTimeDiffVsSlotID"));
    h_offsets[2] = (TH2I*)f->Get(Form("TAGH_timewalk/Offsets/tagh_time_rf"));
    h_offsets[0]->GetYaxis()->SetRangeUser(-4,4);
    h_offsets[1]->GetYaxis()->SetRangeUser(-4,4);
    h_offsets[2]->GetYaxis()->SetRangeUser(-20,20);
    for (Int_t i = 0; i < 274; ++i)
    {
        h_tdc[i] = (TH2I*)f->Get(Form("TAGH_timewalk/Timewalk/TAGHRF_tdcTimeDiffVsPulseHeight_%i",i+1));
        h_tw[i] = (TH2I*)f->Get(Form("TAGH_timewalk/Corrected_Timewalk/TAGHRF_correctedTdcTimeDiffVsPulseHeight_%i",i+1));
        h_tw[i]->SetTitle(Form("Timewalk Col %i",i+1));
    }

    // Set up the output statistics file
    char statsfile_name[300];
    sprintf(statsfile_name,"results/verify/stats-%d.txt",run_numb);
    FILE *statsfile = fopen(statsfile_name,"w");
  
    // Initialize the offset arrays
    double tdc_adc_mean[274], tdc_adc_error[274], tdc_rf_mean[274], tdc_rf_error[274], t_rf_mean[274], t_rf_error[274];
    memset(tdc_adc_mean,0.0,274); 
    memset(tdc_adc_error,0.0,274); 
    memset(tdc_rf_mean,0.0,274); 
    memset(tdc_rf_error,0.0,274); 
    memset(t_rf_mean,0.0,274); 
    memset(t_rf_error,0.0,274);

    // Get the offsets using Gaussian fits and print them
    for (Int_t i = 0; i < 274; ++i)
    {
        if (i < 274)
//         if (i<127 || (i>177 && i<257))
        {
            TF1 *f1 = new TF1("f1","gaus",-10.,10.);
            f1->SetParameter(1,0);
            f1->SetParameter(2,0.2);
            if (h_offsets[0]->ProjectionY("channel",i+1,i+1)->GetEntries()>1000)
            {
                if (i<16)
                {  
                    h_offsets[0]->GetYaxis()->SetRangeUser(-2,2);
                    tdc_adc_mean[i] = h_offsets[0]->ProjectionY("channel",i+1,i+1)->GetMean();
                    tdc_adc_error[i] = h_offsets[0]->ProjectionY("channel",i+1,i+1)->GetRMS();          
                }
                else
                {
                    h_offsets[0]->ProjectionY("channel",i+1,i+1)->Fit("f1","Q","",-4,4);
                    tdc_adc_mean[i] = f1->GetParameter(1);
                    tdc_adc_error[i] = f1->GetParameter(2);
                }
            }
            else
            {
                tdc_adc_mean[i] = 0.0;
                tdc_adc_error[i] = 0.0;
            }

            if (h_tdc[i]->ProjectionY()->GetEntries()>1000)
            {
                h_tdc[i]->ProjectionY()->Fit("f1","Q","",-4,4);
                tdc_rf_mean[i] = f1->GetParameter(1);
                tdc_rf_error[i] = f1->GetParameter(2);
            }
            else
            {
                tdc_rf_mean[i] = 0.0;
                tdc_rf_error[i] = 0.0;
            }

            if (h_tw[i]->ProjectionY()->GetEntries()>1000)
            {
                h_tw[i]->ProjectionY()->Fit("f1","Q","",-4,4);
                t_rf_mean[i] = f1->GetParameter(1);
                t_rf_error[i] = f1->GetParameter(2);
            }
            else
            {
                t_rf_mean[i] = 0.0;
                t_rf_error[i] = 0.0;
            }

        }
        else
        {
            tdc_adc_mean[i] = 0; tdc_adc_error[i] = 0; tdc_rf_mean[i] = 0; tdc_rf_error[i] = 0; t_rf_mean[i] = 0; t_rf_error[i] = 0;
        }

        fprintf(statsfile, "%4d %14.3f %14.3f %14.3f %14.3f %14.3f %14.3f \n",i+1, tdc_adc_mean[i], tdc_adc_error[i], tdc_rf_mean[i], tdc_rf_error[i], t_rf_mean[i], t_rf_error[i]); 
    }
    fclose(statsfile);
    
    // Set up the graphs
    TGraph *g_dt[3]={NULL};
    double channels[274], zeros[274];
    memset(channels,0,274); memset(zeros,0,274);
    for (Int_t i = 0; i < 274; ++i)
    {
        channels[i] = i+1;
        zeros[i] = 0;
    }
    g_dt[0] = new TGraphErrors(274, channels, tdc_adc_mean, zeros, tdc_adc_error); 
    g_dt[0]->SetTitle(Form("%d TDC-ADC", run_numb)); 
    g_dt[1] = new TGraphErrors(274, channels, t_rf_mean, zeros, t_rf_error);
    g_dt[1]->SetTitle(Form("%d T-RF", run_numb));  
    g_dt[2] = new TGraphErrors(274, channels, tdc_rf_mean, zeros, tdc_rf_error);
    g_dt[2]->SetTitle(Form("%d TDC-RF", run_numb)); 
    
    // Set up the output plot file (the plots detailed for all the channels as backup)
    char plotfile[300], plotfile1[300], plotfile2[300];
    sprintf(plotfile,"results/verify/plots-%d.pdf",run_numb);
    strcpy(plotfile1, plotfile);  
    strcpy(plotfile2, plotfile); 
    strcat(plotfile1, "(");   
    strcat(plotfile2, ")");  
    
    // Set up the output image file (the plot checked by eyes)
    char imagefile[300];
    sprintf(imagefile,"results/verify/image-%d.png",run_numb);

    // Plot the graph using the fitting results
    for (Int_t i = 0; i < 3; ++i)
    {
        g_dt[i]->GetYaxis()->SetRangeUser(-4,4);
        g_dt[i]->SetMarkerSize(0.1);
        g_dt[i]->GetXaxis()->SetTitle("channel");
        g_dt[i]->GetYaxis()->SetTitle("dt (ns)"); 
        g_dt[i]->Draw("AP");
        line->Draw();
        c1->Print(plotfile1,"pdf");
        if (i==1)
            c1->Print(imagefile);
        c1->Clear();
    }
    
    // Plot the original histograms
    for (Int_t i = 0; i < 3; ++i)
    {
        h_offsets[i]->SetMarkerSize(0.25);
        h_offsets[i]->Draw("colz");
        line->Draw();
        gPad->SetLogz();
        c1->Print(plotfile1,"pdf");
        c1->Clear();
    }
    
    // Plot the time-walked corrected TDC-RF distribution for all the channels
    c1->Divide(8,5);    
    int plot = 1;
    for (Int_t i = 0; i < 274; ++i)
    {

        c1->cd(plot);
        h_tw[i]->Draw("colz");
        line->Draw();line->Draw();line->Draw();line->Draw();
        h_tw[i]->SetMarkerSize(0.25);
        gPad->SetLogz();
        plot++;
        if (plot==41)
        {
            c1->Print(plotfile1,"pdf");
            c1->Clear();
            c1->Divide(8,5);
            plot = 1;
        }
        if (i==273)
        {
            c1->Print(plotfile2,"pdf");
        }
    }
}      
