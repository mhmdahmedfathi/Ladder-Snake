
#pragma once
#include "Card.h"
#include <iostream>
using namespace std;
#include <fstream> 
class CardNine : public Card
{
 CellPosition CellToMove ;
	
public:
	CardNine(const CellPosition & pos); // A Constructor takes card position
	CardNine();
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardNine which is: Cell to move

	virtual void Load(ifstream& Infile);

	virtual void EditCardParameters(Grid * pGrid); // Edits the parameters of CardNine which is: Cell to move
	virtual void Save(ofstream &OutFile, type T);//TO SAVE CARD NINE

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardNine on the passed Player

	virtual ~CardNine(); // A Virtual Destructor

};
