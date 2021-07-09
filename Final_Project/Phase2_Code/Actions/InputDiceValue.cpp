#include "InputDiceValue.h"

#include "../Grid/Grid.h"
#include "../Player/Player.h"

InputDiceValue::InputDiceValue(ApplicationManager* pApp):Action(pApp)
{

}

void InputDiceValue::ReadActionParameters()
{
	//No Parameters For This Action
}

void InputDiceValue::Execute()
{
	Grid* pGrid = pManager->GetGrid(); // Get Grid
	if (pGrid->GetEndGame()) //Check if the Game is ended
		return;
	else
	{
		Input* PIn = pGrid->GetInput(); // Get Input 
		
		
		Output* pOut = pGrid->GetOutput(); // Get Output
		//Get Dice Number
		int diceNumber; 
		pOut->PrintMessage("Please Enter a Dice Number between 1 -6");
		diceNumber = PIn->GetInteger(pOut);
		//Ask For Validation
		if (diceNumber > 6 || diceNumber <1)
		{
			pGrid->PrintErrorMessage("Invalid Input: \"a dice number must be between 1-6\" Press to Continue...");
			return;
		}
		 // 3- Get the "current" player from pGrid
		Player* p = pGrid->GetCurrentPlayer();
        // 4- Move the currentPlayer using function Move of class player
		p->Move(pGrid, diceNumber);
		// 5- Advance the current player number of pGrid
		pGrid->AdvanceCurrentPlayer();

	}
}

InputDiceValue::~InputDiceValue()
{
}
