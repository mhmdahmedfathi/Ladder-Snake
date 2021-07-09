#include "CardSeven.h"
#include "Output.h"
#include "RollDiceAction.h"
#include <time.h> 
CardSeven::CardSeven(const CellPosition& pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 7; // set the inherited cardNumber data member with the card number (7 here)
}

CardSeven::~CardSeven(void)
{
}
void CardSeven::ReadCardParameters(Grid* pGrid)
{

}
void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	pGrid->PrintErrorMessage("CONGRATULATIONS, you'll get another roll dice!...Click to roll");
	srand((int)time(NULL)); // time is for different seed each run
	int diceNumber = 1 + rand() % 6;
	pPlayer->Move(pGrid, diceNumber);
}



