#include <iostream>
#include <fstream>
#include <sstream>
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include <string>

#include "fileList.hh"

#include "SetBranchEnv.hh"
#include "BranchEnv.hh"
#include "functions.hh"

#include "sample_Maker.hh"


//void run_loop(TString type, int spinSet, TString categNameOption, string mass0, TString regions){
int main(int argc, char *argv[]){


	// Argc substition
	std::cout << argv[1] << ":" << argv[2] << ":" <<
		argv[3] << ":" << argv[4] << ":" << argv[5] << ":" << argv[6] << ":" << argv[7] << ":" << argv[8]<< std::endl;

	type = TString(argv[1]);
	categoryTag = TString(argv[2]);
	regimeTag = TString(argv[3]);
	signalTag = TString(argv[4]);
	regions = TString(argv[5]);	
	mass0 = std::string(argv[6]);
	mc16 = std::string(argv[7]);
	MVAtype = std::string(argv[8]);
		
	categNameOption="";

	// Path setting
	if(mc16!="ad"){
		prePath = prePath + "_" + mc16 + "/";
	}else{
		prePath = prePath + "/";
	}

	// MC, Data, Signal List
	std::vector<TString> mcHistoList;
        std::vector<TString> dataHistoList; 
	std::vector<TString> signalHistoList;
	if( mc16=="a" ){
		std::cout << "mc16a" << std::endl; 
		mcList = mcList_a;
		dataList = dataList_a;
	}
	else if( mc16=="d" ){
		std::cout << "mc16d" << std::endl; 
		mcList = mcList_d;
		dataList = dataList_d;
	}
	else if( mc16=="ad" ){
		std::cout << "mc16ad" << std::endl; 
		mcList = mcList_ad;
		dataList = dataList_ad;
	}

	mcHistoList = pathAdder(mcList, prePath);	
        dataHistoList = pathAdder(dataList, prePath);
	signalList = makeSigList(TString(mass0), signalTag, categoryTag, "dir"); 
	signalDirList_sub = makeSigList(TString(mass0), signalTag, categoryTag, "dir"); 
	signalHistoList = pathAdder(signalDirList_sub, prePath);
	for(UInt_t i=0; i<signalList.size(); i++){
		std::cout << i << " : " << signalList.at(i) << std::endl;
	}

		
	// Output flle ......
	SetFileName(signalList, signalTag, regions, TString(mass0), regimeTag);

	TString rootName;
	TString mode;	
	if( type == "sig" ) rootName = "signal";
	else if( type == "bkg" ) rootName = "Zjets";
	else rootName = "data";
	
	TString mkfile = newCategName;
	gROOT->ProcessLine(Form( ".! mkdir %s" , mkfile.Data() ));

	if( type == "sig" ){
		newRootfileName = newCategName + "/" + rootName + "." + mc16 + ".root";
		newTxtfileName = newCategName + "/" + rootName + "." + mc16 + ".txt";
	}else{
		newRootfileName = newCategName + "/../" + signalTag + "_" + regimeTag + regions + rootName + "." + mc16 + ".root";
		newTxtfileName = newCategName + "/../" + signalTag + "_" + regimeTag + regions + rootName + "." + mc16 + ".txt";
	}

	
	newf = new TFile(newRootfileName, "recreate");
        newtr = new TTree("coll","coll");
	BranchEnv(newtr);

	fout.open(newTxtfileName.Data());

	
	if( type=="sig" ){
		// Signal
		std::cout << "Signal sample processing .." << std::endl;
		for(int i=0; i<int(signalList.size()); i++){
			std::cout << signalList.at(i) << std::endl;
       			sample_Maker( signalHistoList.at(i), type, signalTag, regions, regimeTag, MVAtype);
       		}
	}else if(type=="bkg"){
		// Bkg
		std::cout << "Background sample processing .." << std::endl;
		for(int i=0; i<int(mcList.size()); i++){
			std::cout << mcList.at(i) << std::endl;
			sample_Maker( mcHistoList.at(i), type, signalTag, regions, regimeTag, MVAtype);
		}
		
	}else{	
		// Data
		std::cout << "Real Data processing .."<< std::endl;
		for(int i=0; i<int(dataList.size()); i++){
			std::cout << dataList.at(i) << std::endl;
			sample_Maker( dataHistoList.at(i), type, signalTag, regions, regimeTag, MVAtype);
		}
	}

	newf->cd();
	newtr->Write();
	newf->Close();

	fout.close();


}
