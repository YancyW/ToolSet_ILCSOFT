#include "CMC.h"
bool ToolSet::CMC::Judge_Beam_Energy(MCParticle* input){
	if(Data_Type::Equal_Float(input->getEnergy(),125.003063)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Has_Parent(MCParticle* input){
	if(Get_Parents_Number(input)==0){
		return(false);
	}
	return(true);
}

bool ToolSet::CMC::Judge_Has_GrandParent(MCParticle* input){
	if(Judge_Has_Parent(input)){
		if(Judge_Has_Parent(input->getParents()[0])){
			return(true);
		}
	}
	return(false);
}

bool ToolSet::CMC::Judge_Has_Daughter(MCParticle* input){
	if(Get_Daughters_Number(input)==0){
		return(false);
	}
	return(true);
}

bool ToolSet::CMC::Judge_Has_GrandDaughter(MCParticle* input){
	if(Judge_Has_Daughter(input)){
		if(Judge_Has_Daughter(input->getDaughters()[0])){
			return(true);
		}
	}
	return(false);
}

//MS -- mediator particle
bool ToolSet::CMC::Judge_Is_MS(MCParticle* input){
	if(input->getGeneratorStatus()==2){
		return(true);
	}
	return(false);
}

//TFS -- temporary final particle (some particle may decay in the detector)
bool ToolSet::CMC::Judge_Is_TFS(MCParticle* input){
	if(input->getGeneratorStatus()==0){
		return(true);
	}
	else if(input->getGeneratorStatus()==1){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Pythia_TFS(MCParticle* input){
	if(Judge_Is_Overlay(input)){
		return(false);
	}
	if(input->getGeneratorStatus()==1){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Judge_Is_Detector_TFS(MCParticle* input){
	if(Judge_Is_Overlay(input)){
		return(false);
	}
	if(input->getGeneratorStatus()==0){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Overlay(MCParticle* input){
	if(input->isOverlay()==1){
		return(true);
	}
	return(false);

}

bool ToolSet::CMC::Judge_Is_Overlay_TFS(MCParticle* input){
	if(!Judge_Is_Overlay(input)){
		return(false);
	}
	if(input->getGeneratorStatus()==1){
		return(true);
	}
	else if(input->getGeneratorStatus()==0){
		return(true);
	}
	return(false);
}







//particle pdg

bool ToolSet::CMC::Judge_Is_Electron(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==11){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Judge_Is_Muon(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==13){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Tau(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==13){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Lepton(MCParticle* input){
	if(Judge_Is_Electron(input)||Judge_Is_Muon(input)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Neutrino(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==12||pdg==14||pdg==16){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_HeavyBoson(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==23||pdg==24||pdg==25){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Photon(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==22){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_NeutralHadron(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	float charge=std::abs(input->getCharge());
	if(charge!=0){
		return(false);
	}

	if(CFlavor::Judge_Is_Hadron(pdg)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Judge_Is_ChargedHadron(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	float charge=std::abs(input->getCharge());
	if(charge==0){
		return(false);
	}

	if(CFlavor::Judge_Is_Hadron(pdg)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Judge_Is_Gluon(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==21){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_Quark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg>=1&&pdg<=6){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_LightQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg>=1&&pdg<=3){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_TopQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==6){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_BottomQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==5){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_CharmQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(pdg==4){
		return(true);
	}
	return(false);
}

