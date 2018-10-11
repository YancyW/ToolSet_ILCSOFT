#pragma once
#ifndef CMC_H
#define CMC_H  
#define BEAM_ENERGY 500
#define BEAM_ANGLE  0.007
#include <iostream>
#include <fstream>
#include <set>

#include <vector>
#include <stack>

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
	MCParticle& operator+(const MCParticle& MC1,const MCParticle& MC2);

	class CMC{
		public:
			// functions for normal calculation
			static MCParticle* NewParticle(float px, float py, float pz,float E,MCParticle* test);

			static MCParticle* Add(const MCParticle* MC1,const MCParticle* MC2);
			static MCParticle* Minus(const MCParticle* MC1,const MCParticle* MC2);
			static MCParticle* Equal(const MCParticle* MC1) ;
			static TLorentzVector  Minus_To_Lorentz(const MCParticle* MC1, const MCParticle* MC2) ;

			static bool Compare_as_E(MCParticle* i, MCParticle* j){
				return (i->getEnergy()>j->getEnergy());
			}

			/*
			   template<typename TCAngle>
			   static bool Compare_as_Angle(std::pair<float,TCAngle> i, std::pair<float,TCAngle> j){
			   return (i.first>j.first);
			   }
			   */

			static bool Compare_as_Angle(const std::pair<float,MCParticle*> &i, const std::pair<float,MCParticle*> &j){
				return ((i.first) < (j.first));
			}

			template<typename TMag>
				static float Cal_Mag   (TMag MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.Mag());
				}

			template<typename TP>
				static float Cal_P (TP MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.P());
				}

			template<typename TVect>
				static TVector3 Cal_Vect(TVect MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.Vect());
				}

			template<typename TPT>
				static float Cal_PT(TPT MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum() ,MC->getEnergy());
					return(vec.Perp());
				}

			template<typename TPT>
				static float Cal_PT    (TPT MC    , TPT Ref    ){
					TLorentzVector vec =TLorentzVector(MC->getMomentum() ,MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					return(vec.Perp(ref.Vect()));
				}



			template<typename TTheta>
				static float Cal_CosTheta(TTheta  MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.CosTheta());
				}

			template<typename TTheta>
				static float Cal_CosTheta(TTheta  MC, TTheta  Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float angle=vec.Angle(ref.Vect());
					return(TMath::Cos(angle));
				}

			template<typename TAngle>
				static float Cal_Angle(TAngle MC, TAngle Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float angle=vec.Angle(ref.Vect());
					return(angle);
				}

			template<typename TAngle>
				static float Cal_Angle_Deg(TAngle MC, TAngle Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float angle=vec.Angle(ref.Vect());
					return(TMath::RadToDeg()*angle);
				}

			template<typename TPhi>
				static float Cal_Azimuth(TPhi MC){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					return(vec.Phi());
				}


			template<typename TPhi>
				static float Cal_Azimuth(TPhi MC, TPhi Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					return(vec.DeltaPhi(ref));
				}


			template<typename TPhi>
				static float Cal_Acoplanarity(TPhi MC, TPhi Ref){
					TLorentzVector vec =TLorentzVector(MC->getMomentum(),MC->getEnergy());
					TLorentzVector ref =TLorentzVector(Ref->getMomentum(),Ref->getEnergy());
					float phi_open = vec.DeltaPhi(ref);
					float phi_a    = 3.1415926 - std::abs(phi_open);
					return(phi_a);
				}



			static float Cal_IsolationAngle(MCParticle* MC, std::vector<MCParticle*> Ref){
				std::vector<std::pair<float,MCParticle*> >Ref_angle;
				for(unsigned int i=0;i<Ref.size();i++){
					std::pair<float,MCParticle*> pair_tmp = std::make_pair(Cal_Angle_Deg(MC,Ref[i]),Ref[i]);
					Ref_angle.push_back(pair_tmp);
				}
				std::sort(Ref_angle.begin(),Ref_angle.end(),Compare_as_Angle);
				for(unsigned int i=0;i<Ref_angle.size();i++){
				}

				float sum_energy=0;
				float angle=0;
				for(unsigned int i=0;i<Ref_angle.size();i++){
					sum_energy = sum_energy + Ref_angle[i].second->getEnergy();
					angle=Ref_angle[i].first;
					if(sum_energy>1){
						if(angle>2){
							return(angle-0.1);
						}
						else{
							return(angle);
						}
					}
				}
				return(180);
			}
			/*
			   template<typename TISAngle>
			   static float Cal_IsolationAngle(TISAngle MC, std::vector<TISAngle> Ref){
			   float min_angle=10000;
			   std::vector<std::pair<float,TISAngle> >Ref_angle;
			   for(unsigned int i=0;i<Ref.size();i++){
			   std::pair<float,TISAngle> pair_tmp = std::make_pair(Cal_Angle(MC,Ref[i]),Ref[i]);
			   Ref_angle.push_back(pair_tmp);
			   }
			   std::stable_sort(Ref_angle.begin(),Ref_angle.end(),Compare_as_Angle);

			   float sum_energy=0;
			   float angle=0;
			   for(unsigned int i=0;i<Ref_angle.size();i++){
			   sum_energy = sum_energy + Ref_angle[i].second->getEnergy();
			   if(sum_energy>1){
			   return(angle);
			   }
			   else{
			   angle=Ref_angle[i].first;
			   }
			   }
			   return(180);
			   }
			   */

			// functions for get basic particle properties 
			static int  Get_Parents_Number(MCParticle* input)               ;
			static int  Get_Daughters_Number(MCParticle* input)             ;
			// functions for Judge particle status 
			static bool Status_Beam_Energy(MCParticle* input)               ;
			static bool Status_Has_Parent(MCParticle* input)                ;
			static bool Status_Has_GrandParent(MCParticle* input)           ;
			static bool Status_Has_Daughter(MCParticle* input)              ;
			static bool Status_Has_GrandDaughter(MCParticle* input)         ;
			static bool Status_Is_MS(MCParticle* input)                     ;
			static bool Status_Is_TFS(MCParticle* input)                    ;
			static bool Status_Is_Pythia_TFS(MCParticle* input)             ;
			static bool Status_Is_Detector_TFS(MCParticle* input)           ;
			static bool Status_Is_Pythia(MCParticle* input)                 ;
			static bool Status_Is_Overlay(MCParticle* input)                ;
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
			static bool Status_Is_TopQuark(MCParticle* input)               ;
			static bool Status_Is_BottomQuark(MCParticle* input)            ;
			static bool Status_Is_CharmQuark(MCParticle* input)             ;

			// functions for Judge particle type 
			static bool Judge_Is_Beam(MCParticle* input)                    ;
			static bool Judge_Parents_Are_Beam(MCParticle* input)           ;
			static bool Judge_GrandParents_Are_Beam(MCParticle* input)      ;
			static bool Judge_Is_IS_Electron(MCParticle* input)             ;
			static bool Judge_Is_IS_Photon(MCParticle* input)               ;

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

			// for ID 
			static std::vector<MCParticle*> Get_MC_ParticleType(std::vector<MCParticle*> MCs,signed int PDG) ;

			static std::vector<int>         Get_ParentsPID(MCParticle* MC) ;

			static std::vector<int>         Get_DaughtersPID(MCParticle* MC) ;

			// for chain 
			static std::vector<MCParticle*> MCToPythiaShowering(MCParticle* input);

			static std::vector<MCParticle*> MCToHardScattering(MCParticle* input);

			static void                     Get_MC_HardScattering_Sort(std::vector<MCParticle*> MCs, std::vector<MCParticle*> &ISRlepton , std::vector<MCParticle*> &ISRphoton, std::vector<MCParticle*> &ObjetctParticle) ;

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
	};
}


#endif

