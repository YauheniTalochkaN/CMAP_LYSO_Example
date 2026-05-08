#pragma once

#include "RunManager.hh"

class UserWorldConstruction : public WorldConstruction
{
public:
	UserWorldConstruction();
	~UserWorldConstruction() override;
	void BuildGeometry() override;
    MaterialProperties* BuildProperties(const TString&);
};