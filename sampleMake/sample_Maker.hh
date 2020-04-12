bool isGetThis(long l, TString mode, TString type){
	
	if( mode=="train" ){
		if( l%2 != 0 ){
			return true;
		}else{
			return false;
		}
	}else if( mode=="test" ){
		if( l%2 == 0 ){
			return true;
		}else{
			return false;
		}
	}
}

// Main
void sample_Maker(TString file, TString type, TString signalTag, TString regions, TString regime, TString MVA){

	//TString filepath = prePath + submitDir + file + ".root"; // CxAODv26
	TString filepath = file;

	TFile *f = new TFile(filepath);
        TTree *tr = (TTree*)f->Get( "Nominal" ); //trName

	SetBranchEnv(tr, signalTag);

	long nEvent = tr->GetEntries();
	double thres;
	if (type=="bkg") thres = 0.0; //0.94
	else if(type=="sig") thres = 0.0;
	else if(type=="data") thres = 0.0;

	double valval;
	double valval2;
	for(long l=0; l<nEvent; l++){
		tr->GetEntry(l);
		
		if( regime == "Resolved" && MVA=="angle"){

			valval = rTheta1;
			if( valval > -10 
			     && ( rRegion->find("Resolved") != std::string::npos
			          || rRegion->find("Untagged") != std::string::npos
			          || rRegion->find("Tagged") != std::string::npos 
				)
			     && ( rRegion->find("SR") != std::string::npos
			          || rRegion->find("CR") != std::string::npos 
				)
			){ 

				wTheta1 = rTheta1;
				wTheta2 = rTheta2;
				wThetaStar = rThetaStar;
				wPhi = rPhi;
				wPhi1 = rPhi1;

				wMjj = rMjj;
				wMlljj = rMlljj;

				wdR_vbfjet1_Zll = rdR_vbfjet1_Zll;
				wdR_vbfjet2_Zll = rdR_vbfjet2_Zll;
				wdR_vbfjet1_Vqq = rdR_vbfjet1_Vqq;
				wdR_vbfjet2_Vqq = rdR_vbfjet2_Vqq;
				wdR_vbfjets = rdR_vbfjets;

				wbtagCategory = 1 ? rj1_isBTagged + rj2_isBTagged == 2 : 0;

				newtr->Fill();

				fout << rTheta1 << "," << rTheta2 << "," << rThetaStar << "," << rPhi << ", " << rPhi1 << std::endl;
			}

		}else if( regime == "Merged" && MVA=="angle"){

			valval = rTheta1_boosted;
			if( valval > -10
			     && rRegion->find("Merged") != std::string::npos
			     && ( rRegion->find("SR") != std::string::npos
			          || rRegion->find("CR") != std::string::npos 
				)
			){

				wTheta1_boosted = rTheta1_boosted;
				wThetaStar_boosted = rThetaStar_boosted;
				wPhi1_boosted = rPhi1_boosted;

				wMJ = rMJ;
				wMllJ = rMllJ;

				wdR_vbfjet1_Zll_boosted = rdR_vbfjet1_Zll_boosted;
				wdR_vbfjet2_Zll_boosted = rdR_vbfjet2_Zll_boosted;
				wdR_vbfjet1_Vqq_boosted = rdR_vbfjet1_Vqq_boosted;
				wdR_vbfjet2_Vqq_boosted = rdR_vbfjet2_Vqq_boosted;
				wdR_vbfjets_boosted = rdR_vbfjets_boosted;

				newtr->Fill();

				fout << rTheta1_boosted << "," << rThetaStar_boosted << "," << rPhi1_boosted << std::endl;
			}

		}else if( regime == "Resolved" && MVA=="VBFjets"){

			valval = rMvbfjj;
			valval2 = rMlljj;
			if( valval >= 0 && valval2 >= 0
			     && ( rRegion->find("Resolved") != std::string::npos
			          || rRegion->find("Untagged") != std::string::npos
			          || rRegion->find("Tagged") != std::string::npos 
				)
			     && ( rRegion->find("SR") != std::string::npos
			          || rRegion->find("CR") != std::string::npos 
				)
			){

				wMvbfjj = rMvbfjj;
				wPtvbfjj = rPtvbfjj;
				wdEtavbfjj = rdEtavbfjj;
				wPtBalance = rPtBalance;
				wPtBalance_num = rPtBalance_num;
				wPtBalance_num_vbf = rPtBalance_num_vbf;
				wPtBalance_num_vv = rPtBalance_num_vv;
				wPtBalance_den = rPtBalance_den;
				wPtBalance_den_vbf = rPtBalance_den_vbf;
				wPtBalance_den_vv = rPtBalance_den_vv;
				wMaxEta = rMaxEta;
				wEtaStar = rEtaStar;

				wdEta_vbfjet1_Zll = rdEta_vbfjet1_Zll;
				wdEta_vbfjet2_Zll = rdEta_vbfjet2_Zll;
				wdEta_vbfjet1_Vqq = rdEta_vbfjet1_Vqq;
				wdEta_vbfjet2_Vqq = rdEta_vbfjet2_Vqq;

				wMVBFjj = rMVBFjj;
				wDeltaEtaVBFjj = rDeltaEtaVBFjj;
				wisVBFTruthJ1 = risVBFTruthJ1;
				wisVBFTruthJ2 = risVBFTruthJ2;
				wNumTrkPt500PVJ1 = rNumTrkPt500PVJ1;
				wNumTrkPt500PVJ2 = rNumTrkPt500PVJ2;
				wNumTrkPt1000PVJ1 = rNumTrkPt1000PVJ1;
				wNumTrkPt1000PVJ2 = rNumTrkPt1000PVJ2;
				wTrackWidthPt500PVJ1 = rTrackWidthPt500PVJ1;
				wTrackWidthPt500PVJ2 = rTrackWidthPt500PVJ2;
				wTrackWidthPt1000PVJ1 = rTrackWidthPt1000PVJ1;
				wTrackWidthPt1000PVJ2 = rTrackWidthPt1000PVJ2;
				wWidthJ1 = rWidthJ1;
				wWidthJ2 = rWidthJ2;
				wFJvtJ1 = rFJvtJ1;
				wFJvtJ2 = rFJvtJ2;


				wMjj = rMjj;
				wMlljj = rMlljj;

				newtr->Fill();
			}

		}else if( regime == "Merged" && MVA=="VBFjets"){

			valval = rMvbfjj;
			valval2 = rMllJ;
			if( valval >= 0 && valval2 >= 0
			     && rRegion->find("Merged") != std::string::npos
			     && ( rRegion->find("SR") != std::string::npos
			          || rRegion->find("CR") != std::string::npos 
				)
			){

				wMvbfjj = rMvbfjj;
				wPtvbfjj = rPtvbfjj;
				wdEtavbfjj = rdEtavbfjj;
				wPtBalance_boosted = rPtBalance_boosted;
				wMaxEta = rMaxEta;
				wEtaStar_boosted = rEtaStar_boosted;

				wdEta_vbfjet1_Zll = rdEta_vbfjet1_Zll;
				wdEta_vbfjet2_Zll = rdEta_vbfjet2_Zll;
				wdEta_vbfjet1_Vqq_boosted = rdEta_vbfjet1_Vqq_boosted;
				wdEta_vbfjet2_Vqq_boosted = rdEta_vbfjet2_Vqq_boosted;

				wMVBFjj = rMVBFjj;
				wDeltaEtaVBFjj = rDeltaEtaVBFjj;
				wisVBFTruthJ1 = risVBFTruthJ1;
				wisVBFTruthJ2 = risVBFTruthJ2;
				wNumTrkPt500PVJ1 = rNumTrkPt500PVJ1;
				wNumTrkPt500PVJ2 = rNumTrkPt500PVJ2;
				wNumTrkPt1000PVJ1 = rNumTrkPt1000PVJ1;
				wNumTrkPt1000PVJ2 = rNumTrkPt1000PVJ2;
				wTrackWidthPt500PVJ1 = rTrackWidthPt500PVJ1;
				wTrackWidthPt500PVJ2 = rTrackWidthPt500PVJ2;
				wTrackWidthPt1000PVJ1 = rTrackWidthPt1000PVJ1;
				wTrackWidthPt1000PVJ2 = rTrackWidthPt1000PVJ2;
				wWidthJ1 = rWidthJ1;
				wWidthJ2 = rWidthJ2;
				wFJvtJ1 = rFJvtJ1;
				wFJvtJ2 = rFJvtJ2;


				wMJ = rMJ;
				wMllJ = rMllJ;

				newtr->Fill();
			}

		}

	}// Event loop
}
		
