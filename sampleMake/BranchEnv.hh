// Files 
TFile *newf;
TTree *newtr;

std::ofstream fout;

// Variables
Float_t wMjj;
Float_t wMJ;
Float_t wMlljj;
Float_t wMllJ;

Float_t wTheta1;
Float_t wTheta2;
Float_t wThetaStar;
Float_t wPhi;
Float_t wPhi1;

Float_t wTheta1_boosted;
Float_t wThetaStar_boosted;
Float_t wPhi1_boosted;

Float_t wdR_vbfjet1_Zll;
Float_t wdR_vbfjet2_Zll;
Float_t wdR_vbfjet1_Vqq;
Float_t wdR_vbfjet2_Vqq;
Float_t wdR_vbfjets;

Float_t wdR_vbfjet1_Zll_boosted;
Float_t wdR_vbfjet2_Zll_boosted;
Float_t wdR_vbfjet1_Vqq_boosted;
Float_t wdR_vbfjet2_Vqq_boosted;
Float_t wdR_vbfjets_boosted;

Float_t wMVBFjj;
Float_t wDeltaEtaVBFjj;

Int_t wbtagCategory;

Float_t wMvbfjj;
Float_t wPtvbfjj;
Float_t wdEtavbfjj;
Float_t wPtBalance;
Float_t wPtBalance_num;
Float_t wPtBalance_num_vbf;
Float_t wPtBalance_num_vv;
Float_t wPtBalance_den;
Float_t wPtBalance_den_vbf;
Float_t wPtBalance_den_vv;
Float_t wPtBalance_boosted;
Float_t wMaxEta;
Float_t wEtaStar;
Float_t wEtaStar_boosted;
Float_t wdEta_vbfjet1_Zll;
Float_t wdEta_vbfjet2_Zll;
Float_t wdEta_vbfjet1_Vqq;
Float_t wdEta_vbfjet2_Vqq;
Float_t wdEta_vbfjet1_Vqq_boosted;
Float_t wdEta_vbfjet2_Vqq_boosted;

Int_t wisVBFTruthJ1;
Int_t wisVBFTruthJ2;
Float_t wNumTrkPt500PVJ1;
Float_t wNumTrkPt500PVJ2;
Float_t wNumTrkPt1000PVJ1;
Float_t wNumTrkPt1000PVJ2;
Float_t wTrackWidthPt500PVJ1;
Float_t wTrackWidthPt500PVJ2;
Float_t wTrackWidthPt1000PVJ1;
Float_t wTrackWidthPt1000PVJ2;
Float_t wWidthJ1;
Float_t wWidthJ2;
Float_t wFJvtJ1;
Float_t wFJvtJ2;

void BranchEnv(TTree *tr){

	tr->Branch("Mjj", &wMjj);
	tr->Branch("MJ", &wMJ);
	tr->Branch("Mlljj", &wMlljj);
	tr->Branch("MllJ", &wMllJ);

	tr->Branch("Theta1", &wTheta1);
	tr->Branch("Theta2", &wTheta2);
	tr->Branch("ThetaStar", &wThetaStar);
	tr->Branch("Phi", &wPhi);
	tr->Branch("Phi1", &wPhi1);
	
	tr->Branch("Theta1_boosted", &wTheta1_boosted);
	tr->Branch("ThetaStar_boosted", &wThetaStar_boosted);
	tr->Branch("Phi1_boosted", &wPhi1_boosted);

	tr->Branch("dR_vbfjet1_Zll", &wdR_vbfjet1_Zll);
	tr->Branch("dR_vbfjet2_Zll", &wdR_vbfjet2_Zll);
	tr->Branch("dR_vbfjet1_Vqq", &wdR_vbfjet1_Vqq);
	tr->Branch("dR_vbfjet2_Vqq", &wdR_vbfjet2_Vqq);
	tr->Branch("dR_vbfjets", &wdR_vbfjets);

	tr->Branch("dR_vbfjet1_Zll_boosted", &wdR_vbfjet1_Zll_boosted);
	tr->Branch("dR_vbfjet2_Zll_boosted", &wdR_vbfjet2_Zll_boosted);
	tr->Branch("dR_vbfjet1_Vqq_boosted", &wdR_vbfjet1_Vqq_boosted);
	tr->Branch("dR_vbfjet2_Vqq_boosted", &wdR_vbfjet2_Vqq_boosted);
	tr->Branch("dR_vbfjets_boosted", &wdR_vbfjets_boosted);

	tr->Branch("MVBFjj", &wMVBFjj);
	tr->Branch("DeltaEtaVBFjj", &wDeltaEtaVBFjj);

	tr->Branch("btagCategory", &wbtagCategory);

	tr->Branch("Mvbfjj", &wMvbfjj);
	tr->Branch("Ptvbfjj", &wPtvbfjj);
	tr->Branch("dEtavbfjj", &wdEtavbfjj);
	tr->Branch("PtBalance", &wPtBalance);
	tr->Branch("PtBalance_num", &wPtBalance_num);
	tr->Branch("PtBalance_num_vbf", &wPtBalance_num_vbf);
	tr->Branch("PtBalance_num_vv", &wPtBalance_num_vv);
	tr->Branch("PtBalance_den", &wPtBalance_den);
	tr->Branch("PtBalance_den_vbf", &wPtBalance_den_vbf);
	tr->Branch("PtBalance_den_vv", &wPtBalance_den_vv);
	tr->Branch("PtBalance_boosted", &wPtBalance_boosted);
	tr->Branch("MaxEta", &wMaxEta);
	tr->Branch("EtaStar", &wEtaStar);
	tr->Branch("EtaStar_boosted", &wEtaStar_boosted);
	tr->Branch("dEta_vbfjet1_Zll", &wdEta_vbfjet1_Zll);
	tr->Branch("dEta_vbfjet2_Zll", &wdEta_vbfjet2_Zll);
	tr->Branch("dEta_vbfjet1_Vqq", &wdEta_vbfjet1_Vqq);
	tr->Branch("dEta_vbfjet2_Vqq", &wdEta_vbfjet2_Vqq);
	tr->Branch("dEta_vbfjet1_Vqq_boosted", &wdEta_vbfjet1_Vqq_boosted);
	tr->Branch("dEta_vbfjet2_Vqq_boosted", &wdEta_vbfjet2_Vqq_boosted);

	tr->Branch("isVBFTruthJ1", &wisVBFTruthJ1);
	tr->Branch("isVBFTruthJ2", &wisVBFTruthJ2);
	tr->Branch("NumTrkPt500PVJ1", &wNumTrkPt500PVJ1);
	tr->Branch("NumTrkPt500PVJ2", &wNumTrkPt500PVJ2);
	tr->Branch("NumTrkPt1000PVJ1", &wNumTrkPt1000PVJ1);
	tr->Branch("NumTrkPt1000PVJ2", &wNumTrkPt1000PVJ2);
	tr->Branch("TrackWidthPt500PVJ1", &wTrackWidthPt500PVJ1);
	tr->Branch("TrackWidthPt500PVJ2", &wTrackWidthPt500PVJ2);
	tr->Branch("TrackWidthPt1000PVJ1", &wTrackWidthPt1000PVJ1);
	tr->Branch("TrackWidthPt1000PVJ2", &wTrackWidthPt1000PVJ2);
	tr->Branch("WidthJ1", &wWidthJ1);
	tr->Branch("WidthJ2", &wWidthJ2);
	tr->Branch("FJvtJ1", &wFJvtJ1);
	tr->Branch("FJvtJ2", &wFJvtJ2);

}

