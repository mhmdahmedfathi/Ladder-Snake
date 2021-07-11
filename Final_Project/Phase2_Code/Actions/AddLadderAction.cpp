#include "AddLadderAction.h"

#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"
#include "../GameObjects/Ladder.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/Cards/Card.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{
	int x, y;
	Grid* pGrid = pManager->GetGrid();	//Get a pointer to the Grid
	Output* pOut = pGrid->GetOutput();	//Get a pointer to the output
	Input* pIn = pGrid->GetInput();		//Get a pointer to the input
	Ladder* pladder;					//Get a pointer to the Ladder
	Snake* psnake;						//Get a pointer to the Snake
	CellPosition NextLadderStart;		//Get a pointer to the StartCell of the ladder
	CellPosition NextLadderEnd;			//Get a pointer to the EndCell of the ladder
	
	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	
	//string debugstr = "VCell = " + to_string(startPos.VCell()) + " HCell = " + to_string(startPos.HCell());
	//pGrid->PrintErrorMessage(debugstr);
	
	//Check the Validation of StartPosition
	if (startPos.VCell() == 0)
	{
		pOut->PrintMessage("Start Cell can't be the most upper cell. Click to Continue...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	    Valid = false;
		return;
	}
	else if (startPos.GetCellNum() == 1) {
		pOut->PrintMessage("The ladder's start cell can't be the first cell. Click to Continue...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		Valid = false;
		return;
	}
	for (int i = startPos.VCell(); i >= 0; i--) {
		CellPosition StartPos = startPos;
		StartPos.SetVCell(i);
		psnake = pGrid->GetNextSnake(StartPos);

		if (psnake != NULL && psnake->GetPosition().HCell() == startPos.HCell())
		{
			if (psnake->GetEndPosition().GetCellNum() == startPos.GetCellNum()) {
				pOut->PrintMessage("Invalid: Start cell can't be an end of a snake. Click to Continue...");
				StartPos.RemoveVCell();
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
	for (int i = 8; i >= startPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;
		StartPos.SetVCell(i);
		pladder = pGrid->GetNextLadder(StartPos);
	   
		if (pladder != NULL && pladder->GetStartPosition().VCell() >=startPos.VCell())
		{
			NextLadderStart = pladder->GetPosition();
			NextLadderEnd = pladder->GetEndPosition();

			if (startPos.HCell() == NextLadderStart.HCell())
			{
				if (startPos.VCell() > NextLadderEnd.VCell())
				{
					pOut->PrintMessage("Two ladders cannot overlap. Click to Continue...");
				}
				else if (startPos.VCell() == NextLadderEnd.VCell()){
					pOut->PrintMessage("Start cell cannot be a end of another ladder. Click to Continue...");
				}
				else {
					continue;
				}
				StartPos.RemoveVCell();
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	
	// Check its Validation relative to the start cell
	if (endPos.HCell() != startPos.HCell()) {
		pOut->PrintMessage("Invalid: the start and end cell should be in the same column. Click to Continue...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		Valid = false;
		return;
	}
	if (endPos.VCell() >= startPos.VCell())
	{
		pOut->PrintMessage("Invalid: End cell can't be below or on the start cell. Click to Continue...");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		Valid = false;
		return;
	}

   for (int i = startPos.VCell(); i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;
		StartPos.SetVCell(i);
		pladder = pGrid->GetNextLadder(StartPos);

		if (pladder != NULL && pladder->GetStartPosition().GetCellNum() <= endPos.GetCellNum())
		{
			NextLadderStart = pladder->GetPosition();
			NextLadderEnd = pladder->GetEndPosition();

			if (endPos.HCell() == NextLadderStart.HCell())
			{
				if (endPos.VCell() < NextLadderStart.VCell())
				{
					pOut->PrintMessage("Two ladders cannot overlap. Click to Continue...");
					StartPos.RemoveVCell();
				}
				else if (endPos.VCell() == NextLadderStart.VCell()) {
					pOut->PrintMessage("End cell cannot be a start of another ladder. Click to Continue...");
					StartPos.RemoveVCell();
				}
				else {
					continue;
				}
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
   
   GameObject* pGameobject = pGrid->GetGameObjects(endPos);

   if (pGameobject != NULL && dynamic_cast<Snake*>(pGameobject) != NULL && pGameobject->GetPosition().GetCellNum() == endPos.GetCellNum())
   {
	   pOut->PrintMessage("Invalid: end cell cannot be a start of a snake. Click to Continue...");
	   pIn->GetPointClicked(x, y);
	   pOut->ClearStatusBar();
	   Valid = false;
	   return;
   }
   
	pOut->ClearStatusBar();
	// Clear messages
}


// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	if (Valid)
	{

		// Create a Ladder object with the parameters read from the user
		Ladder* pLadder = new Ladder(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pLadder);

		// if the GameObject cannot be added
		if (!added)
		{
			delete pLadder;
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}
}
