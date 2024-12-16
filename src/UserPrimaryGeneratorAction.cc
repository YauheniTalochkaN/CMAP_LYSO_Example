#include "UserPrimaryGeneratorAction.hh"

UserPrimaryGeneratorAction::UserPrimaryGeneratorAction() : PrimaryGeneratorAction()
{

}

UserPrimaryGeneratorAction::~UserPrimaryGeneratorAction()
{

}

void UserPrimaryGeneratorAction::GeneratePrimaries()
{    
    TrackPoint primary_particle;
    primary_particle.kinetic_energy = 1.0 * unit_eV;
    primary_particle.momentum_direction = TVector3(1, 0, 0);
    primary_particle.point = TVector3(0, 0, 0);
    primary_particle.time = 0;
    RunManager::getInstance()->GetTrackPropagation()->AddNewTrack(RunManager::getInstance()->GetPhysicsList()->CreateElectron(primary_particle));
}