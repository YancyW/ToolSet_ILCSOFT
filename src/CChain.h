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
			MCParticle*              _head; 
			MCParticle*              _head_assist; 
			Chain_Type               _end; 
		public:
			CChain_Single (){
				Init();
			}

			CChain_Single (MCParticle* input){
				Get_Chain(input);
			}

			MCParticle* Head(){
				return(_head);
			}

			MCParticle* Head_Assist(){
				return(_head_assist);
			}

			Chain_Type End(){
				return(_end);
			}

			void Init();

			void Get_RC(LCRelationNavigator* relation);

			void Push_Back(MCParticle* input);

			void Recurse_Chain(MCParticle* input);

			void Push_Forward(MCParticle* input);

			void TraceBack_Chain(MCParticle* input);

			void Get_Chain(MCParticle* input);

			void Get_Chain_FromMCFS(MCParticle* input);

			void Print();

			void Clear();

			void Print_test();

			void Puttree(MCParticle* input,int h);
	};

	class CChain_Vec{
		private:
			std::vector<CChain_Single> _chain_vec; 
			LCRelationNavigator*       _nav_from_pfo_to_mc;
			LCRelationNavigator*       _nav_from_mc_to_pfo;
		public: 
			std::vector<CChain_Single>          Chain_Vec(){return(_chain_vec);}
			void                                Get_Nav(LCRelationNavigator* input);
			void                                Get_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* input);
			void                                Get_ChainVec_FromMCFS(std::vector<MCParticle*> MCs) ;
			void                                Print() ;


			std::vector<MCParticle*>                                        Get_MCHead();
			std::vector<std::vector<MCParticle*> >                          Get_MCEnd();
			std::vector<Chain_End_Type_Vec >                                Get_RC();
			bool                                                            Get_SpecialRC(int pdg,std::string marker,std::vector<std::vector<ReconstructedParticle*> > & output);
			std::vector<std::vector<ReconstructedParticle*> >               Get_EnergeticRC(int pdg);
			std::vector<std::vector<ReconstructedParticle*> >               Get_WeightedRC(int pdg);
			void                                                            Init();
			bool                                                            Compare_SpecialRC(int pdg);
	}; 
}
#endif

