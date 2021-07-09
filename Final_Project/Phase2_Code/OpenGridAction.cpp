#include "OpenGridAction.h"
#include"Action.h"
#include <iostream>
using namespace std;
#include <fstream> 
#include "Grid.h"

OpenGridAction::OpenGridAction(ApplicationManager *pApp) : Action(pApp)
{
}
void OpenGridAction::ReadActionParameters()
{
	Grid * PG = pManager->GetGrid(); // POINTER TO THE GRID
	//  Getting  a Pointer to the Input / Output Interfaces from the Grid
	Input* pi = PG->GetInput();
	Output* po = PG->GetOutput();
	po->PrintMessage("Please Enter name of the saved file you want to open  ...");
	FileName = pi->GetSrting(po);
	InFile.open(FileName);
	if (!(InFile.is_open()))
	{
		po->PrintMessage("this file is not found ,please try again ...");

	}
}
void OpenGridAction::Execute()
{
	
	Grid * PG = pManager->GetGrid();// POINTER TO THE GRID
	Output* po=PG->GetOutput();
	PG->ClearAll(InFile);
	ReadActionParameters(); // reading action parameters
	InFile >> Ladder::CountLadder;
	if (Ladder::CountLadder != 0)
	{
		for (int i = 0; i < Ladder::CountLadder; i++)
		{
			Ladder*L = new Ladder;
			L->Load(InFile);
			GameObject *pgame = L;
			PG->AddObjectToCell(pgame);
			pgame->Draw(po);
		}
	}
	InFile >> Snake::CountSnake;
	if (Snake::CountSnake != 0){
		for (int i = 0; i < Snake::CountSnake; i++)
		{
			Snake*S = new Snake;
			S->Load(InFile);
			GameObject *pgame = S;
			PG->AddObjectToCell(pgame);
			pgame->Draw(po);
		}

	}

	InFile >> Card::CountCard;
	if (Card::CountCard != 0)
	{
		for (int i = 0; i < Card::CountCard; i++)
		{
			Card * C = new Card;
			C->Load(InFile);
			if (C->GetCardNumber() == 1)
			{
				CardOne* C1 = new CardOne ;
				*C1 = *((CardOne*)C);
				C1->Load(InFile);
				PG->AddObjectToCell(C1);
				C1->Draw(po);
			}
			else if (C->GetCardNumber() == 2)
			{
				CardTwo* C2 = new CardTwo;
				*C2 = *((CardTwo*)C);
				C2->Load(InFile);
				PG->AddObjectToCell(C2);
				C2->Draw(po);
			}
			else if (C->GetCardNumber() == 9)
			{
				CardNine* C9 = new CardNine;
				*C9 = *((CardNine*)C);
				C9->Load(InFile);
				PG->AddObjectToCell(C9);
				C9->Draw(po);
			}
			else if (C->GetCardNumber() == 10)
			{
				CardTen* C10 = new CardTen;
				*C10 = *((CardTen*)C);
				C10->Load(InFile);
				PG->AddObjectToCell(C10);
				
				C10->Draw(po);
			}
			else if (C->GetCardNumber() == 11)
			{
				CardEleven* C11 = new CardEleven;
				*C11 = *((CardEleven*)C);
				C11->Load(InFile);
				PG->AddObjectToCell(C11);
				C11->Draw(po);
			}

			else if (C->GetCardNumber() == 12)
			{
				
				CardTwelve* C12 = new CardTwelve;
				*C12 = *((CardTwelve*)C);
				C12->Load(InFile);
				PG->AddObjectToCell(C12);
				C12->Draw(po);
			}
			else if (C->GetCardNumber() == 13)
			{
				
				CardThirteen* C13 = new CardThirteen;
				*C13 = *((CardThirteen*)C);
				C13->Load(InFile);
				PG->AddObjectToCell(C13);
				C13->Draw(po);
			}
			else if (C->GetCardNumber() == 14)
			{
				CardFourteen* C14 = new CardFourteen;
				*C14 = *((CardFourteen*)C);
				C14->Load(InFile);
				PG->AddObjectToCell(C14);
				C14->Draw(po);
			}
			else
			{
				GameObject *pgame = C;
				PG->AddObjectToCell(pgame);
				pgame->Draw(po);
			}
		}
	}
}
OpenGridAction::~OpenGridAction(void)
{
}
