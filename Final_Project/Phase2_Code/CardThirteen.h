#pragma once
#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 


class CardThirteen : public Card
{
	static int CardPrice;
	static int Fees;
	static bool Exists13;
	static bool isBought;
	static Player* cardOwner;
	static int Only1Time;// to make sure that we saved fees and price only one time
	static int Only1TimeLoad;

public:
	CardThirteen(const CellPosition & pos); // A Constructor takes card position
	CardThirteen();//A default constructor

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardThirteen which is: 

	virtual void EditCardParameters(Grid * pGrid); // Edits the parameters of CardThirteen which is: Cardprice and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardThirteen on the passed Player
	
	virtual void Load(ifstream& Infile);
	virtual void Save(ofstream &OutFile, type T);//TO SAVE CARD 13
	
	virtual ~CardThirteen(); // A Virtual Destructor

};

