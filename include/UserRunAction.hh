#pragma once

#include "RunManager.hh"

class UserRunAction : public RunAction
{
public:
	UserRunAction();
	~UserRunAction() override;
	void EndOfCurrentStepOfRun() override;
	void EndOfRun() override;
};