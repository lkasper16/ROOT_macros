#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>

void mergePionTTrees(const char* file1, const char* file2, const char* file3) {
  
	std::vector<TString> treeNames = {"gem_hits", "mmg1_hits", "urw_hits"};
	char outputFile[120];
  sprintf(outputFile, "allPi_%s", file1);  
  
    TFile* outputFirstFile = TFile::Open("outputFirstFile.root", "RECREATE");
    TFile* outputSecondFile = TFile::Open("outputSecondFile.root", "RECREATE");
    TFile* mergedFile = TFile::Open(outputFile, "RECREATE");
    cout << "Output file created: " << outputFile << endl;
    if (!mergedFile || mergedFile->IsZombie()) {
        std::cerr << "Error: Could not create output file " << outputFile << endl;
        return;
    }
    
    for (int i=0; i<treeNames.size(); i++) {
    	
    	TString treeName = treeNames[i];
    	//cout << treeName << endl;
    	
    	TFile* firstInputFile = TFile::Open(file2, "READ");
        if (!firstInputFile || firstInputFile->IsZombie()) {
            std::cerr << "Error: Could not open file " << file2 << endl;
            return;
        }
        TTree* firstTree = (TTree*)firstInputFile->Get(treeName);
        if (!firstTree) {
            std::cerr << "Error: Could not find tree " << treeName << " in " << file2 << endl;
            firstInputFile->Close();
            continue;
        }
        std::vector<bool>* parID = nullptr;
        firstTree->SetBranchAddress("parID", &parID);
        mergedFile->cd();
        TTree* newFirstTree = firstTree->CloneTree(0);
        firstTree->CopyAddresses(newFirstTree);
        char newTreeName[120];
        sprintf(newTreeName, "%s_f2", treeName.Data());
        newFirstTree->SetName(newTreeName);
        firstInputFile->cd();
        
        for (Long64_t i=0; i<firstTree->GetEntries(); i++) {
            firstTree->GetEntry(i);
            bool isOne = false;
            //-- Skip writing all parID==1 (electron) entries from file1 TTrees
            for (size_t j=0; j<parID->size(); j++) {
                //cout << "***RADTREE: index=" << j << " parID=" << (*parID)[j] << endl;
                if ((*parID)[j]) {
                    isOne = true;
                    break;
                }
            }
            if (isOne) {
                continue;
            }
            mergedFile->cd();
            newFirstTree->Fill();
        }
        firstInputFile->Close();
        
        
        TFile* secondInputFile = TFile::Open(file3, "READ");
        if (!secondInputFile || secondInputFile->IsZombie()) {
            std::cerr << "Error: Could not open file " << file3 << endl;
            return;
        }
        TTree* secondTree = (TTree*)secondInputFile->Get(treeName);
        if (!secondTree) {
            std::cerr << "Error: Could not find tree " << treeName << " in " << file3 << endl;
            secondInputFile->Close();
            continue;
        }
        secondTree->SetBranchAddress("parID", &parID);
        mergedFile->cd();
        TTree* newSecondTree = secondTree->CloneTree(0);
        secondTree->CopyAddresses(newSecondTree);
        char newNRTreeName[120];
        sprintf(newNRTreeName, "%s_f3", treeName.Data());
        newSecondTree->SetName(newNRTreeName);
        secondInputFile->cd();
        
        for (Long64_t i=0; i<secondTree->GetEntries(); i++) {
            secondTree->GetEntry(i);
            bool isOne = false;
            //-- Skip writing all parID==1 (Electron) entries from file3 TTrees
            for (size_t j=0; j<parID->size(); j++) {
                //cout << "***NORADTREE: index=" << j << " parID=" << (*parID)[j] << endl;
                if ((*parID)[j]) {
                    isOne = true;
                    break;
                }
            }
            if (isOne) {
                continue;
            }
           /* // Change parID from 1 to 0 for remaining (El) entries
            for (size_t j=0; j<parID->size(); j++) {
                if ((*parID)[j]) {
                    (*parID)[j] = false;
                }
            }*/
            mergedFile->cd();
            newSecondTree->Fill();
        }
        secondInputFile->Close();
        
       
        outputFirstFile->cd();
        TTree* mergedTree = newFirstTree->CloneTree();
        mergedTree->SetName(treeName);
        mergedTree->Write(treeName);
        cout << "TTree " << treeName << " Written ok to " << outputFirstFile->GetName() << endl;
        outputSecondFile->cd();
        mergedTree = newSecondTree->CloneTree();
        mergedTree->SetName(treeName);
        mergedTree->Write(treeName);
        cout << "TTree " << treeName << " Written ok to " << outputSecondFile->GetName() << endl;
        cout<<"==================================================================="<<endl;
    }
    outputFirstFile->Close();
    outputSecondFile->Close();
    TFile* gem_file = new TFile("gem_file.root", "RECREATE");
    TChain mergedChaing("gem_hits");
    mergedChaing.Add("outputFirstFile.root");
    mergedChaing.Add("outputSecondFile.root");
    mergedChaing.Add(file1); ///////
    mergedChaing.Merge(gem_file, 0);
    cout << "Entries in merged gem Chain: " << mergedChaing.GetEntries() << endl;
    TFile* mmg1_file = new TFile("mmg1_file.root", "RECREATE");
    TChain mergedChainm("mmg1_hits");
    mergedChainm.Add("outputFirstFile.root");
    mergedChainm.Add("outputSecondFile.root");
    mergedChainm.Add(file1); ///////
    mergedChainm.Merge(mmg1_file, 0);
    cout << "Entries in merged mmg Chain: " << mergedChainm.GetEntries() << endl;
    TFile* urw_file = new TFile("urw_file.root", "RECREATE");
    TChain mergedChainu("urw_hits");
    mergedChainu.Add("outputFirstFile.root");
    mergedChainu.Add("outputSecondFile.root");
    mergedChainu.Add(file1); ///////
    mergedChainu.Merge(urw_file, 0);
    cout << "Entries in merged uRWell Chain: " << mergedChainu.GetEntries() << endl;
    
    mergedFile->Close();
    outputFirstFile->Delete();
    outputSecondFile->Delete();
    cout << "Merged TTrees saved to " << outputFile << endl;
}
