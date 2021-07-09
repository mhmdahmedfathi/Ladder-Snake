#include "DeleteGameObjectAction.h"
#include "Grid.h"
#include "Input.h"
#include "Output.h"

DeleteGameObjectAction::DeleteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
	pGrid = pManager->GetGrid();
	// Initializes the pManager pointer of Action with the passed pointer
}
DeleteGameObjectAction::~DeleteGameObjectAction()
{
}

void DeleteGameObjectAction::ReadActionParameters()
{


	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("Click on the game object you want to delete.");
	cellpos = pIn->GetCellClicked();
	//  Clear status bar
	pOut->ClearStatusBar();

}

void DeleteGameObjectAction::Execute()
{
	ReadActionParameters();
	pGrid = pManager->GetGrid();
	if (pGrid->GetGameObjects(cellpos) != NULL)
	{
		pGrid->RemoveObjectFromCell(cellpos);
	}
	else 
		pGrid->PrintErrorMessage("The clicked cell has no object to delete!.. Click to continue..");
}
