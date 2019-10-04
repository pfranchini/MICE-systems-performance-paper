#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1I.h"
#include "TPad.h"
#include "TCanvas.h"

#include "src/common_cpp/DataStructure/Data.hh"
#include "src/common_cpp/DataStructure/Spill.hh"
#include "src/common_cpp/DataStructure/TOFEvent.hh"
#include "src/common_cpp/DataStructure/RunHeaderData.hh"
#include "src/common_cpp/DataStructure/JobHeaderData.hh"
#include "src/common_cpp/DataStructure/RunHeader.hh"
#include "src/common_cpp/DataStructure/JobHeader.hh"

#include "tof_event.h"

int getRunNumber(TFile* f);
string getMausVersion(TFile* f);
TTree* prepareTree(tof_event* evt);
void resetTofEvent(tof_event* evt);
void getTofSpData(tof_event_sp* evt, MAUS::TOF2SpacePointArray* tofsp);
void getTofSlbData(tof_event_slb* evt, MAUS::TOF2SlabHitArray* tofslb);
void getDigits(tof_event_dg* evt, MAUS::TOF2DigitArray* tofdg);

#ifndef FOR
#define FOR(i, size) for(int i = 0; i < size; i++)
#endif

int process_multi_events(const char* fname, const char* outfname, const int nevts = 0) {


    // prepare histograms
    TH1I* hDt = new TH1I("hDt", "", 100, -1., 1.);
    TH1I* hDt1of2 = new TH1I("hDt1of2", "", 100, -1., 1.);
    TH1I* hDt2of2 = new TH1I("hDt2of2", "", 100, -1., 1.);
    TH1I* hDt1of1 = new TH1I("hDt1of1", "", 100, -1., 1.);


    // open input file
    // TFile *f = new TFile(fname);

    // if (!f->IsOpen())
    // 	return -1;


    // prepare the input tree
    TChain* tree = new TChain("Spill");
    tree->Add(fname);

    if (tree->GetNtrees() == 0) {
      cerr<<"did not retrieve any tree from file(s) specified: "<<fname<<endl;
      return -1;
    }

    MAUS::Data* data = 0;
    tree->SetBranchAddress("data", &data);

    // int RunNum = getRunNumber(tree->GetFile());
    // string maus_version = getMausVersion(tree->GetFile());

    // cout<<"Processing run number "<<RunNum<<endl;

    // open output file
    TFile* outf = new TFile(outfname,
			    "recreate");
    if (outf->IsOpen())
	cout<<"Will store output tree into file "<<outf->GetName()<<endl;
    else
	return -1;


    // prepare output tree
    tof_event evt[3] = {};
    TTree* outtree = prepareTree(evt);



    unsigned counter = 0;
    int upcount = 0;
    int downcount = 0;


    tree->GetEntry(0);
    unsigned size = tree->GetEntriesFast();

    cout<<"Starting to process spills, current run has about "<<size<<" of them."<<endl;

    if (nevts)
	size = nevts;

    // loop over spills
    unsigned i = 0;
    int fiftieth = size / 50;
    cout<<"|                                                  |\r|";
    while ( tree->GetEntry(i) ) {
	i++;
	if ( i%fiftieth == 0 ) {
	    cout<<"-";
	    cout.flush();
	}

	if (nevts && nevts < i) break;

	MAUS::Spill* spill = data->GetSpill();

	if (spill->GetDaqEventType().compare("physics_event")) continue;

	// loop over reconstructed events
	for (unsigned j = 0; j < spill->GetReconEventSize(); j++) {
	    MAUS::TOFEvent* tof = spill->GetAReconEvent(j).GetTOFEvent();

	    // Get TOF2 event
	    MAUS::TOF2SpacePointArray* tof2sp = tof->GetTOFEventSpacePointPtr()->GetTOF2SpacePointArrayPtr();
	    //cout<<tof2sp->size()<<endl; // how many space point were reconstructed

	    // get point's dt
	    if (tof2sp->size() > 0) {
		double dt = tof2sp->at(0).GetDt();
		hDt->Fill(dt);

		if (tof2sp->size() > 1) {
		    dt = tof2sp->at(0).GetDt();
		    hDt1of2->Fill(dt);

		    dt = tof2sp->at(1).GetDt();
		    hDt2of2->Fill(dt);
		} else {
		    hDt1of1->Fill(dt);
		}

		if (tof2sp->size() > 2)
		    counter++;
	    }

	    // store TOF0,1,2 data
	    // space points
	    getTofSpData(&(evt[2].sp), tof2sp);
	    MAUS::TOF0SpacePointArray* tof0sp = tof->GetTOFEventSpacePointPtr()->GetTOF0SpacePointArrayPtr();
	    getTofSpData(&(evt[0].sp), tof0sp);
	    MAUS::TOF1SpacePointArray* tof1sp = tof->GetTOFEventSpacePointPtr()->GetTOF1SpacePointArrayPtr();
	    getTofSpData(&(evt[1].sp), tof1sp);

	    // slab hits
	    MAUS::TOF0SlabHitArray* tof0slb = tof->GetTOFEventSlabHitPtr()->GetTOF0SlabHitArrayPtr();
	    getTofSlbData(&(evt[0].slb), tof0slb);
	    MAUS::TOF1SlabHitArray* tof1slb = tof->GetTOFEventSlabHitPtr()->GetTOF1SlabHitArrayPtr();
	    getTofSlbData(&(evt[1].slb), tof1slb);
	    MAUS::TOF2SlabHitArray* tof2slb = tof->GetTOFEventSlabHitPtr()->GetTOF2SlabHitArrayPtr();
	    getTofSlbData(&(evt[2].slb), tof2slb);

	    // digits
	    MAUS::TOF0DigitArray* tof0dg = tof->GetTOFEventDigitPtr()->GetTOF0DigitArrayPtr();
	    getDigits(&(evt[0].dg), tof0dg);
	    MAUS::TOF1DigitArray* tof1dg = tof->GetTOFEventDigitPtr()->GetTOF1DigitArrayPtr();
	    getDigits(&(evt[1].dg), tof1dg);
	    MAUS::TOF2DigitArray* tof2dg = tof->GetTOFEventDigitPtr()->GetTOF2DigitArrayPtr();
	    getDigits(&(evt[2].dg), tof2dg);


	    // tracker related stuff
	    MAUS::SciFiTrackPArray array = spill->GetAReconEvent(j).GetSciFiEvent()->scifitracks();
	    int up = 0;
	    int down = 0;
	    FOR(j, array.size()) {
		if (array.at(j)->tracker() == 1)
		    down++;
		else if (array.at(j)->tracker() == 0)
		    up++;
	    }

	    evt[0].tkuntracks = up;
	    evt[0].tkdntracks = down;

	    if (up > 0) upcount++;
	    if (down > 0) downcount++;

	    outtree->Fill();
	    resetTofEvent(evt);

	}

	// if ( i % 100 == 0 ) {
	//     cout<<"At spill "<<i<<" of "<<size<<endl;
	// }
    }
    cout<<"|"<<endl;

    cout<<"There were "<<counter<<" particle triggers with more than 2 space points in TOF2."<<endl;

    cout<<upcount<<" events had at least 1 track in TKU"<<endl;
    cout<<downcount<<" events had at least 1 track in TKD"<<endl;

    outf->Write(); outf->Close();

    //f->Close();



    // TCanvas* c = new TCanvas("c", "");
    // c->Divide(2,2);

    // c->cd(1);
    // hDt->Draw();
    // c->cd(2);
    // hDt1of2->Draw();
    // c->cd(3);
    // hDt2of2->Draw();
    // c->cd(4);
    // hDt1of1->Draw();


    // c->SaveAs("plots/tofcheck/tof2_slab_dt.pdf");

    return 0;
}


