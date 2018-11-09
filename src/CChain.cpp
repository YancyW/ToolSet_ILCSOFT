#include "CChain.h"
#include "CMC.h"

/*****************************************************************************************
* functions for completeness 
*****************************************************************************************/

void ToolSet::CChain_Vec::Init() {
	_chain_vec.clear();
	_nav_from_rc_to_mc = NULL;
 	_nav_from_mc_to_rc = NULL;
}

void ToolSet::CChain_Vec::Print() {
	for( int i = 0; i < _chain_num; i++ ){
		_chain_vec[i].Print();
	}
}

void ToolSet::CChain_Vec::Clear() {
	for( int i = 0; i < _chain_num; i++ ){
		_chain_vec[i].Clear();
	}
	_chain_vec.clear();
}


/*****************************************************************************************
* return member value  
*****************************************************************************************/

std::vector<MCParticle*> ToolSet::CChain_Vec::Get_MCInput(){
	std::vector<MCParticle*> input;
	for(int i=0;i<_chain_num;i++){
		MCParticle* input_tmp= _chain_vec[i].Input();
		if(input_tmp!=NULL){
			input.push_back(input_tmp);
		}
	}
	return(input);
}

std::vector<ReconstructedParticle*> ToolSet::CChain_Vec::Get_RCInput(){
	std::vector<ReconstructedParticle*> input;
	for(int i=0;i<_chain_num;i++){
		ReconstructedParticle* input_tmp= _chain_vec[i].Input_RC();
		if(input_tmp!=NULL){
			input.push_back(input_tmp);
		}
	}
	return(input);
}

std::vector<std::vector<MCParticle*> >ToolSet::CChain_Vec::Get_MCHead(){
	std::vector<std::vector<MCParticle*> > head;
	for(int i=0;i<_chain_num;i++){
		head.push_back(_chain_vec[i].Head());
	}
	return(head);
}

std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_MCNextHead(){
	std::vector<std::vector<MCParticle*> >head;
	for(int i=0;i<_chain_num;i++){
		head.push_back(_chain_vec[i].Next_Head());
	}
	return(head);
}

std::vector<std::vector<MCParticle*> >ToolSet::CChain_Vec::Get_MCNextNextHead(){
	std::vector<std::vector<MCParticle*> >head;
	for(int i=0;i<_chain_num;i++){
		head.push_back(_chain_vec[i].Next_Next_Head());
	}
	return(head);
}

std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_MCEnd(){
	std::vector<std::vector<MCParticle*> > end;
	end.clear();
	for(int i=0;i<_chain_num;i++){
		end.push_back(_chain_vec[i].MCEnd());
	}
	return(end);
}


std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_Chain(){
	std::vector<std::vector<MCParticle*> > chain;
	chain.clear();

	for(int i=0;i<_chain_num;i++){
		std::vector<MCParticle*> chain_tmp=_chain_vec[i].Chain();
		chain.push_back(chain_tmp);
	}
	return(chain);
}



std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_Trim_Chain(){
	std::vector<std::vector<MCParticle*> > chain;
	for(int i=0;i<_chain_num;i++){
	   std::vector<MCParticle*> chain_tmp=_chain_vec[i].Trim_Chain();
	   chain.push_back(chain_tmp);                                                                                                                                                                                                                                           
	
	}
	return(chain);
}




std::vector<std::vector<ToolSet::Chain_End_Type > > ToolSet::CChain_Vec::Get_RC(){
	std::vector<std::vector<ToolSet::Chain_End_Type > > rc_end;
	for(int i=0;i<_chain_num;i++){
		rc_end.push_back(_chain_vec[i].RC());
	}
	return(rc_end);
}


std::vector<std::vector<std::vector<ReconstructedParticle*> > > ToolSet::CChain_Vec::Get_RC_Particle(){
	std::vector<std::vector<std::vector<ReconstructedParticle*> > > rc_end;
	for(int i=0;i<_chain_num;i++){
		rc_end.push_back(_chain_vec[i].RC_Particle());
	}
	return(rc_end);
}



std::vector<std::vector<std::vector<float> > > ToolSet::CChain_Vec::Get_RC_Weight(){
	std::vector<std::vector<std::vector<float> > > rc_end;
	for(int i=0;i<_chain_num;i++){
		rc_end.push_back(_chain_vec[i].RC_Weight());
	}
	return(rc_end);
}



std::vector<std::vector<MCParticle*> >     ToolSet::CChain_Vec::Get_Extra_MC(){
	std::vector<std::vector<MCParticle* > > mc;
	for(int i=0;i<_chain_num;i++){
		mc.push_back(_chain_vec[i].Extra_MC());
	}
	return(mc);
}


