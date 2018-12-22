#include "../WRFile/WRFile.hh"


void drawSignal(int index =0)
{

  WRFile BinFile("signal_data.bin");
  BinFile.IBinFile();
  BinFile.ReadBinFile(index);
  BinFile.CloseIBinFile();
  
  vector<int> bin,sig;
  for (int i=0;i<1000;i++)
    bin.push_back(i);
  sig.assign(BinFile.inputData.begin(),BinFile.inputData.end());

  TGraph *gSig = new TGraph(1000,&bin[0],&sig[0]);
  gSig->Draw("al");

}
