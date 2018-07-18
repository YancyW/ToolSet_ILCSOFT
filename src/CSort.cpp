#include "CSort.h"
ToolSet::CSort::CSort(){
	init();
}


ToolSet::CSort::CSort(std::vector<MCParticle*> input){
	init();
	_source= input;
	_nsource= _source.size();
	_Used = true;
}

void ToolSet::CSort::set_Source(std::vector<MCParticle*> input){
	_source  = input;
	_nsource = _source.size();
	_Used = true;
}

void ToolSet::CSort::set_Class(int pdg){
	if(!_Used){
		return;
	}

	std::vector<MCParticle*> data_tmp; 
	_sort.insert(make_pair(pdg,data_tmp));
}

void ToolSet::CSort::set_Sort(int pdg){
	if(!_Used){
		return;
	}

	if(pdg<0){
		pdg=-pdg;
	}

	std::map<int, std::vector<MCParticle*> >::iterator it = _sort.find(pdg);

	if(it == _sort.end()){
		set_Class(pdg);
	}


	for( int i = 0; i < _nsource; i++ ){
		if(std::abs(_source[i]->getPDG())==pdg){
			_sort[pdg].push_back(_source[i]); 
		}
	}

}

bool ToolSet::CSort::get_Sort(int pdg, std::vector<MCParticle*> & output){
	if(!_Used){
		return(false);
	}

	if(pdg<0){
		pdg=-pdg;
	}

	std::map<int, std::vector<MCParticle*> >::iterator it = _sort.find(pdg);

	if(it == _sort.end()){
		return(false);
	}

	output = _sort[pdg];
	return(true);
}

void ToolSet::CSort::Print(){

	std::map<int, std::vector<MCParticle*> >::iterator it = _sort.begin();
	for(;it!=_sort.end();it++){
		ShowMessage(2,"pdg:", it->first,it->second);
	}
}

void ToolSet::CSort::init(){
	_sort.clear();
	_source.clear();
	_nsource=0;
	_Used=false;
}
