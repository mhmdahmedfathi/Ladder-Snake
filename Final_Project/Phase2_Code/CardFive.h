
#pragma once
#include "Card.h"
class CardFive : public Card
{
public:

	CardFive(const CellPosition & pos); // A Constructor takes card position
	virtual ~CardFive(void);  // A Virtual Destructor
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardFive on the passed Player
	// by moving forward the same number of steps that he just rolled	
};
