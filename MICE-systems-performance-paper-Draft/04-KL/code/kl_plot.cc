// P.F. edited 31/05/2021


void kl_plot(){

  //
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat("");
  gStyle->SetOptTitle(0);


  TFile* file = new TFile("KL_histos.root","READ");
 
  
  
  //////////////////////
  //Muons
  
  TH1F* hmu300 = (TH1F*) file->Get("mu300");
  TH1F* hmu240 = (TH1F*) file->Get("mu240");
  TH1F* hmu200 = (TH1F*) file->Get("mu200");
  TH1F* hmu170 = (TH1F*) file->Get("mu170");
  TH1F* hmu140 = (TH1F*) file->Get("mu140");
  
      
  TCanvas *c1 = new TCanvas("c1","KL Performance",200,10,1400,1000);
   c1->cd();

  
  hmu300->GetXaxis()->SetTitle("ADC product");
  
  hmu300->SetLineWidth(2);
  hmu300->SetLineColor(kRed+1);
  //hmu300->SetFillColor(4);
  //hmu300->SetFillStyle(3003);
  hmu300->Draw("");

  hmu240->SetLineWidth(2);
  hmu240->SetLineColor(kOrange+1);
  //hmu240->SetFillColor(2);
  //hmu240->SetFillStyle(3356);
  hmu240->Draw("same");   
  
  hmu200->SetLineWidth(2);
  hmu200->SetLineColor(kGreen+1);
  //hmu200->SetFillColor(1);
  //hmu200->SetFillStyle(3365);
  hmu200->Draw("same");

  hmu170->SetLineWidth(2);
  hmu170->SetLineColor(kBlue);
  //hmu170->SetFillColor(3);
  //hmu170->SetFillStyle(3003);
  hmu170->Draw("same");

  hmu140->SetLineWidth(2);
  hmu140->SetLineColor(kMagenta);
  //hmu140->SetFillColor(6);
  //hmu140->SetFillStyle(3244);
  hmu140->Draw("same");



  TLegend *legmu = new TLegend(0.6, 0.5, 0.85, 0.85);
  legmu->SetBorderSize(0);
  legmu->AddEntry(hmu140,"140 MeV/c", "l");
  legmu->AddEntry(hmu170,"170 MeV/c", "l");
  legmu->AddEntry(hmu200,"200 MeV/c", "l");
  legmu->AddEntry(hmu240,"240 MeV/c", "l");
  legmu->AddEntry(hmu300,"300 MeV/c", "l");
  legmu->Draw();


  c1->SaveAs("muon.pdf");
  
  /////////////////////////////
  //pions
  
   TH1F* hpi300 = (TH1F*) file->Get("pi300");
   TH1F* hpi240 = (TH1F*) file->Get("pi240");
   TH1F* hpi200 = (TH1F*) file->Get("pi200");
   TH1F* hpi170 = (TH1F*) file->Get("pi170");

   TCanvas *c2 = new TCanvas("c2","KL Performance",200,10,1400,1000);
   c2->cd();

  //  hpi300->SetTitle("KL response to pions");
  hpi300->GetXaxis()->SetTitle("ADC product");

  hpi300->SetLineWidth(2);
  hpi300->SetLineColor(kRed+1);
  //  hpi300->SetFillColor(4);
  //hpi300->SetFillStyle(3003);
  hpi300->Draw();

  hpi240->SetLineWidth(2);
  hpi240->SetLineColor(kOrange+1);
  //  hpi240->SetFillColor(2);
  //hpi240->SetFillStyle(3356);
  hpi240->Draw("same");

  hpi200->SetLineWidth(2);
  hpi200->SetLineColor(kGreen+1);
  //  hpi200->SetFillColor(1);
  //hpi200->SetFillStyle(3365);
  hpi200->Draw("same");


  hpi170->SetLineWidth(2);
  hpi170->SetLineColor(kBlue);
  //  hpi170->SetFillColor(3);
  //hpi170->SetFillStyle(3003);
  hpi170->Draw("same");




  TLegend *legpi = new TLegend(0.6, 0.5, 0.85, 0.85);
  legpi->SetBorderSize(0);
  legpi->AddEntry(hpi170,"170 MeV/c", "l");
  legpi->AddEntry(hpi200,"200 MeV/c", "l");
  legpi->AddEntry(hpi240,"240 MeV/c", "l");
  legpi->AddEntry(hpi300,"300 MeV/c", "l");
  legpi->Draw();


  c2->SaveAs("pion.pdf");
  
  /////////////////////////////                                                                                                      
  //electrons                                                                                                                         
   TH1F* he300 = (TH1F*) file->Get("e300");
   TH1F* he240 = (TH1F*) file->Get("e240");
   TH1F* he200 = (TH1F*) file->Get("e200");
   TH1F* he170 = (TH1F*) file->Get("e170");
   TH1F* he140 = (TH1F*) file->Get("e140");

 
   
  TCanvas *c3 = new TCanvas("c3","KL Performance",200,10,1400,1000);
   c3->cd();

 

  //  he200->SetTitle("KL response to electrons");
  he140->GetXaxis()->SetTitle("ADC product");

  he140->SetLineWidth(2);
  he140->SetLineColor(kMagenta);
  //he140->SetFillColor(6);                                                                                                                    
  //he140->SetFillStyle(3244);                                                                                                                 
  he140->Draw();



  he300->SetLineWidth(2);
  he300->SetLineColor(kRed+1);
  //he300->SetFillColor(4);
  //he300->SetFillStyle(3003);
  he300->Draw("same");

  he240->SetLineWidth(2);
  he240->SetLineColor(kOrange+1);
  //he240->SetFillColor(2);
  //he240->SetFillStyle(3356);
  he240->Draw("same");

  he200->SetLineWidth(2);
  he200->SetLineColor(kGreen+1);
  //he200->SetFillColor(1);
  //he200->SetFillStyle(3365);
  he200->Draw("same");

  he170->SetLineWidth(2);
  he170->SetLineColor(kBlue);
  //he170->SetFillColor(3);                                                                                                                    
  //he170->SetFillStyle(3003);                                                                                                                 
  he170->Draw("same");


  TLegend *lege = new TLegend(0.6, 0.5, 0.85, 0.85);
  lege->SetBorderSize(0);
  lege->AddEntry(he140,"140 MeV/c", "l");
  lege->AddEntry(he170,"170 MeV/c", "l");                                                                                            
  lege->AddEntry(he200,"200 MeV/c", "l");
  lege->AddEntry(he240,"240 MeV/c", "l");
  lege->AddEntry(he300,"300 MeV/c", "l");
  lege->Draw();


  c3->SaveAs("electron.pdf");
  
  
  /////////////////////////////                                                                                                         
  //mu.vs.e @ 140 MeV                                                                                                                           

  TCanvas *c4 = new TCanvas("c4","KL Performance",200,10,1400,1000);
  c4->cd();

  //  hmu200->SetTitle("KL response to muons, pions and electrons @ 200 MeV/c");
  hmu140->GetXaxis()->SetTitle("ADC product");

  hmu140->SetLineColor(kRed+1);
  hmu140->GetXaxis()->SetLabelSize(0.045);
  hmu140->GetYaxis()->SetLabelSize(0.045);
  hmu140->GetXaxis()->SetTitleSize(0.045);
  hmu140->GetYaxis()->SetTitleSize(0.045);
  hmu140->Draw();
  
  he140->SetLineColor(kGreen+1);
  he140->Draw("same");

  TLegend *leg140 = new TLegend(0.6, 0.5, 0.85, 0.85);
  leg140->SetHeader("140 MeV/c"); 
  leg140->SetBorderSize(0);
  leg140->AddEntry(hmu140,"muons", "l");
  leg140->AddEntry(he140,"electrons", "l");
  leg140->Draw();


  c4->SaveAs("mu_vs_e_140MeV.pdf");
  c4->SaveAs("mu_vs_e_140MeV.png");

  /////////////////////////////////////////////
  //pi.vs.mu.vs.e @ 170 MeV                                                                                                                           

  TCanvas *c5 = new TCanvas("c5","KL Performance",200,10,1400,1000);
  c5->cd();

  hmu170->GetXaxis()->SetTitle("ADC product");

  hmu170->SetLineColor(kRed+1);
  hmu170->GetXaxis()->SetLabelSize(0.045);
  hmu170->GetYaxis()->SetLabelSize(0.045);
  hmu170->GetXaxis()->SetTitleSize(0.045);
  hmu170->GetYaxis()->SetTitleSize(0.045);
  hmu170->Draw();

  hpi170->SetLineColor(kBlue);
  hpi170->Draw("same");

  he170->SetLineColor(kGreen+1);
  he170->Draw("same");


  TLegend *leg170 = new TLegend(0.6, 0.5, 0.85, 0.85);
  leg170->SetHeader("170 MeV/c"); 
  leg170->SetBorderSize(0);
  leg170->AddEntry(hmu170,"muons", "l");
  leg170->AddEntry(hpi170,"pions", "l");
  leg170->AddEntry(he170,"electrons", "l");
  leg170->Draw();


  c5->SaveAs("mu_vs_pi_vs_e_170MeV.pdf");
  c5->SaveAs("mu_vs_pi_vs_e_170MeV.png");
 
  /////////////////////////////////////////////
  //pi.vs.mu.vs.e @ 200 MeV                                                                                                                           

  TCanvas *c6 = new TCanvas("c6","KL Performance",200,10,1400,1000);
  c6->cd();

  //  hmu200->SetTitle("KL response to muons, pions and electrons @ 200 MeV/c");
  hmu200->GetXaxis()->SetTitle("ADC product");

  hmu200->SetLineColor(kRed+1);
  hmu200->GetXaxis()->SetLabelSize(0.045);
  hmu200->GetYaxis()->SetLabelSize(0.045);
  hmu200->GetXaxis()->SetTitleSize(0.045);
  hmu200->GetYaxis()->SetTitleSize(0.045);
  hmu200->Draw();

  hpi200->SetLineColor(kBlue);
  hpi200->Draw("same");

  he200->SetLineColor(kGreen+1);
  he200->Draw("same");


  TLegend *leg200 = new TLegend(0.6, 0.5, 0.85, 0.85);
  leg200->SetHeader("200 MeV/c"); 
  leg200->SetBorderSize(0);
  leg200->AddEntry(hmu200,"muons", "l");
  leg200->AddEntry(hpi200,"pions", "l");
  leg200->AddEntry(he200,"electrons", "l");
  leg200->Draw();


  c6->SaveAs("mu_vs_pi_vs_e_200MeV.pdf");
  c6->SaveAs("mu_vs_pi_vs_e_200MeV.png");

  /////////////////////////////////////////////
  //pi.vs.mu.vs.e @ 240 MeV                                                                                                                           

  TCanvas *c7 = new TCanvas("c7","KL Performance",200,10,1400,1000);
  c7->cd();

  hmu240->GetXaxis()->SetTitle("ADC product");

  hmu240->SetLineColor(kRed+1);
  hmu240->GetXaxis()->SetLabelSize(0.045);
  hmu240->GetYaxis()->SetLabelSize(0.045);
  hmu240->GetXaxis()->SetTitleSize(0.045);
  hmu240->GetYaxis()->SetTitleSize(0.045);
  hmu240->Draw();

  hpi240->SetLineColor(kBlue);
  hpi240->Draw("same");

  he240->SetLineColor(kGreen+1);
  he240->Draw("same");


  TLegend *leg240 = new TLegend(0.6, 0.5, 0.85, 0.85);
  leg240->SetHeader("240 MeV/c"); 
  leg240->SetBorderSize(0);
  leg240->AddEntry(hmu240,"muons", "l");
  leg240->AddEntry(hpi240,"pions", "l");
  leg240->AddEntry(he240,"electrons", "l");
  leg240->Draw();


  c7->SaveAs("mu_vs_pi_vs_e_240MeV.pdf");
  c7->SaveAs("mu_vs_pi_vs_e_240MeV.png");

  /////////////////////////////                                                                                                                            
  //pi.vs.mu.vs.e @ 300 MeV                                                                                                                                

  TCanvas *c8 = new TCanvas("c8","KL Performance",200,10,1400,1000);
  c8->cd();

  //  hmu300->SetTitle("KL response to muons and pions @ 300 MeV/c");
  hmu300->GetXaxis()->SetTitle("ADC product");

  hmu300->SetLineColor(kRed+1);
  hmu300->GetXaxis()->SetLabelSize(0.045);
  hmu300->GetYaxis()->SetLabelSize(0.045);
  hmu300->GetXaxis()->SetTitleSize(0.045);
  hmu300->GetYaxis()->SetTitleSize(0.045);
  hmu300->Draw();

  hpi300->SetLineColor(kBlue);
  hpi300->Draw("same");

  he300->SetLineColor(kGreen+1);
  he300->Draw("same");


  TLegend *leg300 = new TLegend(0.6, 0.5, 0.85, 0.85);
  leg300->SetHeader("300 MeV/c"); 
  leg300->SetBorderSize(0);
  leg300->AddEntry(hmu300,"muons", "l");
  leg300->AddEntry(hpi300,"pions", "l");
  leg300->AddEntry(he300,"electrons", "l");
  leg300->Draw();


  c8->SaveAs("mu_vs_pi_vs_e_300MeV.pdf");
  c8->SaveAs("mu_vs_pi_vs_e_300MeV.png");



  /////////////////////////////                                                                                                         
  //multiplicity @ 240 MeV                                                                                                                           

  TH1F* hmulte = (TH1F*) file->Get("kl_e_eff");
  TH1F* hmultmu = (TH1F*) file->Get("kl_mu_eff");
  TH1F* hmultpi = (TH1F*) file->Get("kl_pi_eff");

  
  TCanvas *c9 = new TCanvas("c9","KL Performance",200,10,1400,1000);
  c9->cd();
  //  hmultmu->SetTitle("Multiplicity @ 240 MeV/c");
  hmultmu->GetXaxis()->SetTitle("Number of KL cells");

  hmultmu->SetLineWidth(2);
  hmultmu->SetLineColor(kRed+1);
  hmultmu->Draw();

  hmultpi->SetLineWidth(2);
  hmultpi->SetLineColor(kBlue);
  hmultpi->Draw("same");

  hmulte->SetLineWidth(2);
  hmulte->SetLineColor(kGreen+1);
  hmulte->Draw("same");



  TLegend *legmult = new TLegend(0.6, 0.5, 0.85, 0.85);
  legmult->SetBorderSize(0);
  legmult->AddEntry(hmultmu,"muons", "l");
  legmult->AddEntry(hmultpi,"pions", "l");
  legmult->AddEntry(hmulte,"electrons", "l");
  legmult->Draw();
  
  c9->SaveAs("multiplicity_240MeV.pdf");

 
}
