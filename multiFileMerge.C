#include <iostream>
#include <fstream>
#include <string>
#include <TTree.h>
#include <TStopwatch.h>
#include <TList.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

using namespace std;

void multiFileMerge(const char* inputFile){
  
  TStopwatch timer;
  timer.Start();
  
  std::ifstream readFile(inputFile);
  std::string readFileName;
  std::string lastFileName;
  std::string runNumber;
  if (!readFile.is_open()) return;
  TChain ch("events");
  
  while (std::getline(readFile, readFileName)) {
    lastFileName = readFileName;
    runNumber = readFileName.substr(4,6);
    cout<<"Adding TTree from "<<readFileName<<endl;
    ch.Add(readFileName.c_str());
  }
  readFile.close();
  
  int nTrees = ch.GetNtrees();
  int nEnts = ch.GetEntries();
  cout << "# of trees: " << nTrees <<  endl;
  cout << "# of entries: " << nEnts <<  endl;
  
  TFile* outputFile;
  char outputFileName[256];
  //snprintf(outputFileName, sizeof(outputFileName), "~lkasper/trd_root/ROOT_MERGED/Run_%s_chain_%01dTrees_%06dEntries.root", runNumber.c_str(), nTrees, nEnts);
  sprintf(outputFileName, "~lkasper/trd_root/ROOT_MERGED/eventsChain_%06dEntries_%01dTrees.root",nEnts,nTrees);
  printf("Creating new root file %s \n",outputFileName);
  outputFile = new TFile(outputFileName, "RECREATE");
  
  cout<<"Merging "<<nTrees<<" trees into output file..."<<endl;
  ch.Merge(outputFile, 0);
  cout<<"Merge complete"<<endl;
  ch.ls();
  
  timer.Stop();
  timer.Print();
  
}

