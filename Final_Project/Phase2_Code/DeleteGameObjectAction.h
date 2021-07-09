#pragma once

#include "Action.h"

class DeleteGameObjectAction : public Action
{
	// [Action Parameters]
	CellPosition cellpos; // cell position of the object
	Grid* pGrid; 

public:
	DeleteGameObjectAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads DeleteGameObject action parameters 

	virtual void Execute();

	virtual ~DeleteGameObjectAction(); // A Virtual Destructor
};

