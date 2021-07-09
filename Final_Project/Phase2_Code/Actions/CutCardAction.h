#pragma once

#include "Action.h"

class CutCardAction : public Action
{
	// 2- cell position of the card
	CellPosition cardPosition;


public:
	CutCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads action parameter ( cardPosition)

	virtual void Execute();
	virtual ~CutCardAction(); // A Virtual Destructor
};

