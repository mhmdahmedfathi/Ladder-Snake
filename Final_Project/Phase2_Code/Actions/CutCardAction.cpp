#include "CutCardAction.h"
#include "../Grid/Grid.h"
#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"
#include "../GameObjects/Cards/CardOne.h"

CutCardAction::CutCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CutCardAction::~CutCardAction()
{
}

void CutCardAction::ReadActionParameters()
{
	// 1- Get a Pointer to the Input / Output Interfaces

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardPosition" parameter (its cell position) 
	pOut->PrintMessage("Click on the source cell.");
	cardPosition = pIn->GetCellClicked();
	//  Clear status bar
	pOut->ClearStatusBar();
}

void CutCardAction::Execute()
{
	ReadActionParameters();
	Card* pCard = NULL; // will point to the card object type

	Grid* pGrid = pManager->GetGrid();
	pCard = pGrid->HasCard(cardPosition);
	if (pCard != NULL)
	{
		
		pGrid->SetClipboard(pCard);
		pGrid->RemoveObjectFromCell(cardPosition);
		pGrid->PrintErrorMessage("The card has been successfully cut. Click to refresh...");
		
	}
	else
		pGrid->PrintErrorMessage("You've clicked on a cell that doesn't contain a card!");

}
