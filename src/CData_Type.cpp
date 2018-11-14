#include "CData_Type.h"
TString ToolSet::Data_Type::Int_to_String(int i){
	TString fnum;
	std::stringstream num;

	num << i;
	num >> fnum;
	return(fnum);
}

TString ToolSet::Data_Type::Int_to_String_descrip(int i){
	TString fnum;
	TString fdescrip[6]= {"first","second","third","fourth","fifth","sixth"};

	fnum = fdescrip[i];
	return(fnum);
}


void ToolSet::Data_Type::CountNumber(Int_t variable, Int_t tot_num, Int_t slot,TString  Message){
	if(tot_num>slot*100){
		if(variable%slot == 0 && variable!=0){
			ShowMessage(2,Message,variable);
		}
	}
	else{
		if(variable%(tot_num/100) == 0 && variable!=0){
			ShowMessage(2,Message,variable/(tot_num/100),"%");
		}
	}

}

bool ToolSet::Data_Type::Equal_Float(float f1, float f2){
	if(std::abs(f1-f2)/f2<Epsilon_Small){
		return(true);
	}
	return(false);
}

int ToolSet::Data_Type::Get_Pos(std::vector<float> input, std::string label){
	if(input.size()<=0){return(-1);}
	if(label!="max" && label!="min"){ShowMessage(2,"Error:in ToolSet::Data_Type::Get_Pos(), not a correct label",label);return(-1);}
	float max=0;
	int   pos=0;
	for(unsigned int i=0;i<input.size();i++){
		if(label=="max"){
			if(input[i]>max){
				max=input[i];
				pos = i;
			}
		}
		else if(label=="min"){
			max = 10000000;
			if(input[i]<max){
				max=input[i];
				pos = i;
			}
		}
	}
	return(pos);
}
