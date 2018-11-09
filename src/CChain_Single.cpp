#include "CChain_Single.h"

/*****************************************************************************************
* functions for completeness 
*****************************************************************************************/


void ToolSet::CChain_Single::Init(){
	_input = NULL;
	_input_rc = NULL;
	_combined_RC =NULL;
	_has_trim_chain = false;
	_has_set_rc = false;
	_nav_from_mc_to_rc = NULL;
	_nav_from_rc_to_mc = NULL;
}

void ToolSet::CChain_Single::Print(){
	ShowMessage(2,"chain size",_chain.size());
	std::vector<int> counter_branch; 
	counter_branch.push_back(0);
	int branch_num=0;
	int inter_num =10000;
	for(unsigned int i=0;i<_chain.size();i++){
		if(CMC::Judge_HardScattering_FS(_chain[i])&&(CMC::Judge_PythiaShowering_FS(_chain[i])||CMC::Judge_DetectorSimulating_FS(_chain[i]))){
			std::cout << "chain: " << std::endl;
			printf("%5i\n",_chain[i]->getPDG());
		}
		else if(CMC::Judge_HardScattering_FS(_chain[i])&& !(CMC::Judge_PythiaShowering_FS(_chain[i])||CMC::Judge_DetectorSimulating_FS(_chain[i]))){
			std::cout << "chain: " << std::endl;
			printf("%5i",_chain[i]->getPDG());
			counter_branch[branch_num]++;
		}
		else if( !CMC::Judge_HardScattering_FS(_chain[i])&& (CMC::Judge_PythiaShowering_FS(_chain[i])||CMC::Judge_DetectorSimulating_FS(_chain[i]))){
			if(inter_num==0){
				printf("%5s", "     ");
				for(int j=0;j<counter_branch[branch_num-1]-1;j++){
					printf("%9s", "--->     ");
				}
			}
			printf("%4s", "--->");
			printf("%5i\n", _chain[i]->getPDG());
			branch_num++;
			counter_branch.push_back(0);
			counter_branch[branch_num]++;
			inter_num=0 ;
		}
		else {
			if(inter_num==0){
				printf("%5s", "     ");
				for(int j=0;j<counter_branch[branch_num-1]-1;j++){
					printf("%9s", "--->     ");
				}
			}
			printf("%4s", "--->");
			printf("%5i", _chain[i]->getPDG());
			counter_branch[branch_num]++;
			inter_num++ ;
		}
	}

	std::cout << "head:[" << _head[0]->getPDG() << "]--->" << "end:[";
	for(unsigned int i=0;i<_end.size();i++){
		std::cout << _end[i].first->getPDG() ;
		for(unsigned int j=0;j<_end[i].second.first.size();j++){
			std::cout << "(" <<  _end[i].second.second[j]->getType() ;
			std::cout << "," <<  _end[i].second.first[j] << ")";
		}
		if(i!=_end.size()-1){
			std::cout<< ", ";
		}
	}
	std::cout << "]"<<std::endl;
}

void ToolSet::CChain_Single::Clear(){
	_head.clear();
	_next_head.clear(); 
	_next_next_head.clear();
	_chain.clear();
	_trim_chain.clear();
	_end.clear();
	_end_MC.clear();
	_RC.clear();
	_RC_Particle.clear();
	_RC_Weight.clear();
	_flat_RC.clear();
	_fromRC_MC.clear();
	_fromRC_Weight.clear();
	_extra_MC.clear();
	if(_combined_RC!=NULL){
		delete _combined_RC;
	}
}


/*****************************************************************************************
* functions for basic setting 
*****************************************************************************************/





void ToolSet::CChain_Single::Set_Nav_From_MC_To_RC(LCRelationNavigator* relation){
	_nav_from_mc_to_rc = relation;
}

void ToolSet::CChain_Single::Set_Nav_From_RC_To_MC(LCRelationNavigator* relation){
	_nav_from_rc_to_mc = relation;
}

void ToolSet::CChain_Single::Set_RC(){
	if(_nav_from_mc_to_rc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Single::Set_RC, mc_to_rc_link is not set before using RC functions");
		exit(0);
	}
	for(unsigned int i=0;i<_end_MC.size();i++){

		//LCObjectVec frompars = _nav_from_mc_to_rc->getRelatedFromObjects(_end_MC[i]) ;

		std::vector<ReconstructedParticle*> to_tmp=CRC::Get_PFO_From_MC       (_end_MC[i],_nav_from_mc_to_rc);
		std::vector<float>                  weight=CRC::Get_PFO_Weight_From_MC(_end_MC[i],_nav_from_mc_to_rc); 

		_RC_Particle.push_back(to_tmp);
		_RC_Weight.push_back(weight);

		_RC.push_back(std::make_pair(weight,to_tmp));

	}

	_has_set_rc = true;
	Set_End_Type();
	Set_Flat_RC();
	Set_MC_From_Flat_RC();
	Set_Extra_MC();
	Set_Combined_RC();

	return;
}


