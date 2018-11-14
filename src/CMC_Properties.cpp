#include "CMC.h"

int ToolSet::CMC::Get_Parents_Number(MCParticle* input){
	return(input->getParents().size());
}

int ToolSet::CMC::Get_Daughters_Number(MCParticle* input){
	return(input->getDaughters().size());
}

std::vector<int> ToolSet::CMC::Get_ParentsPID(MCParticle* MC) {
	std::vector<int> ids;

	if(Get_Parents_Number(MC)!=0){
		for(int i=0;i<Get_Parents_Number(MC);i++){
			ids.push_back(MC->getParents()[i]->getPDG());
		}
	}
	else{
		ids.push_back(-1);
		ids.push_back(-1);
	}

	// always make sure ids has at least two elements, if not use -1 to instead.
	if(ids.size()==1){
		ids.push_back(-1);
	}
	return(ids);
}

std::vector<int> ToolSet::CMC::Get_DaughtersPID(MCParticle* MC) {
	std::vector<int> ids;

	if(Get_Daughters_Number(MC)!=0){
		for(int i=0;i<Get_Daughters_Number(MC);i++){
			ids.push_back(MC->getDaughters()[i]->getPDG());
		}
	}
	else{
		ids.push_back(-1);
		ids.push_back(-1);
	}

	// always make sure ids has at least two elements, if not use -1 to instead.
	if(ids.size()==1){
		ids.push_back(-1);
	}


	return(ids);
}

