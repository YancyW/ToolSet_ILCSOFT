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



std::vector<MCParticle*> ToolSet::CMC::Get_MC_ParticleType(std::vector<MCParticle*> MCs,signed int PDG) {
	std::vector<MCParticle*> output;
	int num = MCs.size();
	for( int i = 0; i < num; i++ ){
		if(MCs[i]->getPDG()==PDG){
			output.push_back(MCs[i]);
		}
	}
	return(output);
}


std::vector<int> ToolSet::CMC::Get_ParentsPID(MCParticle* MC) {
	std::vector<int> ids;

	if(Get_Parents_Number(MC)!=0){
		for(int i=0;i<Get_Parents_Number(MC);i++){
			ids.push_back(MC->getParents()[i]->getPDG());
		}
	}
	else{
		ids.push_back(-1);
		ids.push_back(-1);
	}

	// always make sure ids has at least two elements, if not use -1 to instead.
	if(ids.size()==1){
		ids.push_back(-1);
	}
	return(ids);
}

std::vector<int> ToolSet::CMC::Get_DaughtersPID(MCParticle* MC) {
	std::vector<int> ids;

	if(Get_Daughters_Number(MC)!=0){
		for(int i=0;i<Get_Daughters_Number(MC);i++){
			ids.push_back(MC->getDaughters()[i]->getPDG());
		}
	}
	else{
		ids.push_back(-1);
		ids.push_back(-1);
	}

	// always make sure ids has at least two elements, if not use -1 to instead.
	if(ids.size()==1){
		ids.push_back(-1);
	}


	return(ids);
}


std::vector<MCParticle*> ToolSet::CMC::MCToPythiaShowering(MCParticle* input){
	std::vector<MCParticle*> output;
	if(Judge_PythiaShowering_FS(input)){
		output.push_back(input);
		return(output);
	}
	for(int i=0;i< Get_Parents_Number(input);i++){
		std::vector<MCParticle*> output_tmp;
		output_tmp=MCToPythiaShowering(input->getParents()[i]);
		for(unsigned int j=0;j< output_tmp.size();j++){
			output.push_back(output_tmp[j]);
		}
	}
	return(output);
}


std::vector<MCParticle*> ToolSet::CMC::MCToHardScattering(MCParticle* input){
	std::vector<MCParticle*> output;
	if(Judge_HardScattering_FS(input)){
		output.push_back(input);
		return(output);
	}
	for(int i=0;i< Get_Parents_Number(input);i++){
		std::vector<MCParticle*> output_tmp;
		output_tmp=MCToHardScattering(input->getParents()[i]);
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
		int pdg = std::abs(MC->getPDG());
		if(PDG=="quark"){
			if(pdg>=1 && pdg<=6){
				output.push_back(MC);
			}
		}
		else if(PDG=="light_quark"){
			if(pdg>=1 && pdg<=3){
				output.push_back(MC);
			}
		}
		else if(PDG=="heavy_quark"){
			if(pdg>=4 && pdg<=6){
				output.push_back(MC);
			}
		}
		else if(PDG=="lepton"){
			if(pdg==11 || pdg<=13){
				output.push_back(MC);
			}
		}
		else if(PDG=="neutrino"){
			if(pdg==12 || pdg==14 ||pdg==16){
				output.push_back(MC);
			}
		}
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
	if(pdg[0]==-5&&pdg[1]==5){
		channel = 5.0;
	}
	else if(pdg[0]==-4&&pdg[1]==4){
		channel = 4.0;
	}
	else if(pdg[0]==-6&&pdg[1]==6){
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
	else if(pdg[0]==-11&&pdg[1]==11){
		channel 	= 11.0;
	}
	else if(pdg[0]==-13&&pdg[1]==13){
		channel 	= 13.0;
	}
	else if(pdg[0]==-15&&pdg[1]==15){
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
	else if(pdg[0]==21&&pdg[1]==21){
		channel 	= 21.0;//gluon-gluon
	}
	else if(pdg[0]==22&&pdg[1]==22){
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

void ToolSet::CMC::Remove_Duplication(std::vector<MCParticle*> &MCs) {
	sort( MCs.begin(), MCs.end()  );
	MCs.erase( unique( MCs.begin(), MCs.end()  ), MCs.end()  );
}

std::vector<MCParticle*> ToolSet::CMC::Pass_DetectorAngle(std::vector<MCParticle*> &MCs) {
	int num = MCs.size();
	std::vector<MCParticle*> output;
	for( int i = 0; i < num; i++ ){
		MCParticle* MC = MCs[i];
		if(std::abs(Cal_CosTheta(MC))<0.996){
			output.push_back(MC);
		}
	}
	return(output);
}


MCParticle* ToolSet::CMC::Get_Visible(std::vector<MCParticle*> in){

	int num=in.size();

	MCParticle* visible;
	if(num<=0){
		visible=NewParticle(0,0,0,0,visible);
		return(visible);
	}

	TLorentzVector VS(0,0,0,0);
	for(int i=0;i<num;i++){
		TLorentzVector Vnew(in[i]->getMomentum(),in[i]->getEnergy());
		VS+=Vnew;
	}

	visible = NewParticle(VS[0],VS[1],VS[2],VS[3],visible);
	return(visible);

}



MCParticle* ToolSet::CMC::Get_InVisible(std::vector<MCParticle*> in){
	MCParticle* visible = Get_Visible(in);
	MCParticle* RCCollider=NewParticle(BEAM_ENERGY*sin(BEAM_ANGLE),0,0,BEAM_ENERGY,in[0]);

	MCParticle* invisible= Minus(RCCollider,visible);
	delete RCCollider;
	delete visible;
	return(invisible);
}

TLorentzVector ToolSet::CMC::Get_Visible_To_Lorentz(std::vector<MCParticle*> in){

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
	TLorentzVector visible = Get_Visible_To_Lorentz(in);
	TLorentzVector RCCollider=TLorentzVector(BEAM_ENERGY*sin(BEAM_ANGLE),0,0,BEAM_ENERGY);
	TLorentzVector invisible= RCCollider-visible;
	return(invisible);
}

