#pragma once
#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 
class CardTwelve : public Card
{
	static int CardPrice;
	static int Fees;
	static bool Exists12;
	static bool isBought;
	static Player* cardOwner;
	static int Only1Time;// to make sure that we saved fees and price only one time
	static int Only1TimeLoad;

public:
	CardTwelve(const CellPosition & pos); // A Constructor takes card position
	
	CardTwelve();//A default constructor

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardTwelve which is: 

	virtual void EditCardParameters(Grid * pGrid); // Edits the parameters of CardTwelve which is: Cardprice and Fees

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardTwelve on the passed Player
  
	virtual void Load(ifstream& Infile);
	virtual void Save(ofstream &OutFile, type T);//TO SAVE CARD 12

	virtual ~CardTwelve(); // A Virtual Destructor

};

