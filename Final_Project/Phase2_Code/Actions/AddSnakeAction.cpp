#include "AddSnakeAction.h"

#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/Ladder.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	int x, y;
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();//get a pointer to the Grid
	Output* pOut = pGrid->GetOutput();//Get a pointer to the output
	Input* pIn = pGrid->GetInput();//GEt a pointer to the input
	Snake *pSnake;//GEt a pointer to the Snake
	CellPosition NextSnakeStart;//GEt a pointer to the StartCell of the Snake
	CellPosition NextSnakeEnd;//GEt a pointer to the EndCell of the Snake
	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	//Check the Validation of StartPosition
	if (startPos.VCell() == 8)
	{
		pOut->PrintMessage("Check Snake Specification");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		Valid = false;
		return;
	}
	for (int i = 8; i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos;//initialize the StartPos Hcell
		StartPos.SetVCell(i);//Set the StartPos VCell
		pSnake = pGrid->GetNextSnake(StartPos);//Get the Snake have the same hcell
		Ladder* pladder = pGrid->GetNextLadder(StartPos);
		if (pSnake != NULL ) //The Cell Have a Snake
		{
			NextSnakeEnd = pSnake->GetEndPosition();//Get the end of the Snake
			if (startPos.GetCellNum() == NextSnakeEnd.GetCellNum() )
			{
				pOut->PrintMessage("Start cell cannot be a end of another ladder or snake");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
		if (pladder != NULL) //The Cell Have a ladder
		{
			CellPosition NextLadderEnd = pladder->GetEndPosition(); // Get the end of the ladder
			if ( startPos.GetCellNum() == NextLadderEnd.GetCellNum()) //check the validity
			{
				pOut->PrintMessage("Start cell cannot be a end of another ladder or snake");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
	for (int i = 8; i >= 0; i--)
	{
		CellPosition StartPos = startPos; //get the HCell
		StartPos.SetVCell(i); //set VCell
		pSnake = pGrid->GetNextSnake(StartPos); // search for snake

		if (pSnake != NULL)
		{
			NextSnakeStart = pSnake->GetPosition(); // get a pointer to the start of the snake
			NextSnakeEnd = pSnake->GetEndPosition();// get a pointer to the end of the snake

			if (startPos.HCell() == NextSnakeStart.HCell() && ((startPos.VCell() >= NextSnakeStart.VCell() && startPos.VCell() <= NextSnakeEnd.VCell()) ))
			{
				pOut->PrintMessage("Two Snakes cannot overlap");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();
	// Check its Validation
	if (endPos.VCell() < startPos.VCell())
	{
		pOut->PrintMessage("end cell cannot be smaller than start cell");
		pIn->GetPointClicked(x, y);
		pOut->ClearStatusBar();
		Valid = false;
		return;
	}

	for (int i = 8; i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos; //get the HCell
		StartPos.SetVCell(i); //set VCell
		GameObject* pGameobject = pGrid->GetGameObjects(StartPos); // get a pointer to the game object

		if (pGameobject != NULL)
		{
			NextSnakeStart = pGameobject->GetPosition();//get a pointer to start of the snake
			if (endPos.GetCellNum() == NextSnakeStart.GetCellNum())
			{
				pOut->PrintMessage("end cell cannot be a start of another ladder or snake");
				pIn->GetPointClicked(x, y);
				pOut->ClearStatusBar();
				Valid = false;
				return;
			}
		}
	}
	for (int i = 8; i >= endPos.VCell(); i--)
	{
		CellPosition StartPos = startPos; //get the HCell
		StartPos.SetVCell(i); //set VCell
		pSnake = pGrid->GetNextSnake(StartPos); // search for snake

		if (pSnake != NULL)
		{
			NextSnakeStart = pSnake->GetPosition();//get a pointer to the start of the snake
			NextSnakeEnd = pSnake->GetEndPosition();//get a pointer to the end of the snake

			if (endPos.HCell() == NextSnakeStart.HCell() &&( (endPos.VCell() > NextSnakeStart.VCell() && endPos.VCell() < NextSnakeEnd.VCell()) || (startPos.VCell() < NextSnakeStart.VCell() && endPos.VCell() > NextSnakeStart.VCell()) || (endPos.GetCellNum() == NextSnakeEnd.GetCellNum())))
			{
				pOut->PrintMessage("Two Snakes cannot overlap");
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
void AddSnakeAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (Valid) // check the validity

		// Create a Snake object with the parameters read from the user
	{
		Snake* pSnake = new Snake(startPos, endPos);

		Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

		// Add the card object to the GameObject of its Cell:
		bool added = pGrid->AddObjectToCell(pSnake);

		// if the GameObject cannot be added
		if (!added)
		{
			// Print an appropriate message
			pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
		}
		// Here, the Snake is created and added to the GameObject of its Cell, so we finished executing the AddSnakeAction
	}
}
