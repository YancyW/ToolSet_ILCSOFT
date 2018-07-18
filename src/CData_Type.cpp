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
	TString fdescrip[6]= {"leading","second","third","fourth","fifth","sixth"};

	fnum = fdescrip[i];
	return(fnum);
}

 TString ToolSet::Data_Type::NameHistogram(TString signal_name, TString class_name, TString observable_name, int i){

	TString Final_Name;
	TString fnum;

	fnum=Int_to_String(i);
	Final_Name=signal_name+"_"+class_name+"_"+observable_name+"_"+fnum;

	return(Final_Name);
}

 TString ToolSet::Data_Type::NameDescrip(TString class_name, TString observable_name, int i){

	TString Final_Name;
	TString desnum;

	desnum=Int_to_String_descrip(i);
	Final_Name=desnum+"_"+class_name+"_"+observable_name;

	return(Final_Name);
}

 TString ToolSet::Data_Type::GetUnit(TString observe_name){
	TString unit_name;
	if(observe_name == "pt"){
		unit_name="GeV";
	}
	else if(observe_name == "mass"){
		unit_name="GeV";
	}
	else{unit_name="";}

	return(unit_name);
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
	if(std::abs(f1-f2)<Epsilon_Small){
		return(true);
	}
	return(false);
}

