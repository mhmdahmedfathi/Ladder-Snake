#pragma once
#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 
class CardEleven : public Card
{

	static int CardPrice;
	static int Fees;
	static bool Exists11;
	static bool isBought;
	static Player* cardOwner;
	static int Only1Time;// to make sure that we saved fees and price only one time
	static int Only1TimeLoad;

public:
	CardEleven(const CellPosition & pos); // A Constructor takes card position
	CardEleven();
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardEleven which is: 

	virtual void EditCardParameters(Grid * pGrid); // Edits the parameters of CardEleven which is: Cardprice and fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardEleven on the passed Player
	virtual void Save(ofstream &OutFile, type T);//TO SAVE CARD 11
	virtual void Load(ifstream &Infile);	// Loads and Reads the GameObject parameters from the file
	virtual ~CardEleven(); // A Virtual Destructor
};

