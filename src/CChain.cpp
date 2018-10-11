#include "CChain.h"



void ToolSet::CChain_Single::Init(){
	_head = NULL;
	_head_assist = NULL;
	_next_head = NULL;
	_next_next_head = NULL;
	_has_trim_chain = false;
	_has_set_rc = false;
	_nav_from_mc_to_rc = NULL;
	_nav_from_rc_to_mc = NULL;
}

void ToolSet::CChain_Single::Set_Nav_From_MC_To_RC(LCRelationNavigator* relation){
	_nav_from_mc_to_rc = relation;
}

void ToolSet::CChain_Single::Set_Nav_From_RC_To_MC(LCRelationNavigator* relation){
	_nav_from_rc_to_mc = relation;
}

void ToolSet::CChain_Single::Set_RC(){
	if(_nav_from_mc_to_rc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Single::Set_RC, rc_link is not set before using RC functions");
		exit(0);
	}
	for(unsigned int i=0;i<_end.size();i++){
		std::vector<std::pair<float, ReconstructedParticle*> > to_tmp;

		LCObjectVec frompars = _nav_from_mc_to_rc->getRelatedFromObjects(_end[i].first) ;
		std::vector<float> weight = _nav_from_mc_to_rc->getRelatedFromWeights(_end[i].first);

		for(unsigned int j=0;j<frompars.size();j++){
			ReconstructedParticle* recpfo = dynamic_cast<ReconstructedParticle*>(frompars[j]);
			to_tmp.push_back(std::make_pair(weight[j],recpfo));
		}
		_end[i].second=to_tmp;
	}
	_has_set_rc = true;
	return;
}


//give a initial particle,  get where does it go to 
void ToolSet::CChain_Single::Push_Back(MCParticle* input){
	if(CMC::Judge_HardScattering_FS(input)){
		_head = input;
	}
	if(CMC::Judge_HardScattering_Next_FS(input)){
		_next_head = input;
	}
	if(CMC::Judge_HardScattering_Next_Next_FS(input)){
		_next_next_head= input;
	}
	_chain.push_back(input);
	if(CMC::Judge_PythiaShowering_FS(input)||CMC::Judge_DetectorSimulating_FS(input)){
		std::vector<std::pair<float, ReconstructedParticle*> > rec_tmp;
		rec_tmp.clear();
		std::pair<MCParticle*,std::vector<std::pair<float, ReconstructedParticle*> > >input_pair=std::make_pair(input,rec_tmp);
		_end.push_back(input_pair);
	}
}


void ToolSet::CChain_Single::Recurse_Chain(MCParticle* input){
	Push_Back(input);
	if(CMC::Judge_PythiaShowering_FS(input)||CMC::Judge_DetectorSimulating_FS(input)){
		return;
	}
	for(int i=0;i<CMC::Get_Daughters_Number(input);i++){
		Recurse_Chain(input->getDaughters()[i]);
	}
}



//give a final particle,  get where does it come from
void ToolSet::CChain_Single::Push_Forward(MCParticle* input){
	//	std::cout<< "in Push_Forward::entering Push_Forward" << std::endl;
	if(CMC::Judge_HardScattering_FS(input)){
		//		std::cout<< "in Push_Forward::get a head" << std::endl;
		if(_head!=NULL){
			_head_assist  = input;
		}
		else{
			_head = input;
		}
	}
	if(CMC::Judge_HardScattering_Next_FS(input)){
		_next_head = input;
	}
	if(CMC::Judge_HardScattering_Next_Next_FS(input)){
		_next_next_head= input;
	}
	_chain.push_back(input);
	if(CMC::Judge_PythiaShowering_FS(input)||CMC::Judge_DetectorSimulating_FS(input)){
		//		std::cout<< "in Push_Forward::get an end" << std::endl;
		std::vector<std::pair<float, ReconstructedParticle*> > rec_tmp;
		rec_tmp.clear();
		std::pair<MCParticle*,std::vector<std::pair<float, ReconstructedParticle*> > >input_pair=std::make_pair(input,rec_tmp);
		_end.push_back(input_pair);
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








void ToolSet::CChain_Single::Set_Chain(MCParticle* input){
	Init();
	if(!CMC::Judge_HardScattering_FS(input)){
		return;
	}
	Recurse_Chain(input);
	Set_Trim_Chain();
}


void ToolSet::CChain_Single::Set_Trim_Chain(){
	//| ShowMessage(2,"Error, in CChain_Single:: _chain",_chain);
	bool get_chain=false;
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
						get_chain = true;
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
						get_chain = true;
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
		if(_trim_chain[i]->getPDG()!=new_vec.back()->getPDG()){
			new_vec.push_back(_trim_chain[i]);
		}
	}
	MCParticle* last_one=_trim_chain.front();
	_trim_chain.clear();

	_trim_chain=new_vec;
	_trim_chain.push_back(last_one);
}



void ToolSet::CChain_Single::Set_Chain_FromMCFS(MCParticle* input){
	//	std::cout<< "in Get_Chain_FromMCFS:: make sure input is a FS" << std::endl;
	if(!CMC::Judge_PythiaShowering_FS(input)&&!CMC::Judge_DetectorSimulating_FS(input)){
		return;
	}
	//	std::cout<< "begin Get_Chain_FromMCFS" << std::endl;
	TraceBack_Chain(input);
	Set_Trim_Chain();
	Minimize_Trim_Chain();
}


void ToolSet::CChain_Single::Set_Chain_FromRCFS(ReconstructedParticle* input){
	//	std::cout<< "in Get_Chain_FromMCFS:: make sure input is a FS" << std::endl;
	if(_nav_from_rc_to_mc==NULL){
		ToolSet::ShowMessage(2,"in ToolSet::CChain_Single::Set_Chain_FromRCFS, rc_link is not set before using RC functions");
		exit(0);
	}
	
	std::vector<MCParticle*> from_this_mc;
	LCObjectVec mc_objects= _nav_from_rc_to_mc->getRelatedToObjects(input);
	FloatVec mc_weight= _nav_from_rc_to_mc->getRelatedToWeights(input);
	float min_weight=-10000;
	int   min_pos=-1;
	for( unsigned int j = 0; j < mc_weight.size(); j++ ){
		if(min_weight<mc_weight[j]){
			min_weight=mc_weight[j];
			min_pos=j;
		}
	}
	for( unsigned int j = 0; j < mc_objects.size(); j++ ){
		MCParticle* recpfo = dynamic_cast< MCParticle* >( mc_objects[j] );
		from_this_mc.push_back(recpfo);
	}
	if(from_this_mc.size()>0&&min_pos>=0){
		ShowMessage(2,"input mc",from_this_mc[min_pos]);
		Set_Chain_FromMCFS(from_this_mc[min_pos]);
	}
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

	std::cout << "head:[" << _head->getPDG() << "]--->" << "end:[";
	for(unsigned int i=0;i<_end.size();i++){
		std::cout << _end[i].first->getPDG() ;
		for(unsigned int j=0;j<_end[i].second.size();j++){
			std::cout << "(" <<  _end[i].second[j].second->getType() ;
			std::cout << "," <<  _end[i].second[j].first << ")";
		}
		if(i!=_end.size()-1){
			std::cout<< ", ";
		}
	}
	std::cout << "]"<<std::endl;
}

void ToolSet::CChain_Single::Clear(){
	_head = NULL;
	_head_assist = NULL;
	_chain.clear();
	_end.clear();
}


