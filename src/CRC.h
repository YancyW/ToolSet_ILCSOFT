#pragma once
#ifndef CRC_H
#define CRC_H  
#include <iostream>
#include <fstream>
#include <set>

#include <vector>
#include <stack>
#include <cmath>

//LCIO
#include <EVENT/LCCollection.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include "UTIL/PIDHandler.h"
#include "LCIOSTLTypes.h"
#include "UTIL/LCRelationNavigator.h"

//ROOT
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include "TRandom.h"
#include "CFormat.h"
#include "CMC.h"
#include "CData_Type.h"

using namespace lcio;

namespace ToolSet{

	ReconstructedParticle& operator+(const ReconstructedParticle& MC1,const ReconstructedParticle& MC2);

	ReconstructedParticle& operator-(const ReconstructedParticle& MC1,const ReconstructedParticle& MC2);

	class CRC{
		public :
			static bool Compare_as_Angle_RC(const std::pair<float,ReconstructedParticle*> &i, const std::pair<float,ReconstructedParticle*> &j){
				return ((i.first) < (j.first));
			}

			static ReconstructedParticle* NewParticle(double px, double py, double pz, double E, ReconstructedParticle* test);

			static ReconstructedParticle* Add(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2);

			static ReconstructedParticle* Minus(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2);

			static ReconstructedParticle* Equal(const ReconstructedParticle* MC1) ;

			static bool Same_Particle(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2);



			static float Cal_IsolationAngle(ReconstructedParticle* MC, std::vector<ReconstructedParticle*> Ref){
				std::vector<std::pair<float,ReconstructedParticle*> >Ref_angle;
				for(unsigned int i=0;i<Ref.size();i++){
					std::pair<float,ReconstructedParticle*> pair_tmp = std::make_pair(CMC::Cal_Angle_Deg(MC,Ref[i]),Ref[i]);
					Ref_angle.push_back(pair_tmp);
				}
				std::sort(Ref_angle.begin(),Ref_angle.end(),Compare_as_Angle_RC);

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

			//get status
			static bool                   Judge_Is_FromOverlay(ReconstructedParticle* in, LCRelationNavigator* nav);

			//get special particle into a vector 
			static std::vector<ReconstructedParticle*> Get_POParticle(LCCollection* AllPOs) ;

			static std::vector<ReconstructedParticle*> Get_POParticleType(std::vector<ReconstructedParticle*> POs,int PDG) ;
			static std::vector<ReconstructedParticle*> Get_POParticleType_Abs(std::vector<ReconstructedParticle*> POs,int PDG) ;
			static std::vector<ReconstructedParticle*> Get_POParticleType(std::vector<ReconstructedParticle*> POs,std::string PDG) ;

			static std::vector<ReconstructedParticle*> Get_POParticlePairType( std::vector<ReconstructedParticle*> PFOs,int PDG, int counter_minus, int counter_plus, int counter_pair) ;

			// get particle from Link
			static std::vector<MCParticle*>   Get_MC_From_PFO(ReconstructedParticle* &source, LCRelationNavigator* &relation);
			static std::vector<std::vector<MCParticle*> > Get_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation);
			static std::vector<MCParticle*>            Get_A_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation);
			static std::vector<ReconstructedParticle*>               Get_PFO_From_MC(MCParticle* &source, LCRelationNavigator* &relation);
			static std::vector<std::vector<ReconstructedParticle*> > Get_PFO_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation);
			static std::vector<ReconstructedParticle*>               Get_A_PFO_From_MC_Vec(std::vector<MCParticle*> &sourc, LCRelationNavigator* &relation);

			// get weight from Link
			static std::vector<float>               Get_MC_Weight_From_PFO(ReconstructedParticle* &source, LCRelationNavigator* &relation);
			static std::vector<std::vector<float> > Get_MC_Weight_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation);
			static std::vector<float>               Get_PFO_Weight_From_MC(MCParticle* &source, LCRelationNavigator* &relation);
			static std::vector<std::vector<float> > Get_PFO_Weight_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation);

			// get visible/in visible
			static ReconstructedParticle* Get_Visible(std::vector<ReconstructedParticle*> in);
			static ReconstructedParticle* Get_InVisible(std::vector<ReconstructedParticle*> in);
			static TLorentzVector         Get_Visible_To_Lorentz(std::vector<ReconstructedParticle*> in);
			static TLorentzVector         Get_InVisible_To_Lorentz(std::vector<ReconstructedParticle*> in);


	        static std::vector<ReconstructedParticle*> Get_PO_Overlay(std::vector<ReconstructedParticle*> input, LCRelationNavigator* &nav);

	};
}
#endif
