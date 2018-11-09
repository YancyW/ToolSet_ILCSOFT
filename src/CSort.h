#pragma once
#ifndef CSORT_H
#define CSORT_H  
#include <iostream>
#include <fstream>
#include <set>

#include <vector>
#include <stack>
#include <cmath>

//LCIO
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Vertex.h>
#include <IMPL/MCParticleImpl.h>
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
#include "CRC.h"
#include "CPrint.h"

namespace ToolSet{
	class CSort{
		private:
			std::map<int, std::vector<MCParticle*> > _sort;
			std::vector<MCParticle*> _source;
			int _nsource;
			bool _Used;
			void set_Class(int pdg);

		public:

			CSort();

			CSort(std::vector<MCParticle*> input);

			void set_Source(std::vector<MCParticle*> input);

			void set_Sort(int pdg);

			bool get_Sort(int pdg, std::vector<MCParticle*> & output);

			void Print();

			void init();
	};
}
#endif
