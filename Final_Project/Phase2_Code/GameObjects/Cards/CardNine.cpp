
#include "CardNine.h"
#include <iostream>
using namespace std;
#include <fstream> 



CardNine::CardNine(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 9; // set the inherited cardNumber data member with the card number (9 here)
}

CardNine::CardNine()
{
}

CardNine::~CardNine(void)
{
}

void CardNine::ReadCardParameters(Grid * pGrid)
{

	// Geting a Pointer to the Input / Output Interfaces from the Grid
	Input * pi = pGrid->GetInput();
	Output * po = pGrid->GetOutput();
	
	
		// printing a descriptive message to the user
		po->PrintMessage("New CardNine : Enter cell number you want to move to...");
		int CELLNUM = pi->GetInteger(po);
	
		while (CELLNUM > 99 || CELLNUM <= 0){
			po->PrintMessage("Cell number must be between 1-99, Enter cell number again...");
			CELLNUM = pi->GetInteger(po);
		}
		CellToMove = CellToMove.GetCellPositionFromNum(CELLNUM);
		po->ClearStatusBar();// Clearing the status bar

}
void  CardNine::Load(ifstream& Infile)
{
	int cellnum;
	Infile >> cellnum;
	CellToMove = CellPosition::GetCellPositionFromNum(cellnum);
}




void CardNine::EditCardParameters(Grid * pGrid)
{
	// Geting a Pointer to the Input / Output Interfaces from the Grid
	Input * pi = pGrid->GetInput();
	Output * po = pGrid->GetOutput();
	
		// printing a descriptive message to the user
		po->PrintMessage("Editing CardNine: Enter cell number want the passing player to move to... ");
		int CELLNUM = pi->GetInteger(po);

		while (CELLNUM>99 || CELLNUM <= 0){
			po->PrintMessage("Cell number must be between 1-99, Enter the cell number again... ");
			CELLNUM = pi->GetInteger(po);
		}

		CellToMove = CellToMove.GetCellPositionFromNum(CELLNUM);

		po->ClearStatusBar();// Clearing the status bar
		
		pGrid->PrintErrorMessage("Card Edited Successfully, Click to continue... ");

}

void CardNine::Save(ofstream &OutFile, type T)
{
	if (T == card)
	{
		Card::Save(OutFile, card);
		int cellnum = CellToMove.GetCellNum();
		OutFile << cellnum;//saving cell number of the cell that card 2 sent the player to

	}
}
void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);

	pGrid->PrintErrorMessage("You will move to cell "+to_string (CellPosition ::GetCellNumFromPosition(CellToMove))+" Click to Move...");
	// updating player cell with the cell specified by the user
	pGrid->UpdatePlayerCell(pPlayer, CellToMove);
}
