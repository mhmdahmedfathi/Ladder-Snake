#include "AddCardAction.h"
#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"
#include "../GameObjects/Cards/CardOne.h"
#include "../GameObjects/Cards/CardTwo.h"
#include "../GameObjects/Cards/CardThree.h"
#include "../GameObjects/Cards/CardFour.h"
#include "../GameObjects/Cards/CardFive.h"
#include "../GameObjects/Cards/CardSix.h"
#include "../GameObjects/Cards/CardSeven.h"
#include "../GameObjects/Cards/CardEight.h"
#include "../GameObjects/Cards/CardNine.h"
#include "../GameObjects/Cards/CardTen.h"
#include "../GameObjects/Cards/CardEleven.h"
#include "../GameObjects/Cards/CardTwelve.h"
#include "../GameObjects/Cards/CardThirteen.h"
#include "../GameObjects/Cards/CardFourteen.h"


AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces

	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	// 2- Read the "cardNumber" parameter and set its data member
	pOut->PrintMessage("Enter cardNumber: ");
	int cardNum = pIn->GetInteger(pOut);

	//Validation
	if (cardNum < 1 || cardNum>14) {
		pOut->PrintMessage("Invalid Card Number, Cards have Numbers from 1-14, Operation cancelled, click to continue... ");
		cardNumber = -1;
		return; 
	}

	cardNumber = cardNum;

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member
	pOut->PrintMessage("Click on the cell you would like to add card " + to_string(cardNumber) + " to");
	cardPosition = pIn->GetCellClicked(); //Both vCell and hCell of the cell will be set to -1 if the click isnot within the grid range


	// 4- Make the needed validations on the read parameters
	if (cardPosition.HCell() == -1 || cardPosition.VCell() == -1)
	{
		cardNumber = -1;
		pGrid->PrintErrorMessage("Invalid position, Operation cancelled, click to continue... ");
		return;
	}


	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute()
{

	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- The first line of any Action Execution is to read its parameter first
	ReadActionParameters();

		// 2- Switch case on cardNumber data member and create the appropriate card object type
		Card* pCard = NULL; // will point to the card object type
		switch (cardNumber)
		{
		case 1:
			pCard = new CardOne(cardPosition);
			break;

		case 2:
			pCard = new CardTwo(cardPosition);
			break;

		case 3:
			pCard = new CardThree(cardPosition);
			break;

		case 4:
			pCard = new CardFour(cardPosition);
			break;

		case 5:
			pCard = new CardFive(cardPosition);
			break;

		case 6:
			pCard = new CardSix(cardPosition);
			break;

		case 7:
			pCard = new CardSeven(cardPosition);
			break;

		case 8:
			pCard = new CardEight(cardPosition);
			break;

		case 9:
			pCard = new CardNine(cardPosition);
			break;

		case 10:
			pCard = new CardTen(cardPosition);
			break;

		case 11:
			pCard = new CardEleven(cardPosition);
			break;

		case 12:
			pCard = new CardTwelve(cardPosition);
			break;

		case 13:
			pCard = new CardThirteen(cardPosition);
			break;

		case 14:
			pCard = new CardFourteen(cardPosition);
			break;

		default:
			break;

		}

		// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
		if (pCard)
		{
			// We get a pointer to the Grid from the ApplicationManager
			Grid * pGrid = pManager->GetGrid();

			
			// Add the card object to the GameObject of its Cell:
			bool isAdded = pGrid->AddObjectToCell(pCard);

			// if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
			if (!isAdded)
			{
				Output* pOut = pGrid->GetOutput();

				//We cannot add it if there is an existing gamObject or if we want to add it to the first or the last cell
				pGrid->PrintErrorMessage("Invalid position, check card's instructions, Click to continue..");
				delete pCard;
				pOut->ClearStatusBar();

			}
			else
			{
				//  Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type
				pCard->ReadCardParameters(pGrid);

			}

		}
	
	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction
}
