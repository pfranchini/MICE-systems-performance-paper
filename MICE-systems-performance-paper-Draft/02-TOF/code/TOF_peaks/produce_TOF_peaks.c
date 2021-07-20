{    

  gStyle -> SetOptFit(1);  

  TFile file("TOF_peaks.root","read");
  TH1F *TOF01;
  TCanvas *c1 = (TCanvas*)file.Get("c");
  TOF01 = (TH1F*)c1->GetPrimitive("hinverted");
  //c1->Clear();
  //  c1->Draw();
  //TCanvas *c;

  //  TOF01->Fit("gaus","L","",24.26);

  TOF01->Draw();

  TCanvas c("c","tof01",1400,600);


  fit_el = new TF1("m1","gaus",25.2,25.535);
  fit_mu = new TF1("m2","gaus",29.5,30.9);

  fit_el->SetLineWidth(3);
  fit_el->SetLineColor(kRed);       
  fit_el->SetLineStyle(kDashed);    

  fit_mu->SetName("fit_mu");                                                                                                                                                 fit_mu->SetLineWidth(3);           
  fit_mu->SetLineColor(kGreen+1);
  fit_mu->SetLineStyle(kDashed);     
  
  TOF01->Fit(fit_el,"R");
  TOF01->Fit(fit_mu,"R+");

  /*
  // fit electron and muon peaks
  TOF01 -> Fit("gaus", "L", "", 25.1,25.7);
  TF1* fit_el = TOF01->GetFunction("gaus");
  fit_el->SetName("fit_el");
  fit_el->SetLineWidth(2);
  fit_el->SetLineColor(kRed);
  fit_el->SetLineStyle(kDashed);
  fit_el->FixParameter(0, fit_el->GetParameter(0));




  TOF01 -> Fit("gaus", "L", "", 29.5,31.);
  TF1* fit_mu = TOF01->GetFunction("gaus");
  fit_mu->SetName("fit_mu");
  fit_mu->SetLineWidth(2);
  fit_mu->SetLineColor(kGreen+1);
  fit_mu->SetLineStyle(kDashed);
  fit_mu->FixParameter(0, fit_mu->GetParameter(0));
  // fit_mu->SetParName(1, "#mu");                                                                                                                                          
  // fit_mu->SetParName(2, "#sigma");                                                                                                                                      


  */


  //  TOF01->GetXaxis()->SetTitleSize(1);
  //TOF01->GetYaxis()->SetTitleSize(1);
  TOF01->GetXaxis()->SetTitle("Time [ns]");

  TOF01->Draw();

  c.SaveAs("test.png");
  c.SaveAs("test.pdf");


}
