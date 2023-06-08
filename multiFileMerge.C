#include <iostream>
#include <fstream>
#include <string>
#include <TTree.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TRandom2.h>
#include <TRandom.h>
#include <TStopwatch.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TList.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TLine.h>
#include <TBox.h>
#include <TObject.h>
#include <TLegend.h>
#include <TProfile.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

using namespace std;

void multiFileMerge(){
  
  TStopwatch timer;
  timer.Start();
  
  //A chain is a collection of files containg TTree objects
  //Use TChain for multiple files - All constructors are equivalent
  TChain ch("events");
  
  //// XeCO2 files ////
  ch.Add("/store/user/kaspel1/FNAL2023_Data/ROOTData/Run_003287.root");
  ch.Add("/store/user/kaspel1/FNAL2023_Data/ROOTData/Run_003288.root");
  
  
  int nTrees = ch.GetNtrees();
  int nEnts = ch.GetEntries();
  cout << "# of trees: " << nTrees <<  endl;
  cout << "# of entries: " << nEnts <<  endl;
  
   // Declaration of leaf types
   ULong64_t       srs_raw_count;
   vector<unsigned int> *srs_raw_roc;
   vector<unsigned int> *srs_raw_slot;
   vector<unsigned int> *srs_raw_channel;
   vector<unsigned int> *srs_raw_apv_id;
   vector<unsigned int> *srs_raw_channel_apv;
   vector<unsigned short> *srs_raw_best_sample;
   vector<unsigned short> *srs_raw_samples_index;
   vector<unsigned short> *srs_raw_samples_count;
   vector<unsigned short> *srs_raw_samples;
   ULong64_t       f125_wraw_count;
   vector<unsigned int> *f125_wraw_roc;
   vector<unsigned int> *f125_wraw_slot;
   vector<unsigned int> *f125_wraw_channel;
   vector<bool>    *f125_wraw_invalid_samples;
   vector<bool>    *f125_wraw_overflow;
   vector<unsigned int> *f125_wraw_itrigger;
   vector<unsigned short> *f125_wraw_samples_index;
   vector<unsigned short> *f125_wraw_samples_count;
   vector<unsigned short> *f125_wraw_samples;
   ULong64_t       f250_wraw_count;
   vector<unsigned int> *f250_wraw_roc;
   vector<unsigned int> *f250_wraw_slot;
   vector<unsigned int> *f250_wraw_channel;
   vector<bool>    *f250_wraw_invalid_samples;
   vector<bool>    *f250_wraw_overflow;
   vector<unsigned int> *f250_wraw_itrigger;
   vector<unsigned short> *f250_wraw_samples_index;
   vector<unsigned short> *f250_wraw_samples_count;
   vector<unsigned short> *f250_wraw_samples;
   ULong64_t       f125_pulse_count;
   vector<unsigned int> *f125_pulse_roc;
   vector<unsigned int> *f125_pulse_slot;
   vector<unsigned int> *f125_pulse_channel;
   vector<unsigned int> *f125_pulse_npk;
   vector<unsigned int> *f125_pulse_le_time;
   vector<unsigned int> *f125_pulse_time_quality_bit;
   vector<unsigned int> *f125_pulse_overflow_count;
   vector<unsigned int> *f125_pulse_pedestal;
   vector<unsigned int> *f125_pulse_integral;
   vector<unsigned int> *f125_pulse_peak_amp;
   vector<unsigned int> *f125_pulse_peak_time;
   vector<unsigned int> *f125_pulse_word1;
   vector<unsigned int> *f125_pulse_word2;
   vector<unsigned int> *f125_pulse_nsamples_pedestal;
   vector<unsigned int> *f125_pulse_nsamples_integral;
   vector<bool>    *f125_pulse_emulated;
   vector<unsigned int> *f125_pulse_le_time_emulated;
   vector<unsigned int> *f125_pulse_time_quality_bit_emulated;
   vector<unsigned int> *f125_pulse_overflow_count_emulated;
   vector<unsigned int> *f125_pulse_pedestal_emulated;
   vector<unsigned int> *f125_pulse_integral_emulated;
   vector<unsigned int> *f125_pulse_peak_amp_emulated;
   vector<unsigned int> *f125_pulse_peak_time_emulated;
   ULong64_t       f250_pulse_count;
   //vector<unsigned int> *f250_pulse_roc;
   //vector<unsigned int> *f250_pulse_slot;
   //vector<unsigned int> *f250_pulse_channel;
   vector<unsigned int> *f250_pulse_event_within_block;
   vector<bool>    *f250_pulse_qf_pedestal;
   vector<unsigned int> *f250_pulse_pedestal;
   vector<unsigned int> *f250_pulse_integral;
   vector<bool>    *f250_pulse_qf_nsa_beyond_ptw;
   vector<bool>    *f250_pulse_qf_overflow;
   vector<bool>    *f250_pulse_qf_underflow;
   vector<unsigned int> *f250_pulse_nsamples_over_threshold;
   vector<unsigned int> *f250_pulse_course_time;
   vector<unsigned int> *f250_pulse_fine_time;
   vector<unsigned int> *f250_pulse_pulse_peak;
   vector<bool>    *f250_pulse_qf_vpeak_beyond_nsa;
   vector<bool>    *f250_pulse_qf_vpeak_not_found;
   vector<bool>    *f250_pulse_qf_bad_pedestal;
   vector<unsigned int> *f250_pulse_pulse_number;
   vector<unsigned int> *f250_pulse_nsamples_integral;
   vector<unsigned int> *f250_pulse_nsamples_pedestal;
   vector<bool>    *f250_pulse_emulated;
   vector<unsigned int> *f250_pulse_integral_emulated;
   vector<unsigned int> *f250_pulse_pedestal_emulated;
   vector<unsigned int> *f250_pulse_time_emulated;
   vector<unsigned int> *f250_pulse_course_time_emulated;
   vector<unsigned int> *f250_pulse_fine_time_emulated;
   vector<unsigned int> *f250_pulse_pulse_peak_emulated;
   vector<unsigned int> *f250_pulse_qf_emulated;
   ULong64_t       gem_scluster_count;
   vector<double>  *gem_scluster_x;
   vector<double>  *gem_scluster_y;
   vector<double>  *gem_scluster_energy;
   vector<double>  *gem_scluster_adc;
   ULong64_t       srs_prerecon_count;
   vector<double>  *srs_prerecon_y;
   vector<double>  *srs_prerecon_x;
  
   // Set object pointer
   srs_raw_roc = 0;
   srs_raw_slot = 0;
   srs_raw_channel = 0;
   srs_raw_apv_id = 0;
   srs_raw_channel_apv = 0;
   srs_raw_best_sample = 0;
   srs_raw_samples_index = 0;
   srs_raw_samples_count = 0;
   srs_raw_samples = 0;
   f125_wraw_roc = 0;
   f125_wraw_slot = 0;
   f125_wraw_channel = 0;
   f125_wraw_invalid_samples = 0;
   f125_wraw_overflow = 0;
   f125_wraw_itrigger = 0;
   f125_wraw_samples_index = 0;
   f125_wraw_samples_count = 0;
   f125_wraw_samples = 0;
   f250_wraw_roc = 0;
   f250_wraw_slot = 0;
   f250_wraw_channel = 0;
   f250_wraw_invalid_samples = 0;
   f250_wraw_overflow = 0;
   f250_wraw_itrigger = 0;
   f250_wraw_samples_index = 0;
   f250_wraw_samples_count = 0;
   f250_wraw_samples = 0;
   f125_pulse_roc = 0;
   f125_pulse_slot = 0;
   f125_pulse_channel = 0;
   f125_pulse_npk = 0;
   f125_pulse_le_time = 0;
   f125_pulse_time_quality_bit = 0;
   f125_pulse_overflow_count = 0;
   f125_pulse_pedestal = 0;
   f125_pulse_integral = 0;
   f125_pulse_peak_amp = 0;
   f125_pulse_peak_time = 0;
   f125_pulse_word1 = 0;
   f125_pulse_word2 = 0;
   f125_pulse_nsamples_pedestal = 0;
   f125_pulse_nsamples_integral = 0;
   f125_pulse_emulated = 0;
   f125_pulse_le_time_emulated = 0;
   f125_pulse_time_quality_bit_emulated = 0;
   f125_pulse_overflow_count_emulated = 0;
   f125_pulse_pedestal_emulated = 0;
   f125_pulse_integral_emulated = 0;
   f125_pulse_peak_amp_emulated = 0;
   f125_pulse_peak_time_emulated = 0;
   f250_pulse_event_within_block = 0;
   f250_pulse_qf_pedestal = 0;
   f250_pulse_pedestal = 0;
   f250_pulse_integral = 0;
   f250_pulse_qf_nsa_beyond_ptw = 0;
   f250_pulse_qf_overflow = 0;
   f250_pulse_qf_underflow = 0;
   f250_pulse_nsamples_over_threshold = 0;
   f250_pulse_course_time = 0;
   f250_pulse_fine_time = 0;
   f250_pulse_pulse_peak = 0;
   f250_pulse_qf_vpeak_beyond_nsa = 0;
   f250_pulse_qf_vpeak_not_found = 0;
   f250_pulse_qf_bad_pedestal = 0;
   f250_pulse_pulse_number = 0;
   f250_pulse_nsamples_integral = 0;
   f250_pulse_nsamples_pedestal = 0;
   f250_pulse_emulated = 0;
   f250_pulse_integral_emulated = 0;
   f250_pulse_pedestal_emulated = 0;
   f250_pulse_time_emulated = 0;
   f250_pulse_course_time_emulated = 0;
   f250_pulse_fine_time_emulated = 0;
   f250_pulse_pulse_peak_emulated = 0;
   f250_pulse_qf_emulated = 0;
   gem_scluster_x = 0;
   gem_scluster_y = 0;
   gem_scluster_energy = 0;
   gem_scluster_adc = 0;
   srs_prerecon_y = 0;
   srs_prerecon_x = 0;

   ch.SetBranchAddress("srs_raw_count", &srs_raw_count);
   ch.SetBranchAddress("srs_raw_roc", &srs_raw_roc);
   ch.SetBranchAddress("srs_raw_slot", &srs_raw_slot);
   ch.SetBranchAddress("srs_raw_channel", &srs_raw_channel);
   ch.SetBranchAddress("srs_raw_apv_id", &srs_raw_apv_id);
   ch.SetBranchAddress("srs_raw_channel_apv", &srs_raw_channel_apv);
   ch.SetBranchAddress("srs_raw_best_sample", &srs_raw_best_sample);
   ch.SetBranchAddress("srs_raw_samples_index", &srs_raw_samples_index);
   ch.SetBranchAddress("srs_raw_samples_count", &srs_raw_samples_count);
   ch.SetBranchAddress("srs_raw_samples", &srs_raw_samples);
   ch.SetBranchAddress("f125_wraw_count", &f125_wraw_count);
   ch.SetBranchAddress("f125_wraw_roc", &f125_wraw_roc);
   ch.SetBranchAddress("f125_wraw_slot", &f125_wraw_slot);
   ch.SetBranchAddress("f125_wraw_channel", &f125_wraw_channel);
   ch.SetBranchAddress("f125_wraw_invalid_samples", &f125_wraw_invalid_samples);
   ch.SetBranchAddress("f125_wraw_overflow", &f125_wraw_overflow);
   ch.SetBranchAddress("f125_wraw_itrigger", &f125_wraw_itrigger);
   ch.SetBranchAddress("f125_wraw_samples_index", &f125_wraw_samples_index);
   ch.SetBranchAddress("f125_wraw_samples_count", &f125_wraw_samples_count);
   ch.SetBranchAddress("f125_wraw_samples", &f125_wraw_samples);
   ch.SetBranchAddress("f250_wraw_count", &f250_wraw_count);
   //ch.SetBranchAddress("f250_pulse_roc", &f250_pulse_roc);
   //ch.SetBranchAddress("f250_pulse_slot", &f250_pulse_slot);
   //ch.SetBranchAddress("f250_pulse_channel", &f250_pulse_channel);
   ch.SetBranchAddress("f250_wraw_roc", &f250_wraw_roc);
   ch.SetBranchAddress("f250_wraw_slot", &f250_wraw_slot);
   ch.SetBranchAddress("f250_wraw_channel", &f250_wraw_channel);
   ch.SetBranchAddress("f250_wraw_invalid_samples", &f250_wraw_invalid_samples);
   ch.SetBranchAddress("f250_wraw_overflow", &f250_wraw_overflow);
   ch.SetBranchAddress("f250_wraw_itrigger", &f250_wraw_itrigger);
   ch.SetBranchAddress("f250_wraw_samples_index", &f250_wraw_samples_index);
   ch.SetBranchAddress("f250_wraw_samples_count", &f250_wraw_samples_count);
   ch.SetBranchAddress("f250_wraw_samples", &f250_wraw_samples);
   ch.SetBranchAddress("f125_pulse_count", &f125_pulse_count);
   ch.SetBranchAddress("f125_pulse_roc", &f125_pulse_roc);
   ch.SetBranchAddress("f125_pulse_slot", &f125_pulse_slot);
   ch.SetBranchAddress("f125_pulse_channel", &f125_pulse_channel);
   ch.SetBranchAddress("f125_pulse_npk", &f125_pulse_npk);
   ch.SetBranchAddress("f125_pulse_le_time", &f125_pulse_le_time);
   ch.SetBranchAddress("f125_pulse_time_quality_bit", &f125_pulse_time_quality_bit);
   ch.SetBranchAddress("f125_pulse_overflow_count", &f125_pulse_overflow_count);
   ch.SetBranchAddress("f125_pulse_pedestal", &f125_pulse_pedestal);
   ch.SetBranchAddress("f125_pulse_integral", &f125_pulse_integral);
   ch.SetBranchAddress("f125_pulse_peak_amp", &f125_pulse_peak_amp);
   ch.SetBranchAddress("f125_pulse_peak_time", &f125_pulse_peak_time);
   ch.SetBranchAddress("f125_pulse_word1", &f125_pulse_word1);
   ch.SetBranchAddress("f125_pulse_word2", &f125_pulse_word2);
   ch.SetBranchAddress("f125_pulse_nsamples_pedestal", &f125_pulse_nsamples_pedestal);
   ch.SetBranchAddress("f125_pulse_nsamples_integral", &f125_pulse_nsamples_integral);
   ch.SetBranchAddress("f125_pulse_emulated", &f125_pulse_emulated);
   ch.SetBranchAddress("f125_pulse_le_time_emulated", &f125_pulse_le_time_emulated);
   ch.SetBranchAddress("f125_pulse_time_quality_bit_emulated", &f125_pulse_time_quality_bit_emulated);
   ch.SetBranchAddress("f125_pulse_overflow_count_emulated", &f125_pulse_overflow_count_emulated);
   ch.SetBranchAddress("f125_pulse_pedestal_emulated", &f125_pulse_pedestal_emulated);
   ch.SetBranchAddress("f125_pulse_integral_emulated", &f125_pulse_integral_emulated);
   ch.SetBranchAddress("f125_pulse_peak_amp_emulated", &f125_pulse_peak_amp_emulated);
   ch.SetBranchAddress("f125_pulse_peak_time_emulated", &f125_pulse_peak_time_emulated);
   ch.SetBranchAddress("f250_pulse_count", &f250_pulse_count);
   ch.SetBranchAddress("f250_pulse_event_within_block", &f250_pulse_event_within_block);
   ch.SetBranchAddress("f250_pulse_qf_pedestal", &f250_pulse_qf_pedestal);
   ch.SetBranchAddress("f250_pulse_pedestal", &f250_pulse_pedestal);
   ch.SetBranchAddress("f250_pulse_integral", &f250_pulse_integral);
   ch.SetBranchAddress("f250_pulse_qf_nsa_beyond_ptw", &f250_pulse_qf_nsa_beyond_ptw);
   ch.SetBranchAddress("f250_pulse_qf_overflow", &f250_pulse_qf_overflow);
   ch.SetBranchAddress("f250_pulse_qf_underflow", &f250_pulse_qf_underflow);
   ch.SetBranchAddress("f250_pulse_nsamples_over_threshold", &f250_pulse_nsamples_over_threshold);
   ch.SetBranchAddress("f250_pulse_course_time", &f250_pulse_course_time);
   ch.SetBranchAddress("f250_pulse_fine_time", &f250_pulse_fine_time);
   ch.SetBranchAddress("f250_pulse_pulse_peak", &f250_pulse_pulse_peak);
   ch.SetBranchAddress("f250_pulse_qf_vpeak_beyond_nsa", &f250_pulse_qf_vpeak_beyond_nsa);
   ch.SetBranchAddress("f250_pulse_qf_vpeak_not_found", &f250_pulse_qf_vpeak_not_found);
   ch.SetBranchAddress("f250_pulse_qf_bad_pedestal", &f250_pulse_qf_bad_pedestal);
   ch.SetBranchAddress("f250_pulse_pulse_number", &f250_pulse_pulse_number);
   ch.SetBranchAddress("f250_pulse_nsamples_integral", &f250_pulse_nsamples_integral);
   ch.SetBranchAddress("f250_pulse_nsamples_pedestal", &f250_pulse_nsamples_pedestal);
   ch.SetBranchAddress("f250_pulse_emulated", &f250_pulse_emulated);
   ch.SetBranchAddress("f250_pulse_integral_emulated", &f250_pulse_integral_emulated);
   ch.SetBranchAddress("f250_pulse_pedestal_emulated", &f250_pulse_pedestal_emulated);
   ch.SetBranchAddress("f250_pulse_time_emulated", &f250_pulse_time_emulated);
   ch.SetBranchAddress("f250_pulse_course_time_emulated", &f250_pulse_course_time_emulated);
   ch.SetBranchAddress("f250_pulse_fine_time_emulated", &f250_pulse_fine_time_emulated);
   ch.SetBranchAddress("f250_pulse_pulse_peak_emulated", &f250_pulse_pulse_peak_emulated);
   ch.SetBranchAddress("f250_pulse_qf_emulated", &f250_pulse_qf_emulated);
   ch.SetBranchAddress("gem_scluster_count", &gem_scluster_count);
   ch.SetBranchAddress("gem_scluster_x", &gem_scluster_x);
   ch.SetBranchAddress("gem_scluster_y", &gem_scluster_y);
   ch.SetBranchAddress("gem_scluster_energy", &gem_scluster_energy);
   ch.SetBranchAddress("gem_scluster_adc", &gem_scluster_adc);
   ch.SetBranchAddress("srs_prerecon_count", &srs_prerecon_count);
   ch.SetBranchAddress("srs_prerecon_y", &srs_prerecon_y);
   ch.SetBranchAddress("srs_prerecon_x", &srs_prerecon_x);
   
   TFile* outputFile = TFile::Open("eventsTree_3287_3288.root","RECREATE");
   //outputFile->mkdir("~/TRDPrototype/")->cd();
   ch.Merge(outputFile, 0); //Merge all entries in the chain to a new tree in this new file
   //ch.MakeClass("treeAnalyze");
   ch.ls();
   
   timer.Stop();
   timer.Print();
   
}

