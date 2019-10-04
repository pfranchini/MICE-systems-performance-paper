void plotTOF0_TOF01(const char* fname = "output_data/10248/v3.2.0_newCalib_4ns/"
		    "10248_v3.2.0_wSlabs_wDigits_new_tof_calib_4ns.root",
		    const char* outpref = "plots/tof/")
{
    //TFile *f = TFile::Open("output_data/10248/v3.1.2_newCalib_3ns/10248_wSlabs_wDigits.root");
    TFile *f = TFile::Open(fname);
    TTree* tof_tree = (TTree*)f->Get("tof_tree");

    tof_tree->Draw("tof0t[0]>>h(1800, -110, -20)",
		   "tof1npoints > 0 && tof0npoints == 1", "");
    tof_tree->Draw("tof0t[0] - tof1t[0]>>htof(3600, -110, -20)",
		   "tof1npoints == 1 && tof0npoints == 1", "");
    tof_tree->Draw("(tof0slabpmt0rawt[0]+tof0slabpmt0rawt[1]"
		   "+tof0slabpmt1rawt[0]+tof0slabpmt1rawt[1])*0.25"
		   ">>hraw(1800, -110, -20)",
		   "tof1npoints > 0 && tof0npoints == 1 && tof0nslabs == 2", "");

    // draw tof0 time vs charge
    tof_tree->Draw("tof0t[0]:tof0q[0]>>htvsq(400,0,20e3, 500, -45, -20)",
		   "tof1npoints > 0 && tof0npoints == 1", "");
    // draw tof0 time vs charge in tof1
    tof_tree->Draw("tof0t[0]:tof1q[0]>>htvsq1(400,0,20e3, 500, -45, -20)",
		   "tof1npoints == 1 && tof0npoints == 1", "");
    // draw tof1 time vs charge in tof1
    tof_tree->Draw("tof1t[0]:tof1q[0]>>ht1vsq1(400,0,20e3, 100, -2, 2)",
		   "tof1npoints == 1 && tof0npoints == 1", "");


    const float low[3] = {-36., -32., -26.};
    const float hi[3] = {-32., -29., -24.5};
    const char* titles[3] = {"pions", "muons", "electrons"};
    TH2* htvsq1pid [3] = {};
    TH2* ht1vsq1pid [3] = {};

    // draw tof0 time vs charge in tof1 - pion, muon, electron
    for (unsigned i = 0; i < 3; i++) {
	tof_tree->Draw(Form("tof0t[0]:tof1q[0]>>htvsq1_%d(400,0,20e3, 500, -45, -20)", i),
		       Form("tof1npoints == 1 && tof0npoints == 1 &&"
			    "tof0t[0] > %.2f && tof0t[0] < %.2f", low[i], hi[i]));
	htvsq1pid[i] = (TH2*)gDirectory->Get(Form("htvsq1_%d", i));
    }

    TCanvas* c3 = new TCanvas("c3", "", 900, 300);
    c3->Divide(3,1);
    for (unsigned i = 0; i < 3; i++) {
	c3->cd(i+1);
	htvsq1pid[i] -> SetStats(0);
	htvsq1pid[i] -> Draw("colz");
	htvsq1pid[i] -> SetTitle(Form("%s;Charge in TOF1 [ADC];Time in TOF0 [ns]",
				      titles[i]));
    }
    c3->SaveAs(Form("%stof0_vs_tof1q_bypid.pdf", outpref));



    // draw tof1 time vs charge in tof1 - pion, muon, electron
    for (unsigned i = 0; i < 3; i++) {
	tof_tree->Draw(Form("tof1t[0]:tof1q[0]>>ht1vsq1_%d(400,0,20e3, 100, -2, 2)", i),
		       Form("tof1npoints == 1 && tof0npoints == 1 &&"
			    "tof0t[0] > %.2f && tof0t[0] < %.2f", low[i], hi[i]));
	ht1vsq1pid[i] = (TH2*)gDirectory->Get(Form("ht1vsq1_%d", i));
    }

    for (unsigned i = 0; i < 3; i++) {
	c3->cd(i+1);
	ht1vsq1pid[i] -> SetStats(0);
	ht1vsq1pid[i] -> Draw("colz");
	ht1vsq1pid[i] -> SetTitle(Form("%s;Charge in TOF1 [ADC];Time in TOF1 [ns]",
				       titles[i]));
    }
    c3->SaveAs(Form("%stof1_vs_tof1q_bypid.pdf", outpref));





    TH1* hraw = (TH1*)gDirectory->Get("hraw");
    hraw->SetLineColor(kGreen+2);
    TH1* h =  (TH1*)gDirectory->Get("h");
    TH1* htof =  (TH1*)gDirectory->Get("htof");
    TH2* htvsq =  (TH2*)gDirectory->Get("htvsq");
    TH2* htvsq1 =  (TH2*)gDirectory->Get("htvsq1");
    TH2* ht1vsq1 =  (TH2*)gDirectory->Get("ht1vsq1");
    //hraw->SetLineColor(kGreen+2);
    cout<<htof->GetEntries()<<endl;


    TCanvas* c2 = new TCanvas("c2", "", 2);
    htvsq->SetStats(0);
    htvsq->Draw("colz");
    c2->SaveAs(Form("%stof0_vs_q.pdf", outpref));

    htvsq1->SetStats(0);
    htvsq1->Draw("colz");
    c2->SaveAs(Form("%stof0_vs_tof1q.pdf", outpref));

    ht1vsq1->SetStats(0);
    ht1vsq1->Draw("colz");
    c2->SaveAs(Form("%stof1_vs_tof1q.pdf", outpref));


    TCanvas* c1 = new TCanvas("c1", "", 600,600);
    c1->Divide(1,2);

    // THStack* hs = new THStack("hs", "TOF0 Station;Time [ns]");
    // hs->Add(h);
    // hs->Add(hraw);

    h->SetStats(0);
    hraw->SetStats(0);

    // hs->Draw("nostack");

    h->SetTitle("Fully corrected;Time [ns]");
    htof->SetTitle("Fully corrected - TOF0 and TOF0 - TOF1;Time [ns]");
    hraw->SetTitle("Uncorrected;Time [ns]");

    htof->SetFillColor(kRed-9);
    htof->SetLineColor(kRed);

    c1->cd(1); htof->Draw(); h->Draw("same");
    c1->cd(2); hraw->Draw();


    // center on muon peak and set the same axis range

    double centre1 = h->GetBinCenter(h->GetMaximumBin());
    double centre2 = hraw->GetBinCenter(hraw->GetMaximumBin());
    double width = 10.;

    h->SetAxisRange(centre1 - width, centre1 + width);
    htof->SetAxisRange(centre1 - width, centre1 + width);
    hraw->SetAxisRange(centre2 - width, centre2 + width);

    // c1->BuildLegend(0.31,0.70,0.69,0.85);

    c1->SaveAs(Form("%stof01_tof0_corrected_vs_uncorrected.pdf", outpref));
    c1->SaveAs(Form("%stof01_tof0_corrected_vs_uncorrected.root", outpref));
}
