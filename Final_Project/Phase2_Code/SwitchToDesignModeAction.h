#pragma once

#include "Action.h"

class SwitchToDesignModeAction : public Action
{
	// [Action Parameters]
	CellPosition cell;
	


public:
	SwitchToDesignModeAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SwitchToDesignModeAction(); // A Virtual Destructor
};
