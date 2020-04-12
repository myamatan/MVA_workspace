// Split function
std::vector<std::string> split(const std::string& input, char delimiter)
{
    std::istringstream stream(input);

    std::string field;
    std::vector<std::string> result;
    while (std::getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

// Mass range
std::vector<TString> makeSigList(TString mass0="300to1400", TString signal="ggH", TString category="ggF", TString o_type="hist"){
	std::vector<TString> mass;

	if( signal == "VBFH" || signal == "VBFHVT" ) category = "VBF";
	if( mass0.Contains("to") ){
		std::string first = mass0(0, mass0.Index("to"));
                std::string last = mass0(mass0.Index("to")+2, mass0.Length() );
                int fN = stoi(first)/100;
                int lN = stoi(last)/100;
                int nSig = lN-fN;
                int massStep = 0;
		for( int i=0; i<nSig+1; i++){
			TString massName;
			TString massName2;
			std::string m = std::to_string((i+fN)*100);
			if( signal == "ggH" | signal == "VBFH" ){
				if( category == "ggF" ){
					massName = "ggH" + TString(m) + "ZZllqq";
					massName2 = "HZZllqq_ggH" + TString(m);
				}else if( category == "VBF" ){
					massName = "VBFH" + TString(m) + "ZZllqq";
					massName2 = "HZZllqq_VBFH" + TString(m);
				}
			}else if( signal == "RSG" | signal == "Kp5RSG" ){
				massName = signal + "ZZllqq" + TString(m);
				if( TString(m).Length() == 3 ) massName2 = "RS_G_ZZm0" + TString(m);
				else massName2 = "RS_G_ZZm" + TString(m);
			}else if( signal == "HVT" | signal == "VBFHVT" ){
				if( category == "ggF" ){
					massName = "HVTWZllqq" + TString(m);
					if( TString(m).Length() == 3 ){
						massName2 = "HVTm0" + TString(m);
					}else{
						 massName2 = "HVTm" + TString(m);
					}
				}else if( category == "VBF" ){
					massName = "vbfHVTWZllqq" + TString(m);
					if( TString(m).Length() == 3 ){
						massName2 = "vbfHVTm0" + TString(m);
					}else{
						massName2 = "vbfHVTm" + TString(m);
					}
				}
				
			}
                        if( o_type == "hist" ) mass.push_back(massName);
			else mass.push_back(massName2);
                        if( (signal == "ggH" || signal == "VBFH") && m=="1000") massStep = 1;
                        if( (signal == "RSG" | signal == "Kp5RSG" || signal == "HVT" | signal == "VBFHVT" ) && m=="2000") massStep = 1;
                        if( (signal == "RSG" | signal == "Kp5RSG" || signal == "HVT" | signal == "VBFHVT" ) && m=="3000") massStep = 4;
			// VBFHVT error handle
                        if( (signal == "VBFHVT" ) && m=="2000" ) massStep = 3;
                        if( (signal == "VBFHVT" ) && m=="2400" ) massStep = 1;
                        i = i + massStep;
                }
	}
	else if( mass0.Contains("A") ){
		const std::string input = mass0.Data();
		for(const std::string& m : split(input, 'A')){
			TString massName;
			TString massName2;
			if( signal == "ggH" | signal == "VBFH" ){
				if( category == "ggF" ){
					massName = "ggH" + TString(m) + "ZZllqq";
					massName2 = "HZZllqq_ggH" + TString(m);
				}else if( category == "VBF" ){
					massName = "VBFH" + TString(m) + "ZZllqq";
					massName2 = "HZZllqq_VBFH" + TString(m);
				}
			}else if( signal == "RSG" | signal == "Kp5RSG" ){
				massName = signal + "ZZllqq" + TString(m);
				if( TString(m).Length() == 3 ) massName2 = "RS_G_ZZm0" + TString(m);
				else massName2 = "RS_G_ZZm" + TString(m);
			}else if( signal == "HVT" | signal == "VBFHVT" ){
				if( category == "ggF" ){
					massName = "HVTWZllqq" + TString(m);
					if( TString(m).Length() == 3 ){
						massName2 = "HVTm0" + TString(m);
					}else{
						 massName2 = "HVTm" + TString(m);
					}
				}else if( category == "VBF" ){
					massName = "vbfHVTWZllqq" + TString(m);
					if( TString(m).Length() == 3 ){
						massName2 = "vbfHVTm0" + TString(m);
					}else{
						massName2 = "vbfHVTm" + TString(m);
					}
				}
				
			}
                        if( o_type == "hist" ) mass.push_back(massName);
			else mass.push_back(massName2);
                }
        }else{
		TString massName;
		TString massName2;
		if( signal == "ggH" | signal == "VBFH" ){
			if( category == "ggF" ){
				massName = "ggH" + mass0 + "ZZllqq";
				massName2 = "HZZllqq_" + signal + mass0;
			}else if( category == "VBF" ){
				massName = "VBFH" + mass0 + "ZZllqq";
				massName2 = "HZZllqq_" + signal + mass0;
			}
		}else if( signal == "RSG" | signal == "Kp5RSG" ){
			massName = signal + "ZZllqq" + mass0;
			if( mass0.Length() == 3 ) massName2 = "RS_G_ZZm0" + mass0;
			else massName2 = "RS_G_ZZm" + mass0;	
		}else if( signal == "HVT" | signal == "VBFHVT" ){
			if( category == "ggF" ){
				massName = "HVTWZllqq" + mass0;
				if( mass0.Length() == 3 ){
					massName2 = "HVTm0" + mass0;
				}else{
					massName2 = "HVTm" + mass0;
				}
			}else if( category == "VBF" ){
				massName = signal + "WZllqq" + mass0;
				if( mass0.Length() == 3 ){
					massName2 = "vbfHVTm0" + mass0;
				}else{
					massName2 = "vbfHVTm" + mass0;
				}
			}
		}
		if( o_type == "hist" ) mass.push_back(massName);
		else mass.push_back(massName2);
        }
        return mass;
};

// Path adder 
std::vector<TString>  pathAdder(std::vector<TString> file, TString path){
	for(int i=0; i<file.size(); i++){
		file.at(i) = path + "submitDir_" + file.at(i) + "/data-MVATree/" + file.at(i) + ".root";
	}
	return file; 
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
	newCategName = abPath+ "output/" + signalTag + "_" + regime + regions + massRange + "/";
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
			
