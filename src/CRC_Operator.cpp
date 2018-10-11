#include "CRC.h" 

ReconstructedParticle*  ToolSet::CRC::Add(const ReconstructedParticle* RC1, const ReconstructedParticle* RC2) {
	ReconstructedParticleImpl* RC = new ReconstructedParticleImpl;
	TVector3  p1=RC1->getMomentum();
	TVector3  p2=RC2->getMomentum();
	TVector3  p0=p1+p2;
	double energy=(RC1->getEnergy()+RC2->getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double mass;
	if(mass2<0){
		mass=0;
	}
	else{
		mass= std::sqrt(mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	RC->setMomentum(fl0);
	RC->setMass    (mass);
	RC->setEnergy(energy);
	RC->setCharge  (RC1->getCharge()+RC2->getCharge());
	RC->setType    (10000); 
	ReconstructedParticle* RC0 = dynamic_cast<ReconstructedParticle*> (RC);
	return(RC0);
}



ReconstructedParticle*  ToolSet::CRC::Minus(const ReconstructedParticle* RC1, const ReconstructedParticle* RC2) {
	ReconstructedParticleImpl* RC = new ReconstructedParticleImpl;
	TVector3  p1=RC1->getMomentum();
	TVector3  p2=RC2->getMomentum();
	TVector3  p0=p1-p2;
	double energy=(RC1->getEnergy()-RC2->getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double mass;
	if(mass2<0){
		mass=0;
	}
	else{
		mass= std::sqrt(mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	RC->setMomentum(fl0);
	RC->setMass    (mass);
	RC->setEnergy  (energy);
	RC->setCharge  (RC1->getCharge());
	RC->setType    (10000); 
	ReconstructedParticle* RC0 = dynamic_cast<ReconstructedParticle*> (RC);
	return(RC0);
}


ReconstructedParticle*  ToolSet::CRC::Equal(const ReconstructedParticle* MC1) {
	ReconstructedParticleImpl* MC = new ReconstructedParticleImpl;
	TVector3  p1=MC1->getMomentum();
	double fl0[3]={p1.Px(),p1.Py(),p1.Pz()};
	MC->setMomentum(fl0);
	MC->setMass    (MC1->getMass());
	MC->setEnergy  (MC1->getEnergy());
	MC->setCharge  (MC1->getCharge());
	MC->setType    (MC1->getType()); 
	ReconstructedParticle* MC0 = dynamic_cast<ReconstructedParticle*> (MC);
	return(MC0);
}


ReconstructedParticle* ToolSet::CRC::NewParticle(double px, double py, double pz,double E, ReconstructedParticle* test){
	ReconstructedParticleImpl* tmp= new ReconstructedParticleImpl;
	double Pnew[3] = {px,py,pz};
	tmp->setMomentum(Pnew);
	tmp->setEnergy(E);
	ReconstructedParticle* new_particle=dynamic_cast<ReconstructedParticle*>(tmp);
	return(new_particle);
}

ReconstructedParticle&  ToolSet::operator +(const ReconstructedParticle &RC1, const ReconstructedParticle &RC2) {
	ReconstructedParticleImpl* RC = new ReconstructedParticleImpl;
	TVector3  p1=RC1.getMomentum();
	TVector3  p2=RC2.getMomentum();
	TVector3  p0=p1+p2;
	double energy=(RC1.getEnergy()+RC2.getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double mass;
	if(mass2<0){
		mass=0;
	}
	else{
		mass= std::sqrt(mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	RC->setMomentum(fl0);
	RC->setEnergy(energy);
	RC->setMass    (mass);
	RC->setCharge  (RC1.getCharge()+RC2.getCharge());
	RC->setType    (10000); 
	ReconstructedParticle* RC0 = dynamic_cast<ReconstructedParticle*> (RC);
	return(*RC0);
}

ReconstructedParticle&  ToolSet::operator -(const ReconstructedParticle &RC1, const ReconstructedParticle &RC2) {
	ReconstructedParticleImpl* RC = new ReconstructedParticleImpl;
	TVector3  p1=RC1.getMomentum();
	TVector3  p2=RC2.getMomentum();
	TVector3  p0=p1-p2;
	double energy=(RC1.getEnergy()-RC2.getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double mass;
	if(mass2<0){
		mass=0;
	}
	else{
		mass= std::sqrt(mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	RC->setMomentum(fl0);
	RC->setEnergy(energy);
	RC->setMass    (mass);
	RC->setCharge  (RC1.getCharge()+RC2.getCharge());
	RC->setType    (10000); 
	ReconstructedParticle* RC0 = dynamic_cast<ReconstructedParticle*> (RC);
	return(*RC0);
}



bool ToolSet::CRC::Same_Particle(const ReconstructedParticle* MC1,const ReconstructedParticle* MC2){
	if(std::abs(MC1->getEnergy()-MC2->getEnergy())<0.00000001){
		return(true);
	}
	return(false);
}
