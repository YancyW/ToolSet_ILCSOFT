#include "CChain.h"



void ToolSet::CChain_Single::Init(){
	//_head = std::nullptr_t null;
	_head = NULL;
	_head_assist = NULL;
}


void ToolSet::CChain_Single::Get_RC(LCRelationNavigator* relation){
	for(unsigned int i=0;i<_end.size();i++){
		std::vector<std::pair<float, ReconstructedParticle*> > to_tmp;

		LCObjectVec frompars = relation->getRelatedFromObjects(_end[i].first) ;
		std::vector<float> weight = relation->getRelatedFromWeights(_end[i].first);

		for(unsigned int j=0;j<frompars.size();j++){
			ReconstructedParticle* recpfo = dynamic_cast<ReconstructedParticle*>(frompars[j]);
			to_tmp.push_back(std::make_pair(weight[j],recpfo));
		}
		_end[i].second=to_tmp;
	}
	return;
}


//give a initial particle,  get where does it go to 
void ToolSet::CChain_Single::Push_Back(MCParticle* input){
	if(CMC::Judge_HardScattering_FS(input)){
		_head = input;
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








void ToolSet::CChain_Single::Get_Chain(MCParticle* input){
	if(!CMC::Judge_HardScattering_FS(input)){
		return;
	}
	Recurse_Chain(input);
}


void ToolSet::CChain_Single::Get_Chain_FromMCFS(MCParticle* input){
//	std::cout<< "in Get_Chain_FromMCFS:: make sure input is a FS" << std::endl;
	if(!CMC::Judge_PythiaShowering_FS(input)&&!CMC::Judge_DetectorSimulating_FS(input)){
		return;
	}
//	std::cout<< "begin Get_Chain_FromMCFS" << std::endl;
	TraceBack_Chain(input);
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


