#pragma once
#ifndef CData_Type_H
#define CData_Type_H  
#define Epsilon_Small  0.00001   
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "CFormat.h" 

namespace ToolSet{
	class Data_Type{
		public:
			/**
			 * @brief Int_to_String : data type changing
			 *
			 * @param i
			 *
			 * @return 
			 */
			static TString Int_to_String(int i);
			/**
			 * @brief Int_to_String_descrip : use word to describe rank
			 *
			 * @param i
			 *
			 * @return 
			 */
			static TString Int_to_String_descrip(int i);

			/**
			 * @brief CountNumber : print out how many events have been dealed with
			 *
			 * @param variable
			 * @param tot_num
			 * @param slot
			 * @param Message
			 */
			static void CountNumber(Int_t variable, Int_t tot_num, Int_t slot,TString  Message);

			/**
			 * @brief Equal_Float : judge whether two floats are equal, ignore the small fluctuation
			 *
			 * @param f1
			 * @param f2
			 *
			 * @return 
			 */
			static bool Equal_Float(float f1, float f2);

			/**
			 * @brief Get_Pos : get the maximum/minimum number position
			 *
			 * @param input
			 * @param label : only can be "max" or "min"
			 *
			 * @return 
			 */
			static int Get_Pos(std::vector<float> input, std::string label);
	};
}
#endif
