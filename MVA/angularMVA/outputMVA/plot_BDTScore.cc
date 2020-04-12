void SetHistoStyle(TH1D *h, TString fileName, Color_t col, bool isTrain){
  	h->SetStats(0);
       	h->SetTitle(fileName);
        h->SetLineColor(col);
	if( !isTrain ){
		h->SetFillStyle(3003);
		h->SetFillColor(col);
	}	
	if( isTrain ) h->SetLineStyle(2);
        h->SetLineWidth(3);
	h->GetXaxis()->SetRangeUser(-1.0,1.0);
        h->GetXaxis()->SetTitle("BDT Discriminant");
}
	

//root -b -q 'plot_BDTScore.cc("ggH","Resolved","700")'

void plot_BDTScore(TString gp="VBFH", TString regime="Resolved", TString mass="700", TString op=".myDNN"){

	TString fileName = gp + "_" + regime + "_SRCR_" + mass + op;
	
	//TString method = "BDTG_" + fileName;
	TString method = "PyKeras";

        TFile *f = new TFile("./" +fileName+".root");
        
	std::cout << "fileName : " << fileName << std::endl;

	gDirectory->cd("test");
	//gDirectory->cd("weights");

	gDirectory->cd("Method_"+method);

	TDirectoryFile *df = (TDirectoryFile*)gDirectory->Get(method);

	TH1D *h_sig;
        TH1D *h_bkg;
	TH1D *h_Train_sig;
        TH1D *h_Train_bkg;
        TH1D *h_roc;
       	h_sig = (TH1D*)df->Get("MVA_"+method+"_S");
        h_bkg = (TH1D*)df->Get("MVA_"+method+"_B");
       	h_Train_sig = (TH1D*)df->Get("MVA_"+method+"_Train_S");
        h_Train_bkg = (TH1D*)df->Get("MVA_"+method+"_Train_B");
        h_roc = (TH1D*)df->Get("MVA_"+method+"_rejBvsS");

	// ROC integral	
	double roc_value = h_roc->Integral();
	TString roc = Form("/ROC:%0.3f", int(roc_value*10)*1e-3);
	// Significance
	double binWidth = h_sig->Integral("width")/h_sig->Integral();	
	double nsig = h_sig->Integral();
	double nbkg = h_bkg->Integral();
	double maxSig = 0.;
	for(UInt_t i=0; i<h_sig->GetNbinsX()+1; i++){
		double nsigCut = h_sig->Integral(i,h_sig->GetNbinsX()+1); 
		double nbkgCut = h_bkg->Integral(i,h_bkg->GetNbinsX()+1); 
		double sigChange = (nsigCut/sqrt(nbkgCut))/(nsig/sqrt(nbkg));
		if( sigChange > maxSig ) maxSig = sigChange;
	}
	TString sigRate = Form("/Sig:%0.3f", int(maxSig*100)*1e-2);
	

        TCanvas *cv = new TCanvas();
        cv->cd();

        cv->SetTitle(fileName);

	double sigMax = h_sig->GetMaximum();
	double bkgMax = h_bkg->GetMaximum();

	if( sigMax > bkgMax ){
		SetHistoStyle(h_sig, fileName+roc+sigRate, kBlue, false);
		h_sig->GetYaxis()->SetRangeUser(0., sigMax*1.2);
        	h_sig->Draw("HIST");
		SetHistoStyle(h_bkg, fileName+roc+sigRate, kRed, false);
        	h_bkg->Draw("HIST same");
	}else{
		SetHistoStyle(h_bkg, fileName+roc+sigRate, kRed, false);
		h_bkg->GetYaxis()->SetRangeUser(0., bkgMax*1.2);
        	h_bkg->Draw("HIST");
		SetHistoStyle(h_sig, fileName+roc+sigRate, kBlue, false);
        	h_sig->Draw("HIST same");
	}
	SetHistoStyle(h_Train_sig, fileName+roc+sigRate, kBlue, true);
        h_Train_sig->Draw("HIST same");
	SetHistoStyle(h_Train_bkg, fileName, kRed, true);
        h_Train_bkg->Draw("HIST same");

        cv->Print("./plots/"+ fileName + ".png");
}
