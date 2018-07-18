#pragma once
#ifndef CVECTOR_H
#define CVECTOR_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

namespace ToolSet{
	template <typename TVector_add>
		static std::vector<TVector_add> operator + (std::vector<TVector_add> V1, std::vector<TVector_add> V2){
			std::vector <TVector_add> Vnew;

			Vnew.resize(V1.size()+V2.size());
			copy(V1.begin(),V1.end(),Vnew.begin());
			copy(V2.begin(),V2.end(),Vnew.begin()+V1.size());

			stable_sort(Vnew.begin(),Vnew.end());
			reverse(Vnew.begin(),Vnew.end());
			return(Vnew);
		}

	template<typename VEC_CONTAIN>
		static bool Vec_Judge_Contain(std::vector<VEC_CONTAIN> vec, VEC_CONTAIN input){
			if(std::find(vec.begin(), vec.end(), input) != vec.end()) {
				return(true);
			} 
			else {
				return(false);
			}
		}

}

#endif
