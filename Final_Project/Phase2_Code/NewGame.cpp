#include "NewGame.h"
#include "Grid.h"
#include "Player.h"
NewGame::NewGame(ApplicationManager* pApp) : Action(pApp)
{
}

void NewGame::ReadActionParameters()
{
	//No Parameters For This Action
}

void NewGame::Execute()
{
	Grid* pGrid = pManager->GetGrid();//get pGrid of the object
	Output* pOut = pGrid->GetOutput(); //get pOut
	Input* pIn = pGrid->GetInput();//Get Input
	int x, y; //coordenets
	CellPosition FirstCell(1);  //To Start From First Cell
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		Player *pPlayer = pGrid->GetCurrentPlayer(); //Get Current Player
		pGrid->UpdatePlayerCell(pPlayer,FirstCell ); // To Return To the first cell
		
		pPlayer->SetWallet(100);// To Set The Wallet To 100
		pPlayer->setturncount(0);//set turn count to 0
		pGrid->AdvanceCurrentPlayer(); // To Go To The Next Player
	}
	pGrid->SetCurrentPlayer(0); // To Return To Player 0
	pGrid->SetEndGame(false);
	pManager->UpdateInterface(); // To Update The Info of The Players
	pOut->PrintMessage("New Game Is Started");
	pIn->GetPointClicked(x, y); // Wait Mouse Click
	pOut->ClearStatusBar(); // Clear StatusBar
}

NewGame::~NewGame()
{
}
