
#include"CFlavor.h"
bool ToolSet::CFlavor::Status_Is_Hadron(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg>100 && pdg <600){
		return(true);
	}
	if(pdg>1000 && pdg <6000){
		return(true);
	}
	//choose 1500-1600
	if((pdg%1000)>100 && (pdg%1000) <600){
		return(true);
	}
	//choose 11500-1600
	if((pdg%10000)>1000 && (pdg%10000) <6000){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Electron(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==11){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Muon(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==13){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Tau(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==15){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Lepton(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(Status_Is_Electron(pdg)||Status_Is_Muon(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Photon(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==22){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Neutrino(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==12||pdg==14||pdg==16){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_HeavyBoson(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==23||pdg==24||pdg==25){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_NeutralHadron(int signed_pdg, float charge){
	int pdg=std::abs(signed_pdg);
	if(charge!=0){
		return(false);
	}

	if(CFlavor::Status_Is_Hadron(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_ChargedHadron(int signed_pdg, float charge){
	int pdg=std::abs(signed_pdg);
	if(charge==0){
		return(false);
	}

	if(CFlavor::Status_Is_Hadron(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Quark(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg>=1&&pdg<=6){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_LightQuark(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg>=1&&pdg<=3){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_HeavyQuark(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg>=4&&pdg<=6){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_Gluon(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==21){
		return(true);
	}
	return(false);
}
bool ToolSet::CFlavor::Status_Is_TopQuark(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==6){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_BottomQuark(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==5){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Is_CharmQuark(int signed_pdg){
	int pdg=std::abs(signed_pdg);
	if(pdg==4){
		return(true);
	}
	return(false);
}


bool ToolSet::CFlavor::Status_Are_ElectronPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(signed_pdg1!=-signed_pdg2){return(false);}
	if(Status_Is_Electron(pdg1)&&Status_Is_Electron(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_MuonPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(signed_pdg1!=-signed_pdg2){return(false);}
	if(Status_Is_Muon(pdg1)&&Status_Is_Muon(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_TauPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(signed_pdg1!=-signed_pdg2){return(false);}
	if(Status_Is_Tau(pdg1)&&Status_Is_Tau(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_GluonPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(Status_Is_Gluon(pdg1)&&Status_Is_Gluon(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_PhotonPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(Status_Is_Photon(pdg1)&&Status_Is_Photon(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_BottomPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(signed_pdg1!=-signed_pdg2){return(false);}
	if(Status_Is_BottomQuark(pdg1)&&Status_Is_BottomQuark(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_CharmPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(signed_pdg1!=-signed_pdg2){return(false);}
	if(Status_Is_CharmQuark(pdg1)&&Status_Is_CharmQuark(pdg2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CFlavor::Status_Are_TopPair(int signed_pdg1, int signed_pdg2){
	int pdg1=std::abs(signed_pdg1);
	int pdg2=std::abs(signed_pdg2);
	if(signed_pdg1!=-signed_pdg2){return(false);}
	if(Status_Is_TopQuark(pdg1)&&Status_Is_TopQuark(pdg2)){
		return(true);
	}
	return(false);
}
