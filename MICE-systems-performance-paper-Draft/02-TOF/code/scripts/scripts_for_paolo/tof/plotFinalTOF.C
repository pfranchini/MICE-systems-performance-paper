#define FNAME "plots/tof/tof01_tof0_corrected_vs_uncorrected.root"
#define HNAME "htof"


int plotFinalTOF() {
    gROOT->ForceStyle();
    //gStyle->SetPadBottomMargin(0.25);
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(100001);
    gStyle->SetNdivisions(505,"y");
    gStyle->SetFitFormat(".2f");
    gStyle->SetStatFont(42);
    gStyle->SetStatFontSize(0.04);


    auto f = new TFile(FNAME, "read");
    auto c1 = (TCanvas*) f->Get("c1");
    gROOT->cd();
    auto h = (TH1*)c1->FindObject(HNAME)->Clone();
    f->Close();

    //h->SetLin
    h->SetTitle("TOF1 - TOF0");
    h -> SetFillStyle(0);

    // invert histogram
    auto hnew = (TH1*) h->Clone("hinverted");
    int nbins = h->GetNbinsX();
    for (int i = 1; i <= nbins; i++) {
	hnew->SetBinContent(i, h->GetBinContent(nbins-i + 1));
    }
    hnew->GetListOfFunctions()->Remove(hnew->GetFunction("stats"));

    double min = -38;
    double max = -22;

    auto c = new TCanvas("c","", 600,300);
    hnew->Draw();
    hnew->GetXaxis()->SetRange(0,-1);
    double low = hnew->GetBinLowEdge(1);
    double hi = hnew->GetBinLowEdge(nbins+1);
    hnew->GetXaxis()->SetLimits(-hi, -low);

    hnew->SetAxisRange(23.,38.);


    // fit electron and muon peaks
    hnew -> Fit("gaus", "L", "", 25.,25.8);
    TF1* fit_el = hnew->GetFunction("gaus");
    fit_el->SetName("fit_el");
    fit_el->SetLineWidth(2);
    fit_el->SetLineColor(kRed);
    fit_el->SetLineStyle(kDashed);
    fit_el->FixParameter(0, fit_el->GetParameter(0));
    // fit_el->SetParName(1, "#mu");
    // fit_el->SetParName(2, "#sigma");
    c->Update();
    hnew->GetListOfFunctions()->Remove(fit_el);

    double width = 0.16;
    // get first stats
    auto stats1 = (TPaveStats*) hnew->GetFunction("stats");
    // remove them from the list
    hnew->GetListOfFunctions()->Remove(stats1);
    // draw them again
    stats1->SetTextColor(fit_el->GetLineColor());
    stats1->SetX1NDC(0.25);
    stats1->SetX2NDC(0.25+width);
    //stats1->SetY1NDC(0.7);
    stats1->Draw();


    hnew -> Fit("gaus", "L", "", 29.5,31.);
    TF1* fit_mu = hnew->GetFunction("gaus");
    fit_mu->SetName("fit_mu");
    fit_mu->SetLineWidth(2);
    fit_mu->SetLineColor(kGreen+1);
    fit_mu->SetLineStyle(kDashed);
    fit_mu->FixParameter(0, fit_mu->GetParameter(0));
    // fit_mu->SetParName(1, "#mu");
    // fit_mu->SetParName(2, "#sigma");
    c->Update();

    auto stats2 = (TPaveStats*) hnew->GetFunction("stats");
    // draw them again
    stats2->SetTextColor(fit_mu->GetLineColor());
    stats2->SetX1NDC(0.5);
    stats2->SetX2NDC(0.5+width);

    double height = stats2->GetY2NDC() - stats2->GetY1NDC();
    stats2->SetY1NDC(0.5);
    stats2->SetY2NDC(0.5 + height);
    //stats2->Draw();

    hnew->GetListOfFunctions()->Add(fit_el);


    c -> SaveAs("plots/tof/TOF_peaks.pdf");
    c -> SaveAs("plots/tof/TOF_peaks.root");

    return 0;
}
