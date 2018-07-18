#include "CMC.h"

int ToolSet::CMC::Get_Parents_Number(MCParticle* input){
	return(input->getParents().size());
}

int ToolSet::CMC::Get_Daughters_Number(MCParticle* input){
	return(input->getDaughters().size());
}

