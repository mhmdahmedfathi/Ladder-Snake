#include "SwitchToDesignModeAction.h"
#include "../Grid/Grid.h"
#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"
#include "NewGame.h"

SwitchToDesignModeAction::SwitchToDesignModeAction(ApplicationManager* pApp) : Action(pApp)
{
	// pNewGame(pApp);

	// Initializes the pManager pointer of Action with the passed pointer
}

SwitchToDesignModeAction::~SwitchToDesignModeAction()
{
}

void SwitchToDesignModeAction::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
    pGrid->PrintErrorMessage("Design Mode Action is activated..click to continue");
}

void SwitchToDesignModeAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	NewGame pNewGame(pManager);

	pNewGame.Execute();
	pOut->CreateDesignModeToolBar();
	pOut->ClearGridArea();
}



