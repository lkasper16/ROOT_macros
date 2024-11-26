#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>

void makeNoRadTTree(const char* radFile, const char* noRadFile) {
    
	std::vector<TString> treeNames = {"gem_hits", "mmg1_hits"};
	char outputFile[120];
    sprintf(outputFile, "nrc_%s", radFile);
    
    
    TFile* outputRadFile = TFile::Open("outputRadFile.root", "RECREATE");
    TFile* outputNoRadFile = TFile::Open("outputNoRadFile.root", "RECREATE");
    TFile* mergedFile = TFile::Open(outputFile, "RECREATE");
    cout << "Output file created: " << outputFile << endl;
    if (!mergedFile || mergedFile->IsZombie()) {
        std::cerr << "Error: Could not create output file " << outputFile << endl;
        return;
    }
    
    for (int i=0; i< treeNames.size(); i++) {
    	
    	TString treeName = treeNames[i];
    	//cout << treeName << endl;
    	
    	TFile* radInputFile = TFile::Open(radFile, "READ");
        if (!radInputFile || radInputFile->IsZombie()) {
            std::cerr << "Error: Could not open file " << radFile << endl;
            return;
        }
        TTree* radTree = (TTree*)radInputFile->Get(treeName);
        if (!radTree) {
            std::cerr << "Error: Could not find tree " << treeName << " in " << radFile << endl;
            radInputFile->Close();
            continue;
        }
        std::vector<bool>* parID = nullptr;
        radTree->SetBranchAddress("parID", &parID);
        mergedFile->cd();
        TTree* newRadTree = radTree->CloneTree(0);
        radTree->CopyAddresses(newRadTree);
        char newTreeName[120];
        sprintf(newTreeName, "%s_Rad", treeName.Data());
        newRadTree->SetName(newTreeName);
        radInputFile->cd();
        
        for (Long64_t i = 0; i < radTree->GetEntries(); i++) {
            radTree->GetEntry(i);
            bool isZero = false;
            //-- Skip writing all parID==0 (pion) entries from radFile TTrees
            for (size_t j = 0; j < parID->size(); j++) {
                //cout << "***RADTREE: index=" << j << " parID=" << (*parID)[j] << endl;
                if (!(*parID)[j]) {
                    isZero = true;
                    break;
                }
            }
            if (isZero) {
                continue;
            }
            
            mergedFile->cd();
            newRadTree->Fill();
        }
        radInputFile->Close();
        
        
        TFile* noRadInputFile = TFile::Open(noRadFile, "READ");
        if (!noRadInputFile || noRadInputFile->IsZombie()) {
            std::cerr << "Error: Could not open file " << noRadFile << endl;
            return;
        }
        TTree* noRadTree = (TTree*)noRadInputFile->Get(treeName);
        if (!noRadTree) {
            std::cerr << "Error: Could not find tree " << treeName << " in " << noRadFile << endl;
            noRadInputFile->Close();
            continue;
        }
        noRadTree->SetBranchAddress("parID", &parID);
        mergedFile->cd();
        TTree* newNoRadTree = noRadTree->CloneTree(0);
        noRadTree->CopyAddresses(newNoRadTree);
        char newNRTreeName[120];
        sprintf(newNRTreeName, "%s_NoRad", treeName.Data());
        newNoRadTree->SetName(newNRTreeName);
        noRadInputFile->cd();
        
        for (Long64_t i = 0; i < noRadTree->GetEntries(); i++) {
            noRadTree->GetEntry(i);
            bool isZero = false;
            //-- Skip writing all parID==0 (pion) entries from noRadFile TTrees
            for (size_t j = 0; j < parID->size(); j++) {
                //cout << "***NORADTREE: index=" << j << " parID=" << (*parID)[j] << endl;
                if (!(*parID)[j]) {
                    isZero = true;
                    break;
                }
            }
            if (isZero) {
                continue;
            }
            // Change parID from 1 to 0 for remaining (El) entries
            for (size_t j = 0; j < parID->size(); j++) {
                if ((*parID)[j]) {
                    (*parID)[j] = false;
                }
            }
            mergedFile->cd();
            newNoRadTree->Fill(); //Fill only electron entries with their parID now reassigned to 0
        }
        noRadInputFile->Close();
        
        
        outputRadFile->cd();
        TTree* mergedTree = newRadTree->CloneTree();
        mergedTree->SetName(treeName);
        mergedTree->Write(treeName);
        cout << "TTree " << treeName << " Written ok to " << outputRadFile->GetName() << endl;
        outputNoRadFile->cd();
        mergedTree = newNoRadTree->CloneTree();
        mergedTree->SetName(treeName);
        mergedTree->Write(treeName);
        cout << "TTree " << treeName << " Written ok to " << outputNoRadFile->GetName() << endl;
        
        
        
        //mergedFile->cd();
      //  TTree* mergedTree = newRadTree->CloneTree();
     //   mergedTree->SetName(treeName);
        
        //newRadTree->Print();
        //newNoRadTree->Print();
        /*
        TChain mergedChain(treeName);
        //newRadTree->SetName(treeName);
        mergedChain.Add(outputRadFile);
        //newNoRadTree->SetName(treeName);
        mergedChain.Add(outputNoRadFile);
        mergedChain.Write();
        cout << "Entries in mergedChain: " << mergedChain.GetEntries() << endl;
        mergedChain.Print();
        */
        /*
        Long64_t nEntries1 = newRadTree->GetEntries();
        cout << "Copying " << nEntries1 << " entries from newRadTree..." << endl;
        newRadTree->CopyAddresses(mergedTree);
        newNoRadTree->CopyAddresses(mergedTree);
        newRadTree->CopyEntries(mergedTree);
        cout << "Entries in mergedTree after copying newRadTree: " << mergedTree->GetEntries() << endl;
        Long64_t nEntries2 = newNoRadTree->GetEntries();
        cout << "Copying " << nEntries2 << " entries from newNoRadTree..." << endl;
        //newNoRadTree->CopyAddresses(mergedTree);
        newNoRadTree->CopyEntries(mergedTree);
        cout << "Entries in mergedTree after copying newNoRadTree: " << mergedTree->GetEntries() << endl;
        mergedFile->cd();
        mergedTree->Write(treeName, TObject::kOverwrite);
        newRadTree->Write();
        newNoRadTree->Write();
        mergedTree->Print();
        */
        cout<<"==================================================================="<<endl;
    }
    outputRadFile->Close();
    outputNoRadFile->Close();
    mergedFile->cd();
    TChain mergedChaing("gem_hits");
    mergedChaing.Add("outputRadFile.root");
    mergedChaing.Add("outputNoRadFile.root");
    mergedChaing.Write();
    cout << "Entries in merged gem Chain: " << mergedChaing.GetEntries() << endl;
    //mergedChaing.Print();
    TChain mergedChainm("mmg1_hits");
    mergedChainm.Add("outputRadFile.root");
    mergedChainm.Add("outputNoRadFile.root");
    mergedChainm.Write();
    cout << "Entries in merged mmg Chain: " << mergedChainm.GetEntries() << endl;
    
    mergedFile->Close();
    outputRadFile->Delete();
    outputNoRadFile->Delete();
    cout << "Merged TTrees saved to " << outputFile << endl;
}
