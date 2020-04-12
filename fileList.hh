////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//
TString type;
int spinSet;
TString categNameOption;
std::string mass0;
TString regime;
TString regions;
TString categ;
TString otherSample;
TString isBkg;
TString MVAparam="";
TString MVA="";
TString p1="";
TString p2="";
TString p3="";

// Regions
TString categoryTag = "ggF";
TString regimeTag = "Resolved";
TString signalTag = "ggH";
TString regionTag = "_SRCR_";

////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// for Initialize
TString newCategName;
TString newCategName_corr;
TString key_sp;
TString prePath = "/data/maxi136/atljphys/myamatan/CxAODReader_output/2018.02.16.boostedbtagging/";
TString prePath_2;
TString prePath_out;
TString weightName;
TString weightName_svm;
std::vector<TString> mc_submit;
std::vector<std::vector<TString> > signal_list;


// for bsub
TString abPath ="/data/data3/zp/myamatan/angularAna/ang_BDT/";

// Path adder 
std::vector<TString>  pathAdder(std::vector<TString> file, TString path){
	for(int i=0; i<file.size(); i++){
		file.at(i) = path + "submitDir_" + file.at(i) + "/data-MVATree/" + file.at(i) + ".root";
	}
	return file; 
};


// Spin set list
std::vector<std::vector<std::string> > spinlist = { // spin, hist-name, initial-of-each-hist
			{"sp0","HZZllqq","ggFVBF"},
			{"sp1","HVTWZ","inclusive"},
			{"sp2","RS_G_ZZ","inclusive"}
};

TString massName(std::vector<std::vector<std::string> > Mass){
	if( Mass.size() > 1){
		TString name = Mass.front().at(0) + "to" + Mass.back().at(0);
		return name;
	}else{
		TString name = Mass.front().at(0);
		return name;
	}
}		


// Path adder
TString pathMaker(TString prePath, TString list){
	TString path = prePath + list;
	return path;
}

// rootfile name for MC
std::vector<TString> mcList = {
					"ZeeB_v221",
					"ZeeC_v221",
					"ZeeL_v221",
					"ZeeHPT_v221",
					"ZmumuB_v221",
					"ZmumuC_v221",
					"ZmumuL_v221",
					"ZmumuHPT_v221",
					"ZtautauB_v221",
					"ZtautauC_v221",
					"ZtautauL_v221",
					"ZtautauHPT_v221",
					"ZnunuB_v221",
					"ZnunuC_v221",
					"ZnunuL_v221",
					"ZnunuHPT_v221",
					"WW_improved",
					"WZ_improved",
					"ZZ_improved",
					"ttbar",
					"singletop_t",
					"singletop_s",
					"singletop_Wt"
};			
// for data
std::vector<TString> dataList = {
					  "data15",
					  "data16"
};
// for Signal
std::vector<TString> signalList;
std::vector<TString> signalDirList_sub;

/*

// Backgorund
std::vector<std::vector<TString> > bkg_list = { 
			{"ZeeB_v221","Z_Nominal"},
                        {"ZeeC_v221","Z_Nominal"},
                        {"ZeeL_v221","Z_Nominal"},
                        {"ZeeHPT_v221","Z_Nominal"},
                        {"ZmumuB_v221","Z_Nominal"},
                        {"ZmumuC_v221","Z_Nominal"},
                        {"ZmumuL_v221","Z_Nominal"},
                        {"ZmumuHPT_v221","Z_Nominal"},
                        {"ZtautauB_v221","Z_Nominal"},
                        {"ZtautauC_v221","Z_Nominal"},
                        {"ZtautauL_v221","Z_Nominal"},
                        {"ZtautauHPT_v221","Z_Nominal"},
                        {"WW_improved","WW_Nominal"},
                        {"WZ_improved","WZ_Nominal"},
                        {"ZZ_improved","ZZ_Nominal"},
                        {"ttbar","ttbar_Nominal"},
                        {"singletop_t","stopt_Nominal"},
                        {"singletop_s","stops_Nominal"},
                        {"singletop_Wt","stopWt_dilep_Nominal"}
 };

// Data
std::vector<std::vector<TString> > data_list = {
                        {"data15","data_Nominal"},
                        {"data16","data_Nominal"}
 };
*/

// signal
std::string initialHist(std::string type, std::string mass){
	std::string name;
        if( type == "sp0" ){
                if( mass == "1000" || mass == "2000") name = "ggH" + mass + "ZZllqq_Nominal";
                else name = "ggH" + mass + "NWZZllqq_Nominal";
                return name;
        }else if( type == "sp1" ){
                name = "HVTWZllqq" + mass + "_Nominal";
                return name;
        }else{
                if( mass.size() == 3 ) mass = "0" + mass;
                name = "GZZllqqc10m" + mass + "_Nominal";
                return name;
        }
}

