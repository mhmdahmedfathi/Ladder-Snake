#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 

int Card::CountCard = 0;//Iintialization for static data member

Card::Card(const CellPosition& pos) : GameObject(pos) // sets the cell position of the GameObject
{
	CountCard++;
}

Card::Card()
{
}

void Card::SetCardNumber(int cnum)
{
	cardNumber = (cnum < 1 || cnum>14) ? -1 : cnum;
	
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::Draw(Output* pOut) const
{

	//n//TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);


}

void Card::ReadCardParameters(Grid* pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::EditCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::setposition(CellPosition pos)
{
	position = pos;
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

void Card::Save(ofstream &OutFile, type T)
{
	if (T == card)
	{
		OutFile <<endl << cardNumber << " ";
		int CellNum = CellPosition::GetCellNumFromPosition(GetPosition()); // getting cell number of card position 
		OutFile << CellNum << " ";
	}
	else return;
}
void Card::Load(ifstream& Infile)
{
	Infile >> cardNumber;	

	int CellNum;
	Infile >> CellNum;
	position = CellPosition::GetCellPositionFromNum(CellNum);
}

Card::~Card()
{
}
