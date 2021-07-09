#pragma once
#include "Card.h"

#include <iostream>
using namespace std;
#include <fstream> 

class CardTen : public Card
{
	static int CardPrice;
	static int Fees;
	static bool Exists10;
	static bool isBought;
	static Player* cardOwner;
	static int Only1Time;// to make sure that we saved fees and price only one time
	static int Only1TimeLoad;

public:
	CardTen(const CellPosition & pos); // A Constructor takes card position
	CardTen();//default constructor
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardTen which is: 

	virtual void EditCardParameters(Grid * pGrid); // Edits the parameters of CardTen which is: Cardprice and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTen on the passed Player
	virtual void Save(ofstream &OutFile, type T);
	virtual void Load(ifstream& Infile);
	//TO SAVE CARD TEN

	virtual ~CardTen(); // A Virtual Destructor

};

