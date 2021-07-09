#pragma once
#include "Card.h"

class CardEight : public Card
{

public:
	CardEight(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of CardEight which is: 

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardEight on the passed Player

	virtual ~CardEight(); // A Virtual Destructor

	
};

