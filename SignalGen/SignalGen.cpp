#include "../WRFile/WRFile.hh"

void SignalGen()
{

  //Spectrum form.
  TF1 *fSpec = new TF1("fSpec",
		       "gaus(0)+pow([3]*x+[4],2)+[5]+[6]*exp(-[7]*x)",0,32768);
  fSpec->SetParameters(500,13000,800,0.001,-35,200,5e05,0.05);

  //Signal form.
  TF1 *fSig  = new TF1("fSig","[0]*sin(x*[1]+[2])+[3]*cos(x*[4]+[5])+[6]+gaus(7)",0,1000);
  fSig->SetNpx(1000); fSig->SetParameter(0,150); fSig->SetParameter(3,150);
  fSig->SetParameter(6,100); fSig->SetParameter(8,500); fSig->SetParameter(9,100);

  //Expected Spectrum
  TH1F *hSpec = new TH1F("hSpec","Spectrum Example",50,0,32768);

  //Open Output File
  WRFile BinFile("signal_data.bin");
  BinFile.OBinFile();
 
  unsigned amplitude,amp_rand;
  int CheckGaus;
  for(int i=0;i<20000;i++){
    
    amp_rand = (int)fSpec->GetRandom();
    amplitude = amp_rand > 300 ? amp_rand : 0;
    CheckGaus = amplitude == 0 ? 0 : 1;

    fSig->SetParameter(1,TMath::Pi()*((double)rand()/RAND_MAX));
    fSig->SetParameter(2,TMath::Pi()*((double)rand()/RAND_MAX));
    fSig->SetParameter(4,TMath::Pi()*((double)rand()/RAND_MAX));
    fSig->SetParameter(5,TMath::Pi()*((double)rand()/RAND_MAX));
    fSig->SetParameter(7,amplitude);

    BinFile.WriteBinFile(fSig,amplitude,CheckGaus);
    
    hSpec->Fill(amplitude);

  }
  BinFile.CloseOBinFile();

  hSpec->Draw("ep");
  
}
