#include "CMC.h"


std::vector<MCParticle*> ToolSet::CMC::Get_Particle(bool (*Judge)(MCParticle*), std::vector<MCParticle*> MCs){
	std::vector<MCParticle*> Parton;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge(MCs[i])){
			Parton.push_back(MCs[i]);
		}
		else 
		{
			continue;
		}
	}
	return(Parton);


}

/*****************************************************************************************
 * @Name: Get_MCParticle 
 *
 * @Param: AllMC
 *
 * @Returns: all mc particles
 *****************************************************************************************/
std::vector<MCParticle*> ToolSet::CMC::Get_MCParticle(LCCollection* AllMC) {
	std::vector<MCParticle*> FS;
	int nMC = AllMC->getNumberOfElements();
	for( int i = 0; i < nMC; i++ ){
		MCParticle* MC = dynamic_cast< MCParticle* >( AllMC->getElementAt(i) );
		FS.push_back(MC);
	}
	return(FS);
}




std::vector<MCParticle*> ToolSet::CMC::Get_MC_HardScattering_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> Parton;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_HardScattering_FS(MCs[i])){
			Parton.push_back(MCs[i]);
		}
	}
	return(Parton);
}



std::vector<MCParticle*> ToolSet::CMC::Get_MC_OnlyPythiaShowering_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS_PythiaLevel;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_OnlyPythiaShowering_FS(MCs[i])){
			FS_PythiaLevel.push_back(MCs[i]);
		}
	}
	return(FS_PythiaLevel);
}

std::vector<MCParticle*> ToolSet::CMC::Get_MC_PythiaShowering_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS_PythiaLevel;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_PythiaShowering_FS(MCs[i])){
			FS_PythiaLevel.push_back(MCs[i]);
		}
	}
	return(FS_PythiaLevel);
}


std::vector<MCParticle*> ToolSet::CMC::Get_MC_OnlyDetectorSimulating_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS_DetectorLevel;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_OnlyDetectorSimulating_FS(MCs[i])){
			FS_DetectorLevel.push_back(MCs[i]);
		}
	}
	return(FS_DetectorLevel);
}

std::vector<MCParticle*> ToolSet::CMC::Get_MC_DetectorSimulating_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS_DetectorLevel;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_DetectorSimulating_FS(MCs[i])){
			FS_DetectorLevel.push_back(MCs[i]);
		}
	}
	return(FS_DetectorLevel);
}




std::vector<MCParticle*> ToolSet::CMC::Get_MC_Overlay_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS_Overlay;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_Overlay_FS(MCs[i])){
			FS_Overlay.push_back(MCs[i]);
		}
	}
	return(FS_Overlay);
}

std::vector<MCParticle*> ToolSet::CMC::Get_MC_All_FS(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_All_FS(MCs[i])){
			FS.push_back(MCs[i]);
		}
	}
	return(FS);
}


std::vector<MCParticle*> ToolSet::CMC::Get_MC_PythiaShowering_All(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> Vec;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Judge_PythiaShowering_All(MCs[i])){
			Vec.push_back(MCs[i]);
		}
	}
	return(Vec);
}

std::vector<MCParticle*> ToolSet::CMC::Get_MC_DetectorSimulating_All(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> Vec;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Status_Is_Detector_TFS(MCs[i])){
			Vec.push_back(MCs[i]);
		}
	}
	return(Vec);
}


std::vector<MCParticle*> ToolSet::CMC::Get_MC_Overlay_All(std::vector<MCParticle*> MCs) {
	std::vector<MCParticle*> FS_Overlay;
	int nMC = MCs.size();
	for( int i = 0; i < nMC; i++ ){
		if(Status_Is_Overlay(MCs[i])){
			FS_Overlay.push_back(MCs[i]);
		}
	}
	return(FS_Overlay);
}




std::vector<MCParticle*> ToolSet::CMC::Get_MC_To_PythiaShowering(MCParticle* input){
	std::vector<MCParticle*> output;
	if(Judge_PythiaShowering_FS(input)){
		output.push_back(input);
		return(output);
	}
	for(int i=0;i< Get_Parents_Number(input);i++){
		std::vector<MCParticle*> output_tmp;
		output_tmp=Get_MC_To_PythiaShowering(input->getParents()[i]);
		for(unsigned int j=0;j< output_tmp.size();j++){
			output.push_back(output_tmp[j]);
		}
	}
	return(output);
}


