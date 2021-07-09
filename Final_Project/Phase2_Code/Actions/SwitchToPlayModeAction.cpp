#include "SwitchToPlayModeAction.h"
#include "../Grid/Grid.h"
#include "../GUIClasses/Input.h"
#include "../GUIClasses/Output.h"


SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{

	Grid* pGrid = pManager->GetGrid();
	pGrid->PrintErrorMessage("Play Mode Action is activated..click to continue");

}

void SwitchToPlayModeAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->CreatePlayModeToolBar();

}
