#include "PasteCardAction.h"
#include "../Grid/Grid.h"
#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"
#include "../GameObjects/Cards/CardOne.h"


PasteCardAction::PasteCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

PasteCardAction::~PasteCardAction()
{
}

void PasteCardAction::ReadActionParameters()
{

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Read the "cardPosition" parameter (its cell position) 
	pOut->PrintMessage("Click on the destination cell.");
	newCardPosition = pIn->GetCellClicked();
	// Clear status bar
	pOut->ClearStatusBar();
}

void PasteCardAction::Execute()
{
	ReadActionParameters();
	Card::CountCard++;
	Card* pCard = NULL; // will point to the card object type
	Grid* pGrid = pManager->GetGrid();
	//first we have to check a card in the clicked cell
	pCard = pGrid->HasCard(newCardPosition);
	if (pCard != NULL)
		pGrid->PrintErrorMessage("You've clicked on a cell that already contains a CARD!");
	else
	{
		pCard = pGrid->GetClipboard();
		pCard->setposition(newCardPosition);
		pGrid->AddObjectToCell(pCard);
	}
}


