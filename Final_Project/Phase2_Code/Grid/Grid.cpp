#include "Grid.h"

#include "Cell.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Ladder.h"
#include "../GameObjects/Cards/Card.h"
#include "../Player/Player.h"
#include "../GameObjects/Snake.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========


bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();

	//You cannot replace gameobjects in the first or the last cell
	if (pos.GetCellNum() == 1 || pos.GetCellNum() == 99){
		return false;
	}

	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


Card* Grid::HasCard(CellPosition pos)
{
	return (CellList[pos.VCell()][pos.HCell()]->HasCard());
}

Snake* Grid::HasSnake(CellPosition pos)
{
	return (CellList[pos.VCell()][pos.HCell()]->HasSnake());
}

Ladder* Grid::HasLadder(CellPosition pos)
{
	return (CellList[pos.VCell()][pos.HCell()]->HasLadder());
}

void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		if (CellList[pos.VCell()][pos.HCell()]->GetGameObject() != NULL)
		{
			Ladder* pLadder = dynamic_cast<Ladder*>(CellList[pos.VCell()][pos.HCell()]->GetGameObject());
			if (pLadder != NULL)
				Ladder::CountLadder--;
			Snake* pSnake = dynamic_cast<Snake*>(CellList[pos.VCell()][pos.HCell()]->GetGameObject());
			if (pSnake != NULL)
				Snake::CountSnake--;
			Card* pCard = dynamic_cast<Card*>(CellList[pos.VCell()][pos.HCell()]->GetGameObject());
			if (pCard != NULL)
				Card::CountCard--;
			
				// Note: you can deallocate the object here before setting the pointer to null if it is needed
		}
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
		
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	
	
	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}

// ========= Other Getters =========

GameObject* Grid::GetGameObjects(const CellPosition& position)
{

	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		GameObject* pObject = CellList[i][startH]->GetGameObject();
			if (pObject != NULL)
				return pObject;
	}
	return NULL; // not found

}

void Grid::SetCurrentPlayer(int x)
{
	currPlayerNumber = x;
}

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
 
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	Ladder* pladder ;
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			pladder = CellList[i][j]->HasLadder();

			if (pladder != NULL)
			{
				return pladder;
				
			}
			//TODO: Check if CellList[i][j] has a ladder, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}


Snake* Grid::GetNextSnake(const CellPosition& position)
{
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	Snake* pSnake;
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{
			pSnake = CellList[i][j]->HasSnake();

			if (pSnake != NULL)
			{
				return pSnake;

			}
			//TODO: Check if CellList[i][j] has a Snake, if yes return it
		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

// ========= User Interface Functions =========
void Grid::ClearAll(ifstream& OutFile)
{
	for (int v = 8; v >= 0; v--)// for loop to scan the vertical cells
	{
		for (int h = 0; h < 11; h++)///for loop to scan the horizontale cells
		{
			GameObject* GObj = CellList[v][h]->GetGameObject();

			if (GObj != NULL)
			{
				RemoveObjectFromCell(CellList[v][h]->GetCellPosition());
			}

		}

	}
	UpdateInterface();

}
bool Grid::Ice(Player* SpecialAttackCaller)
{
	int CallerNum = SpecialAttackCaller->getPlayerNum();

	Input* pIn = this->GetInput();
	Output* pOut = this->GetOutput();
	pOut->PrintMessage("Enter the player's number you want to prevent from rolling next time");
	int FreezedPlayerNum = pIn->GetInteger(pOut);
	if (FreezedPlayerNum == CallerNum)
	{
		this->PrintErrorMessage("InValid, you can not Freeze yourself, Click to Continue...");
		return false;

	}
	else if (FreezedPlayerNum > 3 || FreezedPlayerNum < 0)
	{
		this->PrintErrorMessage("InValid, Player's Number must be within 0-3, Click to Continue...");
		return false;
	}
	else if ((PlayerList[FreezedPlayerNum]->getAppliedAttackType()) != "None")
	{
		this->PrintErrorMessage("InValid, This player has arleady an applied attack, Click to Continue...");
		return false;
	}


	PlayerList[FreezedPlayerNum]->setIceWillMove(1);
	PlayerList[FreezedPlayerNum]->setAppliedAttackType("Ice");
	PlayerList[FreezedPlayerNum]->setIsDeniedValue(0);


	return true;

}


bool Grid::Fire(Player* SpecialAttackCaller)
{
	int CallerNum = SpecialAttackCaller->getPlayerNum();

	Input* pIn = this->GetInput();
	Output* pOut = this->GetOutput();
	pOut->PrintMessage("Enter player's number you want to Duduce 20 coins for 3 turns from him...");
	int FiredPlayerNum = pIn->GetInteger(pOut);
	if (FiredPlayerNum == CallerNum)
	{
		this->PrintErrorMessage("InValid, you can not Fire yourself, Click to Continue...");
		return false;

	}
	else if (FiredPlayerNum > 3 || FiredPlayerNum< 0)
	{
		this->PrintErrorMessage("InValid, Player's Number must be within 0-3, Click to Continue...");
		return false;
	}
	else if ((PlayerList[FiredPlayerNum]->getAppliedAttackType()) != "None")
	{
		this->PrintErrorMessage("InValid, This player has arleady an applied attack, Click to Continue...");
		return false;
	}


	PlayerList[FiredPlayerNum]->setFireTurns(1);
	PlayerList[FiredPlayerNum]->setAppliedAttackType("Fire");

	return true;

}


bool Grid::Poison(Player* SpecialAttackCaller)
{

	int CallerNum = SpecialAttackCaller->getPlayerNum();

	Input* pIn = this->GetInput();
	Output* pOut = this->GetOutput();
	pOut->PrintMessage("Enter player's number you want to Poison...");
	int PoisonedPlayerNum = pIn->GetInteger(pOut);
	if (PoisonedPlayerNum == CallerNum)
	{
		this->PrintErrorMessage("InValid, you can not Poison yourself, Click to Continue...");
		return false;

	}
	else if (PoisonedPlayerNum > 3 || PoisonedPlayerNum < 0)
	{
		this->PrintErrorMessage("InValid, Player's Number must be within 0-3, Click to Continue...");
		return false;
	}
	else if ((PlayerList[PoisonedPlayerNum]->getAppliedAttackType()) != "None")
	{
		this->PrintErrorMessage("InValid, This player has arleady an applied attack, Click to Continue...");
		return false;
	}


	PlayerList[PoisonedPlayerNum]->setPoisonTurns(1);
	PlayerList[PoisonedPlayerNum]->setAppliedAttackType("Poison");

	return true;

}



void Grid::Lightning(Player* SpecialAttackCaller)
{
	int CallerNum = SpecialAttackCaller->getPlayerNum();

	for (int i = 0; i < 4; i++)
	{
		if (i != CallerNum)
		{
			PlayerList[i]->SetWallet((PlayerList[i]->GetWallet()) - 20);
			PrintErrorMessage("We're sorry Player" + to_string(i) + ", but Player" + to_string(CallerNum) + " have ordered to deduce 20 coins from you...Click to continue");
		}
	}
}


void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}
void Grid::SaveAll(ofstream& OutFile, type T)
{
	for (int v = 8; v >= 0; v--)// for loop to scan the vertical cells
	{
		for (int h = 0; h < 11; h++)///for loop to scan the horizontale cells
		{
			GameObject* GObj = CellList[v][h]->GetGameObject();
			if (GObj != NULL)
			{
				GObj->Save(OutFile, T);
			}
		}

	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}


Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) 
	{
		for (int j = 0; j < NumHorizontalCells; j++) 
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		delete PlayerList[i];
	}

}