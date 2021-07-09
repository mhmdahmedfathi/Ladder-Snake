#pragma once
#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 
class CardFourteen : public Card
{
	static int CardPrice;
	static int Fees;
	static bool Exists14;
	static bool isBought;
	static Player* cardOwner;
	static int Only1Time;// to make sure that we saved fees and price only one time
	static int Only1TimeLoad;

public:
	CardFourteen(const CellPosition& pos); // A Constructor takes card position
	CardFourteen();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardFourteen which is: 

	virtual void EditCardParameters(Grid* pGrid); // Edits the parameters of CardFourteen which is: Cardprice and Fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFourteen on the passed Player
	virtual void Load(ifstream& Infile);
	virtual void Save(ofstream& OutFile, type T);//TO SAVE CARD 14


	virtual ~CardFourteen(); // A Virtual Destructor
};

