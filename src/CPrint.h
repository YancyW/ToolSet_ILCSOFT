#pragma once
#ifndef CPRINT_H
#define CPRINT_H  
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <IMPL/MCParticleImpl.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include "UTIL/PIDHandler.h"
#include "LCIOSTLTypes.h"
#include "TLorentzVector.h"
using namespace lcio;

namespace ToolSet{
	/**
	 * @brief << print event information, event number and collection name
	 *
	 * @param ostr
	 * @param in
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const LCEvent *in);

	/**
	 * @brief << print MCParticle information
	 *
	 * @param ostr
	 * @param in
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const MCParticle *in);
	/**
	 * @brief << print ReconstructedParticle information
	 *
	 * @param ostr
	 * @param in
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const ReconstructedParticle *in);
	/**
	 * @brief << print track information
	 *
	 * @param ostr
	 * @param in
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const Track *in);

	/**
	 * @brief << print the vector of MCParticle
	 *
	 * @param ostr
	 * @param invec
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const std::vector<MCParticle*> &invec);
	/**
	 * @brief << print the vector of ReconstructedParticle
	 *
	 * @param ostr
	 * @param invec
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const std::vector<ReconstructedParticle*> &invec);
	/**
	 * @brief << print the vector of track
	 *
	 * @param ostr
	 * @param invec
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const std::vector<Track*> &invec);

	/**
	 * @brief << print TLorentzVector
	 *
	 * @param ostr
	 * @param invec
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const TLorentzVector &invec);
	/**
	 * @brief << print the vector of TLorentzVector
	 *
	 * @param ostr
	 * @param invec
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const std::vector<TLorentzVector> &invec);

	/**
	 * @brief << print the vector of int 
	 *
	 * @param ostr
	 * @param in
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const std::vector<int> &in);
	/**
	 * @brief << print the vector of float
	 *
	 * @param ostr
	 * @param in
	 *
	 * @return 
	 */
	std::ostream & operator << (std::ostream & ostr, const std::vector<float> &in);

}
#endif
