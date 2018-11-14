/**
 * @file CMC.h
 * @brief 
 * @author Yan Wang - yan.wang@desy.de
 * @version 1.0
 * @date 2018-11-14
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
#ifndef CMC_H
#define CMC_H  
#include <iostream>
#include <fstream>
#include <set>

#include <vector>
#include <stack>
#include <cmath>

//LCIO
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/Vertex.h>
#include <IMPL/MCParticleImpl.h>
#include "UTIL/PIDHandler.h"
#include "LCIOSTLTypes.h"

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include "TRandom.h"
#include "CFormat.h"
#include "CData_Type.h"
#include "CFlavor.h"


using namespace lcio;

namespace ToolSet{
	/**
	 * @brief operator+ : same with CMC::Add, add four momentum of two MCParticle
	 * Notice: this will use the "new" keyword, and generate a new MCParticle in the heap, so remember to delete this pointer
	 *
	 * @param MC1
	 * @param MC2
	 *
	 * @return 
	 */
	MCParticle& operator+(const MCParticle& MC1,const MCParticle& MC2);

	/**
	 * @brief : functions for MCParticles
	 */
	class CMC{
		private:
			static float _collider_energy;
			static float _beam_energy;
			static float _beam_cross_angle;
		public:
			/**
			 * @brief Get_Collider_Energy : changing the collider energy, default is 500 GeV
			 * Notice: when using the CRC::InVisible(), it also will load the value from here
			 *
			 * @return 
			 */
			static void  Set_Collider_Energy(float input);
			/**
			 * @brief Set_Beam_Cross_Angle : changing beam crossing angle, default is 0.007
			 * Notice: when using the CRC::InVisible(), it also will load the value from here
			 *
			 *
			 * @param input
			 */
			static void  Set_Beam_Cross_Angle(float input);

			/**
			 * @brief Get_Collider_Energy : show the collider energy when generating
			 *
			 * @return 
			 */
			static float Get_Collider_Energy();
			/**
			 * @brief Get_Beam_Energy : show the energy for initial beam after having the detector simulation.
			 * Notice: for ILC, there will be a x-direction boost, so the beam energy is not collider_energy/2 any more, but a little larger.
			 *
			 * @return 
			 */
			static float Get_Beam_Energy();
			/**
			 * @brief Get_Beam_Cross_Angle : get the collider crossing angle 
			 *
			 * @return 
			 */
			static float Get_Beam_Cross_Angle();
			// functions for normal calculation
			/**
			 * @brief NewParticle : generate a new MCParticle
			 * Notice: this will use the "new" keyword, and generate a new MCParticle in the heap, so remember to delete this pointer
			 *
			 * @param px
			 * @param py
			 * @param pz
			 * @param E
			 * @param test : this is only for function overload, it doesn't have really usage, so you can provide any MCParticle* type pointer
			 *
			 * @return 
			 */
			static MCParticle* NewParticle(float px, float py, float pz,float E,MCParticle* test);
			/**
			 * @brief NewParticle : generate a new MCParticle
			 * Notice: this will use the "new" keyword, and generate a new MCParticle in the heap, so remember to delete this pointer
			 *
			 * @param p
			 * @param test : this is only for function overload, it doesn't have really usage, so you can provide any MCParticle* type pointer
			 *
			 * @return 
			 */
			static MCParticle* NewParticle(TLorentzVector &p, MCParticle* test);

			/**
			 * @brief Add : add four momentum of two MCParticle
			 * Notice: this will use the "new" keyword, and generate a new MCParticle in the heap, so remember to delete this pointer
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static MCParticle* Add(const MCParticle* MC1,const MCParticle* MC2);
			/**
			 * @brief Minus : minus four momentum of two MCParticle
			 * Notice: this will use the "new" keyword, and generate a new MCParticle in the heap, so remember to delete this pointer
			 *  
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static MCParticle* Minus(const MCParticle* MC1,const MCParticle* MC2);
			/**
			 * @brief Equal : generate a new MCParticle equal to the input one
			 * This is different from use "=", "=" will give the pointer address to the new pointer, they are still pointing to the same particle. But "equal" will generate a new MCParticle, whose property is the same with the old
			 * one.
			 * Notice: this will use the "new" keyword, and generate a new MCParticle in the heap, so remember to delete this pointer
			 *         
			 *
			 * @param MC1
			 *
			 * @return 
			 */
			static MCParticle* Equal(const MCParticle* MC1) ;
			/**
			 * @brief Minus_To_Lorentz : minus four momentum of two MCParticle, return a TLorentzVector of the four momentum 
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static TLorentzVector  Minus_By_Lorentz(const MCParticle* MC1, const MCParticle* MC2) ;

			/**
			 * @brief Compare_as_E : compare funcion by the energy for MCParticle, equals to < operator 
			 *
			 * @param i
			 * @param j
			 *
			 * @return 
			 */
			static bool Compare_as_E(const MCParticle* i, const MCParticle* j){
				return (i->getEnergy()>j->getEnergy());
			}

			/**
			 * @brief Compare_as_Angle : compare funcion by the costheta for MCParticle, equals to < operator 
			 *
			 * @param i
			 * @param j
			 *
			 * @return 
			 */
			static bool Compare_as_Angle(const MCParticle* i, const MCParticle* j){
				float cos_i=Cal_CosTheta(i);
				float cos_j=Cal_CosTheta(j);
				return (cos_i  > cos_j);
			}

			/**
			 * @brief Compare_as_Pair : compare function by any value paired to MCParticle*
			 *
			 * @param i
			 * @param j
			 *
			 * @return 
			 */
			static bool Compare_as_Pair(const std::pair<float,MCParticle*> &i, const std::pair<float,MCParticle*> &j){
				return ((i.first) > (j.first));
			}

			/**
			 * @brief  : calculate Magnitude of the four momentum
			 *
			 * @tparam TMag
			 * @param MC
			 *
			 * @return 
			 */
			template<typename TMag>
				static float Cal_Mag   (TMag MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.Mag());
				}

			/**
			 * @brief Cal_P : calculate the magnitude of the three momentum, |vect{P}|
			 * 
			 * @tparam TP
			 * @param MC
			 *
			 * @return 
			 */
			template<typename TP>
				static float Cal_P (TP MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.P());
				}

			/**
			 * @brief Cal_Vect : get three momentum
			 *
			 * @tparam TVect
			 * @param MC
			 *
			 * @return 
			 */
			template<typename TVect>
				static TVector3 Cal_Vect(TVect MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.Vect());
				}

			/**
			 * @brief Cal_PT : calculate pt to the lab frame
			 *
			 * @tparam TPT
			 * @param MC
			 *
			 * @return 
			 */
			template<typename TPT>
				static float Cal_PT(TPT MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum() ,MC->getEnergy());
					return(vec.Perp());
				}

			/**
			 * @brief  : calculate pt to the reference axis
			 *
			 * @tparam TPT
			 * @param 
			 * @param 
			 *
			 * @return 
			 */
			template<typename TPT>
				static float Cal_PT    (TPT MC    , TPT Ref    ){
					TLorentzVector vec =TLorentzVector(MC->getMomentum() ,MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					return(vec.Perp(ref.Vect()));
				}



			/**
			 * @brief Cal_CosTheta : calculate costheta
			 *
			 * @tparam TTheta
			 * @param MC
			 *
			 * @return 
			 */
			template<typename TTheta>
				static float Cal_CosTheta(TTheta  MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.CosTheta());
				}

			/**
			 * @brief Cal_CosTheta : calculate costheta to the reference axis
			 *
			 * @tparam TTheta
			 * @param MC
			 * @param Ref
			 *
			 * @return 
			 */
			template<typename TTheta>
				static float Cal_CosTheta(TTheta  MC, TTheta  Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float angle=vec.Angle(ref.Vect());
					return(TMath::Cos(angle));
				}

			/**
			 * @brief Cal_Angle : calculate the angle of radian with acos to the reference axis
			 *
			 * @tparam TAngle
			 * @param MC
			 * @param Ref
			 *
			 * @return 
			 */
			template<typename TAngle>
				static float Cal_Angle(TAngle MC, TAngle Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float angle=vec.Angle(ref.Vect());
					return(angle);
				}

			/**
			 * @brief Cal_Angle_Deg : calculate the angle of degree with acos to the reference axis
			 *
			 * @tparam TAngle
			 * @param MC
			 * @param Ref
			 *
			 * @return 
			 */
			template<typename TAngle>
				static float Cal_Angle_Deg(TAngle MC, TAngle Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float angle=vec.Angle(ref.Vect());
					return(TMath::RadToDeg()*angle);
				}

			/**
			 * @brief Cal_Azimuth : calculate azimuth angle in the lab frame
			 *
			 * @tparam TPhi
			 * @param MC
			 *
			 * @return 
			 */
			template<typename TPhi>
				static float Cal_Azimuth(TPhi MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.Phi());
				}


			/**
			 * @brief Cal_Azimuth : calculate aximuth anlge to the reference axis
			 *
			 * @tparam TPhi
			 * @param MC
			 * @param Ref
			 *
			 * @return 
			 */
			template<typename TPhi>
				static float Cal_Azimuth(TPhi MC, TPhi Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					return(vec.DeltaPhi(ref));
				}


			/**
			 * @brief Cal_Acoplanarity : calculate acoplanarity
			 * acoplan = pi - |phi|
			 *
			 * @tparam TPhi
			 * @param MC
			 * @param Ref
			 *
			 * @return 
			 */
			template<typename TPhi>
				static float Cal_Acoplanarity(TPhi MC, TPhi Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float phi_open = vec.DeltaPhi(ref);
					float phi_a    = 3.1415926 - std::abs(phi_open);
					return(phi_a);
				}



			/**
			 * @brief Cal_IsolationAngle : calculate minimal isolation angle
			 *
			 * @param MC
			 * @param Ref
			 *
			 * @return 
			 */
			static float Cal_IsolationAngle(MCParticle* MC, std::vector<MCParticle*> Ref, float minimal_energy_in_the_cone=1, float minimal_angle_from_input=2){
				// get the angle between MC and other particle, then rank the angle from small to large
				std::vector<std::pair<float,MCParticle*> >Ref_angle;
				for(unsigned int i=0;i<Ref.size();i++){
					if(MC==Ref[i]){continue;}
					std::pair<float,MCParticle*> pair_tmp = std::make_pair(Cal_Angle_Deg(MC,Ref[i]),Ref[i]);
					Ref_angle.push_back(pair_tmp);
				}
				std::sort(Ref_angle.begin(),Ref_angle.end(),Compare_as_Pair);
				for(unsigned int i=0;i<Ref_angle.size();i++){
				}

				// make a cone around the input MC, if the sum of the energies inside the cone is larger than the minimal_energy_in_the_cone, give the angle value
				float sum_energy=0;
				float angle=0;
				for(unsigned int i=0;i<Ref_angle.size();i++){
					sum_energy = sum_energy + Ref_angle[i].second->getEnergy();
					angle=Ref_angle[i].first;
					if(sum_energy>minimal_energy_in_the_cone){
						if(angle>minimal_angle_from_input){
							return(angle-0.01);
						}
						else{
							return(angle);
						}
					}
				}
				return(180);
			}

			/**
			 * functions for get basic particle properties 
			 */
			/**
			 * @brief Get_Parents_Number : parents number
			 *
			 * @param input
			 *
			 * @return 
			 */
			static int  Get_Parents_Number(MCParticle* input)               ;
			/**
			 * @brief Get_Daughters_Number : daughter number
			 *
			 * @param input
			 *
			 * @return 
			 */
			static int  Get_Daughters_Number(MCParticle* input)             ;
			/**
			 * @brief Get_ParentsPID : parents PDG code
			 *
			 * @param MC
			 *
			 * @return 
			 */
			static std::vector<int>         Get_ParentsPID(MCParticle* MC) ;
			/**
			 * @brief Get_DaughtersPID : daughter's PDG code
			 *
			 * @param MC
			 *
			 * @return 
			 */
			static std::vector<int>         Get_DaughtersPID(MCParticle* MC) ;


			// functions for Judge particle status 
			/**
			 * @brief Status_Beam_Energy : whether the input energy equals to the beam energy
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Beam_Energy(MCParticle* input)               ;
			/**
			 * @brief Status_Has_Parent : whether has the parents
			 * Notice: for current ILD event generation, 
			 * if no parents -> initial beam
			 * have parents, but no grand parents -> beam after ISR and ISR photons
			 * have grand parents, no parents of grand parents -> hard scattering particle generated in the Whizard
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Has_Parent(MCParticle* input)                ;
			/**
			 * @brief Status_Has_GrandParent : whether has the grand parents
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Has_GrandParent(MCParticle* input)           ;
			/**
			 * @brief Status_Has_Daughter : whether has the daughter
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Has_Daughter(MCParticle* input)              ;
			/**
			 * @brief Status_Has_GrandDaughter : whether has the grand daughter
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Has_GrandDaughter(MCParticle* input)         ;
			/**
			 * @brief Status_Is_MS : whether is a intermediate particle, (generator status==2)
			 *
			 * @param input
			 *
			 * @return 
			 */


