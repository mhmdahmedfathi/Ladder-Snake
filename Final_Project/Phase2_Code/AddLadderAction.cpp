#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

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
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();//get a pointer to the Grid
	Output* pOut = pGrid->GetOutput();//Get a pointer to the output
	Input* pIn = pGrid->GetInput();//GEt a pointer to the input
	Ladder* pladder;//GEt a pointer to the Ladder
	CellPosition NextLadderStart;//GEt a pointer to the StartCell of the ladder
	CellPosition NextLadderEnd;//GEt a pointer to the EndCell of the ladder
	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	//Check the Validation of StartPosition
	if (startPos.VCell() == 0)
	{
		pOut->PrintMessage("Check Ladder Specification");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
	    Valid = false;
		return;
	}
	for (int i = 8; i >= startPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;//initialize the StartPos Hcell
		StartPos.SetVCell(i);//Set the StartPos VCell
		pladder = pGrid->GetNextLadder(StartPos);//Get the Ladder have the same hcell
		if (pladder != NULL ) //The Cell Have a ladder
		{
			NextLadderEnd = pladder->GetEndPosition();//Get the end of the Ladder
			if (startPos.GetCellNum() == NextLadderEnd.GetCellNum())
			{
				pOut->PrintMessage("Start cell cannot be a end of another ladder or snake");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
	for (int i = 8; i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;
		StartPos.SetVCell(i);
		pladder = pGrid->GetNextLadder(StartPos);
	   
		if (pladder != NULL)
		{
			NextLadderStart = pladder->GetPosition();
			NextLadderEnd = pladder->GetEndPosition();

			if (startPos.HCell() == NextLadderStart.HCell() && (startPos.VCell() < NextLadderStart.VCell() && startPos.VCell() > NextLadderEnd.VCell()))
			{
				pOut->PrintMessage("Two ladders cannot overlap");
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
	// Check its Validation
	if (endPos.VCell() > startPos.VCell())
	{
		pOut->PrintMessage("end cell cannot be smaller than start cell");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		Valid = false;
		return;
	}
		
	for (int i = startPos.VCell() ; i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;
		StartPos.SetVCell(i);
		GameObject* pGameobject = pGrid->GetGameObjects(StartPos);
		
		if (pGameobject!=NULL)
		{
			NextLadderEnd=pGameobject->GetPosition();
			if (endPos.GetCellNum() == NextLadderEnd.GetCellNum())
			{
				pOut->PrintMessage("end cell cannot be a start of another ladder or snake");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
   for (int i = startPos.VCell(); i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;
		StartPos.SetVCell(i);
		pladder = pGrid->GetNextLadder(StartPos);

		if (pladder != NULL)
		{
			NextLadderStart = pladder->GetPosition();
			NextLadderEnd = pladder->GetEndPosition();

			if (endPos.HCell() == NextLadderStart.HCell() && (endPos.VCell() < NextLadderStart.VCell() || startPos.VCell() > NextLadderEnd.VCell()))
			{
				pOut->PrintMessage("Two ladders cannot overlap");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
if (endPos.VCell() == startPos.VCell())
{
	pOut->PrintMessage("end cell and start cell are not in the same column ");
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	Valid = false;
	return;
}
	pOut->ClearStatusBar();
	///TODO: Make the needed validations on the read parameters
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
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction
	}
}