void ToolSet::CChain_Single::Set_Flat_RC(){
	std::vector<ReconstructedParticle*> flat_RC=ToolSet::Vec_Flat(_RC_Particle);
	_flat_RC=Vec_Remove_Duplicate(flat_RC);
}

void ToolSet::CChain_Single::Set_Combined_RC(){
	_combined_RC= ToolSet::CRC::Get_Visible(_flat_RC);
}


void ToolSet::CChain_Single::Set_MC_From_Flat_RC(){
	if(_nav_from_rc_to_mc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Single::Set_MC_From_Flat_RC, rc_to_mc link is not set before using Get_MC_From_PFO_Vec functions");
		exit(0);
	}
	std::vector<std::vector<MCParticle*> > _flat_MC_vec=CRC::Get_MC_From_PFO_Vec(_flat_RC, _nav_from_rc_to_mc);
	_fromRC_MC=Vec_Expand_VecVec(_flat_MC_vec);
}

void ToolSet::CChain_Single::Set_Extra_MC(){
	_extra_MC=_fromRC_MC-_end_MC;
}







void ToolSet::CChain_Single::Set_Trim_Chain(){
	//| ShowMessage(2,"Error, in CChain_Single:: _chain",_chain);
	bool has_double_par=false;
	std::vector<MCParticle*> _trim_chain_tmp;
	for(unsigned int i=0;i<_chain.size()-1;i++){
		if(CMC::Get_Parents_Number(_chain[i])==2){
			_trim_chain.assign(_chain.begin(), _chain.begin()+i+1);
			has_double_par = true;
			//| |   ShowMessage(2,"Error, in CChain_Single::in for l",i);
			for(unsigned int j=i+1;j<_chain.size();j++){
				//| |   |   |   ShowMessage(2,"Error, in CChain_Single::in for",i,j);
				if(_chain[i]->getParents()[1]->id()==_chain[j]->id()){
					_trim_chain_tmp.assign(_chain.begin()+i, _chain.begin()+j);
					//| |   |   |   |   ShowMessage(2,"Error, in CChain_Single:: _trim_chain_tmp",_trim_chain_tmp);
					bool has_proton=false;
					for(unsigned int k=0; k<_trim_chain_tmp.size(); k++){
						if(CMC::Judge_Is_Beam(_trim_chain_tmp[k])){
							has_proton = true;
							break;
						}
					}
					if(!has_proton){
						_has_trim_chain = true;
						for(unsigned int trim_index=0;trim_index<_trim_chain_tmp.size();trim_index++){
							_trim_chain.push_back(_trim_chain_tmp[trim_index]);
						}
						//| |   |   |   |   ShowMessage(2,"inside trim", _trim_chain);
						return;
					}
					else{
						_trim_chain_tmp.clear();
						_trim_chain_tmp.assign(_chain.begin()+j, _chain.end());
						_has_trim_chain = true;
						for(unsigned int trim_index=0;trim_index<_trim_chain_tmp.size();trim_index++){
							_trim_chain.push_back(_trim_chain_tmp[trim_index]);

						}
						//| |   |   |   |   ShowMessage(2,"inside trim", _trim_chain);
						return;
					}
				}
			}
		}
	}
	if(!has_double_par){
		_trim_chain.assign(_chain.begin(), _chain.end());
		_has_trim_chain = true;

	}
	//| ShowMessage(2,"Error, in CChain_Single::end ");

}


void ToolSet::CChain_Single::Minimize_Trim_Chain(){
	if(_trim_chain.size()==0){return;}
	std::vector<MCParticle*> new_vec;
	new_vec.push_back(_trim_chain.back());
	for(int i=_trim_chain.size()-2;i>0;--i){
		//not use Vec_Remove_Duplicate, because in the chain, there may be a parent goes to a new particle but actually with the same information
		if(_trim_chain[i]->getPDG()!=new_vec.back()->getPDG()){
			new_vec.push_back(_trim_chain[i]);
		}
	}
	MCParticle* last_one=_trim_chain.front();
	_trim_chain.clear();

	_trim_chain=new_vec;
	_trim_chain.push_back(last_one);
}


void ToolSet::CChain_Single::Set_MC_End(){
	_end_MC=Vec_Remove_Duplicate(_end_MC);
}