int getRunNumber(TFile* f) {

    TTree* tree = (TTree*)f->Get("RunHeader");

    MAUS::RunHeaderData* rh = 0;

    tree->SetBranchAddress("run_header", &rh);
    tree->GetEntry(0);

    return rh->GetRunHeader()->GetRunNumber();
}

string getMausVersion(TFile* f) {

    TTree* tree = (TTree*)f->Get("JobHeader");

    MAUS::JobHeaderData* rh = 0;

    tree->SetBranchAddress("job_header", &rh);
    tree->GetEntry(0);

    string version = rh->GetJobHeader()->GetMausVersionNumber();

    std::size_t pos = version.rfind(" ")+1;
    string result = "v";
    result.append(version.substr(pos));
    return result;
}


TTree* prepareTree(tof_event* evt) {
    TTree* tree = new TTree("tof_tree", "");

    registerOutputTree(tree, evt);

    return tree;
}

void resetTofEvent(tof_event* evt) {
    static const tof_event null_evt = {};
    for (unsigned i = 0; i < 3; i++) {
	evt[i] = null_evt;
    }
}

void getTofSpData(tof_event_sp* evt, MAUS::TOF2SpacePointArray* tofsp) {
    evt->npoints = tofsp->size();
    for (unsigned k = 0; k < evt->npoints; k++) {
	evt->x[k] = tofsp->at(k).GetGlobalPosX();
	evt->y[k] = tofsp->at(k).GetGlobalPosY();
	evt->z[k] = tofsp->at(k).GetGlobalPosZ();

	evt->slabx[k] = tofsp->at(k).GetSlabx();
	evt->slaby[k] = tofsp->at(k).GetSlaby();

	evt->dt[k] = tofsp->at(k).GetDt();
	evt->t[k] = tofsp->at(k).GetTime();
	evt->q[k] = tofsp->at(k).GetCharge();
    }
}

