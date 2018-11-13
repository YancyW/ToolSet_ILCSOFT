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

			return(Vnew);
		}

	template <typename T>
		static void operator+=(std::vector<T> &v1, const std::vector<T> &v2) {
			v1.insert(v1.end(), v2.begin(), v2.end());
		}


	template <typename TVector_minus>
		static std::vector<TVector_minus> operator - (std::vector<TVector_minus> V1, std::vector<TVector_minus> V2){
			std::vector <TVector_minus> Vnew;
			if(V2.size()==0){
				return(V1);
			}
			if(V1.size()==0 ){
				return(Vnew);
			}


			std::vector<unsigned int> remove1;
			for(unsigned int i=0;i<V1.size();i++){
				for(unsigned int j=0;j<V2.size();j++){
					if(V1[i]==V2[j]){
						remove1.push_back(i);
						break;
					}
				}
			}

			stable_sort(remove1.begin(),remove1.end());

			bool	isminused=false;
			for(unsigned int i=0;i<V1.size();i++){
				for(unsigned int j=0;j<remove1.size();j++){
					if(i==remove1[j]){
						isminused=true;
						break;
					}
				}
				if(!isminused){
					Vnew.push_back(V1[i]);
				}
				isminused=false;
			}
			return(Vnew);
		}


	template<typename VEC_FLAT>
		static std::vector<VEC_FLAT> Vec_Flat(std::vector<std::vector<VEC_FLAT> > input){
			std::vector<VEC_FLAT> vec;
			std::vector<VEC_FLAT> vec_tmp;
			for(unsigned int i=0;i<input.size();i++){
				vec_tmp=vec;
				vec=vec_tmp+input[i];
			}
			return(vec);
		}


	template<typename VEC_EXIST>
		static bool Vec_Exist(std::vector<VEC_EXIST>V1, VEC_EXIST  input){                                                                                                                                                                             
			if(V1.size()==0){return(false);}

		    typename std::vector<VEC_EXIST>::iterator ret;
			ret = std::find(V1.begin(), V1.end(), input);
			if(ret == V1.end()){
				return(false);
			}
			else{
				return(true);
			}
		}

	template<typename VEC_DUPLICATE>
		static std::vector<VEC_DUPLICATE> Vec_Remove_Duplicate(std::vector<VEC_DUPLICATE> &V1){                                                                                                                                                                             
			std::vector<VEC_DUPLICATE> V2;
			if(V1.size()==0){return(V2);}
			else{V2=V1;}

			sort( V2.begin(), V2.end()  );
			V2.erase( unique( V2.begin(), V2.end()  ), V2.end()  );
			return(V2);
		}


	template<typename VEC_EXPAND>
		static std::vector<VEC_EXPAND> Vec_Expand_VecVec(std::vector<std::vector<VEC_EXPAND> > &V1){                                                                                                                                                                             
			std::vector<VEC_EXPAND> V2;
			if(V1.size()==0){return(V2);}
			else{V2=Vec_Flat(V1);}

			sort( V2.begin(), V2.end()  );
			V2.erase( unique( V2.begin(), V2.end()  ), V2.end()  );
			return(V2);
		}


	template<typename VEC_DIFFERENCE>
		static std::vector<VEC_DIFFERENCE> Vec_Difference(std::vector<VEC_DIFFERENCE> &V1, std::vector<VEC_DIFFERENCE> &V2){
			std::vector<VEC_DIFFERENCE> result;
			typename std::vector<VEC_DIFFERENCE>::iterator it;

			std::sort (V1.begin(),V1.end());     
			std::sort (V2.begin(),V2.end());   
			it=std::set_difference (V1.begin(), V1.end(), V2.begin(), V2.end(), result.begin());
			result.resize(it-result.begin());
			return(V2);
		}
}
	template<typename VEC_SDIFFERENCE>
		static std::vector<VEC_SDIFFERENCE> Vec_Symmetry_Difference(std::vector<VEC_SDIFFERENCE> &V1, std::vector<VEC_SDIFFERENCE> &V2){
			std::vector<VEC_SDIFFERENCE> result;
			typename std::vector<VEC_SDIFFERENCE>::iterator it;

			std::sort (V1.begin(),V1.end());     
			std::sort (V2.begin(),V2.end());   
			it=std::set_symmetric_difference (V1.begin(), V1.end(), V2.begin(), V2.end(), result.begin());
			result.resize(it-result.begin());
			return(V2);
		}
}

#endif
