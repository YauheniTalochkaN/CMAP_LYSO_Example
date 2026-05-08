#include <iostream>
#include <filesystem>
#include "TROOT.h"
#include "TFile.h"
#include "TString.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TH3I.h"

void GetTrackData(TString name = "Track_Data.root")
{
    TFile *f = 0;
    f = new TFile(name, "update");

    Double_t xx, yy, zz, time, cxx, cyy, czz, ctime, En, Ek;
    Int_t id, numbeam;
    Int_t particle;
    
    TTree *tout = (TTree*)f->Get("Track_Data");

    tout->SetBranchAddress("beam",&numbeam);
    tout->SetBranchAddress("particle",&particle);
    tout->SetBranchAddress("id",&id);
    tout->SetBranchAddress("Energy",&En);
    tout->SetBranchAddress("KEnergy",&Ek);
    tout->SetBranchAddress("x",&xx);
    tout->SetBranchAddress("y",&yy);
    tout->SetBranchAddress("z",&zz);
    tout->SetBranchAddress("time",&time);
    tout->SetBranchAddress("cx",&cxx);
    tout->SetBranchAddress("cy",&cyy);
    tout->SetBranchAddress("cz",&czz);
    tout->SetBranchAddress("ctime",&ctime);

    std::filesystem::create_directories("./Track_Data");

    TString file_name = "./Track_Data/output_data.csv";

    FILE *ff = fopen(file_name, "w");

    fprintf(ff, "xx,yy,zz,time,cxx,cyy,czz,ctime,numbeam,id,particle,En,Ek\n");
    //fprintf(ff, "xx,yy,zz,time,numbeam,id,particle,En,Ek\n");

    Int_t num = tout->GetEntries();
    for(Int_t i = 0; i < num; ++i)
    {
        tout->GetEntry(i, 1);

        fprintf(ff, "%.5e,%.5e,%.5e,%.5e,%.5e,%.5e,%.5e,%.5e,%d,%d,%d,%.5e,%.5e", xx, yy, zz, time, cxx, cyy, czz, ctime, numbeam, id, particle, En, Ek);
        //fprintf(ff, "%.5e,%.5e,%.5e,%.5e,%d,%d,%d,%.5e,%.5e", xx, yy, zz, time, numbeam, id, particle, En, Ek);
        
        if(i < num - 1) fprintf(ff, "\n");
    }

    fclose(ff);	
    
    tout = nullptr;

    f->Close();
    f = nullptr;
}