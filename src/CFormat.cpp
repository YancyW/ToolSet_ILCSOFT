#include "CFormat.h"

void ToolSet::ShowMessage(){
	std::cout << "" << std::endl;
}

void ToolSet::ShowMessage(Int_t level){
	for(int i=0;i<level;i++){
		std::cout << "" << std::endl;
	}
}
