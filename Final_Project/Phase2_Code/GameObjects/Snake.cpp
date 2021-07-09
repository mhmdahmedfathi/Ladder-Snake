#include "Snake.h"
#include "../Player/Player.h"
#include "Cards/Card.h"

int  Snake::CountSnake = 0; //Iintialization for static data member

Snake::Snake(const CellPosition& startCellPos, const CellPosition& endCellPos) : GameObject(startCellPos)
{
	this->EndCellPos = endCellPos;
	CountSnake++;
	///TODO: Do the needed validation
}

Snake::Snake()
{
}

void Snake::Draw(Output* pOut) const
{
	pOut->DrawSnake(position, EndCellPos);
}

void Snake::Apply(Grid* pGrid, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a Snake. Click to continue ...");
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	pGrid->UpdatePlayerCell(pPlayer, EndCellPos);//Move Player
	Cell* pCell = pPlayer->GetCell();//Get The current cell
	GameObject* pobject = pCell->GetGameObject();//Get Pointer to the object on the cell
	if (pCell->HasCard())//apply game object
		pobject->Apply(pGrid, pPlayer);

}

CellPosition Snake::GetEndPosition() const
{
	return EndCellPos;
}
void Snake::Save(ofstream& OutFile, type T)
{
	if (T == snake)
	{
		int startcell = CellPosition::GetCellNumFromPosition(position);
		int endcell = CellPosition::GetCellNumFromPosition(GetEndPosition());
		OutFile << startcell << " " << endcell << endl;
	}
}
void  Snake::Load(ifstream& Infile)
{
	int startcell, endcell;
	Infile >> startcell >> endcell;
	position = CellPosition::GetCellPositionFromNum(startcell);
	EndCellPos = CellPosition::GetCellPositionFromNum(endcell);
}


Snake::~Snake()
{
}
