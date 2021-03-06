#include "CRC.h"
bool ToolSet::CRC::Judge_Is_FromOverlay(ReconstructedParticle* in, LCRelationNavigator* nav){
      
	std::vector<MCParticle*> from_this_mc;
	from_this_mc= Get_MC_From_PFO(in, nav);
	std::vector<float> weight=Get_MC_Weight_From_PFO(in, nav);
	if(from_this_mc.size()>0){
		int pos= Data_Type::Get_Pos(weight, "max");

		if(pos==-1){return(false);}

		if(CMC::Status_Is_Overlay(from_this_mc[pos])){
			return(true);
		}
	}
	return(false);

}


bool ToolSet::CRC::Judge_IsInCone( ReconstructedParticle* input1, ReconstructedParticle* input2, float angle_cut) {
	TVector3 P_1( input1->getMomentum() );

	TVector3 P_2( input2->getMomentum() );

	float cosTheta = P_1.Dot( P_2)/(P_1.Mag()*P_2.Mag());
	if ( cosTheta >= angle_cut)
	{
		return true;
	}
	return false;
}
