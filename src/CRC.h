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

	/**
	 * @brief operator+ : same with CRC::Add, add four momentum of two MCParticle
	 *
	 * @param MC1
	 * @param MC2
	 *
	 * @return 
	 */
	ReconstructedParticle& operator+(const ReconstructedParticle& MC1,const ReconstructedParticle& MC2);

	/**
	 * @brief operator- : same with CRC::Minus, minus four momentum of two MCParticle
	 *
	 * @param MC1
	 * @param MC2
	 *
	 * @return 
	 */
	ReconstructedParticle& operator-(const ReconstructedParticle& MC1,const ReconstructedParticle& MC2);

	/**
	 * @brief : functions for ReconstructedParticle
	 */
	class CRC{
		private:
			static std::vector<ReconstructedParticle*> _new_particles;
		public :
			/**
			 * @brief Clear : all pointers generated in the heap will be deleted
			 */
			static void Clear();
			/**
			 * @brief Compare_as_E : compare funcion by the energy for MCParticle, equals to < operator 
			 *
			 * @param i
			 * @param j
			 *
			 * @return 
			 */
			static bool Compare_as_E(const ReconstructedParticle* i, const ReconstructedParticle* j){
				return (i->getEnergy()>j->getEnergy());
			}

			/**
			 * @brief Compare_as_Angle : compare funcion by the costheta for ReconstructedParticle, equals to < operator 
			 *
			 * @param i
			 * @param j
			 *
			 * @return 
			 */
			static bool Compare_as_Angle(const ReconstructedParticle* i, const ReconstructedParticle* j){
				float cos_i=CMC::Cal_CosTheta(i);
				float cos_j=CMC::Cal_CosTheta(j);
				return (cos_i  > cos_j);
			}
			/**
			 * @brief Compare_as_Pair : compare function by any value paired to ReconstructedParticle*
			 *
			 * @param i
			 * @param j
			 *
			 * @return 
			 */
			static bool Compare_as_Pair(const std::pair<float,ReconstructedParticle*> &i, const std::pair<float,ReconstructedParticle*> &j){
				return ((i.first) < (j.first));
			}

			/**
			 * @brief NewParticle : generate a new ReconstructedParticle 
			 * Notice: this will use the "new" keyword, and generate a new ReconstructedParticle in the heap, so remember to delete this pointer
			 *
			 * @param px
			 * @param py
			 * @param pz
			 * @param E
			 * @param test
			 *
			 * @return 
			 */
			static ReconstructedParticle* NewParticle(double px, double py, double pz, double E, ReconstructedParticle* test);

			/**
			 * @brief NewParticle : generate a new ReconstructedParticle
			 * Notice: this will use the "new" keyword, and generate a new ReconstructedParticle in the heap, so remember to delete this pointer
			 *
			 * @param p
			 * @param test
			 *
			 * @return 
			 */
			static ReconstructedParticle* NewParticle(TLorentzVector &p, ReconstructedParticle* test);

			/**
			 * @brief NewParticle : generate a new ReconstructedParticle
			 * Notice: this will use the "new" keyword, and generate a new ReconstructedParticle in the heap, so remember to delete this pointer
			 *
			 * @param p
			 * @param pdg
			 * @param charge
			 * @param test
			 *
			 * @return 
			 */
			static ReconstructedParticle* NewParticle(TLorentzVector &p, int pdg, float charge, ReconstructedParticle* test);

			/**
			 * @brief Add : add four momentum of two ReconstructedParticle 
			 * Notice: this will use the "new" keyword, and generate a new ReconstructedParticle in the heap, so remember to delete this pointer
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static ReconstructedParticle* Add(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2);

			/**
			 * @brief Minus : minus four momentum of two ReconstructedParticle 
			 * Notice: this will use the "new" keyword, and generate a new ReconstructedParticle in the heap, so remember to delete this pointer
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static ReconstructedParticle* Minus(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2);

			/**
			 * @brief Equal : generate a new ReconstructedParticle equal to the input one
			 * This is different from use "=", "=" will give the pointer address to the new pointer, they are still pointing to the same particle. But "equal" will generate a new MCParticle, whose property is the same with the old
			 * one.
			 * Notice: this will use the "new" keyword, and generate a new ReconstructedParticle in the heap, so remember to delete this pointer
			 *
			 * @param MC1
			 *
			 * @return 
			 */
			static ReconstructedParticle* Equal(const ReconstructedParticle* MC1) ;

			/**
			 * @brief Minus_To_Lorentz : minus four momentum of two ReconstructedParticle, return a TLorentzVector of the four momentum 
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static TLorentzVector  Minus_By_Lorentz(const ReconstructedParticle* MC1, const ReconstructedParticle* MC2) ;

			/**
			 * @brief Same_Particle : judge whether particle are same
			 *
			 * @param MC1
			 * @param MC2
			 *
			 * @return 
			 */
			static bool Same_Particle(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2);



			//get status
			/**
			 * @brief Judge_Is_FromOverlay : the max weight MCParticle of this ReconstructedParticle is the overlay particle 
			 *
			 * @param in
			 * @param nav
			 *
			 * @return 
			 */
			static bool                   Judge_Is_FromOverlay(ReconstructedParticle* in, LCRelationNavigator* nav);
			/**
			 * @brief Judge_IsInCone : judge whether having particles in the cone of the input particle
			 *
			 * @param lep
			 * @param pfo
			 * @param angle_cut
			 *
			 * @return 
			 */
			static bool                     Judge_IsInCone( ReconstructedParticle* input1, ReconstructedParticle* input2, float angle_cut) ;

			//get special particle into a vector 
			/**
			 * @brief Get_POParticle : get all ReconstructedParticle into a vector from the LCCollection 
			 *
			 * @param AllPOs
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_POParticle(LCCollection* AllPOs) ;

			/**
			 * @brief Get_POParticleType : get a special type particle among the give vectors, use the signed pdg code
			 *
			 * @param POs
			 * @param PDG
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_POParticleType(std::vector<ReconstructedParticle*> POs,int PDG) ;
			/**
			 * @brief Get_POParticleType_Abs : get a special type particle among the give vectors, use the absolute value of PDG
			 *
			 * @param POs
			 * @param PDG
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_POParticleType_Abs(std::vector<ReconstructedParticle*> POs,int PDG) ;
			/**
			 * @brief Get_POParticleType : get a special type particle among the given vectors, use the name of particle 
			 *
			 * @param POs
			 * @param PDG : currently supporting "quark", "light_quark", "heavy_quark", "lepton", "neutrino" 
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_POParticleType(std::vector<ReconstructedParticle*> POs,std::string PDG) ;

			// get particle from Link
			/**
			 * @brief Get_MC_From_PFO : get corresponding MCParticles, one ReconstructedParticle will correspond to several MCParticles source
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<MCParticle*>                          Get_MC_From_PFO(ReconstructedParticle* &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_MC_From_PFO_Vec : get corresponding MCParticles from a vector of ReconstructedParticles, one ReconstructedParticle will correspond to several MCParticles source, so return a vector of vector
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<std::vector<MCParticle*> >            Get_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_A_MC_From_PFO_Vec : get corresponding max weighted MCParticles from a vector of ReconstructedParticles, one ReconstructedParticle will correspond to one max weight MCParticle source, so it's a one-to-one
			 * relation 
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<MCParticle*>                          Get_A_MC_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_PFO_From_MC : get corresponding ReconstructedParticle, one MCParticle will correspond to several ReconstructedParticle source
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*>               Get_PFO_From_MC(MCParticle* &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_PFO_From_MC_Vec : get corresponding ReconstructedParticle from a vector of MCParticles, one MCParticle will correspond to several ReconstructedParticle source, so return a vector of vector
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<std::vector<ReconstructedParticle*> > Get_PFO_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_A_PFO_From_MC_Vec : get corresponding max weighted ReconstructedParticle from a vector of MCParticle, one MCParticle will correspond to one max weight ReconstructedParticle source, so it's a one-to-one
			 *
			 * @param sourc
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*>               Get_A_PFO_From_MC_Vec(std::vector<MCParticle*> &sourc, LCRelationNavigator* &relation);

			// get weight from Link
			/**
			 * @brief Get_MC_Weight_From_PFO : get corresponding MCParticles wight, one ReconstructedParticle will correspond to several MCParticles source
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<float>               Get_MC_Weight_From_PFO(ReconstructedParticle* &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_MC_Weight_From_PFO_Vec : get corresponding MCParticle weights from a vector of ReconstructedParticles, one ReconstructedParticle will correspond to several MCParticles source, so return a vector of vector
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<std::vector<float> > Get_MC_Weight_From_PFO_Vec(std::vector<ReconstructedParticle*> &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_PFO_Weight_From_MC : get corresponding ReconstructedParticle weight, one MCParticle will correspond to several ReconstructedParticle source
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<float>               Get_PFO_Weight_From_MC(MCParticle* &source, LCRelationNavigator* &relation);
			/**
			 * @brief Get_PFO_Weight_From_MC_Vec : get corresponding ReconstructedParticle weights from a vector of MCParticles, one MCParticle will correspond to several ReconstructedParticle source, so return a vector of vector
			 *
			 * @param source
			 * @param relation
			 *
			 * @return 
			 */
			static std::vector<std::vector<float> > Get_PFO_Weight_From_MC_Vec(std::vector<MCParticle*> &source, LCRelationNavigator* &relation);

			// get visible/in visible
			/**
			 * @brief Get_Sum : get sum of the input particles 
			 *
			 * @param in
			 *
			 * @return 
			 */
			static ReconstructedParticle* Get_Sum(std::vector<ReconstructedParticle*> in);
			/**
			 * @brief Get_InVisible : get invisible particle, i.e.  collider - sum of input vector
			 *
			 * @param in
			 *
			 * @return 
			 */
			static ReconstructedParticle* Get_InVisible(std::vector<ReconstructedParticle*> in);
			/**
			 * @brief Get_Sum_To_Lorentz : get sum of input particles, return four momentum
			 *
			 * @param in
			 *
			 * @return 
			 */
			static TLorentzVector         Get_Sum_To_Lorentz(std::vector<ReconstructedParticle*> in);
			/**
			 * @brief Get_InVisible_To_Lorentz : get invisible, return four momentum 
			 *
			 * @param in
			 *
			 * @return 
			 */
			static TLorentzVector         Get_InVisible_To_Lorentz(std::vector<ReconstructedParticle*> in);


			/**
			 * @brief Get_PO_Overlay : get overlay particle
			 *
			 * @param input
			 * @param nav
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_PO_Overlay(std::vector<ReconstructedParticle*> input, LCRelationNavigator* &nav);
			/**
			 * @brief Get_InCone : get the particles in the cone
			 *
			 * @param input
			 * @param all : this argument will be changed to remove the particle in the cone of the input
			 * @param cone_size
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_InCone(ReconstructedParticle* input,std::vector<ReconstructedParticle*> &all, float cone_size) ;
			/**
			 * @brief Get_Isolated : get isolated particle
			 *
			 * @param input
			 * @param all
			 * @param outside_cone
			 * @param cone_size
			 *
			 * @return 
			 */
			static std::vector<ReconstructedParticle*> Get_Isolated(std::vector<ReconstructedParticle*> input,std::vector<ReconstructedParticle*> all, std::vector<ReconstructedParticle*> outside_cone, float cone_size) ;
			/**
			 * @brief Get_IsolationAngle : get minimal isolation angle
			 *
			 * @param MC
			 * @param Ref
			 * @param minimal_energy_in_the_cone
			 * @param minimal_angle_from_input
			 *
			 * @return 
			 */
			static float Get_IsolationAngle(ReconstructedParticle* MC, std::vector<ReconstructedParticle*> Ref, float minimal_energy_in_the_cone=1, float minimal_angle_from_input=2 );


	};
}
#endif
