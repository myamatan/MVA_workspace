#include "/nfs_home/home1/myamatan/RootUtils/AtlasStyle.C"


std::vector<Color_t> colList = {
	kBlack,
	//kOrange,
	kRed,
	kBlue,
	kGreen+1
/*
	kRed,
	kRed-3,
	kRed-6,
	kGreen,
	kGreen-3,
	kGreen-6,
	kBlue,
	kBlue-3,
	kBlue-6
*/
};
	


void SetHistoStyle(TH1D *h, int id){
  	h->SetStats(0);
        //h->SetMarkerColor(colList.at(id));
        //h->SetMarkerSize(0.5);
        h->SetLineColor(colList.at(id));
	//h->SetLineStyle(2);
        //h->SetLineWidth(2);
}

// ("fileName", "legendName", "Method type")
TString sig="VBFH";
TString regime="Resolved";
TString massR="300A700A1000A2000";
TString nameID="compa";
std::vector<std::vector<TString> > readList = {
	{sig+"_"+regime+"_SRCR_"+massR, "BDTG", "test", "def"},
	{sig+"_"+regime+"_SRCR_"+massR, "BDTG", "test", "Full"},
	{sig+"_"+regime+"_SRCR_"+massR, "BDTG", "test", "DetaX"},
	{sig+"_"+regime+"_SRCR_"+massR, "BDTG", "test", "allcomb"},
	//{sig+"_"+regime+"_SRCR_"+massR, "BDTG", "test", ""}
	//{sig+"_"+regime+"_SRCR_"+massR, "PyKeras", "test", ".myDNN"}
};

void plotROCcurve(){

	SetAtlasStyle();

	TH1D *h_roc[10];

        TCanvas *cv = new TCanvas();
	TLegend *leg;
	leg = new TLegend(0.18 ,0.28 ,0.78,0.5);
        leg->SetFillStyle(0);
        leg->SetBorderSize(0);
	gStyle->SetStatFormat("6.2g");
        
        cv->cd();
        //cv->SetTitle(fileName);

	nameID = "." + nameID;

	for(UInt_t s=0; s<readList.size(); s++){

        	TFile *f = new TFile(readList.at(s).at(0) + readList.at(s).at(3) + ".root");

        
		gDirectory->cd( readList.at(s).at(2) );

		if( readList.at(s).at(1).Index("SVM") != -1 ){
			gDirectory->cd("Method_SVM");
		}else if( readList.at(s).at(1).Index("BDTG") != -1 ){
			gDirectory->cd("Method_BDTG_"+readList.at(s).at(0));
		}else if( readList.at(s).at(1).Index("PyKeras") != -1 ){
			gDirectory->cd("Method_PyKeras");
		}
		gDirectory->ls();

		TString method = readList.at(s).at(1) + "_" + readList.at(s).at(0);
		if( readList.at(s).at(1)=="PyKeras" ) method = "PyKeras";

		TDirectoryFile *df = (TDirectoryFile*)gDirectory->Get(method);

        	h_roc[s] = (TH1D*)df->Get("MVA_"+method+"_rejBvsS");

		// ROC integral	
		double roc_value = h_roc[s]->Integral();
		//TString roc = Form("ROC:%f", int(roc_value*10)*1e-3);
		//gStyle->SetPaintTextFormat("3.2f");
		TString roc = Form("ROC : %0.3f", roc_value*1e-2);

		SetHistoStyle(h_roc[s], s);
		if( s==0 ) h_roc[s]->Draw("C");
		else h_roc[s]->Draw("C same"); 
		leg->AddEntry(h_roc[s], readList.at(s).at(0) + readList.at(s).at(3) + " ("+roc+")" ,"l");

	}

	cv->SetGridx();
	cv->SetGridy();
	
        leg->Draw();

        cv->Print("./plots/"+ readList.at(0).at(0) + nameID + ".ROC" + ".png");

}
