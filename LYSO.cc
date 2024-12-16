#include "UserDetectorConstruction.hh"
#include "UserPrimaryGeneratorAction.hh"
#include "UserRunAction.hh"

int main(int argc, char *argv[])
{
	gRandom->SetSeed(time(NULL));

	if(argc<2)
	{
    	printf("Not indicated config file! \n");
		return -1;
    }

	RunManager* Run_Manager = RunManager::getInstance();
	Run_Manager->SetDetectorConstruction(new UserDetectorConstruction());
	Run_Manager->SetRunAction(new UserRunAction());
	Run_Manager->SetPrimaryGeneratorAction(new UserPrimaryGeneratorAction());
	Run_Manager->SetTrackPropagation(new TrackPropagation());	
	Run_Manager->SetPhysicsList(new PhysicsList());
	Run_Manager->SetTGeoManager(new TGeoManager("Geometry", "Geometry"));	
	
	Run_Manager->ReadParam(argv[1]);
	Run_Manager->Initialization();

	Run_Manager->Launch();

	Run_Manager->SaveGeom("Geometry.root");

	delete Run_Manager;

	return 0;
}