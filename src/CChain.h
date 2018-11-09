#pragma once
#ifndef CCHAIN_H
#define CCHAIN_H  
#include "CChain_Single.h"

namespace ToolSet{
	typedef std::vector<Chain_Type>  Chain_End_Type_Vec; 

	class CChain_Vec{
		private:
			int                        _chain_num;
			std::vector<CChain_Single> _chain_vec; 
			LCRelationNavigator*       _nav_from_rc_to_mc;
			LCRelationNavigator*       _nav_from_mc_to_rc;
		public: 

			CChain_Vec(){
				Init();
			}

			/*****************************************************************************************
			 * return private value  
			 *****************************************************************************************/

			std::vector<CChain_Single> Chain_Vec(){
				return(_chain_vec);
			}

			LCRelationNavigator* Nav_From_MC_to_RC(){
				return(_nav_from_mc_to_rc);
			}

			LCRelationNavigator* Nav_from_RC_to_MC(){
				return(_nav_from_rc_to_mc);
			}

			/*****************************************************************************************
			 * return member value  
			 *****************************************************************************************/

			std::vector<MCParticle*>                                        Get_MCInput();
			std::vector<ReconstructedParticle*>                             Get_RCInput();
			std::vector<std::vector<MCParticle*> >                          Get_MCHead();
			std::vector<std::vector<MCParticle*> >                          Get_MCNextHead();
			std::vector<std::vector<MCParticle*> >                          Get_MCNextNextHead();
			std::vector<std::vector<MCParticle*> >                          Get_Chain();
			std::vector<std::vector<MCParticle*> >                          Get_Trim_Chain();
			std::vector<std::vector<MCParticle*> >                          Get_MCEnd();
			std::vector<std::vector<ToolSet::Chain_End_Type > >             Get_RC();
			std::vector<std::vector<std::vector<ReconstructedParticle*> > > Get_RC_Particle();
			std::vector<std::vector<std::vector<float> > >                  Get_RC_Weight();
			std::vector<std::vector<MCParticle*> >                          Get_Extra_MC();
			std::vector<std::vector<ReconstructedParticle*> >               Get_Flat_RC();
			std::vector<ReconstructedParticle*>								Get_Combined_RC();
			std::vector<std::vector<MCParticle*> >                          Get_FromRC_MC();

			bool                                                            Get_SpecialRC(int pdg,std::string marker,std::vector<std::vector<ReconstructedParticle*> > & output);
			std::vector<std::vector<ReconstructedParticle*> >               Get_EnergeticRC(int pdg);
			std::vector<std::vector<ReconstructedParticle*> >               Get_WeightedRC(int pdg);
			bool                                                            Compare_SpecialRC(int pdg);

			/*****************************************************************************************
			 * functions for completeness 
			 *****************************************************************************************/

			void                                                            Init();

			void                                                            Print() ;

			// !!! Notice:  Remember to Clear the chain after use it.   If you use combined_RC command, it will build a "new" Particle. So you need to delete this point with Clear() function.
			// I didn't write Clear() into deconstructor because it may cause some trouble when transfer the chain to other functions.
			void                                                            Clear() ;

			/*****************************************************************************************
			 * functions for basic setting 
			 *****************************************************************************************/

			void  Set_Nav_From_MC_To_RC(LCRelationNavigator* input);
			void  Set_Nav_From_RC_To_MC(LCRelationNavigator* input);
			void  Set_Nav(LCRelationNavigator* nav_MC_To_RC, LCRelationNavigator* nav_RC_To_MC);

			void  Set_ChainVec(std::vector<MCParticle*> MCs);
			void  Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* from_mc_to_rc);
			void  Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* from_mc_to_rc, LCRelationNavigator* from_rc_to_mc);

			void  Set_ChainVec_FromMCFS(std::vector<MCParticle*> MCs) ;
			void  Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs) ;
			void  Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs, LCRelationNavigator* input) ;

			void  Set_RC();
			void  Set_MC();

	}; 
}
#endif

