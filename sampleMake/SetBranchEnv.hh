// Loading
Float_t rMjj;
Float_t rMJ;
Float_t rMlljj;
Float_t rMllJ;

Float_t rTheta1;
Float_t rTheta2;
Float_t rThetaStar;
Float_t rPhi;
Float_t rPhi1;
Float_t rTheta1_boosted;
Float_t rThetaStar_boosted;
Float_t rPhi1_boosted;

Float_t rdR_vbfjet1_Zll;
Float_t rdR_vbfjet2_Zll;
Float_t rdR_vbfjet1_Vqq;
Float_t rdR_vbfjet2_Vqq;
Float_t rdR_vbfjets;

Float_t rdR_vbfjet1_Zll_boosted;
Float_t rdR_vbfjet2_Zll_boosted;
Float_t rdR_vbfjet1_Vqq_boosted;
Float_t rdR_vbfjet2_Vqq_boosted;
Float_t rdR_vbfjets_boosted;

Float_t rDeltaEtaVBFjj;
Float_t rMVBFjj;

Float_t rMvbfjj;
Float_t rPtvbfjj;
Float_t rdEtavbfjj;
Float_t rPtBalance;
Float_t rPtBalance_num;
Float_t rPtBalance_num_vbf;
Float_t rPtBalance_num_vv;
Float_t rPtBalance_den;
Float_t rPtBalance_den_vbf;
Float_t rPtBalance_den_vv;
Float_t rPtBalance_boosted;
Float_t rMaxEta;
Float_t rEtaStar;
Float_t rEtaStar_boosted;
Float_t rdEta_vbfjet1_Zll;
Float_t rdEta_vbfjet2_Zll;
Float_t rdEta_vbfjet1_Vqq;
Float_t rdEta_vbfjet2_Vqq;
Float_t rdEta_vbfjet1_Vqq_boosted;
Float_t rdEta_vbfjet2_Vqq_boosted;

Int_t risVBFTruthJ1;
Int_t risVBFTruthJ2;
Float_t rNumTrkPt500PVJ1;
Float_t rNumTrkPt500PVJ2;
Float_t rNumTrkPt1000PVJ1;
Float_t rNumTrkPt1000PVJ2;
Float_t rTrackWidthPt500PVJ1;
Float_t rTrackWidthPt500PVJ2;
Float_t rTrackWidthPt1000PVJ1;
Float_t rTrackWidthPt1000PVJ2;
Float_t rWidthJ1;
Float_t rWidthJ2;
Float_t rFJvtJ1;
Float_t rFJvtJ2;

Int_t rj1_isBTagged;
Int_t rj2_isBTagged;

Float_t weight;

std::string *rRegion;

