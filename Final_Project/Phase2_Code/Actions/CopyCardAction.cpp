#include "CopyCardAction.h"
#include "../Grid/Grid.h"
#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"

CopyCardAction::CopyCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

CopyCardAction::~CopyCardAction()
{
}

void CopyCardAction::ReadActionParameters()
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

void CopyCardAction::Execute()
{
	ReadActionParameters();
	Card* pCard = NULL; // will point to the card object type

	Grid* pGrid = pManager->GetGrid();
	pCard = pGrid->HasCard(cardPosition);
	if (pCard != NULL)
	{
		pGrid->SetClipboard(pCard);
		pGrid->PrintErrorMessage("The card has been successfully copied..Click to continue");
	}
	else
		pGrid->PrintErrorMessage("You've clicked on a cell that doesn't contain a card!");
	pGrid->UpdateInterface();

}
