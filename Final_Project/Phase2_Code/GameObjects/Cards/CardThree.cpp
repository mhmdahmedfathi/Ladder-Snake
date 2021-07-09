#include "CardThree.h"
#include "../Ladder.h"
#include "../../GUIClasses/Output.h"
CardThree::CardThree(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 3; // set the inherited cardNumber data member with the card number (3 here)
}

CardThree::~CardThree(void)
{
}
void CardThree::ReadCardParameters(Grid* pGrid)
{

}

void CardThree::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid,pPlayer);
	CellPosition playerposition = pPlayer->GetCell()->GetCellPosition();
	Ladder* itsladder = pGrid->GetNextLadder(playerposition);
	if (itsladder != NULL)
	{
		pGrid->PrintErrorMessage("CONGRATULATIONS, go to the next ladder if exists..click to continue");
		CellPosition laddersposition = itsladder->GetPosition();
		pGrid->UpdatePlayerCell(pPlayer, laddersposition);
		Cell* pNewCell = pPlayer->GetCell();//Get The current cell
		GameObject* pobject = pNewCell->GetGameObject();//Get Pointer to the object on the cell
		if (pNewCell->HasLadder())//apply game object
			pobject->Apply(pGrid, pPlayer);

	}
	else
	{
		pPlayer->Move(pGrid, 0);
		pGrid->GetOutput()->PrintMessage("CONGRATULATIONS, go to the next ladder if exists..no ladders? HARD LUCK NEXT TIME!");
	}


}

