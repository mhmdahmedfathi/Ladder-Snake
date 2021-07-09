#pragma once

#include "Action.h"


class EditCardAction: public Action
{
	// [Action Parameters]
	int cardNumber;            // 1- the card number
	CellPosition cardPosition; // 2- cell position of the card
	Card* editedCard;

public:
	EditCardAction(ApplicationManager *pApp); // A Constructor

	virtual void ReadActionParameters() ; // Reads EditCardAction action parameters (cardNumber, cardPosition)

	virtual void Execute();  // Executes EditCard action (code depends on action type so virtual)

	virtual ~EditCardAction();  // Virtual Destructor

};


