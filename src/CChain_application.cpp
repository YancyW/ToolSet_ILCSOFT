#include "CChain.h"
#include "CMC.h"

void ToolSet::CChain_Vec::Set_Nav_From_RC_To_MC(LCRelationNavigator* input){
	_nav_from_rc_to_mc = input; 
}

void ToolSet::CChain_Vec::Set_Nav_From_MC_To_RC(LCRelationNavigator* input){
	_nav_from_mc_to_rc = input; 
}

void ToolSet::CChain_Vec::Set_ChainVec(std::vector<MCParticle*> MCs) {
	if(_nav_from_mc_to_rc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Vec::Set_ChainVec, mc_link is not set before using RC functions");
		exit(0);
	}
	int num = MCs.size();
	for( int i = 0; i < num; i++ ){
		CChain_Single chain_tmp(MCs[i]);
		chain_tmp.Set_Nav_From_MC_To_RC(_nav_from_mc_to_rc);
		chain_tmp.Set_RC();
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* input) {
	Set_Nav_From_MC_To_RC(input);
	int num = MCs.size();
	for( int i = 0; i < num; i++ ){
		CChain_Single chain_tmp(MCs[i]);
		chain_tmp.Set_Nav_From_MC_To_RC(_nav_from_mc_to_rc);
		chain_tmp.Set_RC();
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec_FromMCFS(std::vector<MCParticle*> MCs) {
	int num = MCs.size();
	for( int i = 0; i < num; i++ ){
		CChain_Single chain_tmp;
		chain_tmp.Set_Chain_FromMCFS(MCs[i]);
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs) {
	if(_nav_from_rc_to_mc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Vec::Set_ChainVec_FromRCFS, rc_link is not set before using RC functions");
		exit(0);
	}
	int num = RCs.size();
	for( int i = 0; i < num; i++ ){
		CChain_Single chain_tmp;
		chain_tmp.Set_Nav_From_RC_To_MC(_nav_from_rc_to_mc);
		chain_tmp.Set_Chain_FromRCFS(RCs[i]);
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs, LCRelationNavigator* input) {
	Set_Nav_From_RC_To_MC(input);
	int num = RCs.size();
	for( int i = 0; i < num; i++ ){
		CChain_Single chain_tmp;
		chain_tmp.Set_Nav_From_RC_To_MC(_nav_from_rc_to_mc);
		chain_tmp.Set_Chain_FromRCFS(RCs[i]);
		_chain_vec.push_back(chain_tmp);
	}
}

void ToolSet::CChain_Vec::Print() {
	int num = _chain_vec.size();
	for( int i = 0; i < num; i++ ){
		_chain_vec[i].Print();
	}
}

std::vector<MCParticle*> ToolSet::CChain_Vec::Get_MCHead(){
	std::vector<MCParticle*> head;
	head.clear();
	for(unsigned int i=0;i<_chain_vec.size();i++){
		MCParticle* head_tmp= _chain_vec[i].Head();
		if(head_tmp!=NULL){
			head.push_back(head_tmp);
		}
	}
	return(head);
}

std::vector<MCParticle*> ToolSet::CChain_Vec::Get_MCNextHead(){
	std::vector<MCParticle*> head;
	head.clear();
	for(unsigned int i=0;i<_chain_vec.size();i++){
		MCParticle* head_tmp= _chain_vec[i].Next_Head();
		if(head_tmp!=NULL){
			head.push_back(head_tmp);
		}
	}
	return(head);
}

std::vector<MCParticle*> ToolSet::CChain_Vec::Get_MCNextNextHead(){
	std::vector<MCParticle*> head;
	head.clear();
	for(unsigned int i=0;i<_chain_vec.size();i++){
		MCParticle* head_tmp= _chain_vec[i].Next_Next_Head();
		if(head_tmp!=NULL){
			head.push_back(head_tmp);
		}
	}
	return(head);
}

std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_MCEnd(){
	std::vector<std::vector<MCParticle*> > end;
	end.clear();
	for(unsigned int i=0;i<_chain_vec.size();i++){
		std::vector<MCParticle*>  end_tmp;
		for(unsigned int j=0;j<_chain_vec[i].End().size();j++){
			MCParticle* end_tmp_i=_chain_vec[i].End()[j].first;
			if(end_tmp_i!=NULL){
				end_tmp.push_back(end_tmp_i);
			}
		}
		end.push_back(end_tmp);
	}
	return(end);
}


std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_Chain(){
	std::vector<std::vector<MCParticle*> > chain;
	chain.clear();

	for(unsigned int i=0;i<_chain_vec.size();i++){
		std::vector<MCParticle*> chain_tmp=_chain_vec[i].Chain();
		chain.push_back(chain_tmp);
	}
	return(chain);
}



std::vector<std::vector<MCParticle*> > ToolSet::CChain_Vec::Get_Trim_Chain(){
	std::vector<std::vector<MCParticle*> > chain;
	chain.clear();
	for(unsigned int i=0;i<_chain_vec.size();i++){
	   std::vector<MCParticle*> chain_tmp=_chain_vec[i].Trim_Chain();
	   chain.push_back(chain_tmp);                                                                                                                                                                                                                                           
	
	}
	return(chain);
}




std::vector<ToolSet::Chain_End_Type_Vec > ToolSet::CChain_Vec::Get_RC(){
	std::vector<std::vector<Chain_End_Type > > rc_end;
	rc_end.clear();
	for(unsigned int i=0;i<_chain_vec.size();i++){
		std::vector<Chain_End_Type > rc_end_tmp1;
		for(unsigned int j=0;j<_chain_vec[i].End().size();j++){
			rc_end_tmp1.push_back(_chain_vec[i].End()[j].second);
		}
		rc_end.push_back(rc_end_tmp1);
	}
	return(rc_end);
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
	for(unsigned int i=0;i<_chain_vec.size();i++){
		std::vector<ReconstructedParticle*>  rc_end_tmp;
		for(unsigned int j=0;j<_chain_vec[i].End().size();j++){
			int large_index=-1;
			float large_energy=-1;
			for(unsigned int k=0;k<_chain_vec[i].End()[j].second.size();k++){
				if(_chain_vec[i].End()[j].second[k].second->getType() != pdg){
					continue;
				}
				float chain_value=-1;
				if(marker=="energy"){
					chain_value =_chain_vec[i].End()[j].second[k].second->getEnergy();
				}
				else if(marker=="weight"){
					chain_value =_chain_vec[i].End()[j].second[k].first;
				}
				if(chain_value>large_energy){
					large_energy = chain_value;
					large_index  = k;
				}
			}
			if(large_index!=-1){
				rc_end_tmp.push_back(_chain_vec[i].End()[j].second[large_index].second);
			}
		}
		output.push_back(rc_end_tmp);
	}
	return(true);
}

bool ToolSet::CChain_Vec::Compare_SpecialRC(int pdg){
	for(unsigned int i=0;i<_chain_vec.size();i++){
		ReconstructedParticle*  rc_end_tmp=NULL;
		ReconstructedParticle*  rc_end_weight_tmp=NULL;
		for(unsigned int j=0;j<_chain_vec[i].End().size();j++){
			int large_index=-1;
			float large_energy=-1;
			for(unsigned int k=0;k<_chain_vec[i].End()[j].second.size();k++){
				if(_chain_vec[i].End()[j].second[k].second->getType() != pdg){
					continue;
				}
				float chain_value=-1;
				chain_value =_chain_vec[i].End()[j].second[k].second->getEnergy();
				if(chain_value>large_energy){
					large_energy = chain_value;
					large_index  = k;
				}
			}
			if(large_index!=-1){
				rc_end_tmp=_chain_vec[i].End()[j].second[large_index].second;
			}

			int large_weight_index=-1;
			float large_weight=-1;
			for(unsigned int k=0;k<_chain_vec[i].End()[j].second.size();k++){
				if(_chain_vec[i].End()[j].second[k].second->getType() != pdg){
					continue;
				}
				float chain_value=-1;
				chain_value =_chain_vec[i].End()[j].second[k].first;
				if(chain_value>large_weight){
					large_weight= chain_value;
					large_weight_index = k;
				}
			}
			if(large_weight_index!=-1){
				rc_end_weight_tmp=_chain_vec[i].End()[j].second[large_weight_index].second;
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
				for(unsigned int k=0;k<_chain_vec[i].End()[j].second.size();k++){
					ShowMessage(2,"weight"  ,_chain_vec[i].End()[j].second[k].first);
					ShowMessage(2,"particle",_chain_vec[i].End()[j].second[k].second);
				}
			}
		}
	}
	return(true);
}

void ToolSet::CChain_Vec::Init() {
	_chain_vec.clear();
	_nav_from_rc_to_mc = NULL;
 	_nav_from_mc_to_rc = NULL;
}
