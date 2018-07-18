
#include"CFlavor.h"
bool ToolSet::CFlavor::Judge_Is_Hadron(int pdg){
	if(pdg>100 && pdg <600){
		return(true);
	}
	if(pdg>1000 && pdg <6000){
		return(true);
	}
	//choose 1500-1600
	if((pdg%1000)>100 && (pdg%1000) <600){
		return(true);
	}
	//choose 11500-1600
	if((pdg%10000)>1000 && (pdg%10000) <6000){
		return(true);
	}
	return(false);
}
