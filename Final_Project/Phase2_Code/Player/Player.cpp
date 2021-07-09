#include "Player.h"

#include "../GameObjects/GameObject.h"
#include "../Grid/Grid.h"
#include "../GUIClasses/Output.h"
#include "../GameObjects/Cards/CardTen.h"
#include "../GameObjects/Cards/CardEleven.h"
#include "../GameObjects/Cards/CardTwelve.h"
#include "../GameObjects/Cards/CardThirteen.h"
#include "../GameObjects/Cards/CardFourteen.h"
#include "../GameObjects/Cards/CardEight.h"

Player::Player(Cell * pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	this->pCell = pCell;
	this->turnCount = 0;
	countPrisonedTurns = 0;
	deptedFees = 0;
	WillMove = 0;
	isDeniedValue = 2;
	FireTurns = 0;
	PoisonTurns = 0;
	OnlyTwoAttacks = 0;
	AppliedAttackType = "None";

}

// ====== Setters and Getters ======

void Player::SetCell(Cell * cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet >= 0)
		this->wallet = wallet;
	else
		this->wallet = 0;
}

int Player::GetWallet() const
{
	return wallet;
}

void Player::setturncount(int turn)
{
	turnCount = turn;
}

int Player::GetTurnCount() const
{
	return turnCount;
}
int Player::getPlayerNum() const
{
	return playerNum;
}


int Player::GetjustRolledDiceNum() const
{
	return justRolledDiceNum;
}

void Player::IncrementCountPrisonedTurns()
{
	countPrisonedTurns++;
}

void Player::ResetCountPrisonedTurns()
{
	countPrisonedTurns = 0;
}


int Player::getCountPrisonedTurns()
{
	return countPrisonedTurns;

}

void Player::SetDeptedFees(int Fees)
{
	deptedFees = Fees;

}

int Player::GetDeptedFees()
{
	return deptedFees;

}
void Player::setWillMove(int wm)
{
	WillMove = wm;
}


int Player::getWillMove()
{
	return WillMove;
}

void Player::setIceWillMove(int settedValue)
{
	IceWillMove = settedValue;
}


int Player::getIceWillMove()
{
	return IceWillMove;
}

string Player::getAppliedAttackType()
{

	return AppliedAttackType;
}

void Player::setAppliedAttackType(string appliedAttackType)
{
	AppliedAttackType = appliedAttackType;
}


void Player::setIsDeniedValue(int settedValue)
{
	isDeniedValue = 0;
}

void Player::setFireTurns(int settedValue)
{
	FireTurns = settedValue;
}

int Player::getFireTurns()
{
	return FireTurns;
}


void Player::setPoisonTurns(int settedValue)
{
	PoisonTurns = settedValue;
}


// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

}