std::vector<MCParticle*> ToolSet::CMC::Get_MC_To_HardScattering(MCParticle* input){
	std::vector<MCParticle*> output;
	if(Judge_HardScattering_FS(input)){
		output.push_back(input);
		return(output);
	}
	for(int i=0;i< Get_Parents_Number(input);i++){
		std::vector<MCParticle*> output_tmp;
		output_tmp=Get_MC_To_HardScattering(input->getParents()[i]);
		for(unsigned int j=0;j< output_tmp.size();j++){
			output.push_back(output_tmp[j]);
		}
	}
	return(output);
}




void ToolSet::CMC::Get_MC_HardScattering_Sort(std::vector<MCParticle*> MCs, std::vector<MCParticle*> &ISRlepton , std::vector<MCParticle*> &ISRphoton, std::vector<MCParticle*> &OtherParticle) {
	int nMC = MCs.size();

	for( int i = 0; i < nMC; i++ ){
		if(!Judge_HardScattering_FS(MCs[i])){
			exit(0);
		}
		if(Status_Is_Photon(MCs[i])){
			ISRphoton.push_back(MCs[i]); 
		}
		else if(Status_Is_Electron(MCs[i]) || Status_Is_Muon(MCs[i])){
			ISRlepton.push_back(MCs[i]); 
		}
		else{
			OtherParticle.push_back(MCs[i]);
		}
	}

	return;
}



std::vector<MCParticle*> ToolSet::CMC::Get_MCParticleType(std::vector<MCParticle*> MCs,signed int PDG) {
	int num = MCs.size();
	std::vector<MCParticle*> output;
	for( int i = 0; i < num; i++ ){
		MCParticle* MC = MCs[i];
		if(MC->getPDG()==PDG){
			output.push_back(MC);
		}
	}
	return(output);
}


std::vector<MCParticle*> ToolSet::CMC::Get_MCParticleType_Abs(std::vector<MCParticle*> MCs,signed int PDG) {
	int num = MCs.size();
	std::vector<MCParticle*> output;
	for( int i = 0; i < num; i++ ){
		MCParticle* MC = MCs[i];
		if(std::abs(MC->getPDG())==PDG){
			output.push_back(MC);
		}
	}
	return(output);
}

std::vector<MCParticle*> ToolSet::CMC::Get_MCParticleType(std::vector<MCParticle*> MCs,std::string PDG) {
	int num = MCs.size();
	std::vector<MCParticle*> output;
	for( int i = 0; i < num; i++ ){
		MCParticle* MC = MCs[i];
		int pdg = MC->getPDG();
		if(PDG=="quark"){
			if(CFlavor::Status_Is_Quark(pdg)){
				output.push_back(MC);
			}
		}
		else if(PDG=="light_quark"){
			if(CFlavor::Status_Is_LightQuark(pdg)){
				output.push_back(MC);
			}
		}
		else if(PDG=="heavy_quark"){
			if(CFlavor::Status_Is_HeavyQuark(pdg)){
				output.push_back(MC);
			}
		}
		else if(PDG=="lepton"){
			if(CFlavor::Status_Is_Lepton(pdg)){
				output.push_back(MC);
			}
		}
		else if(PDG=="neutrino"){
			if(CFlavor::Status_Is_Neutrino(pdg)){
				output.push_back(MC);
			}
		}
	}
	return(output);
}

std::vector<MCParticle*> ToolSet::CMC::Get_MCParticle_Without_Type(std::vector<MCParticle*> MCs,std::string PDG) {
	int num = MCs.size();
	std::vector<MCParticle*> output;
	for( int i = 0; i < num; i++ ){
		MCParticle* MC = MCs[i];
		int pdg = MC->getPDG();
		if(PDG=="quark"){
			if(CFlavor::Status_Is_Quark(pdg)){
				continue;
			}
		}
		else if(PDG=="light_quark"){
			if(CFlavor::Status_Is_LightQuark(pdg)){
				continue;
			}
		}
		else if(PDG=="heavy_quark"){
			if(CFlavor::Status_Is_HeavyQuark(pdg)){
				continue;
			}
		}
		else if(PDG=="lepton"){
			if(CFlavor::Status_Is_Lepton(pdg)){
				continue;
			}
		}
		else if(PDG=="neutrino"){
			if(CFlavor::Status_Is_Neutrino(pdg)){
				continue;
			}
		}
		output.push_back(MC);
	}
	return(output);
}


