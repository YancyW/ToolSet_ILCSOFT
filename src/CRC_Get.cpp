#include "CRC.h"

std::vector<ReconstructedParticle*> ToolSet::CRC::getPOFinalState(LCCollection* AllPOs) {
	std::vector<ReconstructedParticle*> FS;
	int npo = AllPOs->getNumberOfElements();
	for( int i = 0; i < npo; i++ ){
		ReconstructedParticle* po= dynamic_cast< ReconstructedParticle* >( AllPOs->getElementAt(i) );
		FS.push_back(po);
	}
	return(FS);
}


std::vector<ReconstructedParticle*> ToolSet::CRC::getPOParticleType(std::vector<ReconstructedParticle*> POs,int PDG) {
	int num = POs.size();
	std::vector<ReconstructedParticle*> output;
	for( int i = 0; i < num; i++ ){
		if(POs[i]->getType()==PDG){
			output.push_back(POs[i]);
		}
	}
	return(output);
}




