#pragma once

#include "Grid.h"
#include "Cell.h"

class Player
{
	Cell* pCell;		   // pointer to the current Cell of the player

	const int playerNum;   // the player number (from 0 to MaxPlayerCount-1)
	// player number does NOT change after construction (const.)

	int stepCount;		   // step count which is the same as his cellNum: from 1 to NumVerticalCells*NumHorizontalCells
	int wallet;		       // player's wallet (how many coins he has -- integer)
	int justRolledDiceNum; // the current dice number which is just rolled by the player
	int turnCount;         // a counter that starts with 0, is incremented with each dice roll
	// and reset again when reached 3
	// it is used to indicate when to move and when to add to your wallet

	int countPrisonedTurns;
	int WillMove;
	int deptedFees;


	int isDeniedValue;
	// 0 means denied and do not continue the movefunction
	// 1 means denied but continue the movefunction
	// 2 means notdenied and continue the movefunction

	int IceWillMove;
	string AppliedAttackType;
	string PreviosAttackType;

	int FireTurns;
	int PoisonTurns;
	int OnlyTwoAttacks;  //0 means he haven't ordered a specialattack yet
						//1 means he have ordered one special attack
						//2 means he have ordered 2 and this is the max that he can open

public:

	Player(Cell * pCell, int playerNum); // Constructor making any needed initializations

	// ====== Setters and Getters ======

	void SetCell(Cell * cell);		// A setter for the pCell
	Cell* GetCell() const;			// A getter for the pCell

	void SetWallet(int wallet);		// A setter for the wallet
	int GetWallet() const;			// a getter for the wallet
	
	void setturncount(int turn);
	int GetTurnCount() const;		// A getter for the turnCount
	
	int getPlayerNum() const;
	
	int GetjustRolledDiceNum() const;
	
	void IncrementCountPrisonedTurns();
	int getCountPrisonedTurns();
	void ResetCountPrisonedTurns();

	void SetDeptedFees(int Fees);
	int GetDeptedFees();

	void setWillMove(int wm);
	int getWillMove();

	void IsDenied(Grid* pGrid, int& diceNumber); //To know If he is denied from rolling dice or not

	void setIceWillMove(int settedValue);
	int getIceWillMove();

	string getAppliedAttackType();
	void setAppliedAttackType(string appliedAttackType);

	void setIsDeniedValue(int settedValue);

	void setFireTurns(int settedValue);
	int getFireTurns();

	void setPoisonTurns(int settedValue);
	
	// ====== Drawing Functions ======

	void Draw(Output* pOut) const;			// Draws the Player's Circle on its current cell

	void ClearDrawing(Output* pOut) const;	// Clears the Player's Circle from its current cell

	// ====== Game Functions ======

	void Move(Grid * pGrid, int diceNumber);	// Moves the Player with the passed diceNumber 
	                                            // and Applies the Game Object's effect (if any) of the end reached cell 
	                                            // for example, if the end cell contains a ladder, take it
	
	void AppendPlayerInfo(string & playersInfo) const; // Appends player's info to the input string, 
	                                                   // for example: P0(wallet, turnCount)

};

