void SetHistoStyle(TH1F *h, Color_t col){
  	h->SetStats(0);
        h->SetLineColor(col);
	h->SetFillStyle(3003);
	h->SetFillColor(col);	
        h->SetLineWidth(3);
	//h->GetXaxis()->SetRangeUser(-1.0,1.0);
	h->GetYaxis()->SetRangeUser(0, 0.05);
        //h->GetXaxis()->SetTitle("BDT Discriminant");
}

std::vector<TString> varList_resolved={
"dR_vbfjet1_Zll",
"dR_vbfjet2_Zll",
"dR_vbfjet1_Vqq",
"dR_vbfjet2_Vqq",
"dR_vbfjets"
};

std::vector<TString> varList_merged={
"cosTheta1",
"cosThetaStar",
"Phi1",
"Score"
};

//root -b -q 'plot_var.cc("ggH","Resolved","700")'

void plot_var(TString gp="VBFH", TString regime="Resolved", TString mass="700", TString op=""){

	TString fileName = gp + "_" + regime + "_SRCR_" + mass + op;

	std::vector<TString> *varList;
	if( fileName.Index("Resolved")!=-1 ) varList = &varList_resolved;
	else if(fileName.Index("Merged")!=-1) varList = &varList_merged;
	
	TCanvas* cv;
	TH1F* histo[30];
	TH1F* h[30];

	TLegend *leg;
	gStyle->SetStatFormat("6.2g");

        TFile *f = new TFile("./" +fileName+".root");
	std::cout << "fileName : " << fileName << std::endl;


	TDirectoryFile *df = (TDirectoryFile*)gDirectory->Get("test");
	//TDirectoryFile *df = (TDirectoryFile*)gDirectory->Get("weights");
	TTree *tr = (TTree*)df->Get("TrainTree");

	for(UInt_t i=0; i<varList->size(); i++){

		cv =new TCanvas();
		cv->cd();

		tr->Draw(varList->at(i),"classID==0","HIST norm");
		histo[2*i] = (TH1F*)gROOT->FindObject("htemp");
		h[2*i] = (TH1F*)histo[2*i]->Clone("sig");		
		SetHistoStyle(h[2*i], kBlue);
		
		tr->Draw(varList->at(i),"classID==1","HIST norm");
		histo[2*i+1] = (TH1F*)gROOT->FindObject("htemp");
		h[2*i+1] = (TH1F*)histo[2*i+1]->Clone("bkg");
		SetHistoStyle(h[2*i+1], kRed);

		leg = new TLegend(0.58 ,0.58 ,0.92,0.92);
       		leg->SetFillStyle(0);
	        leg->SetBorderSize(0);


		h[2*i+1]->Draw("HIST");	
		leg->AddEntry(h[2*i+1], "Background","l");
		h[2*i]->Draw("HIST same");
		leg->AddEntry(h[2*i], "Signal","l");
		
		leg->Draw();
        	cv->Print("./plots/var/"+ varList->at(i) + ".png");

		delete leg;
		delete cv;

	}
				

}
