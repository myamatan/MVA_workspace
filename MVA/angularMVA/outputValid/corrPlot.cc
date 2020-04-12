#include "/afs/cern.ch/work/m/myamatan/private/RootUtils/AtlasStyle.C"


std::vector<TString> varList_resolved={
/*
"cosTheta1",
"cosTheta2",
"cosThetaStar",
"Phi",
"Phi1",
"Score"
*/
//"dR_vbfjet1_Zll",
//"dR_vbfjet1_Vqq",
//"dR_vbfjets",
//"Mqq",
"Score",
"Mllqq"
};

std::vector<TString> varList_merged={
"cosTheta1",
"cosThetaStar",
"Phi1",
"Score"
};

//root 'corrPlot.cc("ggH_Resolved_SRCR_Zjets.ad")'
void corrPlot(TString fName="VBFH_Resolved_SRCR_700.ad"){
	
	//SetAtlasStyle();

	std::vector<TString> *varList;
	if( fName.Index("Resolved")!=-1 ) varList = &varList_resolved;
	else if(fName.Index("Merged")!=-1) varList = &varList_merged;
	
	TString fileName = fName+".root";
	TFile *f = new TFile(fileName);
	TTree *tr = (TTree*)f->Get("coll");

	TCanvas* cv =new TCanvas("a","a",900,700);
	cv->Divide( varList->size(), varList->size() );
	
	TH2F* histo;
	TH2F* h[50];

	for(UInt_t i=0; i<varList->size(); i++){
		for(UInt_t j=0; j<varList->size(); j++){
			//std::cout << varList->at(i)+"."+varList->at(j) << std::endl;;		
			cv->cd( i*varList->size()+j + 1);
			tr->Draw(varList->at(i)+":"+varList->at(j),"","colz");
			histo = (TH2F*)gROOT->FindObject("htemp");
			h[i*varList->size()+j] = (TH2F*)histo->Clone(varList->at(i)+"."+varList->at(j));		
			h[i*varList->size()+j]->Draw("colz");

			if( i!=varList->size()-1 ){
				h[i*varList->size()+j]->GetXaxis()->SetLabelSize(0);
			}
			if( j!=0 ){
				h[i*varList->size()+j]->GetYaxis()->SetLabelSize(0);
			}
			//delete histo;
		}
	}
	cv->Print("./plots/"+fileName+".png");


}
        
