
#include "CardOne.h"



CardOne::CardOne(const CellPosition & pos) : Card(pos) // set the cell position of the card
{
	cardNumber = 1; // set the inherited cardNumber data member with the card number (1 here)
	walletAmount = 0;
}
void CardOne::Load(ifstream& Infile)
{

	Infile >> walletAmount;

}

CardOne::CardOne()
{
}

CardOne::~CardOne(void)
{
}

void CardOne::ReadCardParameters(Grid * pGrid)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==


	// 1- Get a Pointer to the Input / Output Interfaces from the Grid
	Input * pi = pGrid->GetInput();
	Output * po = pGrid->GetOutput();
	// 2- Read an Integer from the user using the Input class and set the walletAmount parameter with it
	//    Don't forget to first print to a descriptive message to the user like:"New CardOne: Enter its wallet amount ..."
	
		po->PrintMessage("New CardOne: Enter its wallet amount ...");
		int unValidatedWallet = pi->GetInteger(po);
		while (unValidatedWallet < 0)
		{
			po->PrintMessage("the wallet amount must be positive, please Enter again its wallet amount ..");
			unValidatedWallet = pi->GetInteger(po);

		}
		walletAmount = unValidatedWallet;
		
		// [ Note ]:
		// In CardOne, the only parameter of CardOne is the "walletAmount" value to decrease from player
		// Card parameters are the inputs you need to take from the user in the time of adding the Card in the grid
		// to be able to perform his Apply() action

		// 3- Clear the status bar
		
	
	po->ClearStatusBar();
}

void CardOne::EditCardParameters(Grid * pGrid)
{
	// 1- Getting Pointer to the Input / Output Interfaces

	Input * pi = pGrid->GetInput();
	Output * po = pGrid->GetOutput();

	po->PrintMessage("Editing CardOne: Enter its new Value to decrease the wallet by ...");
	int unValidatedWallet = pi->GetInteger(po);
	while (unValidatedWallet < 0)
	{
		po->PrintMessage("the wallet amount must be positive, please Enter again the Value to decrease ..");
		unValidatedWallet = pi->GetInteger(po);

	}
	walletAmount = unValidatedWallet;

	pGrid->PrintErrorMessage("Card Edited Successfully, Click to continue... ");


}


void CardOne::Apply(Grid* pGrid, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) (numbered below) to implement this function ==

	// 1- Call Apply() of the base class Card to print the message that you reached this card number
	Card::Apply(pGrid, pPlayer);
	(pGrid->GetOutput())->PrintMessage("Your wallet amount will be decreased by"+walletAmount);
	// 2- Decrement the wallet of pPlayCer by the walletAmount data member of CardOne
	int wallet = pPlayer->GetWallet();
	wallet -= walletAmount;
	pPlayer->SetWallet(wallet);

}
void CardOne::Save(ofstream &OutFile, type T)
{
	if (T == card)
	{
		Card::Save(OutFile, card);
		OutFile << walletAmount ;

	}
}



























