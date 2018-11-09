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


std::vector<ReconstructedParticle*> ToolSet::CRC::Get_POParticleType_Abs(std::vector<ReconstructedParticle*> POs,int PDG) {
	int num = POs.size();
	std::vector<ReconstructedParticle*> output;
	for( int i = 0; i < num; i++ ){
		if(std::abs(POs[i]->getType())==PDG){
			output.push_back(POs[i]);
		}
	}
	return(output);
}

std::vector<ReconstructedParticle*> ToolSet::CRC::Get_POParticleType(std::vector<ReconstructedParticle*> POs,std::string PDG) {
	int num = POs.size();
	std::vector<ReconstructedParticle*> output;
	for( int i = 0; i < num; i++ ){
		int pdg = POs[i]->getType();
		if(PDG=="quark"){
			if(CFlavor::Status_Is_Quark(pdg)){
				output.push_back(POs[i]);
			}
		}
		else if(PDG=="light_quark"){
			if(CFlavor::Status_Is_LightQuark(pdg)){
				output.push_back(POs[i]);
			}
		}
		else if(PDG=="heavy_quark"){
			if(CFlavor::Status_Is_HeavyQuark(pdg)){
				output.push_back(POs[i]);
			}
		}
		else if(PDG=="lepton"){
			if(CFlavor::Status_Is_Lepton(pdg)){
				output.push_back(POs[i]);
			}
		}
		else if(PDG=="neutrino"){
			if(CFlavor::Status_Is_Neutrino(pdg)){
				output.push_back(POs[i]);
			}
		}
	}
	return(output);
}

std::vector<MCParticle*>  ToolSet::CRC::Get_MC_From_PFO(ReconstructedParticle* &source, LCRelationNavigator* &relation)
{
	std::vector<MCParticle*>  to; 
	LCObjectVec frompars = relation->getRelatedToObjects(source);

	for( unsigned int j = 0; j < frompars.size(); j++ ){
		MCParticle* recpfo = dynamic_cast< MCParticle* >( frompars[j] );
		to.push_back(recpfo);
	}

	return(to);
}

std::vector<std::vector<MCParticle*> > ToolSet::CRC::Get_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation)
{
	std::vector<std::vector<MCParticle*> > to;
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

	return(to);
}

std::vector<MCParticle*> ToolSet::CRC::Get_A_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation){
	std::vector<std::vector<MCParticle*> > mc_tmp;
	std::vector<MCParticle*>  mc_vec;
	std::vector<std::vector<float> > weight;

	mc_tmp=Get_MC_From_PFO_Vec(source, relation);
	weight= Get_MC_Weight_From_PFO_Vec(source, relation);

	for(unsigned int i=0; i<mc_vec.size(); i++){
		int pos= Data_Type::Get_Pos(weight[i], "max");
		mc_vec.push_back(mc_tmp[i][pos]);
	}
	return(mc_vec);

}

std::vector<float> ToolSet::CRC::Get_MC_Weight_From_PFO(ReconstructedParticle* &source, LCRelationNavigator* &relation){
	std::vector<float> weight = relation->getRelatedToWeights(source);

	return(weight);
}

std::vector<std::vector<float> > ToolSet::CRC::Get_MC_Weight_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation){
	std::vector<std::vector<float> > weight; 
	for( unsigned int i = 0; i < source.size(); i++ ){
		std::vector<float> weight_tmp = relation->getRelatedToWeights(source[i]);
		weight.push_back(weight_tmp);
	}

	return(weight);
}




std::vector<ReconstructedParticle*> ToolSet::CRC::Get_PFO_From_MC(MCParticle* &source, LCRelationNavigator* &relation)
{
	std::vector<ReconstructedParticle*> to;
	LCObjectVec frompars = relation->getRelatedToObjects(source);

	for( unsigned int j = 0; j < frompars.size(); j++ ){
		ReconstructedParticle* recpfo = dynamic_cast< ReconstructedParticle* >( frompars[j] );
		to.push_back(recpfo);
	}
	return(to);
}




std::vector<std::vector<ReconstructedParticle*> > ToolSet::CRC::Get_PFO_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation)
{
	std::vector<std::vector<ReconstructedParticle*> >  to;
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

	return(to);
}

std::vector<ReconstructedParticle*> ToolSet::CRC::Get_A_PFO_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation){
	std::vector<std::vector<ReconstructedParticle*> > mc_tmp;
	std::vector<ReconstructedParticle*>  mc_vec;
	std::vector<std::vector<float> > weight;

	mc_tmp= Get_PFO_From_MC_Vec(source, relation);
	weight= Get_PFO_Weight_From_MC_Vec(source, relation);

	for(unsigned int i=0; i<mc_tmp.size(); i++){
		int pos= Data_Type::Get_Pos(weight[i], "max");
		if(pos>=0){
			mc_vec.push_back(mc_tmp[i][pos]);
		}
	}
	return(mc_vec);

}

std::vector<float> ToolSet::CRC::Get_PFO_Weight_From_MC(MCParticle* &source, LCRelationNavigator* &relation)
{
	std::vector<float> weight = relation->getRelatedToWeights(source);

	return(weight);
}




std::vector<std::vector<float> >ToolSet::CRC::Get_PFO_Weight_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation)
{
	std::vector<std::vector<float> > weight; 
	for( unsigned int i = 0; i < source.size(); i++ ){
		std::vector<float> weight_tmp = relation->getRelatedToWeights(source[i]);

		weight.push_back(weight_tmp);
	}
	return(weight);
}

ReconstructedParticle* ToolSet::CRC::Get_Visible(std::vector<ReconstructedParticle*> in){

	int num=in.size();

	ReconstructedParticle* visible;
	if(num<=0){
		visible=NewParticle(0,0,0,0,visible);
		return(visible);
	}

	TLorentzVector tmp1(in[0]->getMomentum(),in[0]->getEnergy());
	for(int i=1;i<num;i++){
		TLorentzVector tmp2(in[i]->getMomentum(),in[i]->getEnergy());
		tmp1     += tmp2; 
	}

	visible = NewParticle(tmp1,visible);
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


std::vector<ReconstructedParticle*> ToolSet::CRC::Get_PO_Overlay(std::vector<ReconstructedParticle*> input, LCRelationNavigator* &nav){
	std::vector<ReconstructedParticle*> out_pfo;
	int n = input.size();
	for( int i = 0; i < n; i++ ){
		if(Judge_Is_FromOverlay(input[i],nav)){
			out_pfo.push_back(input[i]);
		}
	}
	return(out_pfo);

}
