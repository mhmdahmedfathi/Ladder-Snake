#include "CardEight.h"


CardEight::CardEight(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 8; // set the inherited cardNumber data member with the card number (8 here)
}

CardEight::~CardEight(void)
{
}

void CardEight::ReadCardParameters(Grid* pGrid)
{

}


void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{

	if ((pPlayer->getWillMove()) == 0)
	{
		Card::Apply(pGrid, pPlayer);

		//the first time to reach card eight
		pGrid->PrintErrorMessage("UnFortunately you are prevented from Rolling next turn, Click to continue..  ");
		pPlayer->setWillMove(1);

	}
	else if ((pPlayer->getWillMove()) == 1)
	{
		pGrid->PrintErrorMessage("We told you: you won't move, next turn inshallah, Click to continue..  ");
		pPlayer->setWillMove(2);

	}
	else if ((pPlayer->getWillMove()) == 2)
	{
		pGrid->PrintErrorMessage("It's time to be free, Click to continue..  ");
		pPlayer->setWillMove(0);

	}
}
