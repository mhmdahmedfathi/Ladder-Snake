#pragma once

#include "Action.h"

class SwitchToPlayModeAction : public Action
{
	// [Action Parameters]
	CellPosition cell;

public:
	SwitchToPlayModeAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters();

	virtual void Execute();

	virtual ~SwitchToPlayModeAction(); // A Virtual Destructor
};