#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"

using namespace std;


class WRFile
{

public:
  WRFile(const string filename);
  void OBinFile();
  void IBinFile();
  void WriteBinFile(TF1 *fSig, unsigned amp, int valEx);
  void ReadBinFile(int index);
  void CloseOBinFile();
  void CloseIBinFile();

  vector<int> inputData;
  unsigned amplitudeEx;
  int valueEx;
  
private:
  ofstream obinFile;
  ifstream ibinFile;
  string fileloc;

};
