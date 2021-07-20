#define FNAME "plots/slab_dt/07_overall_slab_dt.root"
#define HPREF "hSlabDt_tof"
#define OUTFNAME "plots/slab_dt/07_overall_slab_dt.pdf"


int plotSlabDtNicer() {
    gROOT->ForceStyle(1);
    gStyle->SetOptStat("e");
    gStyle->SetOptFit(1000001);
    gStyle->SetTitleY(0.97);
    gStyle->SetFitFormat("5.3f");
    gStyle->SetStatFormat("5.3f");
    gStyle->SetHistLineColor(kBlue+2);
    gStyle->SetHistFillColor(kCyan-9);
    //gStyle->SetStatW(0.22);
    // gStyle->SetStatH(0.25);
    gStyle->SetStatFontSize(0.05);


    auto f = new TFile(FNAME, "read");

    auto c = (TCanvas*) f->Get("cc");

    cout<<c<<endl;

    gROOT->cd();

    TH1* hists [3];

    for (int i = 0; i < 3; i++) {
	hists[i] = (TH1*)c->FindObject(Form("%s%d",HPREF,i))->Clone();
	hists[i]->GetListOfFunctions()->Clear();

	hists[i]->Fit("gaus", "L0", "", -0.4,0.4);
	hists[i] -> GetListOfFunctions() -> Print();


	TF1* fit = hists[i] -> GetFunction("gaus");
	fit -> FixParameter( 0, fit->GetParameter(0) );
	fit -> SetLineWidth(1);

	fit -> SetParameter(1, hists[i]->GetMean());
	fit -> SetParameter(2, hists[i]->GetRMS());

	fit -> SetParName(1, "Mean");
	fit -> SetParName(2, "RMS");
    }
    f->Close();


    auto cc = new TCanvas("cc", "", 900, 300);
    cc->Divide(3,1);

    for (int i = 0; i < 3; i++) {
	TPad* pad = (TPad*)cc->cd(i+1);
	//hists[i]->GetListOfFunctions()->Clear();
	hists[i]->Draw();
    }


    cc->SaveAs(OUTFNAME);
    TString ss = OUTFNAME;
    ss.ReplaceAll(".pdf", ".root");
    cc->SaveAs(ss);


    return 0;
}
