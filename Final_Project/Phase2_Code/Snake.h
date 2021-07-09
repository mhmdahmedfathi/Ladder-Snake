#pragma once
#include "GameObject.h"

class Snake: public GameObject // inherited from GameObject

{
		// Note: the "position" data member inherited from the GameObject class is used as the ladder's "Start Cell Position"

		CellPosition EndCellPos; // here is the ladder's End Cell Position


	public:
		static int CountSnake; // to count number of the snakes in the grid

		Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization
		Snake();
		virtual void Draw(Output* pOut) const; // Draws a ladder from its start cell to its end cell

		virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the ladder by moving player to ladder's end cell

		CellPosition GetEndPosition() const; // A getter for the endCellPos data member

		virtual void Save(ofstream& OutFile, type T);//TO SAVE SNAKE
		virtual void Load(ifstream& Infile);	// Loads and Reads the GameObject parameters from the file

		virtual ~Snake(); // Virtual destructor
	};

