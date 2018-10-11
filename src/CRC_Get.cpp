#include "CRC.h"

std::vector<ReconstructedParticle*> ToolSet::CRC::Get_POParticle(LCCollection* AllPOs) {
	std::vector<ReconstructedParticle*> FS;
	int npo = AllPOs->getNumberOfElements();
	for( int i = 0; i < npo; i++ ){
		ReconstructedParticle* po= dynamic_cast< ReconstructedParticle* >( AllPOs->getElementAt(i) );
		FS.push_back(po);
	}
	return(FS);
}


std::vector<ReconstructedParticle*> ToolSet::CRC::Get_POParticleType(std::vector<ReconstructedParticle*> POs,int PDG) {
	int num = POs.size();
	std::vector<ReconstructedParticle*> output;
	for( int i = 0; i < num; i++ ){
		if(POs[i]->getType()==PDG){
			output.push_back(POs[i]);
		}
	}
	return(output);
}


void ToolSet::CRC::Get_MC_From_PFO(ReconstructedParticle* &source, std::vector<MCParticle*>  &to, LCRelationNavigator* &relation)
{
	LCObjectVec frompars = relation->getRelatedToObjects(source);

	for( unsigned int j = 0; j < frompars.size(); j++ ){
		MCParticle* recpfo = dynamic_cast< MCParticle* >( frompars[j] );
		to.push_back(recpfo);
	}

	return;
}

void ToolSet::CRC::Get_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, std::vector<std::vector<MCParticle*> >  &to, LCRelationNavigator* &relation)
{
	for( unsigned int i = 0; i < source.size(); i++ ){
		std::vector<MCParticle*> to_tmp;

		LCObjectVec frompars = relation->getRelatedToObjects(source[i]);

		for( unsigned int j = 0; j < frompars.size(); j++ ){
			MCParticle* recpfo = dynamic_cast< MCParticle* >( frompars[j] );
			to_tmp.push_back(recpfo);
		}
		to.push_back(to_tmp);
		to_tmp.clear();
	}

	return;
}

void ToolSet::CRC::Get_PFO_From_MC(MCParticle* &source, std::vector<ReconstructedParticle*> &to, LCRelationNavigator* &relation)
{
	LCObjectVec frompars = relation->getRelatedToObjects(source);

	for( unsigned int j = 0; j < frompars.size(); j++ ){
		ReconstructedParticle* recpfo = dynamic_cast< ReconstructedParticle* >( frompars[j] );
		to.push_back(recpfo);
	}
	return;
}




void ToolSet::CRC::Get_PFO_From_MC_Vec(std::vector<MCParticle*> &source, std::vector<std::vector<ReconstructedParticle*> >  &to, LCRelationNavigator* &relation)
{
	for( unsigned int i = 0; i < source.size(); i++ ){
		std::vector<ReconstructedParticle*> to_tmp;

		LCObjectVec frompars = relation->getRelatedToObjects(source[i]);

		for( unsigned int j = 0; j < frompars.size(); j++ ){
			ReconstructedParticle* recpfo = dynamic_cast< ReconstructedParticle* >( frompars[j] );
			to_tmp.push_back(recpfo);
		}
		to.push_back(to_tmp);
		to_tmp.clear();
	}

	return;
}


ReconstructedParticle* ToolSet::CRC::Get_Visible(std::vector<ReconstructedParticle*> in){

	int num=in.size();

	ReconstructedParticle* visible;
	ReconstructedParticle* tmp;
	ReconstructedParticle* tmp1;
	if(num<=0){
		visible=NewParticle(0,0,0,0,visible);
		return(visible);
	}

	tmp1=Equal(in[0]);
	for(int i=1;i<num;i++){
		tmp     = Add(tmp1,in[i]); 
		delete tmp1;
		tmp1    = tmp;
	}

	visible = tmp1;
	return(visible);

}



ReconstructedParticle* ToolSet::CRC::Get_InVisible(std::vector<ReconstructedParticle*> in){
	ReconstructedParticle* visible = Get_Visible(in);
	ReconstructedParticle* RCCollider=NewParticle(BEAM_ENERGY*sin(BEAM_ANGLE),0,0,BEAM_ENERGY,in[0]);
	ReconstructedParticle* invisible= Minus(RCCollider,visible);
	delete RCCollider;
	delete visible;
	return(invisible);
}


TLorentzVector ToolSet::CRC::Get_Visible_To_Lorentz(std::vector<ReconstructedParticle*> in){

	int num=in.size();

	TLorentzVector visible;
	visible=TLorentzVector(0,0,0,0);
	if(num<=0){
		return(visible);
	}

	for(int i=0;i<num;i++){
		TLorentzVector Vnew(in[i]->getMomentum(),in[i]->getEnergy());
		visible+=Vnew;
	}

	return(visible);

}

TLorentzVector ToolSet::CRC::Get_InVisible_To_Lorentz(std::vector<ReconstructedParticle*> in){
	TLorentzVector visible = Get_Visible_To_Lorentz(in);
	TLorentzVector RCCollider=TLorentzVector(BEAM_ENERGY*sin(BEAM_ANGLE),0,0,BEAM_ENERGY);
	TLorentzVector invisible= RCCollider-visible;
	return(invisible);
}

