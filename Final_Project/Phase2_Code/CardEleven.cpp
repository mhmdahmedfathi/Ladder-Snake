#include "CardEleven.h"
#include <iostream>
using namespace std;
#include <fstream> 

bool CardEleven::Exists11 = 0;
bool CardEleven::isBought = 0;
int CardEleven::CardPrice = 0;
int CardEleven::Fees = 0;
Player* CardEleven::cardOwner = NULL;
int CardEleven::Only1Time = 0;
int CardEleven::Only1TimeLoad = 0;

CardEleven::CardEleven(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 11; // set the inherited cardNumber data member with the card number (11 here)
}

CardEleven::CardEleven()
{
}


CardEleven::~CardEleven(void)
{
}

void CardEleven::ReadCardParameters(Grid * pGrid)
{

	//Getting a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	//a Static data member to make sure that the parameters of cardEleven has been entered once
	//The parameters of any Card must be entered only at the first time the user adds this card
	if (Exists11){
		return;
	}

	//Reading an Integer from the user using the Input class and set the Price and the Fees parameters with it
	pOut->PrintMessage("New CardEleven: Enter the Card Price to be paid by the cardOwner ...");
	int unValidatedPrice = pIn->GetInteger(pOut);

	//Forcing the User to enter a positive value for CardPrice
	while (unValidatedPrice < 0)
	{
		pOut->PrintMessage("the Card Price must be positive, please Enter again its Card Price ..");
		unValidatedPrice = pIn->GetInteger(pOut);

	}
	CardPrice = unValidatedPrice;


	//Reading an Integer from the user using the Input class and set the Price and the Fees parameters with it
	pOut->PrintMessage("Enter the Card Fees to be paid by the passing player...");
	int unValidatedFees = pIn->GetInteger(pOut);


	//Forcing the User to enter a positive value for CardPrice
	while (unValidatedFees < 0)
	{
		pOut->PrintMessage("the Card Price must be positive, please Enter again its Card Fees ..");
		unValidatedFees = pIn->GetInteger(pOut);

	}
	Fees = unValidatedFees;
	Exists11 = 1;


	//Clearing the status bar
	pOut->ClearStatusBar();

}

void CardEleven::EditCardParameters(Grid * pGrid)
{


	//Getting a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();


	//Reading an Integer from the user using the Input class and set the Price and the Fees parameters with it
	pOut->PrintMessage("Editing CardEleven: Enter the new Card Price to be paid by the cardOwner ...");
	int unValidatedPrice = pIn->GetInteger(pOut);

	//Forcing the User to enter a positive value for CardPrice
	while (unValidatedPrice < 0)
	{
		pOut->PrintMessage("the Card Price must be positive, please Enter again its new Card Price ..");
		unValidatedPrice = pIn->GetInteger(pOut);

	}
	CardPrice = unValidatedPrice;


	//Reading an Integer from the user using the Input class and set the Price and the Fees parameters with it
	pOut->PrintMessage("Enter the new Card Fees to be paid by the passing player...");
	int unValidatedFees = pIn->GetInteger(pOut);


	//Forcing the User to enter a positive value for CardFees
	while (unValidatedFees < 0)
	{
		pOut->PrintMessage("the Card Fees must be positive, please Enter again its new Card Fees ..");
		unValidatedFees = pIn->GetInteger(pOut);

	}
	Fees = unValidatedFees;

	pGrid->PrintErrorMessage("Card Edited Successfully, Click to continue... ");
}

void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	//Calling Apply() of the base class Card to print the message that you reached this card number

	if ((pPlayer->getCountPrisonedTurns() == 0))
	{
		Card::Apply(pGrid, pPlayer);
	}
	//Getting a Pointer to the Input / Output Interfaces from the Grid
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	if (!isBought)
	{

		//checking if the player have enough money to buy this card

		if ((pPlayer->GetWallet()) >= CardPrice)
		{

			//Giving the player the option to either buy this card or not
			pOut->PrintMessage("You have reached CardEleven, card's Price= " + to_string(CardPrice) + " Press 'Y' to buy it or 'N' to skip");

			string state = pIn->GetSrting(pOut);
			if (state == "Y" || state == "y")
			{
				pPlayer->SetWallet((pPlayer->GetWallet()) - CardPrice);
				isBought = 1;
				cardOwner = pPlayer;
			}
			else
			{
				pGrid->PrintErrorMessage("Operation cancelled, you will regret not buying that...Click to continue ");
			}

		}
		else
		{
			pGrid->PrintErrorMessage("Sorry, you don't have enough money to have the option to buy that...Click to continue ");
		}
	}
	//checking if this card has been bought by a player

	if (isBought)
	{
		if (cardOwner == pPlayer)
		{
			pGrid->PrintErrorMessage("You are in your bought Cell...Click to continue ");
		}
		else if (cardOwner != pPlayer)
		{

			//taking the fees form the passing player's wallet and adding this fees to the cardOwner's wallet
			if ((pPlayer->GetWallet()) < Fees)
			{
				if ((pPlayer->getCountPrisonedTurns()) == 0)
				{
					pGrid->PrintErrorMessage("You have reached a bought cell, And You don't have enough money to pay " + to_string(Fees) + " Coins, you will be prisoned till you have enough money...");
				}
				else
				{
					pGrid->PrintErrorMessage("Money isn't enough yet,you will stay prisoned...Tough times never last, but tough people do,Click to continue..");

				}

				pPlayer->IncrementCountPrisonedTurns();
				pPlayer->SetDeptedFees(Fees);
			}
			else
			{
				if ((pPlayer->getCountPrisonedTurns()) != 0)
				{
					pPlayer->SetWallet(((pPlayer->GetWallet()) - Fees));
					cardOwner->SetWallet(((cardOwner->GetWallet()) + Fees));

					pGrid->PrintErrorMessage("Finally you have enough Money to be fred, Click to transfer money :D ....");
					pPlayer->ResetCountPrisonedTurns();
					pPlayer->SetDeptedFees(0);
				}
				else
				{
					pGrid->PrintErrorMessage("You have reached a bought cell, you should pay to player" + to_string(cardOwner->getPlayerNum()) + " " + to_string(Fees) + " Coins, Click to tranfer money...");


					pPlayer->SetWallet((pPlayer->GetWallet()) - Fees);
					cardOwner->SetWallet((cardOwner->GetWallet()) + Fees);

				}
			}

		}
	}

}
void CardEleven::Save(ofstream &OutFile, type T)
{
	if (T == card)
	{
		Card::Save(OutFile, card);
		if (Only1Time == 0)
		{
			OutFile << CardPrice << " " << Fees << endl;
			Only1Time++;
		}
	}
}
void CardEleven::Load(ifstream& Infile)
{
	if (Only1TimeLoad == 0)
	{
		Infile >> CardPrice >> Fees;
		Only1TimeLoad++;
	}
}
