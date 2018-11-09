#pragma once
#ifndef CData_Type_H
#define CData_Type_H  
#define Epsilon_Small  0.1   
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "CFormat.h" 

namespace ToolSet{
	class Data_Type{
		public:
			static TString Int_to_String(int i);
			static TString Int_to_String_descrip(int i);

			static TString NameHistogram(TString signal_name, TString class_name, TString observable_name, int i);
			static TString NameDescrip(TString class_name, TString observable_name, int i);

			static TString GetUnit(TString observe_name);

			template <typename TTname>
				static TString Get_ClassName(TTname x){

					TString tname;
					tname = typeid(x).name();

					return(tname);
				}

			static void CountNumber(Int_t variable, Int_t tot_num, Int_t slot,TString  Message);

			static bool Equal_Float(float f1, float f2);

			static int Get_Pos(std::vector<float> input, std::string label);
	};
}
#endif
