#include "CMC.h"

bool ToolSet::CMC::Judge_Is_Beam(MCParticle* input){
	if((Status_Is_MS(input))&&(Status_Is_Electron(input))&&(!Status_Has_Parent(input))&&(Status_Beam_Energy(input))){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Parents_Are_Beam(MCParticle* input){
	bool no_par = false;
	if(!Status_Has_Parent(input)){
		return(false);
	}
	for(int i=0;i<Get_Parents_Number(input);i++){
		MCParticle* par=input->getParents()[i];
		if(Judge_Is_Beam(par)){
			no_par = true;
			break;
		}
	}
	if(no_par){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_GrandParents_Are_Beam(MCParticle* input){
	bool no_par = false;
	if(!Status_Has_Parent(input)){
		return(false);
	}
	for(int i=0;i<Get_Parents_Number(input);i++){
		MCParticle* par=input->getParents()[i];
		if(Judge_Parents_Are_Beam(par)){
			no_par = true;
			break;
		}
	}
	if(no_par){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_Is_IS_Electron(MCParticle* input){
	if(!Status_Is_MS(input)||!Status_Is_Electron(input)){
		return(false);
	}

	if(Judge_Parents_Are_Beam(input)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Judge_Is_IS_Photon(MCParticle* input){
	if(!Status_Is_MS(input)||!Status_Is_Photon(input)){
		return(false);
	}

	if(Judge_Parents_Are_Beam(input)){
		return(true);
	}
	else if(!Status_Has_Parent(input)){
		return(true);
	}

	return(false);
}



/*****************************************************************************************
 * @Name: Judge_HardScattering_FS
 *
 * @Param: input
 *
 * @Returns: particles in parton level
 *****************************************************************************************/
bool ToolSet::CMC::Judge_HardScattering_FS(MCParticle* input){
	if(Status_Is_Overlay(input)){
		return(false);
	}

	if(!Status_Is_MS(input)){
		return(false);
	}

	if(Judge_Is_Beam(input)){
		//beam is electron/positron
		return(false);
	}		

	if(Status_Has_Parent(input)){
		if(Judge_Parents_Are_Beam(input)&&Status_Is_Photon(input)){
			//beacause ISR photon only can be get before hard-scattering, so its decay chain is one level smaller than others
			return(true);
		}
		if(Judge_GrandParents_Are_Beam(input)&&!Status_Is_NeutralHadron(input)&&!Status_Is_ChargedHadron(input)){
			return(true);
		}
	}
	else{
		// finding overlay hard-scattering part
		// ??? need further discussing
//      if(Status_Is_Photon(input)){
//      	if(!Status_Beam_Energy(input)){
//      		return(true);
//      	}
//      	else{
//      		return(false);
//      	}
//      }
//      if(Status_Is_NeutralHadron(input)||Status_Is_ChargedHadron(input)){
//      	return(false);
//      }
//      else if(Status_Is_Gluon(input)){
//      	return(false);
//      }
//      else{
//      	return(true);
//      }
	}
	return(false);

}

bool ToolSet::CMC::Judge_HardScattering_Next_FS(MCParticle* input){
	if(Status_Is_Overlay(input)){
		return(false);
	}

	if(!Status_Has_Parent(input)){return(false);}
	if((Judge_HardScattering_FS(input->getParents()[0]))){
		return(true);
	}		

	return(false);

}

bool ToolSet::CMC::Judge_HardScattering_Next_Next_FS(MCParticle* input){
	if(Status_Is_Overlay(input)){
		return(false);
	}

	if(!Status_Has_Parent(input)){return(false);}
	if((Judge_HardScattering_Next_FS(input->getParents()[0]))){
		return(true);
	}		

	return(false);

}
/*****************************************************************************************
 * @Name: Judge_PythiaShowering_FS
 *
 * @Param: input
 *
 * @Returns: all final states in MCTruth
 *****************************************************************************************/
bool ToolSet::CMC::Judge_OnlyPythiaShowering_FS(MCParticle* input, LCRelationNavigator* &relation){
	if(!Status_Is_Pythia_TFS(input)){
		return(false);
	}

	LCObjectVec frompars = relation->getRelatedToObjects(input);
	if(frompars.size()!=0){
		// have a link to ReconstructedParticle
		return(true);
	}
	return(false);
}


bool ToolSet::CMC::Judge_PythiaShowering_FS(MCParticle* input){
	if(Status_Is_Pythia_TFS(input)){
		return(true);
	}

	return(false);

}

bool ToolSet::CMC::Judge_PythiaShowering_All(MCParticle* input){
	if(Status_Is_Pythia(input)){
		return(true);
	}

	return(false);

}

bool ToolSet::CMC::Judge_OnlyDetectorSimulating_FS(MCParticle* input, LCRelationNavigator* &relation){
	if(!Status_Is_Detector_TFS(input)){
		return(false);
	}

	LCObjectVec frompars = relation->getRelatedToObjects(input);
	if(frompars.size()!=0){
		// have a link to ReconstructedParticle
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Judge_DetectorSimulating_FS(MCParticle* input, LCRelationNavigator* &relation){
	if(Judge_OnlyDetectorSimulating_FS(input, relation)||Judge_OnlyPythiaShowering_FS(input, relation)){
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Judge_Overlay_FS(MCParticle* input, LCRelationNavigator* &relation){
	if(Status_Is_Overlay_DFS(input)){
		return(true);
	}

	LCObjectVec frompars = relation->getRelatedToObjects(input);
	if(frompars.size()!=0){
		// have a link to ReconstructedParticle
		return(true);
	}

	return(false);
}

bool ToolSet::CMC::Judge_Has_Overlay(std::vector<MCParticle*> input){
	for(unsigned int i=0;i<input.size();i++){
		if(Status_Is_Overlay_DFS(input[i])){
			return(true);
		}
	}
	return(false);
}

bool ToolSet::CMC::Judge_All_FS(MCParticle* input, LCRelationNavigator* &relation){
	if(Judge_DetectorSimulating_FS(input, relation)){
		return(true);
	}
	if(Judge_Overlay_FS(input, relation)){
		return(true);
	}
	return(false);
}

bool ToolSet::CMC::Judge_IsInCone( MCParticle* input1, MCParticle* input2, float angle_cut) {
	TVector3 P_1( input1->getMomentum() );

	TVector3 P_2( input2->getMomentum() );

	float cosTheta = P_1.Dot( P_2)/(P_1.Mag()*P_2.Mag());
	if ( cosTheta >= angle_cut)
	{
		return true;
	}
	return false;
}
