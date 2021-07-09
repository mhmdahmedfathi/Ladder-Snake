
#pragma once
#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 
class CardTwo : public Card
{
	// CardTwo Parameters:
int walletvalue; //the wallet value to increase to the player

public:
	CardTwo(const CellPosition & pos); // A Constructor takes card position
	virtual void Load(ifstream& Infile);
	CardTwo();
	virtual ~CardTwo(void);  // A Virtual Destructor
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardTwo which is: walletvalue

	void EditCardParameters(Grid * pGrid); // Edits the parameters of CardTwo which is: walletValue

	virtual void Save(ofstream &OutFile, type T);//TO SAVE CARD TWO

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwo on the passed Player
	// by incrementing the player's wallet by the wallevalue data member

};
