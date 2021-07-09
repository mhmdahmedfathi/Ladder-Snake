#include "Ladder.h"
#include "Player.h"
#include"Card.h"

int Ladder::CountLadder = 0; //Iintialization for static data member

Ladder::Ladder(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;
	CountLadder++;
	///TODO: Do the needed validation
}

Ladder::Ladder()
{
}

void Ladder::Draw(Output* pOut) const
{
	pOut->DrawLadder(position, endCellPos);
}

void Ladder::Apply(Grid* pGrid, Player* pPlayer) 
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	// == Here are some guideline steps (numbered below) to implement this function ==
	Output *pOut = pGrid->GetOutput();//Get Output
	Input* pIn = pGrid->GetInput(); //Get Input
	// 1- Print a message "You have reached a ladder. Click to continue ..." and wait mouse click
	pOut->PrintMessage("You have reached a ladder. Click to continue ...");
	int x, y;//Cordinates
	pIn->GetPointClicked(x,y);//Wait Mouse Click
	pOut->ClearStatusBar(); //Clear Bar
	// 2- Apply the ladder's effect by moving the player to the endCellPos
	
	pGrid->UpdatePlayerCell(pPlayer , endCellPos);//Move Player
	Cell* pCell = pPlayer->GetCell();//Get The current cell
	GameObject* pobject = pCell->GetGameObject();//Get Pointer to the object on the cell
	if (pCell->HasCard())//apply game object
		pobject->Apply(pGrid, pPlayer);
	//    Review the "pGrid" functions and decide which function can be used for that
	
}

CellPosition Ladder::GetEndPosition() const
{
	return endCellPos;
}

CellPosition Ladder::GetStartPosition() const {
	//the startcell position is the position object of the gameObject Parent
	return GetPosition();
}

void  Ladder::Save(ofstream& OutFile, type T)
{
	if (T == ladder)
	{
		int startcell = CellPosition::GetCellNumFromPosition(position);
		int endcell = CellPosition::GetCellNumFromPosition(GetEndPosition());
		OutFile << startcell << " " << endcell << endl;
	}
}


void Ladder::Load(ifstream& Infile)
{
	int startcell, endcell;
	Infile >> startcell >> endcell;
	position = CellPosition::GetCellPositionFromNum(startcell);
	endCellPos = CellPosition::GetCellPositionFromNum(endcell);
}
Ladder::~Ladder()
{
}
