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
"Mvbfjj",
"Ptvbfjj",
"dEtavbfjj",
"PtBalance",
"MaxEta",
"EtaStar",
"dEta_vbfjet1_Zll",
"dEta_vbfjet2_Zll",
"dEta_vbfjet1_Vqq",
"dEta_vbfjet2_Vqq"
};

std::vector<TString> varList_merged={
"Mvbfjj",
"Ptvbfjj",
"dEtavbfjj",
"PtBalance",
"MaxEta",
"EtaStar_boosted",
"dEta_vbfjet1_Zll",
"dEta_vbfjet2_Zll",
"dEta_vbfjet1_Vqq_boosted",
"dEta_vbfjet2_Vqq_boosted"
};

//root -b -q 'plot_var.cc("ggH","Resolved","700")'

void plot_var(TString gp="VBFH", TString regime="Resolved", TString mass="300A700", TString op=""){

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


		leg = new TLegend(0.65 ,0.68 ,0.9,0.92);
       		leg->SetFillStyle(0);
	        leg->SetBorderSize(0);

		float k_ymax_sig = h[2*i]->GetBinContent( h[2*i]->GetMaximumBin() );
		float k_ymax_bkg = h[2*i+1]->GetBinContent( h[2*i+1]->GetMaximumBin() );
		if( k_ymax_sig > k_ymax_bkg ){
			h[2*i]->Draw("HIST");
			h[2*i]->GetYaxis()->SetRangeUser(0., k_ymax_sig*1.4);
			leg->AddEntry(h[2*i], "Signal","l");
			h[2*i+1]->Draw("HIST same");	
			leg->AddEntry(h[2*i+1], "Background","l");
		}else{
			h[2*i+1]->Draw("HIST");	
			h[2*i+1]->GetYaxis()->SetRangeUser(0., k_ymax_bkg*1.4);
			leg->AddEntry(h[2*i+1], "Background","l");
			h[2*i]->Draw("HIST same");
			leg->AddEntry(h[2*i], "Signal","l");
		}
		
		leg->Draw();
        	cv->Print("./plots/var/"+ varList->at(i) + ".png");

		delete leg;
		delete cv;

	}
				

}
