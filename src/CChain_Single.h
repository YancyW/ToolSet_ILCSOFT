#pragma once
#ifndef CCHAIN_SINGLE__H
#define CCHAIN_SINGLE__H  
#include "TTree.h"
#include "IMPL/MCParticleImpl.h"
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include "UTIL/LCRelationNavigator.h"
#include "CPrint.h"
#include "CMC.h"
#include "CRC.h"
#include "CVector.h"

namespace ToolSet{
	typedef std::pair<std::vector<float>, std::vector<ReconstructedParticle*> >   Chain_End_Type; 
	typedef std::vector<std::pair<MCParticle*, Chain_End_Type > >    Chain_Type; 

	class CChain_Single{
		private:
			//MC input
			MCParticle*                            _input; 
			//RC input
			ReconstructedParticle*                 _input_rc; 


			//hard scattering particle
			std::vector<MCParticle*>               _head; 
			//first decay products from the hard scattering particle
			std::vector<MCParticle*>               _next_head; 
			//second decay products from the hard scattering particle
			std::vector<MCParticle*>               _next_next_head; 


			//all particles in all status  involved in the chain
			std::vector<MCParticle*>               _chain; 
			//all but remove continued unchanged particles involved in the chain
			std::vector<MCParticle*>               _trim_chain; 


			// particles would contribute to PFO, related to their PFOs and weights
			Chain_Type                             _end; 
			// particles would contribute to PFOs  in the chain
			std::vector<MCParticle*>               _end_MC; 
			// PFOs in the chain
			std::vector<Chain_End_Type >           _RC; 
			std::vector<std::vector<ReconstructedParticle*> >   _RC_Particle; 
			std::vector<std::vector<float> >       _RC_Weight; 
			// PFOs, put into one vector, remove duplicated 
			std::vector<ReconstructedParticle*>    _flat_RC; 
			ReconstructedParticle*                 _combined_RC; 


			// particles that first get PFO,  then getting  PFO related MC 
			std::vector<MCParticle*>               _fromRC_MC; 
			std::vector<float>                     _fromRC_Weight; 

			// particle differences that directly from MC_end and from PFO related MC 
			std::vector<MCParticle*>               _extra_MC; 


			//navigator for Linker
			LCRelationNavigator*                   _nav_from_rc_to_mc;
			LCRelationNavigator*                   _nav_from_mc_to_rc;

			// flags
			bool                                   _has_trim_chain;
			bool                                   _has_set_rc;
			bool                                   _has_set_mc;
		public:
			CChain_Single (){
				Init();
			}

			CChain_Single (MCParticle* input){
				Build_Chain(input);
			}

			CChain_Single (ReconstructedParticle* input){
				Build_Chain_FromRCFS(input);
			}

			~CChain_Single (){
				Clear();
			}

			/*****************************************************************************************
			 * return private value  
			 *****************************************************************************************/
			MCParticle* Input(){
				return(_input);
			}

			ReconstructedParticle* Input_RC(){
				return(_input_rc);
			}

			std::vector<MCParticle*> Head(){
				return(_head);
			}

			std::vector<MCParticle*> Next_Head(){
				return(_next_head);
			}

			std::vector<MCParticle*> Next_Next_Head(){
				return(_next_next_head);
			}

			std::vector<MCParticle*> Chain(){
				return(_chain);
			}

			std::vector<MCParticle*> Trim_Chain(){
				return(_trim_chain);
			}

			Chain_Type End(){
				return(_end);
			}

			std::vector<MCParticle*> MCEnd(){
				return(_end_MC);
			}

			std::vector<Chain_End_Type> RC(){
				return(_RC);
			}

			std::vector<std::vector<ReconstructedParticle*> > RC_Particle(){
				return(_RC_Particle);
			}

			std::vector<std::vector<float> > RC_Weight(){
				return(_RC_Weight);
			}

			std::vector<ReconstructedParticle*> Flat_RC(){
				return(_flat_RC);
			}

			ReconstructedParticle* Combined_RC(){
				return(_combined_RC);
			}

			std::vector<MCParticle*> FromRC_MC(){
				return(_fromRC_MC);
			}

			std::vector<float> FromRC_Weight(){
				return(_fromRC_Weight);
			}

			std::vector<MCParticle*> Extra_MC(){
				return(_extra_MC);
			}

			LCRelationNavigator* Nav_From_MC_to_RC(){
				return(_nav_from_mc_to_rc);
			}

			LCRelationNavigator* Nav_from_RC_to_MC(){
				return(_nav_from_rc_to_mc);
			}

			bool Has_Trim_Chain(){
				return(_has_trim_chain);
			}

			bool Has_Set_RC(){
				return(_has_set_rc);
			}

			bool Has_Set_MC(){
				return(_has_set_mc);
			}

			/*****************************************************************************************
			 * functions for completeness 
			 *****************************************************************************************/

			void Init();

			void Print();

			void Clear();

			/*****************************************************************************************
			 * functions for basic setting 
			 *****************************************************************************************/

			void Set_Nav_From_MC_To_RC(LCRelationNavigator* relation);

			void Set_Nav_From_RC_To_MC(LCRelationNavigator* relation);

			void Set_RC();

			void Set_Flat_RC();

			void Set_Combined_RC();

			void Set_MC_From_Flat_RC();

			void Set_Extra_MC();

			void Set_Trim_Chain();

			void Minimize_Trim_Chain();

			void Set_MC_End();

			void Set_End_Type();

			void Set_MC();

			/*****************************************************************************************
			 * functions for building 
			 *****************************************************************************************/

			void Build_Chain(MCParticle* input);

			void Recurse_Chain(MCParticle* input);

			void Push_Back(MCParticle* input);

			void Push_Forward(MCParticle* input);

			void TraceBack_Chain(MCParticle* input);

			void Build_Chain_FromRCFS(ReconstructedParticle* input);

	};
}
#endif

