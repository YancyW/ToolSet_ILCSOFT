#pragma once
#ifndef CRC_H
#define CRC_H  
#include <iostream>
#include <fstream>
#include <set>

#include <vector>
#include <stack>

//LCIO
#include <EVENT/LCCollection.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include <IMPL/ReconstructedParticleImpl.h>
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
#include "CMC.h"

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

		static std::vector<ReconstructedParticle*> getPOFinalState(LCCollection* AllPOs) ;

		static std::vector<ReconstructedParticle*> getPOParticleType(std::vector<ReconstructedParticle*> POs,int PDG) ;

		static std::vector<ReconstructedParticle*> getPOParticlePairType( std::vector<ReconstructedParticle*> PFOs,int PDG, int counter_minus, int counter_plus, int counter_pair) ;

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
	};
}
#endif