std::vector<std::vector<TString> > SIGNAL_LIST(std::vector<std::vector<std::string> > Mass, int spinSet){
			int allN = Mass.size();
			std::vector<std::vector<TString> > list;
			std::vector<TString>  vec;
			std::vector<double> sampleWeight;
			double massN = Mass.size();
			for(UInt_t i=0; i<Mass.size(); i++){
				double w = stoi(Mass.at(i).at(1)) / massN;
				sampleWeight.push_back(w);
			}
			for(UInt_t i=0; i<Mass.size(); i++){
				int loop = allN * sampleWeight.at(i);
				for(int s=0; s<loop; s++){
					vec.push_back(spinlist.at(spinSet).at(1));
					vec.push_back(initialHist(spinlist.at(spinSet).at(0), Mass.at(i).at(0)));
					list.push_back(vec);
					vec.erase( vec.begin(), vec.end() );
				}
			}
			return list;
}						

TString underbar(TString str){
	if( str == "" ){
		return str;
	}else{
		str = str + "_";
		return str;
	}
}

void SetFileName(std::vector<TString> mass, TString signalTag, TString regions, TString massRange, TString regime){ 
	// Category Name 
	newCategName = abPath+ "input/"	+ signalTag + "_" + regime + regions + massRange + "/";
	newCategName_corr = abPath +  "make_correlation/output/" + underbar(MVA) + signalTag + "_" + regime + regions + massRange + MVAparam + "/";
	//////////////////////////////////////////////////////////////////////////////////


	////// pre-step for TMVA (First) ///////////////////
	key_sp = spinlist.at(0).at(0);
	//prePath = "/data/data3/zp/myamatan/angularAna/dataset/" + key_sp + "_nominal/";//CxAODv26
	//prePath = "/data/maxi136/atljphys/myamatan/CxAODReader_output/nominal/";
	
	////// TMVA (Seconde) ///////////////////////
	prePath_2 = newCategName;
	// Pre path out
	prePath_out = abPath + "output/";
	// weight name for make correlation
	weightName = signalTag + "_" + regime + regions + massRange;
	weightName_svm = signalTag + "_" + regime + regions + massRange;
	// submitDir
	mc_submit = {
                        "submitDir_"+key_sp+"_mc/data-minitree/",
                        "submitDir_"+key_sp+"_data/data-minitree/",
                        "submitDir_"+key_sp+"_signal/data-minitree/"
	};
	// Signal list
	//signal_list = SIGNAL_LIST(mass, spinSet);
};

std::vector<std::vector<std::string> > push_sigList(TString mass0, int spinSet){
	std::vector<std::vector<std::string> > mass;
	if( mass0.Contains("to") ){
		std::string first = mass0(0, mass0.Index("to"));
		std::string last = mass0(mass0.Index("to")+1, mass0.Length() );
		int fN = stoi(first)/100;
		int lN = stoi(last)/100;
		int nSig = lN-fN;
		int massStep = 0;
		std::vector<std::string> vec;
		for( int i=0; i<nSig+1; i++){
			vec.push_back(std::to_string((i+fN)*100));
			vec.push_back("1");
			mass.push_back(vec);
			vec.erase( vec.begin(), vec.end() );
			if( spinSet == 0 && std::to_string((i+fN)*100)=="1000") massStep = 1;
			if( spinSet > 0 && std::to_string((i+fN)*100)=="2000") massStep = 1;
			if( spinSet > 0 && std::to_string((i+fN)*100)=="3000") massStep = 4;
			i = i + massStep;
		}
	}else{
		mass.push_back({std::string(mass0), "1"});
	}

	return mass;

}
			

/*
std::vector<std::vector<std::string> > massList(TString mass){
	std::vector<std::vector<std::string> > vecvec;
	std::vector<std::string> vec;
	if( mass.Contains("t") ){
		TString first;
		TString last;
		if( mass(0, mass.Index("t")).Length() == 3 ){
*/			
	


/*
std::vector<std::vector<TString> > signal_list = {
                        
			{spinlist.at(spinSet).at(1),initialHist(spinlist.at(spinSet).at(0), mass)},
			{spinlist.at(spinSet).at(1),initialHist(spinlist.at(spinSet).at(0), mass)},
			{spinlist.at(spinSet).at(1),initialHist(spinlist.at(spinSet).at(0), mass)},

 };
*/

