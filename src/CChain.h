/**
 * @file CChain.h
 * @brief create decay chain for any particles
 * @author Yan Wang - yan.wang@desy.de
 * @version 1.0
 * @date 2018-11-12
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
#ifndef CCHAIN_H
#define CCHAIN_H  
#include "CChain_Single.h"

namespace ToolSet{
	typedef std::vector<Chain_Type>  Chain_Type_Vec; 

	/**
	 * @brief This is the vector of CChain_Single
	 * This class is the vector of CChain_Single, for one input particle will generate one CChain_Single
	 * Functions are provided to make the vector operation more easily. 
	 */
	class CChain_Vec{
		private:
			int                        _chain_num;
			std::vector<CChain_Single> _chain_vec; 
			LCRelationNavigator*       _nav_from_rc_to_mc;
			LCRelationNavigator*       _nav_from_mc_to_rc;
		public: 

			/**
			 * @brief CChain_Vec ： Constructor
			 */
			CChain_Vec(){
				Init();
			}

			/*****************************************************************************************
			 * return private value  
			 *****************************************************************************************/
			/**
			 * @brief Num : number of the chain in this vector
			 *
			 * @return : int 
			 */
			int Num(){
				return(_chain_num);
			}

			/**
			 * @brief Chain_Vec : 
			 *
			 * @return : all chains in this vector
			 */
			std::vector<CChain_Single> Chain_Vec(){
				return(_chain_vec);
			}

			/**
			 * @brief Nav_From_MC_to_RC : Navigator
			 *
			 * @return : nav from MC to RC
			 */
			LCRelationNavigator* Nav_From_MC_to_RC(){
				return(_nav_from_mc_to_rc);
			}

			/**
			 * @brief Nav_from_RC_to_MC : Navigator
			 *
			 * @return : nav from RC to MC
			 */
			LCRelationNavigator* Nav_from_RC_to_MC(){
				return(_nav_from_rc_to_mc);
			}

			/*****************************************************************************************
			 * return member value  
			 *****************************************************************************************/

			/**
			 * @brief Get_MCInput : get input MC particles in all chains
			 *
			 * @return 
			 */
			std::vector<MCParticle*>                                        Get_MCInput();
			/**
			 * @brief Get_RCInput : get all input RC particles in all chains
			 *
			 * @return 
			 */
			std::vector<ReconstructedParticle*>                             Get_RCInput();
			/**
			 * @brief Get_MCHead : get the hard-scattering particles for each chain
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_MCHead();
			/**
			 * @brief Get_MCNextHead : get first decay products from the hard-scattering particles in all chains
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_MCNextHead();
			/**
			 * @brief Get_MCNextNextHead : get first decay products from the hard-scattering particles in all chains
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_MCNextNextHead();
			/**
			 * @brief Get_Chain : get all MC particles in each chains (from hard-scattering to final simulated particle, has duplicated ones)
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_Chain();
			/**
			 * @brief Get_Trim_Chain : get trimed MC particles in each chains (from hard-scattering to final simulated particle), this is more useful in the Hadron Collider.
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_Trim_Chain();
			/**
			 * @brief Get_End : get all final states including MCParticles and the corresponding  ReconstructedParticle (as well as their weights) in each chains. 
			 *
			 * @return 
			 */
			Chain_Type_Vec                                                  Get_End();
			/**
			 * @brief Get_MCEnd : get MC particles which will contribute to the ReconstructedParticle in each chains. 
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_MCEnd();
			/**
			 * @brief Get_RC : get ReconstructedParticle in each chains, it organizes as for each particle in the MCEnd, it has a MCparticle---vector of <(weight, ReconstructedParticle)>
			 *
			 * @return 
			 */
			std::vector<std::vector<ToolSet::Chain_End_Type > >             Get_RC();
			/**
			 * @brief Get_RC_Particle : get ReconstructedParticle in each chains， it organizes as for each particle in the MCEnd, it has a MCParticle -- vector of <ReconstructedParticles>  
			 *
			 * @return 
			 */
			std::vector<std::vector<std::vector<ReconstructedParticle*> > > Get_RC_Particle();
			/**
			 * @brief Get_RC_Weight : get ReconstructedParticle's weight in each chains， it organizes as for each particle in the MCEnd, it has a MCParticle -- vector of <weight>  
			 *
			 * @return 
			 */
			std::vector<std::vector<std::vector<float> > >                  Get_RC_Weight();
			/**
			 * @brief Get_Flat_RC :  get all posible ReconstructedParticle in each chains, comparing Get_RC(), it removes duplicated ones  
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> >               Get_Flat_RC();
			/**
			 * @brief Get_Extra_MC : show the extra contributions for the ReconstructedParticle from other particles that not in each chains
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_Extra_MC();
			/**
			 * @brief Get_Combined_RC : sum all ReconstructedParticle into a new particle in each chains, so that you can compare the energy/momentum loss between original MC particle and ReconstructedParticles. This will generate a new ReconstructedParticle in the heap, so remember to use Clear() function after using CChain_Vec
			 *
			 * @return 
			 */
			std::vector<ReconstructedParticle*>								Get_Combined_RC();
			/**
			 * @brief Get_FromRC_MC : get MCParticles from ReconstructedParticles with other direction linker in each chains.  It's important for cross check particle reconstruction.
			 *
			 * @return 
			 */
			std::vector<std::vector<MCParticle*> >                          Get_FromRC_MC();

			/**
			 * @brief Get_SpecialRC : get a special ReconstructedParticle with parameters
			 *
			 * @param pdg     : particle type
			 * @param label  : using "weight/energetic/first" in the link  to select ReconstructedParticle from MCparticle
			 * @param output  :
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> >              Get_SpecialRC(int pdg,std::string label);
			/**
			 * @brief Get_EnergeticRC : use Get_SpecialRC to get most energetic ReconstructedParticle
			 *
			 * @param pdg
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> >               Get_EnergeticRC(int pdg);
			/**
			 * @brief Get_WeightedRC : use Get_SpecialRC to get most weight ReconstructedParticle
			 *
			 * @param pdg
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> >               Get_WeightedRC(int pdg);
			/**
			 * @brief Get_FirstRC :  use Get_SpecialRC to get first ReconstructedParticle
			 *
			 * @param pdg
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> >               Get_FirstRC(int pdg);
			/**
			 * @brief Get_SpecialRC_Between_Different_RC_Link : get symmetry difference for using different criterions (weight/energy/first place) to select ReconstructedParticles
			 *
			 * @param pdg
			 * @param label1
			 * @param label2
			 *
			 * @return 
			 */
			std::vector<std::vector<ReconstructedParticle*> >               Get_SpecialRC_Between_Different_RC_Link(int pdg, std::string label1, std::string label2);

			/*****************************************************************************************
			 * functions for completeness 
			 *****************************************************************************************/

			void                                                            Init();

			/**
			 * @brief Print : Print the chain content, not well defined, need to update
			 */
			void                                                            Print() ;

			/**
			 * @brief Clear 
			 * Notice:  Remember to Clear the chain after use it.   If you use combined_RC command, it will build a "new" Particle. So you need to delete this point with Clear() function.
			 * I didn't write Clear() into deconstructor because it may cause some trouble when transfer the chain to other functions.
			 */
			void                                                            Clear() ;

			/*****************************************************************************************
			 * functions for basic setting 
			 *****************************************************************************************/

			/**
			 * @brief Set_Nav_From_MC_To_RC : set Nav, input is MC, return the related ReconstructedParticle 
			 *
			 * @param input
			 */
			void  Set_Nav_From_MC_To_RC(LCRelationNavigator* input);
			/**
			 * @brief Set_Nav_From_RC_To_MC : set Nav, input is ReconstructedParticle, return the related MCParticle
			 *
			 * @param input
			 */
			void  Set_Nav_From_RC_To_MC(LCRelationNavigator* input);
			/**
			 * @brief Set_Nav : set both Navgators, first is from MC_to_RC, second is from RC_to_MC
			 *
			 * @param nav_MC_To_RC
			 * @param nav_RC_To_MC
			 */
			void  Set_Nav(LCRelationNavigator* nav_MC_To_RC, LCRelationNavigator* nav_RC_To_MC);

			/**
			 * @brief Set_ChainVec : basic function for CChain.  Use input vector of MCParticles to generate MC decay chain for these particles
			 *
			 * @param MCs
			 */
			void  Set_ChainVec(std::vector<MCParticle*> MCs);
			/**
			 * @brief Set_ChainVec : basic function for CChain.  Use input vector of MCParticles to generate MC decay chain for these particles, and also find related ReconstructedParticles 
			 *
			 * @param MCs
			 * @param from_mc_to_rc
			 */
			void  Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* from_mc_to_rc);
			/**
			 * @brief Set_ChainVec : basic function for CChain.  Use input vector of MCParticles to generate MC decay chain for these particles, and also find related ReconstructedParticles, also use backward linker to get
			 * MCParticles from these ReconstructedParticles
			 *
			 * @param MCs
			 * @param from_mc_to_rc
			 * @param from_rc_to_mc
			 */
			void  Set_ChainVec(std::vector<MCParticle*> MCs, LCRelationNavigator* from_mc_to_rc, LCRelationNavigator* from_rc_to_mc);

			/**
			 * @brief Set_ChainVec_FromMCFS : basic function for CChain.  Use input vector of ReconstructedParticles to generate a chain for further use 
			 *
			 * @param MCs
			 */
			void  Set_ChainVec_FromMCFS(std::vector<MCParticle*> MCs) ;
			/**
			 * @brief Set_ChainVec_FromRCFS : basic function for CChain.  Use input vector of ReconstructedParticles to generate a chain for further use 
			 *
			 * @param RCs
			 */
			void  Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs) ;
			/**
			 * @brief Set_ChainVec_FromRCFS : basic function for CChain.  Use input vector of ReconstructedParticles to generate a chain, and also find the MCParticles which are  related to input RCParticles 
			 *
			 * @param RCs
			 * @param input
			 */
			void  Set_ChainVec_FromRCFS(std::vector<ReconstructedParticle*> RCs, LCRelationNavigator* input) ;

			/**
			 * @brief Set_RC : using MC chain to set ReconstructedParticle part
			 */
			void  Set_RC();
			/**
			 * @brief Set_MC : using ReconstructedParticle to set MCParticle part
			 */
			void  Set_MC();

	}; 
}
#endif

