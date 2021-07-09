
#include "CardTwo.h"
#include <iostream>
using namespace std;
#include <fstream> 


CardTwo::CardTwo(const CellPosition & pos) : Card(pos)
{
	cardNumber = 2;

	walletvalue = 0;
}
void CardTwo::Load(ifstream& Infile)
{
	Infile >> walletvalue;
}

CardTwo::CardTwo()
{
}
CardTwo::~CardTwo(void)
{
}
void CardTwo::ReadCardParameters(Grid * pGrid)
{
	Input * pi = pGrid->GetInput();
	Output * po = pGrid->GetOutput();

			po->PrintMessage("New CardTwo: Enter its wallet amount ...");
			int unValidatedWallet = pi->GetInteger(po);
			while (unValidatedWallet < 0)
			{
				po->PrintMessage("the wallet amount must be positive, please Enter again its wallet amount ..");
				unValidatedWallet = pi->GetInteger(po);

			}
			walletvalue = unValidatedWallet;
		po->ClearStatusBar();  // Clearing the status bar

}

void CardTwo::EditCardParameters(Grid * pGrid)
{
	//Getting Pointer to the Input / Output Interfaces

	Input * pi = pGrid->GetInput();
	Output * po = pGrid->GetOutput();

	po->PrintMessage("Editing CardTwo: Enter its new Value to increase the wallet by ...");
	int unValidatedWallet = pi->GetInteger(po);
	while (unValidatedWallet < 0)
	{
		po->PrintMessage("the wallet amount must be positive, please Enter again the Value to increase ..");
		unValidatedWallet = pi->GetInteger(po);

	}
	walletvalue = unValidatedWallet;
	pGrid->PrintErrorMessage("Card Edited Successfully, Click to continue... ");
}



void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer); // Calling Apply() of the base class Card to print the message that you reached this card number
	
	int wallet = pPlayer->GetWallet();
	wallet += walletvalue; //  incrementing the wallet of pPlayCer by the walletvalue data member of CardTwo
	pPlayer->SetWallet(wallet);
}
void  CardTwo::Save(ofstream &OutFile, type T)
{
	if (T == card)
	{
		Card::Save(OutFile, card);
		OutFile << walletvalue;

	}
}