std::vector<std::vector<ReconstructedParticle*> >     ToolSet::CChain_Vec::Get_Flat_RC(){
	std::vector<std::vector<ReconstructedParticle* > > rc;
	for(int i=0;i<_chain_num;i++){
		rc.push_back(_chain_vec[i].Flat_RC());
	}
	return(rc);
}

std::vector<ReconstructedParticle*>      ToolSet::CChain_Vec::Get_Combined_RC(){
	std::vector<ReconstructedParticle* > rc;
	for(int i=0;i<_chain_num;i++){
		rc.push_back(_chain_vec[i].Combined_RC());
	}
	return(rc);
}



std::vector<std::vector<MCParticle*> >     ToolSet::CChain_Vec::Get_FromRC_MC(){
	std::vector<std::vector<MCParticle* > > mc;
	for(int i=0;i<_chain_num;i++){
		mc.push_back(_chain_vec[i].FromRC_MC());
	}
	return(mc);
}


std::vector<std::vector<ReconstructedParticle*> > ToolSet::CChain_Vec::Get_EnergeticRC(int pdg){
	std::vector<std::vector<ReconstructedParticle*> > output;
	output.clear();
	bool JRC=Get_SpecialRC(pdg,"energy", output);
	if(!JRC){
		output.clear();
	}
	return(output);
}

std::vector<std::vector<ReconstructedParticle*> > ToolSet::CChain_Vec::Get_WeightedRC(int pdg){
	std::vector<std::vector<ReconstructedParticle*> > output;
	output.clear();
	bool JRC=Get_SpecialRC(pdg,"weight", output);
	if(!JRC){
		output.clear();
	}
	return(output);
}


bool ToolSet::CChain_Vec::Get_SpecialRC(int pdg,std::string marker,std::vector<std::vector<ReconstructedParticle*> > &output){
	if(marker!="energy"&&marker!="weight"){
		return(false);
	}
	output.clear();
	for(int i=0;i<_chain_num;i++){
		std::vector<ReconstructedParticle*>  rc_end_tmp;
		for(unsigned int j=0;j<_chain_vec[i].End().size();j++){
			int large_index=-1;
			float large_energy=-1;
			for(unsigned int k=0;k<_chain_vec[i].End()[j].second.second.size();k++){
				if(_chain_vec[i].End()[j].second.second[k]->getType() != pdg){
					continue;
				}
				float chain_value=-1;
				if(marker=="energy"){
					chain_value =_chain_vec[i].End()[j].second.second[k]->getEnergy();
				}
				else if(marker=="weight"){
					chain_value =_chain_vec[i].End()[j].second.first[k];
				}
				if(chain_value>large_energy){
					large_energy = chain_value;
					large_index  = k;
				}
			}
			if(large_index!=-1){
				rc_end_tmp.push_back(_chain_vec[i].End()[j].second.second[large_index]);
			}
		}
		output.push_back(rc_end_tmp);
	}
	return(true);
}

bool ToolSet::CChain_Vec::Compare_SpecialRC(int pdg){
	for(int i=0;i<_chain_num;i++){
		ReconstructedParticle*  rc_end_tmp=NULL;
		ReconstructedParticle*  rc_end_weight_tmp=NULL;
		for(unsigned int j=0;j<_chain_vec[i].End().size();j++){
			int large_index=-1;
			float large_energy=-1;
			for(unsigned int k=0;k<_chain_vec[i].End()[j].second.second.size();k++){
				if(_chain_vec[i].End()[j].second.second[k]->getType() != pdg){
					continue;
				}
				float chain_value=-1;
				chain_value =_chain_vec[i].End()[j].second.second[k]->getEnergy();
				if(chain_value>large_energy){
					large_energy = chain_value;
					large_index  = k;
				}
			}
			if(large_index!=-1){
				rc_end_tmp=_chain_vec[i].End()[j].second.second[large_index];
			}

			int large_weight_index=-1;
			float large_weight=-1;
			for(unsigned int k=0;k<_chain_vec[i].End()[j].second.second.size();k++){
				if(_chain_vec[i].End()[j].second.second[k]->getType() != pdg){
					continue;
				}
				float chain_value=-1;
				chain_value =_chain_vec[i].End()[j].second.first[k];
				if(chain_value>large_weight){
					large_weight= chain_value;
					large_weight_index = k;
				}
			}
			if(large_weight_index!=-1){
				rc_end_weight_tmp=_chain_vec[i].End()[j].second.second[large_weight_index];
			}
			if(rc_end_tmp!=rc_end_weight_tmp){
				ShowMessage(2,"different weight and energy");
				if(rc_end_weight_tmp!=NULL){
					ShowMessage(2,"weight one",rc_end_weight_tmp);
				}
				else{
					ShowMessage(2,"weight one","NULL");
				}
				if(rc_end_tmp!=NULL){
					ShowMessage(2,"energy one",rc_end_tmp);
				}
				else{
					ShowMessage(2,"energy one","NULL");
				}
				for(unsigned int k=0;k<_chain_vec[i].End()[j].second.second.size();k++){
					ShowMessage(2,"weight"  ,_chain_vec[i].End()[j].second.first[k]);
					ShowMessage(2,"particle",_chain_vec[i].End()[j].second.second[k]);
				}
			}
		}
	}
	return(true);
}

