#pragma once

#include "RunManager.hh"

class UserPrimaryGeneratorAction : public PrimaryGeneratorAction 
{
	public:
	UserPrimaryGeneratorAction();
	~UserPrimaryGeneratorAction() override;
	void GeneratePrimaries() override;
};