#include "CardFour.h"
#include "Snake.h"
#include "Output.h"
CardFour::CardFour(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 4; // set the inherited cardNumber data member with the card number (4 here)
}

CardFour::~CardFour(void)
{
}
void CardFour::ReadCardParameters(Grid* pGrid)
{

}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	CellPosition playerposition = pPlayer->GetCell()->GetCellPosition();
	Snake* itssnake = pGrid->GetNextSnake(playerposition);
	if (itssnake != NULL)
	{
		pGrid->PrintErrorMessage("UNFORTUNATELY, go to the next snake if exists..click to continue");
		CellPosition snakesposition = itssnake->GetPosition();
		pGrid->UpdatePlayerCell(pPlayer, snakesposition);
		Cell* pNewCell = pPlayer->GetCell();//Get The current cell
		GameObject* pobject = pNewCell->GetGameObject();//Get Pointer to the object on the cell
		if (pNewCell->HasSnake())//apply game object
			pobject->Apply(pGrid, pPlayer);

	}
	else
	{
		pPlayer->Move(pGrid, 0);
		pGrid->GetOutput()->PrintMessage("UNFORTUNATELY, go to the next snake if exists.. no snakes? LUCKY ONE!");
	}
}


