#include "SaveGridAction.h"
#include"Action.h"
#include <iostream>
using namespace std;
#include <fstream>
#include "Grid.h"

SaveGridAction::SaveGridAction(ApplicationManager* pApp) : Action(pApp)
{

}

SaveGridAction::~SaveGridAction(void)
{
}
void SaveGridAction::ReadActionParameters()
{
	Grid* PG = pManager->GetGrid(); // POINTER TO THE GRID
	//  Getting  a Pointer to the Input / Output Interfaces from the Grid
	Input* pi = PG->GetInput();
	Output* po = PG->GetOutput();
	po->PrintMessage("Please Enter name of the file  ...");
	FileName = pi->GetSrting(po);

}
void SaveGridAction::Execute()
{
	ReadActionParameters(); // reading action parameters
	Grid* PG = pManager->GetGrid(); // POINTER TO THE GRID
	//OutFile.open(FileName); // opening the file to save the data   + ".txt"
	ofstream OutFile(FileName);


	OutFile << Ladder::CountLadder << endl;
	PG->SaveAll(OutFile, ladder); // SAVING ALL THE LADDERS
	OutFile << Snake::CountSnake << endl;
	PG->SaveAll(OutFile, snake); // SAVING ALL THE SNAKEs
	OutFile << Card::CountCard;
	PG->SaveAll(OutFile, card); // SAVING ALL THE CARDS
	OutFile.close(); // to close the file after saving

}
