#include "CMC.h"


MCParticle* ToolSet::CMC::NewParticle(float px, float py, float pz,float E,MCParticle* test){
	MCParticleImpl* tmp= new MCParticleImpl;
    double Pnew[3] = {px,py,pz};
    tmp->setMomentum(Pnew);
	double mass2= std::pow(E,2)-std::pow(px,2)-std::pow(py,2)-std::pow(pz,2);
	double mass;
	if(mass2>=0){
		mass= std::sqrt(mass2);
	}
	else{
		mass=-std::sqrt(-mass2);
	}
    tmp->setMass(mass);
	MCParticle* new_particle=dynamic_cast<MCParticle*>(tmp);
	return(new_particle);
}

MCParticle&  ToolSet::operator +(const MCParticle &MC1, const MCParticle & MC2) {
	MCParticleImpl* MC = new MCParticleImpl ;
	TVector3  p1=MC1.getMomentum();
	TVector3  p2=MC2.getMomentum();
	TVector3  p0=p1+p2;
	double energy=(MC1.getEnergy()+MC2.getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double mass;
	if(mass2>=0){
		mass= std::sqrt(mass2);
	}
	else{
		mass=-std::sqrt(-mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	MC->setMomentum(fl0);
	MC->setMass    (mass);
	MC->setCharge  (MC1.getCharge()+MC2.getCharge());
	MC->setPDG     (10000); 
	MCParticle* MC0 = dynamic_cast<MCParticle*> (MC);
	return(*MC0);
}


MCParticle*  ToolSet::CMC::Equal(const MCParticle* MC1) {
	MCParticleImpl* MC = new MCParticleImpl ;
	TVector3  p1=MC1->getMomentum();
	double fl0[3]={p1.Px(),p1.Py(),p1.Pz()};
	MC->setMomentum(fl0);
	MC->setMass    (MC1->getMass());
	MC->setCharge  (MC1->getCharge());
	MC->setPDG     (MC1->getPDG()); 
	MCParticle* MC0 = dynamic_cast<MCParticle*> (MC);
	return(MC0);
}


MCParticle*  ToolSet::CMC::Add(const MCParticle* MC1, const MCParticle* MC2) {
	MCParticleImpl* MC = new MCParticleImpl ;
	TVector3  p1=MC1->getMomentum();
	TVector3  p2=MC2->getMomentum();
	TVector3  p0=p1+p2;
	double energy=(MC1->getEnergy()+MC2->getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double     mass;
	if(mass2>=0){
		mass= std::sqrt(mass2);
	}
	else{
		mass=-std::sqrt(-mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	MC->setMomentum(fl0);
	MC->setMass    (mass);
	MC->setCharge  (MC1->getCharge()+MC2->getCharge());
	MC->setPDG     (10000); 
	MCParticle* MC0 = dynamic_cast<MCParticle*> (MC);
	return(MC0);
}


MCParticle*  ToolSet::CMC::Minus(const MCParticle* MC1, const MCParticle* MC2) {
	MCParticleImpl* MC = new MCParticleImpl ;
	TVector3  p1=MC1->getMomentum();
	TVector3  p2=MC2->getMomentum();
	TVector3  p0=p1-p2;
	double energy=(MC1->getEnergy()-MC2->getEnergy());
	double mass2= std::pow(energy,2)-p0.Mag2();
	double     mass;
	if(mass2>=0){
		mass= std::sqrt(mass2);
	}
	else{
		mass=-std::sqrt(-mass2);
	}
	double fl0[3]={p0.Px(),p0.Py(),p0.Pz()};
	MC->setMomentum(fl0);
	MC->setMass    (mass);
	MC->setCharge  (MC1->getCharge());
	MC->setPDG     (10000); 
	MCParticle* MC0 = dynamic_cast<MCParticle*> (MC);
	return(MC0);
}




TLorentzVector  ToolSet::CMC::Minus_To_Lorentz(const MCParticle* MC1, const MCParticle* MC2) {
	TLorentzVector p1=TLorentzVector(MC1->getMomentum(),MC1->getEnergy());
	TLorentzVector p2=TLorentzVector(MC2->getMomentum(),MC2->getEnergy());
	TLorentzVector p0=p1-p2;
	return(p0);
}

