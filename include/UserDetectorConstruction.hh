#pragma once

#include "RunManager.hh"

class UserDetectorConstruction : public DetectorConstruction
{
public:
	UserDetectorConstruction();
	~UserDetectorConstruction() override;
	void BuildGeometry() override;
    MaterialProperties* BuildProperties(TString);
};