float ToolSet::CMC::Get_DecayChannel(MCParticle* input) {
	std::vector<int> pdg;
	pdg=Get_DaughtersPID(input->getDaughters()[0]);
	//sort pdg from small to large
	std::sort(pdg.begin(),pdg.end());
	int channel=-1;

	// there is no standard pdg code larger than 40 and smaller than 90. so we define them by ours
	// q-qbar 
	if(CFlavor::Status_Are_BottomPair(pdg[0],pdg[1])){
		channel = 5.0;
	}
	else if(CFlavor::Status_Are_CharmPair(pdg[0],pdg[1])){
		channel = 4.0;
	}
	else if(CFlavor::Status_Are_TopPair(pdg[0],pdg[1])){
		channel = 6.0;
	}
	else if(pdg[0]==-1&&pdg[1]==1){
		channel = 1.0;
	}
	else if(pdg[0]==-2&&pdg[1]==2){
		channel = 2.0;
	}
	else if(pdg[0]==-3&&pdg[1]==3){
		channel = 3.0;
	}
	// l-l+
	else if(CFlavor::Status_Are_ElectronPair(pdg[0],pdg[1])){
		channel 	= 11.0;
	}
	else if(CFlavor::Status_Are_MuonPair(pdg[0],pdg[1])){
		channel 	= 13.0;
	}
	else if(CFlavor::Status_Are_TauPair(pdg[0],pdg[1])){
		channel 	= 15.0;
	}
	// l-vl
	else if(pdg[0]==-11&&pdg[1]==12){
		channel 	= 51.0;//e- - ve
	}
	else if(pdg[0]==-12&&pdg[1]==11){
		channel 	= 52.0;//e- - ve
	}
	else if(pdg[0]==-13&&pdg[1]==14){
		channel 	= 53.0;//e- - ve
	}
	else if(pdg[0]==-14&&pdg[1]==13){
		channel 	= 54.0;//e- - ve
	}
	else if(pdg[0]==-15&&pdg[1]==16){
		channel 	= 55.0;//e- - ve
	}
	else if(pdg[0]==-16&&pdg[1]==15){
		channel 	= 56.0;//e- - ve
	}
	// boson 
	else if(CFlavor::Status_Are_GluonPair(pdg[0],pdg[1])){
		channel 	= 21.0;//gluon-gluon
	}
	else if(CFlavor::Status_Are_PhotonPair(pdg[0],pdg[1])){
		channel 	= 22.0; //gamma-gamma
	}
	else if(pdg[0]==-24&&pdg[1]==24){
		channel 	= 24.0; //WW
	}
	else if(pdg[0]==23&&pdg[1]==23){
		channel 	= 23.0;//ZZ
	}
	else if(pdg[0]==22&&pdg[1]==23){
		channel 	= 45.0; //Z-gamma
	}
	// hadron
	else if(CFlavor::Status_Is_Hadron(pdg[0])&&CFlavor::Status_Is_Hadron(pdg[1])){
		channel 	= 61.0; //hadron hadron
	}
	else{
		channel 	= -1.0;
	}
	return(channel);
}

std::vector<MCParticle*> ToolSet::CMC::Get_In_DetectorAngle(std::vector<MCParticle*> &MCs) {
	int num = MCs.size();
	std::vector<MCParticle*> output;
	for( int i = 0; i < num; i++ ){
		MCParticle* MC = MCs[i];
		if(std::abs(Cal_CosTheta(MC))<_detectable_angle){
			output.push_back(MC);
		}
	}
	return(output);
}


