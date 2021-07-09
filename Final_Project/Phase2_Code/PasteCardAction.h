#pragma once

#include "Action.h"

class PasteCardAction : public Action
{
	CellPosition newCardPosition;


public:
	PasteCardAction(ApplicationManager* pApp); // A Constructor

	virtual void ReadActionParameters(); // Reads  action parameter ( cardPosition)

	virtual void Execute();
	virtual ~PasteCardAction(); // A Virtual Destructor
};