/*****************************************************************************************
 * Readme,  the definition used in this file.
 * getGeneratorStatus = 2  ->  is generated by Pythia/whizard,  resonance
 * getGeneratorStatus = 1  ->  is generated by Pythia, final stable states.
 * getGeneratorStatus = 0  ->  is not generated by Pythia,  but created in the simulation
 *                             this always equal to "simulator status -- s (the first s)", 
 *                                 or equal to using "isCreatedInSimulation()"
 * isOverlay()             ->  is generated in the overlay
 *
 * isStopped ()            ->  the particle lost all k
 * isDecayedInTracker ()   ->  the particle decayed or interacted in a tracking region. 
 * isDecayedInCalorimeter()->  the particle decayed or interacted (non-continuous interaction, particle terminated) in non-tracking region. 
 * hasLeftDetector ()      ->  the particle left the world volume undecayed. 
 *
 *
 * other status not offen used.
 *
 * isBackscattering()      ->  the particle was created by the simulator as a result of an interaction or decay in non-tracking region, e.g. 
 *****************************************************************************************/
			static bool Status_Is_MS(MCParticle* input)                     ;
			/**
			 * @brief Status_Is_TFS : whether is a final state, (Pythia final states or simulation final states)
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Is_TFS(MCParticle* input)                    ;
			/**
			 * @brief Status_Is_Pythia_TFS :whether is a Pythia stable particle
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Is_Pythia_TFS(MCParticle* input)             ;
			/**
			 * @brief Status_Is_Detector_TFS : whether is a possible detector simulated final state 
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Is_Detector_TFS(MCParticle* input)           ;
			/**
			 * @brief Status_Is_Pythia : whether a possible  final state generated from Pythia
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Is_Pythia(MCParticle* input)                 ;
			/**
			 * @brief Status_Is_Overlay : Whether generated from Overlay
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Is_Overlay(MCParticle* input)                ;
			/**
			 * @brief Status_Is_Overlay_DFS : whether a possible Overlay final states 
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Status_Is_Overlay_DFS(MCParticle* input)            ;
			static bool Status_Is_Stopped(MCParticle* input)                ;
			static bool Status_Is_DecayInTracker(MCParticle* input)         ;
			static bool Status_Is_DecayInCalorimeter(MCParticle* input)     ;
			static bool Status_Is_LeftDetector(MCParticle* input)     ;

			// functions for get special particle 
			static bool Status_Is_Electron(MCParticle* input)               ;
			static bool Status_Is_Muon(MCParticle* input)                   ;
			static bool Status_Is_Tau(MCParticle* input)                    ;
			static bool Status_Is_Lepton(MCParticle* input)                 ;
			static bool Status_Is_Neutrino(MCParticle* input)               ;
			static bool Status_Is_HeavyBoson(MCParticle* input)             ;
			static bool Status_Is_Photon(MCParticle* input)                 ;
			static bool Status_Is_NeutralHadron(MCParticle* input)          ;
			static bool Status_Is_ChargedHadron(MCParticle* input)          ;
			static bool Status_Is_Gluon(MCParticle* input)                  ;
			static bool Status_Is_Quark(MCParticle* input)                  ;
			static bool Status_Is_LightQuark(MCParticle* input)             ;
			static bool Status_Is_HeavyQuark(MCParticle* input)             ;
			static bool Status_Is_TopQuark(MCParticle* input)               ;
			static bool Status_Is_BottomQuark(MCParticle* input)            ;
			static bool Status_Is_CharmQuark(MCParticle* input)             ;

			// functions for Judge particle type 
			/**
			 * @brief Judge_Is_Beam : whether it is the beam initial electron/positron
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Judge_Is_Beam(MCParticle* input)                    ;
			/**
			 * @brief Judge_Parents_Are_Beam : whether its parents are initial beam (i.e. the input is the ISR or the beam after ISR)
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Judge_Parents_Are_Beam(MCParticle* input)           ;
			/**
			 * @brief Judge_GrandParents_Are_Beam : whether its grand parents are initial beam (i.e. input is the hard-scattering states)
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Judge_GrandParents_Are_Beam(MCParticle* input)      ;
			/**
			 * @brief Judge_Is_IS_Electron : is the electron/positron after the ISR
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Judge_Is_IS_Electron(MCParticle* input)             ;
			/**
			 * @brief Judge_Is_IS_Photon : is the ISR photon
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Judge_Is_IS_Photon(MCParticle* input)               ;

			/**
			 * @brief Judge_HardScattering_FS : is the hard-scattering states (including ISR photon)
			 *
			 * @param input
			 *
			 * @return 
			 */
			static bool Judge_HardScattering_FS(MCParticle* input)          ;
			static bool Judge_HardScattering_Next_FS(MCParticle* input)     ;
			static bool Judge_HardScattering_Next_Next_FS(MCParticle* input);
			static bool Judge_OnlyPythiaShowering_FS(MCParticle* input)     ;
			static bool Judge_PythiaShowering_FS(MCParticle* input)         ;
			static bool Judge_PythiaShowering_All(MCParticle* input)        ;
			static bool Judge_OnlyDetectorSimulating_FS(MCParticle* input)  ;
			static bool Judge_DetectorSimulating_FS(MCParticle* input)      ;
			static bool Judge_Overlay_FS(MCParticle* input)                 ;
			static bool Judge_Has_Overlay(std::vector<MCParticle*> input)   ;
			static bool Judge_All_FS(MCParticle* input)                     ;


			// functions for get special particle vector 
			//
			static std::vector<MCParticle*> Get_Particle(bool (*Judge)(MCParticle*), std::vector<MCParticle*> AllMC) ;

			static std::vector<MCParticle*> Get_MCParticle(LCCollection* AllMC) ;

			// for the final states 
			static std::vector<MCParticle*> Get_MC_HardScattering_FS(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_PythiaShowering_FS(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_OnlyPythiaShowering_FS(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_DetectorSimulating_FS(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_OnlyDetectorSimulating_FS(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_Overlay_FS(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_All_FS(std::vector<MCParticle*> MCs) ;

			// for all related particle
			static std::vector<MCParticle*> Get_MC_PythiaShowering_All(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_DetectorSimulating_All(std::vector<MCParticle*> MCs) ;

			static std::vector<MCParticle*> Get_MC_Overlay_All(std::vector<MCParticle*> MCs) ;


			// for chain 
			static std::vector<MCParticle*> MCToPythiaShowering(MCParticle* input);

			static std::vector<MCParticle*> MCToHardScattering(MCParticle* input);

			static void                     Get_MC_HardScattering_Sort(std::vector<MCParticle*> MCs, std::vector<MCParticle*> &ISRlepton , std::vector<MCParticle*> &ISRphoton, std::vector<MCParticle*> &ObjetctParticle) ;

			// for ID 
			static std::vector<MCParticle*> Get_MCParticleType(std::vector<MCParticle*> MCs,signed int PDG) ;
			static std::vector<MCParticle*> Get_MCParticleType_Abs(std::vector<MCParticle*> MCs,signed int PDG) ;
			static std::vector<MCParticle*> Get_MCParticleType(std::vector<MCParticle*> MCs,std::string PDG) ;

			static float                    Get_DecayChannel(MCParticle* input) ;

			static void                     Remove_Duplication(std::vector<MCParticle*> &MCs) ;

			static std::vector<MCParticle*> Pass_DetectorAngle(std::vector<MCParticle*> &MCs) ;
			static MCParticle*              Get_Visible(std::vector<MCParticle*> in);
			static MCParticle*              Get_InVisible(std::vector<MCParticle*> in);
			static TLorentzVector           Get_Visible_To_Lorentz(std::vector<MCParticle*> in);
			static TLorentzVector           Get_InVisible_To_Lorentz(std::vector<MCParticle*> in);
			static std::vector<MCParticle*> Get_Isolated(std::vector<MCParticle*> input,std::vector<MCParticle*> all, std::vector<MCParticle*> left) ;
			static bool                     IsInCone( MCParticle* lep, MCParticle* pfo, float angle_cut) ;
	};

}
#endif