void SetBranchEnv(TTree *tr, TString signalTag){

	//// Branch Status Set
	// turn off all variables at beginning
	tr->SetBranchStatus("*",0);
	
	// turn on specific variables
	tr->SetBranchStatus("Theta1_"+signalTag, 1);
	tr->SetBranchStatus("Theta2_"+signalTag, 1);
	tr->SetBranchStatus("ThetaStar_"+signalTag, 1);
	tr->SetBranchStatus("Phi_"+signalTag, 1);
	tr->SetBranchStatus("Phi1_"+signalTag, 1);

	tr->SetBranchStatus("Theta1_boosted_"+signalTag, 1);
	tr->SetBranchStatus("ThetaStar_boosted_"+signalTag, 1);
	tr->SetBranchStatus("Phi1_boosted_"+signalTag, 1);

	tr->SetBranchStatus("jj_m_"+signalTag, 1);
	tr->SetBranchStatus("fatJet_m_"+signalTag, 1);
	tr->SetBranchStatus("lljj_m_"+signalTag, 1);
	tr->SetBranchStatus("llJ_m_"+signalTag, 1);

	tr->SetBranchStatus("dR_vbfjet1_Zll_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjet2_Zll_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjet1_Vqq_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjet2_Vqq_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjets_"+signalTag, 1);

	tr->SetBranchStatus("dR_vbfjet1_Zll_boosted_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjet2_Zll_boosted_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjet1_Vqq_boosted_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjet2_Vqq_boosted_"+signalTag, 1);
	tr->SetBranchStatus("dR_vbfjets_boosted_"+signalTag, 1);

	tr->SetBranchStatus("MVBFjj_"+signalTag, 1);
	tr->SetBranchStatus("DeltaEtaVBFjj_"+signalTag, 1);

	tr->SetBranchStatus("j1_isBTagged_"+signalTag, 1);
	tr->SetBranchStatus("j2_isBTagged_"+signalTag, 1);

	tr->SetBranchStatus("Region_"+signalTag, 1);

	tr->SetBranchStatus("Mvbfjj_"+signalTag, 1);
	tr->SetBranchStatus("Ptvbfjj_"+signalTag, 1);
	tr->SetBranchStatus("dEtavbfjj_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_num_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_num_vbf_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_num_vv_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_den_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_den_vbf_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_den_vv_"+signalTag, 1);
	tr->SetBranchStatus("PtBalance_boosted_"+signalTag, 1);
	tr->SetBranchStatus("MaxEta_"+signalTag, 1);
	tr->SetBranchStatus("EtaStar_"+signalTag, 1);
	tr->SetBranchStatus("EtaStar_boosted_"+signalTag, 1);
	tr->SetBranchStatus("dEta_vbfjet1_Zll_"+signalTag, 1);
	tr->SetBranchStatus("dEta_vbfjet2_Zll_"+signalTag, 1);
	tr->SetBranchStatus("dEta_vbfjet1_Vqq_"+signalTag, 1);
	tr->SetBranchStatus("dEta_vbfjet2_Vqq_"+signalTag, 1);
	tr->SetBranchStatus("dEta_vbfjet1_Vqq_boosted_"+signalTag, 1);
	tr->SetBranchStatus("dEta_vbfjet2_Vqq_boosted_"+signalTag, 1);

	tr->SetBranchStatus("isVBFTruthJ1_"+signalTag, 1);
	tr->SetBranchStatus("isVBFTruthJ2_"+signalTag, 1);
	tr->SetBranchStatus("NumTrkPt500PVJ1_"+signalTag, 1);
	tr->SetBranchStatus("NumTrkPt500PVJ2_"+signalTag, 1);
	tr->SetBranchStatus("NumTrkPt1000PVJ1_"+signalTag, 1);
	tr->SetBranchStatus("NumTrkPt1000PVJ2_"+signalTag, 1);
	tr->SetBranchStatus("TrackWidthPt500PVJ1_"+signalTag, 1);
	tr->SetBranchStatus("TrackWidthPt500PVJ2_"+signalTag, 1);
	tr->SetBranchStatus("TrackWidthPt1000PVJ1_"+signalTag, 1);
	tr->SetBranchStatus("TrackWidthPt1000PVJ2_"+signalTag, 1);
	tr->SetBranchStatus("WidthJ1_"+signalTag, 1);
	tr->SetBranchStatus("WidthJ2_"+signalTag, 1);
	tr->SetBranchStatus("FJvtJ1_"+signalTag, 1);
	tr->SetBranchStatus("FJvtJ2_"+signalTag, 1);

	// SetBranchAddress 
        tr->SetBranchAddress("Theta1_"+signalTag, &rTheta1);
        tr->SetBranchAddress("Theta2_"+signalTag, &rTheta2);
        tr->SetBranchAddress("ThetaStar_"+signalTag, &rThetaStar);
        tr->SetBranchAddress("Phi_"+signalTag, &rPhi);
        tr->SetBranchAddress("Phi1_"+signalTag, &rPhi1);

        tr->SetBranchAddress("Theta1_boosted_"+signalTag, &rTheta1_boosted);
        tr->SetBranchAddress("ThetaStar_boosted_"+signalTag, &rThetaStar_boosted);
        tr->SetBranchAddress("Phi1_boosted_"+signalTag, &rPhi1_boosted);

        tr->SetBranchAddress("jj_m_"+signalTag, &rMjj);
        tr->SetBranchAddress("fatJet_m_"+signalTag, &rMJ);
	tr->SetBranchAddress("lljj_m_"+signalTag, &rMlljj);
	tr->SetBranchAddress("llJ_m_"+signalTag, &rMllJ);

	tr->SetBranchAddress("dR_vbfjet1_Zll_"+signalTag, &rdR_vbfjet1_Zll);
	tr->SetBranchAddress("dR_vbfjet2_Zll_"+signalTag, &rdR_vbfjet2_Zll);
	tr->SetBranchAddress("dR_vbfjet1_Vqq_"+signalTag, &rdR_vbfjet1_Vqq);
	tr->SetBranchAddress("dR_vbfjet2_Vqq_"+signalTag, &rdR_vbfjet2_Vqq);
	tr->SetBranchAddress("dR_vbfjets_"+signalTag, &rdR_vbfjets);

	tr->SetBranchAddress("dR_vbfjet1_Zll_boosted_"+signalTag, &rdR_vbfjet1_Zll_boosted);
	tr->SetBranchAddress("dR_vbfjet2_Zll_boosted_"+signalTag, &rdR_vbfjet2_Zll_boosted);
	tr->SetBranchAddress("dR_vbfjet1_Vqq_boosted_"+signalTag, &rdR_vbfjet1_Vqq_boosted);
	tr->SetBranchAddress("dR_vbfjet2_Vqq_boosted_"+signalTag, &rdR_vbfjet2_Vqq_boosted);
	tr->SetBranchAddress("dR_vbfjets_boosted_"+signalTag, &rdR_vbfjets_boosted);

	tr->SetBranchAddress("MVBFjj_"+signalTag, &rMVBFjj);
	tr->SetBranchAddress("DeltaEtaVBFjj_"+signalTag, &rDeltaEtaVBFjj);

	tr->SetBranchAddress("j1_isBTagged_"+signalTag, &rj1_isBTagged);
	tr->SetBranchAddress("j2_isBTagged_"+signalTag, &rj2_isBTagged);

	tr->SetBranchAddress("Region_"+signalTag, &rRegion);

	tr->SetBranchAddress("Mvbfjj_"+signalTag, &rMvbfjj);
	tr->SetBranchAddress("Ptvbfjj_"+signalTag, &rPtvbfjj);
	tr->SetBranchAddress("dEtavbfjj_"+signalTag, &rdEtavbfjj);
	tr->SetBranchAddress("PtBalance_"+signalTag, &rPtBalance);
	tr->SetBranchAddress("PtBalance_num_"+signalTag, &rPtBalance_num);
	tr->SetBranchAddress("PtBalance_num_vbf_"+signalTag, &rPtBalance_num_vbf);
	tr->SetBranchAddress("PtBalance_num_vv_"+signalTag, &rPtBalance_num_vv);
	tr->SetBranchAddress("PtBalance_den_"+signalTag, &rPtBalance_den);
	tr->SetBranchAddress("PtBalance_den_vbf_"+signalTag, &rPtBalance_den_vbf);
	tr->SetBranchAddress("PtBalance_den_vv_"+signalTag, &rPtBalance_den_vv);
	tr->SetBranchAddress("PtBalance_boosted_"+signalTag, &rPtBalance_boosted);
	tr->SetBranchAddress("MaxEta_"+signalTag, &rMaxEta);
	tr->SetBranchAddress("EtaStar_"+signalTag, &rEtaStar);
	tr->SetBranchAddress("EtaStar_boosted_"+signalTag, &rEtaStar_boosted);
	tr->SetBranchAddress("dEta_vbfjet1_Zll_"+signalTag, &rdEta_vbfjet1_Zll);
	tr->SetBranchAddress("dEta_vbfjet2_Zll_"+signalTag, &rdEta_vbfjet2_Zll);
	tr->SetBranchAddress("dEta_vbfjet1_Vqq_"+signalTag, &rdEta_vbfjet1_Vqq);
	tr->SetBranchAddress("dEta_vbfjet2_Vqq_"+signalTag, &rdEta_vbfjet2_Vqq);
	tr->SetBranchAddress("dEta_vbfjet1_Vqq_boosted_"+signalTag, &rdEta_vbfjet1_Vqq_boosted);
	tr->SetBranchAddress("dEta_vbfjet2_Vqq_boosted_"+signalTag, &rdEta_vbfjet2_Vqq_boosted);

	tr->SetBranchAddress("isVBFTruthJ1_"+signalTag, &risVBFTruthJ1);
	tr->SetBranchAddress("isVBFTruthJ2_"+signalTag, &risVBFTruthJ2);
	tr->SetBranchAddress("NumTrkPt500PVJ1_"+signalTag, &rNumTrkPt500PVJ1);
	tr->SetBranchAddress("NumTrkPt500PVJ2_"+signalTag, &rNumTrkPt500PVJ2);
	tr->SetBranchAddress("NumTrkPt1000PVJ1_"+signalTag, &rNumTrkPt1000PVJ1);
	tr->SetBranchAddress("NumTrkPt1000PVJ2_"+signalTag, &rNumTrkPt1000PVJ2);
	tr->SetBranchAddress("TrackWidthPt500PVJ1_"+signalTag, &rTrackWidthPt500PVJ1);
	tr->SetBranchAddress("TrackWidthPt500PVJ2_"+signalTag, &rTrackWidthPt500PVJ2);
	tr->SetBranchAddress("TrackWidthPt1000PVJ1_"+signalTag, &rTrackWidthPt1000PVJ1);
	tr->SetBranchAddress("TrackWidthPt1000PVJ2_"+signalTag, &rTrackWidthPt1000PVJ2);
	tr->SetBranchAddress("WidthJ1_"+signalTag, &rWidthJ1);
	tr->SetBranchAddress("WidthJ2_"+signalTag, &rWidthJ2);
	tr->SetBranchAddress("FJvtJ1_"+signalTag, &rFJvtJ1);
	tr->SetBranchAddress("FJvtJ2_"+signalTag, &rFJvtJ2);

}

