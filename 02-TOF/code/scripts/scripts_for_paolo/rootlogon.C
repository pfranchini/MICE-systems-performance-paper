void rootlogon() {
  ;
}

void mauslibs() {
  cout << "loading MAUS library..." << endl;
  gROOT->ProcessLine(".L $(MAUS_ROOT_DIR)/src/common_cpp/libMausCpp.so");
  std::string MAUS_ROOT_DIR = gSystem->Getenv("MAUS_ROOT_DIR");
  gROOT->ProcessLine(Form(".include %s/src/common_cpp", MAUS_ROOT_DIR.c_str()));
  gROOT->ProcessLine(Form(".include %s", MAUS_ROOT_DIR.c_str()));
  gSystem->AddIncludePath(Form("-I$%s/src/common_cpp", MAUS_ROOT_DIR.c_str()));
  gSystem->AddIncludePath(Form("-I$%s", MAUS_ROOT_DIR.c_str()));
}