void getTofSlbData(tof_event_slb* evt, MAUS::TOF2SlabHitArray* tofslb) {
    evt->nslabs = tofslb->size();
    for (unsigned k = 0; k < evt->nslabs; k++) {
	evt->plane[k] = tofslb->at(k).GetPlane();
	evt->slab[k] = tofslb->at(k).GetSlab();

	evt->q[k] = tofslb->at(k).GetCharge();
	evt->t[k] = tofslb->at(k).GetTime();
	evt->rawt[k] = tofslb->at(k).GetRawTime();

	evt->pmt0q[k] = tofslb->at(k).GetPmt0Ptr()->GetCharge();
	evt->pmt0t[k] = tofslb->at(k).GetPmt0Ptr()->GetTime();
	evt->pmt0rawt[k] = tofslb->at(k).GetPmt0Ptr()->GetRawTime();
	evt->pmt0dgt[k] = tofslb->at(k).GetPmt0Ptr()->GetLeadingTime();
	evt->pmt0trt[k] = tofslb->at(k).GetPmt0Ptr()->GetTriggerRequestLeadingTime();

	evt->pmt1q[k] = tofslb->at(k).GetPmt1Ptr()->GetCharge();
	evt->pmt1t[k] = tofslb->at(k).GetPmt1Ptr()->GetTime();
	evt->pmt1rawt[k] = tofslb->at(k).GetPmt1Ptr()->GetRawTime();
	evt->pmt1dgt[k] = tofslb->at(k).GetPmt1Ptr()->GetLeadingTime();
	evt->pmt1trt[k] = tofslb->at(k).GetPmt1Ptr()->GetTriggerRequestLeadingTime();
    }
}


void getDigits(tof_event_dg* evt, MAUS::TOF2DigitArray* tofdg) {
    evt->ndigits = tofdg->size();
    for (unsigned k = 0; k < evt->ndigits; k++) {
	evt->plane[k] = tofdg->at(k).GetPlane();
	evt->slab[k] = tofdg->at(k).GetSlab();
	evt->pmt[k] = tofdg->at(k).GetPmt();

	evt->q[k] = tofdg->at(k).GetChargeMm();
	evt->qp[k] = tofdg->at(k).GetChargePm();
	evt->t[k] = tofdg->at(k).GetLeadingTime();
    }
}
