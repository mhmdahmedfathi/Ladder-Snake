
#include "CardSix.h"

CardSix::CardSix(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 6; // set the inherited cardNumber data member with the card number (6 here)
}

CardSix::~CardSix(void)
{
}

void CardSix::ReadCardParameters(Grid * pGrid)
{


	///NO parameters to read from user

}

void CardSix::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer); // Calling Apply() of the base class Card to print the message that you reached this card number
	
	int DiceNum = pPlayer->GetjustRolledDiceNum(); // getting the justRolledDiceNum which the player will move
	
	pPlayer->Move(pGrid, -DiceNum);;// moving the player backward to the same number of steps that he just rolled 
	
}
