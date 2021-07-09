#pragma once

#include "GameObject.h"
#include "Player.h"
#include <iostream>
using namespace std;
#include <fstream> 

// Base Class of All Types of Cards (CardOne, CardTwo, CardThree, ...etc.)
// Note: We will make each type of Card in a separate class because:
// it may have additional data members and functions like: Apply(), ...etc. which have different implementation depending on Card Number
class Card : public GameObject
{
protected:
	int cardNumber; // an integer representing the card number
	
public:
	Card(const CellPosition & pos); // A Constructor for card that takes the cell position of it
	static int CountCard;// to count num. of cards
	Card();
	void SetCardNumber(int cnum);   // The setter of card number
	int GetCardNumber();            // The getter of card number

	void Draw(Output* pOut) const;  // Draws the card number in the cell position of the card
	// It has the same implementation for all Card Types (Non-Virtual)

	virtual void ReadCardParameters(Grid * pGrid); // It reads the parameters specific for each Card Type
	//n//There is some cards which donnot have parameters to be read so i won't implement in them this function
	//n//This is why it's virtual not pure virtual
	// It is a virtual function (implementation depends on Card Type)
	void setposition(CellPosition pos);
	virtual void Apply(Grid* pGrid, Player* pPlayer);  // It applies the effect of the Card Type on the passed player
	// It is a virtual function (implementation depends on Card Type)

	virtual void EditCardParameters(Grid * pGrid);// It reads the parameters specific for editable Card Types to be edited
	 											  // It is a virtual function (implementation depends on Card Type)

	virtual void Save(ofstream &OutFile, type T);
	virtual void Load(ifstream& Infile);
	//TO SAVE CARD 

	virtual ~Card(); // A Virtual Destructor
};

