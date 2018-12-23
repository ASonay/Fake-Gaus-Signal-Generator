#include "WRFile.hh"

WRFile::WRFile(const string filename){
  const string location = "../Data/";
  const string tag = ".bin";
  fileloc.append(location);
  fileloc.append(filename);
  fileloc.append(tag);
  cout << "File location set by: " << fileloc << endl;
}

void WRFile::OBinFile(){
  obinFile.open(fileloc, ios::out | ios::binary);
  if(obinFile)
    cout << "Output file opened successfuly." << endl;
}


void WRFile::WriteBinFile(TF1 *fSig, unsigned amp, int valEx){

  const unsigned size = 1000;
  vector<int> sigBin;

  fSig->SetParameters(150,TMath::Pi()*((double)rand()/RAND_MAX),
		      TMath::Pi()*((double)rand()/RAND_MAX),150,
		      TMath::Pi()*((double)rand()/RAND_MAX),
		      TMath::Pi()*((double)rand()/RAND_MAX),100,
		      amp,500,100);
  
  if(!obinFile){
    cout<<"Error in creating file!!!"<<endl;
    return;
  }

  obinFile.write((char*)&amp,sizeof(amp));
  obinFile.write((char*)&valEx,sizeof(valEx));
  for (unsigned i=0;i<size;i++)
    sigBin.push_back((int)fSig->Eval(i));
  obinFile.write(reinterpret_cast<char*>(sigBin.data()),sigBin.size()*sizeof(int));
  
}

void WRFile::IBinFile(){
  ibinFile.open(fileloc, ios::in | ios::binary);
  if(ibinFile)
    cout << "Input file opened successfuly." << endl;
}


void WRFile::ReadBinFile(int index){
  
  const unsigned size = 1000;

  if(!ibinFile){
    cout<<"File not found!!!"<<endl;
    return;
  }

  inputData.clear();
  for (unsigned i=0;i<size;i++)
    inputData.push_back(0);

  ibinFile.seekg(index*(sizeof(unsigned)+sizeof(int)+inputData.size()*sizeof(int)),ios::beg);
 
  ibinFile.read((char*)&amplitudeEx,sizeof(unsigned));
  ibinFile.read((char*)&valueEx,sizeof(int));
  ibinFile.read(reinterpret_cast<char*>(inputData.data()),inputData.size()*sizeof(int));
  /*
  cout << "Amp: " << amplitudeEx << " Expec: " << valueEx << endl;
  for (unsigned i=0;i<size;i++)
    cout << i << " -- " << inputData[i] << endl;
  */
}

void WRFile::CloseOBinFile(){
  obinFile.close();
  cout << "File closed.." << endl;
}

void WRFile::CloseIBinFile(){
  ibinFile.close();
  cout << "File closed.." << endl;
}