void Player::IsDenied(Grid* pGrid, int& diceNumber)
{
	GameObject* pGameObject = pCell->GetGameObject();

	if ((dynamic_cast<CardTen*>(pGameObject)) || (dynamic_cast<CardEleven*>(pGameObject)) || (dynamic_cast<CardTwelve*>(pGameObject)) || (dynamic_cast<CardThirteen*>(pGameObject)) || (dynamic_cast<CardFourteen*>(pGameObject)))
	{
		if ((wallet < deptedFees) && (countPrisonedTurns != 0))
		{
			diceNumber = 0;
			isDeniedValue = 1; //1 means I am denied from moving but I do want to continue the move function  (Denied && Continue)
		}
		else if ((wallet > deptedFees) && (countPrisonedTurns != 0))
		{
			pGameObject->Apply(pGrid, this);
			isDeniedValue = 2; //2 means I am not denied from moving and I do want to continue the move function  (NotDenied && Continue)
		}
	}
	else if (dynamic_cast<CardEight*>(pGameObject))
	{
		if (WillMove == 1)
		{
			diceNumber = 0;
			pGameObject->Apply(pGrid, this);
			isDeniedValue = 0; //0 means I am denied from moving and I don't want to continue the move function (Denied && NotContinue)
		}
		else
		{
			pGameObject->Apply(pGrid, this);
			isDeniedValue = 2; //2 means I am not denied from moving and I do want to continue the move function  (NotDenied && Continue)

		}
	}
	else if (AppliedAttackType == "Ice")
	{
		if (IceWillMove == 1)
		{
			diceNumber = 0;
			pGrid->PrintErrorMessage("You are freezed, you can't roll this turn, next turn inshallah, Click to continue..  ");
			this->setIceWillMove(2);
			isDeniedValue = 0; //0 means I am denied from moving and I don't want to continue the move function (Denied && NotContinue)
		}
		else if (IceWillMove == 2)
		{
			pGrid->PrintErrorMessage("It's time to be free, Click to continue..  ");
			this->setIceWillMove(0);
			isDeniedValue = 2; //2 means I am not denied from moving and I do want to continue the move function  (NotDenied && Continue)
			AppliedAttackType = "None";
		}

	}
	else if (AppliedAttackType == "Poison")
	{
		//Poison: Choose a player to poison.For 5 turns, deduct 1 number from his dice roll.

		if (PoisonTurns > 0 && PoisonTurns < 6)
		{
			pGrid->PrintErrorMessage("You're Poisoned, Your DiceNumber will be deduced by 1 for 5 Turns...Click to continue  ");
			diceNumber--;
			PoisonTurns++;
		}
		else if (PoisonTurns > 5)
		{
			pGrid->PrintErrorMessage("Congrats, You are healed from the poison...Click to continue");
			AppliedAttackType = "None";
			PoisonTurns = 0;
		}

	}

	//To deduce 20 coins for 3 turns  if he was fired
	if (AppliedAttackType == "Fire")
	{
		if (FireTurns > 0 && FireTurns < 3)
		{
			pGrid->PrintErrorMessage("You are fired, 20 coins will be taken from you..Click to continue");
			wallet -= 20;
			FireTurns++;
		}
		else if (FireTurns == 3)
		{
			pGrid->PrintErrorMessage("Take a deep breath,  this is the last 20 Coins to be deduced...Click to continue");
			wallet -= 20;
			AppliedAttackType = "None";
			FireTurns = 0;
		}

	}


}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	if(pCell->HasCard () ==NULL)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, PURPLE );
	else
		pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);

}

// ====== Game Functions ======

