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
	Grid* pGrid = pManager->GetGrid();

	Card* pCard = NULL;		// will point to a card if exists in the same clicked cell
	Ladder* pLadder = NULL; // will point to a ladder if exists in the same clicked cell
	Snake* pSnake = NULL; // will point to a ladder if exists in the same clicked cell
	
	//VALIDATIONS
	//checking if there was a card in the same clicked cell
	pCard = pGrid->HasCard(newCardPosition);
	pLadder = pGrid->HasLadder(newCardPosition);
	pSnake = pGrid->HasSnake(newCardPosition);

	if (pCard != NULL)
		pGrid->PrintErrorMessage("Invalid Paste: You've clicked on a cell that already contains a CARD!");
	else if (pLadder != NULL)
		pGrid->PrintErrorMessage("Invalid Paste: You've clicked on a cell that contains a start of a LADDER!");
	else if (pSnake != NULL)
		pGrid->PrintErrorMessage("Invalid Paste: You've clicked on a cell that contains a start of a SNAKE!");
	else
	{
		pCard = pGrid->GetClipboard();
		pCard->setposition(newCardPosition);
		pGrid->AddObjectToCell(pCard);
	}
}


