/**
 * @file CChain_Single.h
 * @brief 
 * @author Yan Wang - yan.wang@desy.de
 * @version 1.0
 * @date 2018-11-13
 */
/* Copyright (C) 
 * 2018 - Yan Wang - yan.wang@desy.de
 * Unpublished copyright. All rights rserved by Yan Wang. 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 */
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

	/**
	 * @brief : in this class, it contains two part: MCParticle part and ReconstructedParticle part.
	 * for MCParticle, its stucture is head->decay products -> ... -> many pythia final states -> ... -> many detector simulation final states.
	 * then all final states will get their corresponding ReconstructedParticles with the MCTruthRecoLink
	 * these MCParticle final states as well as their corresponding ReconstructedParticles and weights are stored as pairs together in the Chain_Type
	 * Finally, the ReconstructedParticles also can find their corresponding MCParticles, these MCParticles can be different from the original MC final states, because some ReconstructedParticles have the contribution from other
	 * source.
	 */
	class CChain_Single{
		private:
			/**
			 * @brief store input MCparticles
			 */
			MCParticle*                            _input; 
			/**
			 * @brief : store input ReconstructedParticle
			 */
			ReconstructedParticle*                 _input_rc; 


			/**
			 * @brief : the hard scattering particle in the chain
			 */
			std::vector<MCParticle*>               _head; 
			/**
			 * @brief : first decay products from the hard scattering particle
			 */
			std::vector<MCParticle*>               _next_head; 
			/**
			 * @brief : second decay products from the hard scattering particle
			 */
			std::vector<MCParticle*>               _next_next_head; 


			/**
			 * @brief : all particles in all status  involved in the chain
			 */
			std::vector<MCParticle*>               _chain; 
			/**
			 * @brief : all but remove continued unchanged particles involved in the chain
			 */
			std::vector<MCParticle*>               _trim_chain; 


			/**
			 * @brief : the final states (ReconstructedParticles and their related weights and MCParticles ) in the chain, one head will have many MC ends
			 */
			Chain_Type                             _end; 
			/**
			 * @brief selected MCparticle from the _end, these are particles that would contribute to PFOs in the chain, it is the particles of the pythia final states and all particles in the simulation
			 */
			std::vector<MCParticle*>               _end_MC; 
			/**
			 * @brief selected ReconstructedParticles from the _end, also including their weights
			 */
			std::vector<Chain_End_Type >           _RC; 
			/**
			 * @brief selected ReconstructedParticles from the _end
			 */
			std::vector<std::vector<ReconstructedParticle*> >   _RC_Particle; 
			/**
			 * @brief selected ReconstructedParticles weight from the _end
			 */
			std::vector<std::vector<float> >       _RC_Weight; 
			/**
			 * @brief : expand _RC_Particle into one vector, and remove duplicated ones 
			 */
			std::vector<ReconstructedParticle*>    _flat_RC; 
			/**
			 * @brief : sum all ReconstructedParticle into a new particle, so that you can compare the energy/momentum loss between original MC particle and ReconstructedParticles. This will generate a new ReconstructedParticle in the heap, so remember to use Clear() function after using CChain_Vec
			 */
			ReconstructedParticle*                 _combined_RC; 


			/**
			 * @brief : particles that first get PFO,  then getting  MC that related  PFO 
			 */
			std::vector<MCParticle*>               _fromRC_MC; 
			/**
			 * @brief : particles that first get PFO,  then getting  MC weight that related  PFO 
			 */
			std::vector<float>                     _fromRC_Weight; 

			/**
			 * @brief : show the extra contributions for the ReconstructedParticle from other source that not in this chain
			 */
			std::vector<MCParticle*>               _extra_MC; 


			//navigator for Linker
			/**
			 * @brief : set Nav, input is MC, return the related ReconstructedParticle 
			 */
			LCRelationNavigator*                   _nav_from_rc_to_mc;
			/**
			 * @brief : set Nav, input is ReconstructedParticle, return the related MCParticle
			 */
			LCRelationNavigator*                   _nav_from_mc_to_rc;

			// flags
			/**
			 * @brief : flag for trim duplicated particles in the chain 
			 */
			bool                                   _has_trim_chain;
			/**
			 * @brief : flag for set Reconstructed part
			 */
			bool                                   _has_set_rc;
			/**
			 * @brief : flag for set MC part
			 */
			bool                                   _has_set_mc;
		public:
			/**
			 * @brief CChain_Single : normal constructor
			 */
			CChain_Single (){
				Init();
			}

			/**
			 * @brief CChain_Single : constructor, directly build the  chain of the MC part
			 *
			 * @param input
			 */
			CChain_Single (MCParticle* input){
				Build_Chain(input);
			}

			/**
			 * @brief CChain_Single : constructor, build the chain of the ReconstructedParticle part
			 *
			 * @param input
			 */
			CChain_Single (ReconstructedParticle* input){
				Build_Chain_FromRCFS(input);
			}

			/*****************************************************************************************
			 * return private value  
			 *****************************************************************************************/
			/**
			 * @brief Input : get all input MC particles
			 *
			 * @return 
			 */
			MCParticle* Input(){
				return(_input);
			}

			/**
			 * @brief Input_RC : get all input RC particles
			 *
			 * @return 
			 */
			ReconstructedParticle* Input_RC(){
				return(_input_rc);
			}

			/**
			 * @brief Head : get the hard-scattering particles for the chain
			 *
			 * @return 
			 */
			std::vector<MCParticle*> Head(){
				return(_head);
			}

			/**
			 * @brief Next_Head : get first decay products from the hard-scattering particles in the chains
			 *
			 * @return 
			 */
			std::vector<MCParticle*> Next_Head(){
				return(_next_head);
			}

			/**
			 * @brief Next_Next_Head : get first decay products from the hard-scattering particles in the chains
			 *
			 * @return 
			 */
			std::vector<MCParticle*> Next_Next_Head(){
				return(_next_next_head);
			}

			/**
			 * @brief Chain: get all MC particles in each chains (from hard-scattering to final simulated particle, has duplicated ones)
			 *
			 * @return 
			 */
			std::vector<MCParticle*> Chain(){
				return(_chain);
			}

			/**
			 * @brief Trim_Chain : get trimed MC particles in the chain (from hard-scattering to final simulated particle)
			 *
			 * @return 
			 */
			std::vector<MCParticle*> Trim_Chain(){
				return(_trim_chain);
			}

			/**
			 * @brief End : get all final states including MCParticles and the corresponding  ReconstructedParticle (as well as their weights) in the chain. 
			 *
			 * @return 
			 */
			Chain_Type End(){
				return(_end);
			}

			/**
			 * @brief MCEnd : get final states in the MC part in the chain. 
			 *
			 * @return 
			 */
			std::vector<MCParticle*> MCEnd(){
				return(_end_MC);
			}

			/**
			 * @brief RC : get ReconstructedParticle in the chain, it organizes as for each particle in the MCEnd, it has a MCparticle---vector of <(weight, ReconstructedParticle)>
			 *
			 * @return 
			 */
			std::vector<Chain_End_Type> RC(){
				return(_RC);
			}

			/**
			 * @brief RC_Particle : get ReconstructedParticle in the chain， it organizes as for each particle in the MCEnd, it has a MCParticle -- vector of <ReconstructedParticles>  
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> > RC_Particle(){
				return(_RC_Particle);
			}

			/**
			 * @brief RC_Weight : get ReconstructedParticle's weight in the chain， it organizes as for each particle in the MCEnd, it has a MCParticle -- vector of <weight>  
			 *
			 * @return 
			 */
			std::vector<std::vector<float> > RC_Weight(){
				return(_RC_Weight);
			}

			/**
			 * @brief Flat_RC :  get all posible ReconstructedParticle in the chain, comparing Get_RC(), it removes duplicated ones  
			 *
			 * @return 
			 */
			std::vector<ReconstructedParticle*> Flat_RC(){
				return(_flat_RC);
			}

			/**
			 * @brief Combined_RC : sum all ReconstructedParticle into a new particle in the chain, so that you can compare the energy/momentum loss between original MC particle and ReconstructedParticles. This will generate a new ReconstructedParticle in the heap, so remember to use Clear() function after using CChain_Vec
			 *
			 * @return 
			 */
			ReconstructedParticle* Combined_RC(){
				return(_combined_RC);
			}

			/**
			 * @brief FromRC_MC : get MCParticles from ReconstructedParticles with other direction linker in the chain.  It's important for cross check particle reconstruction.
			 *
			 * @return 
			 */
			std::vector<MCParticle*> FromRC_MC(){
				return(_fromRC_MC);
			}

			/**
			 * @brief FromRC_Weight : get MCParticles weight from ReconstructedParticles with other direction linker in the chain.  It's important for cross check particle reconstruction.
			 *
			 * @return 
			 */
			std::vector<float> FromRC_Weight(){
				return(_fromRC_Weight);
			}

			/**
			 * @brief Extra_MC : show the extra contributions for the ReconstructedParticle from other particles that not in the chain
			 *
			 * @return 
			 */
			std::vector<MCParticle*> Extra_MC(){
				return(_extra_MC);
			}

			/**
			 * @brief Nav_From_MC_to_RC : Nav, input is MC, return the related ReconstructedParticle 
			 *
			 * @return 
			 */
			LCRelationNavigator* Nav_From_MC_to_RC(){
				return(_nav_from_mc_to_rc);
			}

			/**
			 * @brief Nav_from_RC_to_MC : Nav, input is ReconstructedParticle, return the related MCParticle
			 *
			 * @return 
			 */
			LCRelationNavigator* Nav_from_RC_to_MC(){
				return(_nav_from_rc_to_mc);
			}

			/**
			 * @brief Has_Trim_Chain : return flag for trim duplicated particles in the chain 
			 *
			 * @return 
			 */
			bool Has_Trim_Chain(){
				return(_has_trim_chain);
			}

			/**
			 * @brief Has_Set_RC : return flag for set Reconstructed part
			 *
			 * @return 
			 */
			bool Has_Set_RC(){
				return(_has_set_rc);
			}

			/**
			 * @brief Has_Set_MC : return flag for set MC part
			 *
			 * @return 
			 */
			bool Has_Set_MC(){
				return(_has_set_mc);
			}

			/*****************************************************************************************
			 * functions for completeness 
			 *****************************************************************************************/

			void Init();

			void Print();

			/**
			 * @brief Clear : Notice:  Remember to Clear the chain after use it.   If you use combined_RC command, it will build a "new" Particle. So you need to delete this point with Clear() function.
			 * I didn't write Clear() into deconstructor because it may cause some trouble when transfer the chain to other functions.
			 */
			void Clear();

			/*****************************************************************************************
			 * functions for basic setting 
			 *****************************************************************************************/

			/**
			 * @brief Set_Nav_From_MC_To_RC : set Nav
			 *
			 * @param relation
			 */
			void Set_Nav_From_MC_To_RC(LCRelationNavigator* relation);

			/**
			 * @brief Set_Nav_From_RC_To_MC : set Nav
			 *
			 * @param relation
			 */
			void Set_Nav_From_RC_To_MC(LCRelationNavigator* relation);

			/**
			 * @brief Set_RC : if having the MC part, with this command, it can first get all corresponding ReconstructedParticles from the final states in the MC parts, 
			 * then set all RC part structure, it also includes Set_End_Type(), Set_Flat_RC(), Set_MC_From_Flat_RC(), Set_Extra_MC(), Set_Combined_RC()
			 */
			void Set_RC();

			/**
			 * @brief Set_Flat_RC :  get all posible ReconstructedParticle , it collects all ReconstructedParticles in the chain and removes duplicated ones  
			 */
			void Set_Flat_RC();

			/**
			 * @brief Set_Combined_RC : sum all ReconstructedParticle into a new particle in each chains, so that you can compare the energy/momentum loss between original MC particle and ReconstructedParticles. This will generate a new ReconstructedParticle in the heap, so remember to use Clear()
			 */
			void Set_Combined_RC();

			/**
			 * @brief Set_MC_From_Flat_RC  : after having ReconstructedParticles, using this to get corresponding MCParticles
			 */
			void Set_MC_From_Flat_RC();

			/**
			 * @brief Set_Extra_MC : set the extra contributions for the ReconstructedParticle from other particles that not in this chain
			 */
			void Set_Extra_MC();

			/**
			 * @brief Set_Trim_Chain : trim duplicated particles in the decay chain, this is more useful in the Hadron Collider
			 */
			void Set_Trim_Chain();

			/**
			 * @brief Minimize_Trim_Chain : minimize the trim chain
			 */
			void Minimize_Trim_Chain();

			/**
			 * @brief Set_MC_End : remove duplicated MC final states ()
			 */
			void Set_MC_End();

			/**
			 * @brief Set_End_Type : build relation between MC final states and ReconstructedParticles 
			 */
			void Set_End_Type();

			/**
			 * @brief Set_MC : using ReconstructedParticle to set MCParticle part
			 */
			void Set_MC();

			/*****************************************************************************************
			 * functions for building 
			 *****************************************************************************************/

			/**
			 * @brief Build_Chain : build MC parts structure
			 *
			 * @param input
			 */
			void Build_Chain(MCParticle* input);

			/**
			 * @brief Recurse_Chain : get decay particles from the input
			 *
			 * @param input
			 */
			void Recurse_Chain(MCParticle* input);

			/**
			 * @brief Push_Back : recurse function in the Recurse_Chain()
			 *
			 * @param input
			 */
			void Push_Back(MCParticle* input);

			/**
			 * @brief TraceBack_Chain : get particles where the input is decayed from, it is in the opposite direction of the Recurse_Chain().
			 * So if the input particle is in the middle position, use Recurse_Chain, will get what this input decays, 
			 * using TraceBack_Chain will get where does this input coming from. combining two functions will get a complete decay chain from the hard-scattering to detector simulation.
			 *
			 * @param input
			 */
			void TraceBack_Chain(MCParticle* input);

			/**
			 * @brief Push_Forward : recurse function in the TraceBack_Chain()
			 *
			 * @param input
			 */
			void Push_Forward(MCParticle* input);

			/**
			 * @brief Build_Chain_FromRCFS : bulid Reconstructed part structure
			 *
			 * @param input
			 */
			void Build_Chain_FromRCFS(ReconstructedParticle* input);

	};
}
#endif

