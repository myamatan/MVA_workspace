////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//
TString categNameOption;
TString regime;
TString regions;
TString categ;

// Regions
TString type = "sig";
TString categoryTag = "ggF";
TString regimeTag = "Resolved";
TString signalTag = "ggH";
TString regionTag = "_SRCR_";
std::string mass0 = "700";
TString mc16 = "a";
TString MVAtype = "angle";

// Lists
std::vector<TString> signalList;
std::vector<TString> signalDirList_sub;

// File path
TString prePath = "/data/maxi136/atljphys/myamatan/CxAODReader_output/2018.08.01.2Lep.vbfVarLooseSp01"; // prePath + "_a/" 
TString abPath = "/home/myamatan/data3/angularAna/MVA_workspace/sampleMake/";
TString newCategName;

TString newRootfileName;
TString newTxtfileName;
////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

// for Initialize
TString key_sp;
TString prePath_out;
std::vector<TString> mc_submit;
std::vector<std::vector<TString> > signal_list;

std::vector<TString> mcList;
std::vector<TString> dataList;

// MC list a
std::vector<TString> mcList_a = {
"ZeeB_Sh221",
"ZeeC_Sh221",
"ZeeL_Sh221",
"Zee_Sh221",
"ZmumuB_Sh221",
"ZmumuC_Sh221",
"ZmumuL_Sh221",
"Zmumu_Sh221",
"ZnunuB_Sh221",
"ZnunuC_Sh221",
"ZnunuL_Sh221",
"Znunu_Sh221",
"ZtautauB_Sh221",
"ZtautauC_Sh221",
"ZtautauL_Sh221",
"Ztautau_Sh221",
"WW_Sh221",
"WZ_Sh221",
"ZZ_Sh221",
"stopWt_PwPy",
"stops_PwPy",
"stopt_PwPy",
"ttbar_nonallhad_PwPy8"
};			
// MC list d
std::vector<TString> mcList_d = {
"ZeeB_Sh221",
"ZeeC_Sh221",
"ZeeL_Sh221",
"Zee_Sh221",
"ZmumuB_Sh221",
"ZmumuC_Sh221",
"ZmumuL_Sh221",
"Zmumu_Sh221",
"ZnunuB_Sh221",
"ZnunuC_Sh221",
"ZnunuL_Sh221",
"Znunu_Sh221",
"WW_Sh221",
"WZ_Sh221",
"ZZ_Sh221",
"ZtautauB_Sh221",
"ZtautauC_Sh221",
"ZtautauL_Sh221",
"Ztautau_Sh221",
"stopWt_PwPy",
"stops_PwPy",
"ttbar_nonallhad_PwPy8"
};			
// MC list a+d
std::vector<TString> mcList_ad = {
"ZeeB_Sh221",
"ZeeC_Sh221",
"ZeeL_Sh221",
"Zee_Sh221",
"ZmumuB_Sh221",
"ZmumuC_Sh221",
"ZmumuL_Sh221",
"Zmumu_Sh221",
"ZnunuB_Sh221",
"ZnunuC_Sh221",
"ZnunuL_Sh221",
"Znunu_Sh221",
"ZtautauB_Sh221",
"ZtautauC_Sh221",
"ZtautauL_Sh221",
"Ztautau_Sh221",
"WW_Sh221",
"WZ_Sh221",
"ZZ_Sh221",
"stopWt_PwPy",
"stops_PwPy",
"stopt_PwPy",
"ttbar_nonallhad_PwPy8"
};			

// Data list a
std::vector<TString> dataList_a = {
					  "data15",
					  "data16"
};
// Data list d
std::vector<TString> dataList_d = {
					  "data17"
};
// Data list a+d
std::vector<TString> dataList_ad = {
					  "data15",
					  "data16",
					  "data17"
};