/*****************************************************************************************
* functions for basic setting 
*****************************************************************************************/

void ToolSet::CChain_Vec::Set_Nav_From_RC_To_MC(LCRelationNavigator* input){
	_nav_from_rc_to_mc = input; 
}

void ToolSet::CChain_Vec::Set_Nav_From_MC_To_RC(LCRelationNavigator* input){
	_nav_from_mc_to_rc = input; 
}

void ToolSet::CChain_Vec::Set_Nav(LCRelationNavigator* nav_MC_To_RC, LCRelationNavigator* nav_RC_To_MC){
	Set_Nav_From_MC_To_RC(nav_MC_To_RC);
	Set_Nav_From_RC_To_MC(nav_RC_To_MC);
}






void ToolSet::CChain_Vec::Set_ChainVec(std::vector<MCParticle*> MCs) {
	_chain_num= MCs.size();
	for( int i = 0; i < _chain_num; i++ ){
		CChain_Single chain_tmp(MCs[i]);
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* from_mc_to_rc) {
	Set_Nav_From_MC_To_RC(from_mc_to_rc);
	_chain_num= MCs.size();
	for( int i = 0; i < _chain_num; i++ ){
		CChain_Single chain_tmp(MCs[i]);
		chain_tmp.Set_Nav_From_MC_To_RC(_nav_from_mc_to_rc);
		chain_tmp.Set_RC();
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* from_mc_to_rc, LCRelationNavigator* from_rc_to_mc) {
	Set_Nav(from_mc_to_rc,from_rc_to_mc);
	_chain_num= MCs.size();
	for( int i = 0; i < _chain_num; i++ ){
		CChain_Single chain_tmp(MCs[i]);
		chain_tmp.Set_Nav_From_MC_To_RC(_nav_from_mc_to_rc);
		chain_tmp.Set_Nav_From_RC_To_MC(_nav_from_rc_to_mc);
		chain_tmp.Set_RC();
		chain_tmp.Set_Flat_RC();
		chain_tmp.Set_MC_From_Flat_RC();
		chain_tmp.Set_Extra_MC();
		_chain_vec.push_back(chain_tmp);
	}
}






void ToolSet::CChain_Vec::Set_ChainVec_FromMCFS(std::vector<MCParticle*> MCs) {
	_chain_num= MCs.size();
	for( int i = 0; i < _chain_num; i++ ){
		CChain_Single chain_tmp;
		chain_tmp.Build_Chain(MCs[i]);
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs) {
	_chain_num= RCs.size();
	for( int i = 0; i < _chain_num; i++ ){
		CChain_Single chain_tmp(RCs[i]);
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs, LCRelationNavigator* input) {
	Set_Nav_From_RC_To_MC(input);
	_chain_num= RCs.size();
	for( int i = 0; i < _chain_num; i++ ){
		CChain_Single chain_tmp(RCs[i]);
		chain_tmp.Set_Nav_From_RC_To_MC(_nav_from_rc_to_mc);
		chain_tmp.Set_MC();
		_chain_vec.push_back(chain_tmp);
	}
}






void ToolSet::CChain_Vec::Set_RC() {
	if(_nav_from_mc_to_rc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Vec::Set_RC, mc_link is not set before using RC functions");
		exit(0);
	}
	for( int i = 0; i < _chain_num; i++ ){
		_chain_vec[i].Set_Nav_From_MC_To_RC(_nav_from_mc_to_rc);
		_chain_vec[i].Set_RC();
	}
}


void ToolSet::CChain_Vec::Set_MC() {
	if(_nav_from_rc_to_mc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Vec::Set_MC, rc_link is not set before using MC functions");
		exit(0);
	}
	for( int i = 0; i < _chain_num; i++ ){
		_chain_vec[i].Set_Nav_From_RC_To_MC(_nav_from_rc_to_mc);
		_chain_vec[i].Set_MC();
	}
}
