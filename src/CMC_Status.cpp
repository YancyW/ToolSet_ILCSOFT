#include "CMC.h"
/*****************************************************************************************
 * Readme,  the definition used in this file.
 * getGeneratorStatus = 2  ->  is generated by Pythia/whizard,  resonance
 * getGeneratorStatus = 1  ->  is generated by Pythia, final stable states.
 * getGeneratorStatus = 0  ->  is not generated by Pythia,  but created in the simulation
 *                             this always equal to "simulator status -- s (the first s)", 
 *                                 or equal to using "isCreatedInSimulation()"
 * isOverlay()             ->  is generated in the overlay
 *
 * isStopped ()            ->  the particle lost all k
 * isDecayedInTracker ()   ->  the particle decayed or interacted in a tracking region. 
 * isDecayedInCalorimeter()->  the particle decayed or interacted (non-continuous interaction, particle terminated) in non-tracking region. 
 * hasLeftDetector ()      ->  the particle left the world volume undecayed. 
 *
 *
 * other status not offen used.
 *
 * isBackscattering()      ->  the particle was created by the simulator as a result of an interaction or decay in non-tracking region, e.g. 
 *****************************************************************************************/
bool ToolSet::CMC::Status_Beam_Energy(MCParticle* input){
	//if(Data_Type::Equal_Float(input->getEnergy(),125.003063)){
	if(!(BEAM_ENERGY/2>120&&BEAM_ENERGY/2<130)&& !(BEAM_ENERGY/2>240&&BEAM_ENERGY/2<260)){
		ToolSet::ShowMessage(2,"Error: not initialize beam energy or, initialize with a wrong number, please be 250/2 or 500/2 GeV in the Toolset::CMC.h macro definition, current beam energy is", BEAM_ENERGY);
	}
	if(Data_Type::Equal_Float(input->getEnergy(),BEAM_ENERGY/2)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Has_Parent(MCParticle* input){
	if(Get_Parents_Number(input)==0){
		return(false);
	}
	return(true);
}

bool ToolSet::CMC::Status_Has_GrandParent(MCParticle* input){
	if(Status_Has_Parent(input)){
		if(Status_Has_Parent(input->getParents()[0])){
			return(true);
		}
	}
	return(false);
}

bool ToolSet::CMC::Status_Has_Daughter(MCParticle* input){
	if(Get_Daughters_Number(input)==0){
		return(false);
	}
	return(true);
}

bool ToolSet::CMC::Status_Has_GrandDaughter(MCParticle* input){
	if(Status_Has_Daughter(input)){
		if(Status_Has_Daughter(input->getDaughters()[0])){
			return(true);
		}
	}
	return(false);
}

//MS -- mediator particle
bool ToolSet::CMC::Status_Is_MS(MCParticle* input){
	if(input->getGeneratorStatus()==2){
		return(true);
	}
	return(false);
}

//TFS -- temporary final particle (some particle may decay in the detector)
bool ToolSet::CMC::Status_Is_TFS(MCParticle* input){
	if(input->getGeneratorStatus()==0){
		return(true);
	}
	else if(input->getGeneratorStatus()==1){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Pythia_TFS(MCParticle* input){
	if(Status_Is_Overlay(input)){
		return(false);
	}
	if(input->getGeneratorStatus()==1){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Status_Is_Detector_TFS(MCParticle* input){
	if(Status_Is_Overlay(input)){
		return(false);
	}
	if(input->getGeneratorStatus()==0){
		if(input->getPDG()<1000000000){
			return(true);
		}
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Pythia(MCParticle* input){
	if(Status_Is_Overlay(input)){
		return(false);
	}
	if(input->getGeneratorStatus()==2){
		return(true);
	}
	if(input->getGeneratorStatus()==1){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Overlay(MCParticle* input){
	if(input->isOverlay()==1){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Overlay_DFS(MCParticle* input){
	if(!Status_Is_Overlay(input)){
		return(false);
	}
	else if(input->getGeneratorStatus()==0||input->getGeneratorStatus()==1){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Status_Is_Stopped(MCParticle* input){
	if(input->isStopped()==1){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Status_Is_DecayInTracker(MCParticle* input){
	if(input->isDecayedInTracker()==1){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Status_Is_DecayInCalorimeter(MCParticle* input){
	if(input->isDecayedInCalorimeter()==1){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Status_Is_LeftDetector(MCParticle* input){
	if(input->hasLeftDetector()==1){
		return(true);
	}
	return(false);
}







//particle pdg

bool ToolSet::CMC::Status_Is_Electron(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Electron(pdg)){
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Status_Is_Muon(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Muon(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Tau(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Tau(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Lepton(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Lepton(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Neutrino(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Neutrino(pdg)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Status_Is_HeavyBoson(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_HeavyBoson(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Photon(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Photon(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_NeutralHadron(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	float charge=std::abs(input->getCharge());

	if(CFlavor::Status_Is_NeutralHadron(pdg,charge)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Status_Is_ChargedHadron(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	float charge=std::abs(input->getCharge());

	if(CFlavor::Status_Is_NeutralHadron(pdg,charge)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Status_Is_Gluon(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Gluon(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_Quark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_Quark(pdg)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Status_Is_LightQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_LightQuark(pdg)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Status_Is_HeavyQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_HeavyBoson(pdg)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Status_Is_TopQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_TopQuark(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_BottomQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_BottomQuark(pdg)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Status_Is_CharmQuark(MCParticle* input){
	int pdg=std::abs(input->getPDG());
	if(CFlavor::Status_Is_CharmQuark(pdg)){
		return(true);
	}
	return(false);
}

