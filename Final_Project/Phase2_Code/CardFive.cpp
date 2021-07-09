
#include "CardFive.h"


CardFive::CardFive(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 5; // set the inherited cardNumber data member with the card number (5 here)
}
CardFive::~CardFive(void)
{
}
void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer); // Calling Apply() of the base class Card to print the message that you reached this card number
	
	int DiceNum = pPlayer->GetjustRolledDiceNum(); // getting the justRolledDiceNum which the player will move
	
	pPlayer->Move(pGrid, DiceNum);// moving the player forward to the same number of steps that he just rolled 
	
}
