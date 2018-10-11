#pragma once
#ifndef CCHAIN_H
#define CCHAIN_H  
#include "TTree.h"
#include "IMPL/MCParticleImpl.h"
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include "UTIL/LCRelationNavigator.h"
#include "CPrint.h"
#include "CMC.h"

namespace ToolSet{
	typedef std::vector<std::pair<float, ReconstructedParticle*> >                Chain_End_Type; 
	typedef std::vector<std::vector<std::pair<float, ReconstructedParticle*> > >  Chain_End_Type_Vec; 
	typedef std::vector<std::pair<MCParticle*,std::vector<std::pair<float, ReconstructedParticle*> > > >    Chain_Type; 

	class CChain_Single{
		private:
			std::vector<MCParticle*> _chain; 
			std::vector<MCParticle*> _trim_chain; 
			MCParticle*              _head; 
			MCParticle*              _next_head; 
			MCParticle*              _next_next_head; 
			MCParticle*              _head_assist; 
			Chain_Type               _end; 
			bool                     _has_trim_chain;
			bool                     _has_set_rc;
			LCRelationNavigator*    _nav_from_rc_to_mc;
			LCRelationNavigator*    _nav_from_mc_to_rc;
		public:
			CChain_Single (){
				Init();
			}

			CChain_Single (MCParticle* input){
				Set_Chain(input);
			}

			MCParticle* Head(){
				if(_has_trim_chain&&_trim_chain.size()>0){
					return(_trim_chain[0]);
				}
				else{
					return(_head);
				}
			}

			MCParticle* Next_Head(){
				if(_has_trim_chain&&_trim_chain.size()>1){
					return(_trim_chain[1]);
				}
				else{
					return(_next_head);
				}
			}

			MCParticle* Next_Next_Head(){
				if(_has_trim_chain&&_trim_chain.size()>2){
					return(_trim_chain[2]);
				}
				else{
					return(_next_next_head);
				}
			}

			MCParticle* Head_Assist(){
				return(_head_assist);
			}

			Chain_Type End(){
				return(_end);
			}

			std::vector<MCParticle*> Chain(){
				return(_chain);
			}

			std::vector<MCParticle*> Trim_Chain(){
				return(_trim_chain);
			}



			void Init();

			void Set_Nav_From_MC_To_RC(LCRelationNavigator* relation);

			void Set_Nav_From_RC_To_MC(LCRelationNavigator* relation);

			void Set_RC();

			void Push_Back(MCParticle* input);

			void Recurse_Chain(MCParticle* input);

			void Push_Forward(MCParticle* input);

			void TraceBack_Chain(MCParticle* input);

			void Set_Chain(MCParticle* input);

			void Set_Trim_Chain();

			void Minimize_Trim_Chain();

			void Set_Chain_FromMCFS(MCParticle* input);

			void Set_Chain_FromRCFS(ReconstructedParticle* input);

			void Print();

			void Clear();

			void Print_test();

			void Puttree(MCParticle* input,int h);
	};

	class CChain_Vec{
		private:
			std::vector<CChain_Single> _chain_vec; 
			LCRelationNavigator*       _nav_from_rc_to_mc;
			LCRelationNavigator*       _nav_from_mc_to_rc;
		public: 

			std::vector<CChain_Single>          Chain_Vec(){return(_chain_vec);}
			void                                Set_Nav_From_MC_To_RC(LCRelationNavigator* input);
			void                                Set_Nav_From_RC_To_MC(LCRelationNavigator* input);
			void                                Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* input);
			void                                Set_ChainVec(std::vector<MCParticle*> MCs);
			void                                Set_ChainVec_FromMCFS(std::vector<MCParticle*> MCs) ;
			void                                Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs) ;
			void                                Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs, LCRelationNavigator* input) ;
			void                                Print() ;


			CChain_Vec(){
				Init();
			}

			void                                                            Init();

			std::vector<MCParticle*>                                        Get_MCHead();
			std::vector<MCParticle*>                                        Get_MCNextHead();
			std::vector<MCParticle*>                                        Get_MCNextNextHead();
			std::vector<std::vector<MCParticle*> >                          Get_Chain();
			std::vector<std::vector<MCParticle*> >                          Get_Trim_Chain();
			std::vector<std::vector<MCParticle*> >                          Get_MCEnd();
			std::vector<ToolSet::Chain_End_Type_Vec >                       Get_RC();
			bool                                                            Get_SpecialRC(int pdg,std::string marker,std::vector<std::vector<ReconstructedParticle*> > & output);
			std::vector<std::vector<ReconstructedParticle*> >               Get_EnergeticRC(int pdg);
			std::vector<std::vector<ReconstructedParticle*> >               Get_WeightedRC(int pdg);
			bool                                                            Compare_SpecialRC(int pdg);
	}; 
}
#endif