void ToolSet::CChain_Single::Set_End_Type(){
	if(!_has_set_rc){return;}
	for(unsigned int i=0;i<_end_MC.size();i++){
		std::pair<MCParticle*,Chain_End_Type >input_pair=std::make_pair(_end_MC[i],_RC[i]);
		_end.push_back(input_pair);
	}
}



void ToolSet::CChain_Single::Set_MC(){
	if(_nav_from_rc_to_mc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Single::Set_RC, rc_link is not set before using RC functions");
		exit(0);
	}

	_fromRC_MC     = CRC::Get_MC_From_PFO       (_input_rc,_nav_from_rc_to_mc);
	_fromRC_Weight = CRC::Get_MC_Weight_From_PFO(_input_rc,_nav_from_rc_to_mc);


	for(unsigned int i=0;i<_fromRC_MC.size();i++){
		Build_Chain(_fromRC_MC[i]);
	}

	_has_set_mc = true;
	return;
}
/*****************************************************************************************
* functions for building 
*****************************************************************************************/

void ToolSet::CChain_Single::Build_Chain(MCParticle* input){
	Init();
	_input = input;
	if(CMC::Judge_HardScattering_FS(input)){
		Recurse_Chain(input);
		Set_Trim_Chain();
		Minimize_Trim_Chain();
		Set_MC_End();
	}
	else if(CMC::Judge_DetectorSimulating_FS(input)){
		TraceBack_Chain(input);
		Set_Trim_Chain();
		Minimize_Trim_Chain();
		Set_MC_End();
	}
	else{
		Recurse_Chain(input);
		TraceBack_Chain(input);
		Set_Trim_Chain();
		Minimize_Trim_Chain();
		Set_MC_End();
	}
	return;
}




void ToolSet::CChain_Single::Recurse_Chain(MCParticle* input){
	Push_Back(input);
	if(CMC::Judge_DetectorSimulating_FS(input)){
		return;
	}
	for(int i=0;i<CMC::Get_Daughters_Number(input);i++){
		Recurse_Chain(input->getDaughters()[i]);
	}
}

//give a initial particle,  get where does it go to 
void ToolSet::CChain_Single::Push_Back(MCParticle* input){
	if(CMC::Judge_HardScattering_FS(input)){
		_head.push_back(input);
	}
	if(CMC::Judge_HardScattering_Next_FS(input)){
		_next_head.push_back(input);
	}
	if(CMC::Judge_HardScattering_Next_Next_FS(input)){
		_next_next_head.push_back(input);
	}
	_chain.push_back(input);
	if(CMC::Status_Is_TFS(input)){
		_end_MC.push_back(input);
	}
}


void ToolSet::CChain_Single::TraceBack_Chain(MCParticle* input){
	//	std::cout<< "in TraceBack_Chain::entering TraceBack_Chain" << std::endl;
	Push_Forward(input);
	//	std::cout<< "in TraceBack_Chain::out of Push_Forward" << std::endl;
	if(CMC::Judge_HardScattering_FS(input)){
		//		std::cout<< "in TraceBack_Chain::Is HardScattering_FS, return" << std::endl;
		return;
	}
	for(int i=0;i<CMC::Get_Parents_Number(input);i++){
		//		std::cout<< "in TraceBack_Chain::recurse into parents' TraceBack_Chain, parent" << i << std::endl;
		TraceBack_Chain(input->getParents()[i]);
		//		std::cout<< "in TraceBack_Chain::out of parents' TraceBack_Chain, parent" << i << std::endl;
	}
}

//give a final particle,  get where does it come from
void ToolSet::CChain_Single::Push_Forward(MCParticle* input){
	//	std::cout<< "in Push_Forward::entering Push_Forward" << std::endl;
	if(CMC::Judge_HardScattering_FS(input)){
		//		std::cout<< "in Push_Forward::get a head" << std::endl;
		_head.push_back(input);
	}
	if(CMC::Judge_HardScattering_Next_FS(input)){
		_next_head.push_back(input);
	}
	if(CMC::Judge_HardScattering_Next_Next_FS(input)){
		_next_next_head.push_back(input);
	}
	_chain.push_back(input);
	if(CMC::Status_Is_TFS(input)){
		//		std::cout<< "in Push_Forward::get an end" << std::endl;
		_end_MC.push_back(input);
	}
}



void ToolSet::CChain_Single::Build_Chain_FromRCFS(ReconstructedParticle* input){
	//	std::cout<< "in Get_Chain_FromMCFS:: make sure input is a FS" << std::endl;
	Init();
	_input_rc = input;
	_flat_RC.push_back(_input_rc);
	
}