void Player::Move(Grid * pGrid, int diceNumber)
{
	
	// == Here are some guideline steps (numbered below) to implement this function ==

	//Getting a Pointer to the Input / Output Interfaces from the Grid
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	turnCount++;
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	if (turnCount % 3 == 0)
	{
		//Asking the user if he want to launch a special attack or recharging if he is not denied from moving 
		if (isDeniedValue == 2 && OnlyTwoAttacks < 2)
		{

			bool IsValidInput = true;
			string ChosenAttackType;
			//Choosing to launch a special attack or to recharge the wallet
			do
			{
				pOut->PrintMessage("Do you wish to launch a special attack instead of recharging? y/n");
				string valueEntered = pIn->GetSrting(pOut);
				if (valueEntered == "y" || valueEntered == "Y")
				{
					
					pGrid->PrintErrorMessage("Choose the special attack type you want to launch! click to Continue ");
					pOut->PrintMessage("P for Poison , L for Lightning , I for Ice , F for Fire ...Don't Forget To Enter Capital Letters :D");

					ChosenAttackType = pIn->GetSrting(pOut);

					if (OnlyTwoAttacks == 1 && PreviosAttackType == ChosenAttackType)
					{
						pGrid->PrintErrorMessage("You Cannot use the a special attack twice, Click to continue...");
						pGrid->PrintErrorMessage("We will reAsk you, Click to continue... ");
						IsValidInput = false;
						continue;
					}

					if (ChosenAttackType == "L")
					{
						pGrid->PrintErrorMessage("Click to Launch..");
						pGrid->Lightning(this);
					}
					else if (ChosenAttackType == "I")
					{

						IsValidInput = pGrid->Ice(this);
						if (IsValidInput == false)
						{
							pGrid->PrintErrorMessage("We will reAsk you, Click to continue... ");
						}
						else
						{
							pGrid->PrintErrorMessage("Click to Launch..");
						}


					}
					else if (ChosenAttackType == "P")
					{


						IsValidInput = pGrid->Poison(this);

						if (IsValidInput == false)
						{
							pGrid->PrintErrorMessage("We will reAsk you, Click to continue... ");
						}
						else
						{
							pGrid->PrintErrorMessage("Click to Launch..");
						}

					}
					else if (ChosenAttackType == "F")
					{

						IsValidInput = pGrid->Fire(this);

						if (IsValidInput == false)
						{
							pGrid->PrintErrorMessage("We will reAsk you, Click to continue... ");
						}
						else
						{
							pGrid->PrintErrorMessage("Click to Launch..");
						}

					}
					else
					{
						pGrid->PrintErrorMessage("InValid Attack, Special attacks are only F, P, L and I...Click to continue");
						IsValidInput = false;
						pGrid->PrintErrorMessage("We will reAsk you, Click to continue... ");
					}

					PreviosAttackType = ChosenAttackType;
					if (IsValidInput)
					{
						OnlyTwoAttacks++;
					}
				}
				else
				{
					pGrid->PrintErrorMessage("You Chosed to Recharge...Click to Recharge");

					wallet += diceNumber * 10;
					IsValidInput = true;
				}


			} while (IsValidInput == false);

			turnCount = 0;
			return;
		}
		else
		{
			//if he is denied recharge his wallet, he don't have except this option, he cannot launch a special attack
			//Or he have finished his special attacks :D
			wallet += diceNumber * 10;
			turnCount = 0;
			return;
		}
	}

	//Calling the function to check if denied or not and to continue the move function or not
	IsDenied(pGrid, diceNumber);


	//To return and don't apply l card twice
	if (isDeniedValue == 0)
	{
		return;
	}

	else if (wallet > 0)
	{
		// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
		//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
		justRolledDiceNum = diceNumber;
		// 3- Set the justRolledDiceNum with the passed diceNumber
		CellPosition pos = pCell->GetCellPosition();
		if ((99 - (pos.GetCellNum() + diceNumber)) < 0)
		{
			string Message;
			if(diceNumber != 1)

			 Message = "your dice number must be smaller than or equal  " + to_string(99 - pos.GetCellNum());
			else
			 Message = "your dice number must be equal  " + to_string(99 - pos.GetCellNum());

			pOut->PrintMessage(Message);
			int x, y;
			pIn->GetPointClicked(x,y);
			pOut->ClearStatusBar();
			return;
		}
		if((pos.GetCellNum() + diceNumber)<100)
		this->stepCount = pos.GetCellNum() + diceNumber;
		
		pos.AddCellNum(justRolledDiceNum);
		
		// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
		//    Using the appropriate function of CellPosition class to update "pos"
		pGrid->UpdatePlayerCell(pGrid->GetCurrentPlayer(), pos);
		// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
		//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
		pGrid->UpdateInterface();

		// 6- Apply() the game object of the reached cell (if any)
		GameObject* pobject = pCell->GetGameObject();
		
		if (pCell->HasCard())
			pobject->Apply(pGrid, this);
		if (pCell->HasLadder())
			pobject->Apply(pGrid, this);
		if (pCell->HasSnake())
			pobject->Apply(pGrid, this);
		// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)
		if (this->stepCount == 99)
		{
			int x, y;
			string Massage = "the Winner Is Player" + to_string(playerNum);
			pOut->PrintMessage(Massage);
			pIn->GetPointClicked(x,y);
			pGrid->SetEndGame(true);
		}
	}
}

void Player::AppendPlayerInfo(string & playersInfo) const
{
	playersInfo += "Player" + to_string(playerNum) + "(" ;
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}