/**
 * Get global Slab DT for all TOFs
 **/

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLegendEntry.h"


#include "../tof_event.h"

#ifndef FOR
#define FOR(i, size) for (int i = 0; i < size; i++)
#endif

int process(const char* fname, const char* outfname) {

    gStyle->SetOptFit(1);

    // open input file
    TChain* tree = new TChain("tof_tree");
    tree->Add(fname);

    // register branches to a data structure
    int size = tree->GetEntries();
    cout<<"Processing "<<size<<" events"<<endl;
    tof_event event[3];
    registerInputTree(tree, event);


    // output histograms
    TH1* hists[3] = {};
    FOR(i, 3) {
	hists[i] = new TH1I( Form("hSlabDt_tof%d", i), Form("TOF%d;#DeltaT [ns]", i), 400, -4, 4);
    }

    int fiftieth = size/50;
    cout<<"|                                                  |\r|";
    cout.flush();

    // loop over all events
    FOR(i, size) {
	if ((i+1)%fiftieth == 0) {
	    cout<<"-";
	    cout.flush();
	}

        tree->GetEntry(i);

	FOR(itof, 3) {
	    // must have 1 sp in TOF1 or in TOF0
	    if ( ((itof == 1)?event[0].sp.npoints:event[1].sp.npoints) != 1 )
		continue;

	    // tof cuts - 2 slabs hit, from different planes
	    if ( event[itof].slb.nslabs != 2 ||
		 event[itof].slb.plane[0] == event[itof].slb.plane[1] )
		continue;

	    double DT = event[itof].slb.t[0]-event[itof].slb.t[1];

	    // DT cut, so that these are not the TDC overflow-effect events
	    if ( abs(DT) > 20e3 )
		 continue;

	    hists[itof]->Fill(DT);
	}
    }
    cout<<"|"<<endl;

    TCanvas c("c", "", 1200, 400);
    c.Divide(3,1);
    TF1 fit("fit", "gaus(0)", -2.,2);
    fit.SetLineWidth(1);

    double max_sigma = 0;

    FOR(i, 3) {
	c.cd(i+1);
	fit.SetParameters(hists[i]->GetMaximum(), 0, 0.1);
	hists[i]->Fit("fit", "L", "", -0.5, 0.5);
	double sigma = abs(fit.GetParameter(2));
	if (sigma > max_sigma)
	    max_sigma = sigma;
    }

    FOR(i, 3) {
	hists[i]->SetAxisRange(-4.*max_sigma, 6.*max_sigma);
	gPad->Modified();
    }

    c.SaveAs(Form("%s.pdf", outfname));
    c.SaveAs(Form("%s.root", outfname));

    return 0;
}
