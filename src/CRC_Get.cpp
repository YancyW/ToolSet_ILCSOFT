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

ReconstructedParticle* ToolSet::CRC::Get_Sum(std::vector<ReconstructedParticle*> in){

	int num=in.size();

	ReconstructedParticle* visible;
	if(num<=0){
		visible=NewParticle(0,0,0,0,visible);
		_new_particles.push_back(visible);
		return(visible);
	}

	TLorentzVector VS(0,0,0,0);
	for(int i=0;i<num;i++){
		TLorentzVector Vnew(in[i]->getMomentum(),in[i]->getEnergy());
		VS+=Vnew; 
	}

	visible = NewParticle(VS, in[0]->getType(),in[0]->getCharge(),visible);
	_new_particles.push_back(visible);
	return(visible);

}


ReconstructedParticle* ToolSet::CRC::Get_InVisible(std::vector<ReconstructedParticle*> in){
	ReconstructedParticle* visible = Get_Sum(in);
	float collider_energy=CMC::Get_Collider_Energy();
	float beam_energy    =CMC::Get_Beam_Energy();
	float beam_cross_angle=CMC::Get_Beam_Cross_Angle();
	float beam_px=collider_energy*tan(beam_cross_angle);
	ReconstructedParticle* RCCollider=NewParticle(beam_px,0,0,beam_energy*2,visible);
	ReconstructedParticle* invisible= Minus(RCCollider,visible);
	delete RCCollider;
	delete visible;
	return(invisible);
}


TLorentzVector ToolSet::CRC::Get_Sum_To_Lorentz(std::vector<ReconstructedParticle*> in){

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
	float collider_energy =CMC::Get_Collider_Energy();
	float beam_energy     =CMC::Get_Beam_Energy();
	float beam_cross_angle=CMC::Get_Beam_Cross_Angle();
	float beam_px=collider_energy*tan(beam_cross_angle);
	TLorentzVector visible = Get_Sum_To_Lorentz(in);
	TLorentzVector RCCollider=TLorentzVector(beam_px,0,0,beam_energy*2);
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


std::vector<ReconstructedParticle*> ToolSet::CRC::Get_InCone(ReconstructedParticle* input,std::vector<ReconstructedParticle*> &all, float cone_size) {
	// the first output is the input
	// other outputs are the particles that in the input cone
	// all will be changed to remove the particle in the input cone
	std::vector<ReconstructedParticle*> output;
	output.push_back(input);

	for(unsigned int i=0;i<all.size();i++){
		if (Judge_IsInCone( input, all[i], cone_size)) {
			output.push_back(all[i]);
		}
	}

	all=all-output;
	return(output);
}


std::vector<ReconstructedParticle*> ToolSet::CRC::Get_Isolated(std::vector<ReconstructedParticle*> input,std::vector<ReconstructedParticle*> all, std::vector<ReconstructedParticle*> outside_cone, float cone_size) {

	std::vector<ReconstructedParticle*> output;
	int num= input.size();
	if(num<1) {
		return output;
	}
	outside_cone = all;
	for( int i = 0; i < num; i++ )
	{
		std::vector<ReconstructedParticle*> in_cone=Get_InCone(input[i],outside_cone, cone_size) ;
		ReconstructedParticle* New = Get_Sum(in_cone); 
		output.push_back(New);
	}
	return output;
}


float ToolSet::CRC::Get_IsolationAngle(ReconstructedParticle* MC, std::vector<ReconstructedParticle*> Ref, float minimal_energy_in_the_cone, float minimal_angle_from_input ){
	std::vector<std::pair<float,ReconstructedParticle*> >Ref_angle;
	for(unsigned int i=0;i<Ref.size();i++){
		if(MC==Ref[i]){continue;}
		std::pair<float,ReconstructedParticle*> pair_tmp = std::make_pair(CMC::Cal_Angle_Deg(MC,Ref[i]),Ref[i]);
		Ref_angle.push_back(pair_tmp);
	}
	std::sort(Ref_angle.begin(),Ref_angle.end(),Compare_as_Pair);

	float sum_energy=0;
	float angle=0;
	for(unsigned int i=0;i<Ref_angle.size();i++){
		sum_energy = sum_energy + Ref_angle[i].second->getEnergy();
		angle=Ref_angle[i].first;
		if(sum_energy>minimal_energy_in_the_cone){
			if(angle>minimal_angle_from_input){
				return(angle-0.01);
			}
			else{
				return(angle);
			}
		}
	}
	return(180);
}