MCParticle* ToolSet::CMC::Get_Sum(std::vector<MCParticle*> in){

	int num=in.size();

	MCParticle* visible;
	if(num<=0){
		visible=NewParticle(0,0,0,0,visible);
		_new_particles.push_back(visible);
		return(visible);
	}

	TLorentzVector VS(0,0,0,0);
	for(int i=0;i<num;i++){
		TLorentzVector Vnew(in[i]->getMomentum(),in[i]->getEnergy());
		VS+=Vnew;
	}

	visible = NewParticle(VS,in[0]->getPDG(), in[0]->getCharge(),visible);
	_new_particles.push_back(visible);
	return(visible);

}


std::vector<MCParticle*> ToolSet::CMC::Get_Visible(std::vector<MCParticle*> in){
	std::vector<MCParticle*> visible_1=Get_In_DetectorAngle(in);
	std::vector<MCParticle*> visible_2=Get_MCParticle_Without_Type(visible_1,"neutrino");
	return(visible_2);
}

MCParticle* ToolSet::CMC::Get_InVisible(std::vector<MCParticle*> in){
	float beam_px= _collider_energy*tan(_beam_cross_angle);
	MCParticle* visible = Get_Sum(in);
	MCParticle* RCCollider=NewParticle(beam_px,0,0,_beam_energy*2,visible);
	MCParticle* invisible= Minus(RCCollider,visible);
	delete RCCollider;
	delete visible;
	return(invisible);
}

TLorentzVector ToolSet::CMC::Get_Sum_To_Lorentz(std::vector<MCParticle*> in){

	int num=in.size();

	TLorentzVector visible;
	visible=TLorentzVector(0,0,0,0);
	if(num<=0){
		return(visible);
	}

	for(int i=0;i<num;i++){
		TLorentzVector Vnew(in[i]->getMomentum(),in[i]->getEnergy());
		visible+=Vnew;
	}

	return(visible);

}

TLorentzVector ToolSet::CMC::Get_InVisible_To_Lorentz(std::vector<MCParticle*> in){
	float beam_px= _collider_energy*tan(_beam_cross_angle);
	TLorentzVector visible = Get_Sum_To_Lorentz(in);
	TLorentzVector RCCollider=TLorentzVector(beam_px,0,0,_beam_energy*2);
	TLorentzVector invisible= RCCollider-visible;
	return(invisible);
}

std::vector<MCParticle*> ToolSet::CMC::Get_InCone(MCParticle* input,std::vector<MCParticle*> &all, float cone_size) {
	// the first output is the input
	// other outputs are the particles that in the input cone
	// all will be changed to remove the particle in the input cone
	std::vector<MCParticle*> output;
	output.push_back(input);

	for(unsigned int i=0;i<all.size();i++){
		if (Judge_IsInCone( input, all[i], cone_size)) {
			output.push_back(all[i]);
		}
	}

	all=all-output;
	return(output);
}


std::vector<MCParticle*> ToolSet::CMC::Get_Isolated(std::vector<MCParticle*> input,std::vector<MCParticle*> all, std::vector<MCParticle*> outside_cone, float cone_size) {

	std::vector<MCParticle*> output;
	int num= input.size();
	if(num<1) {
		return output;
	}
	outside_cone = all;
	for( int i = 0; i < num; i++ )
	{
		std::vector<MCParticle*> in_cone=Get_InCone(input[i],outside_cone, cone_size) ;
		MCParticle* New = Get_Sum(in_cone); 
		output.push_back(New);
	}
	return output;
}



float ToolSet::CMC::Get_IsolationAngle(MCParticle* MC, std::vector<MCParticle*> Ref, float minimal_energy_in_the_cone, float minimal_angle_from_input){
	// get the angle between MC and other particle, then rank the angle from small to large
	std::vector<std::pair<float,MCParticle*> >Ref_angle;
	for(unsigned int i=0;i<Ref.size();i++){
		if(MC==Ref[i]){continue;}
		std::pair<float,MCParticle*> pair_tmp = std::make_pair(Cal_Angle_Deg(MC,Ref[i]),Ref[i]);
		Ref_angle.push_back(pair_tmp);
	}
	std::sort(Ref_angle.begin(),Ref_angle.end(),Compare_as_Pair);

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

