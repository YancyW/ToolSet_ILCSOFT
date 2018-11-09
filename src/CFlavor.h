#pragma once
#ifndef CFLAVOR_H
#define CFLAVOR_H  
#include <cmath>
namespace ToolSet{
	class CFlavor{
		public:
		static bool Status_Is_Hadron(int pdg);
		static bool Status_Is_Electron(int signed_pdg);
		static bool Status_Is_Muon(int signed_pdg);
		static bool Status_Is_Tau(int signed_pdg);
		static bool Status_Is_Lepton(int signed_pdg);
		static bool Status_Is_Photon(int signed_pdg);
		static bool Status_Is_Neutrino(int signed_pdg);
		static bool Status_Is_HeavyBoson(int signed_pdg);
		static bool Status_Is_NeutralHadron(int signed_pdg, float charge);
		static bool Status_Is_ChargedHadron(int signed_pdg, float charge);
		static bool Status_Is_Quark(int signed_pdg);
		static bool Status_Is_LightQuark(int signed_pdg);
		static bool Status_Is_HeavyQuark(int signed_pdg);
		static bool Status_Is_Gluon(int signed_pdg);
		static bool Status_Is_TopQuark(int signed_pdg);
		static bool Status_Is_BottomQuark(int signed_pdg);
		static bool Status_Is_CharmQuark(int signed_pdg);
		static bool Status_Are_ElectronPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_MuonPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_TauPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_GluonPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_PhotonPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_BottomPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_CharmPair(int signed_pdg1, int signed_pdg2);
		static bool Status_Are_TopPair(int signed_pdg1, int signed_pdg2);
	};
}
#endif
