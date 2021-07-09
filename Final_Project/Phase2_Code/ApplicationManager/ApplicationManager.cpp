
//Adding #include for all action types
#include "ApplicationManager.h"
#include "../Actions/AddSnakeAction.h"
#include "../Grid/Grid.h"
#include "../Actions/AddLadderAction.h"
#include "../Actions/AddCardAction.h"
#include "../Actions/RollDiceAction.h"
#include "../Actions/InputDiceValue.h"
#include "../Actions/NewGame.h"
#include "../Actions/CopyCardAction.h"
#include "../Actions/CutCardAction.h"
#include "../Actions/PasteCardAction.h"
#include "../Actions/SwitchToDesignModeAction.h"
#include "../Actions/SwitchToPlayModeAction.h"
#include "../Actions/EditCardAction.h"
#include "../Actions/SaveGridAction.h"
#include "../Actions/DeleteGameObjectAction.h"
#include "../Actions/OpenGridAction.h"

ApplicationManager::ApplicationManager()
{
	// Create Input, output and Grid
	pOut = new Output();
	pIn = pOut->CreateInput();
	pGrid = new Grid(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////////

ApplicationManager::~ApplicationManager()
{
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid * ApplicationManager::GetGrid() const
{
	return pGrid;
}

void ApplicationManager::UpdateInterface() const
{
	pGrid->UpdateInterface();
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{

	case ADD_LADDER:
		// create an object of AddLadderAction here
		pAct = new AddLadderAction(this);
		break;


	case ADD_SNAKE:
		// create an object of AddSnakeAction here
		pAct = new AddSnakeAction(this);
		break;

	case ADD_CARD:
		// create an object of AddCardAction here
		pAct = new AddCardAction(this);
		break;

	case EXIT:
		break;

	case COPY_CARD:
		pAct = new CopyCardAction(this);
		break;

	case CUT_CARD:
		pAct = new CutCardAction(this);
		break;

	case PASTE_CARD:
		pAct = new PasteCardAction(this);
		break;

	case TO_PLAY_MODE:
		pAct = new SwitchToPlayModeAction(this); // temporary till you made its action class (CHANGE THIS LATTER)
		break;

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this); // temporary till you made its action class (CHANGE THIS LATTER)
		break;

	case ROLL_DICE:
		// create an object of RollDiceAction here
		pAct = new RollDiceAction(this);
		break;
		
	case NEW_GAME:
		pAct = new NewGame(this);
		break;
	
	case INPUT_DICE_VALUE:
		pAct = new InputDiceValue(this);
		break;

	case EXIT_PLAY:
		break;

	case EDIT_CARD:
		// create an object of EditCardAction here
		pAct = new EditCardAction(this);
		break;

	case DELETE_OBJECT:
		pAct = new DeleteGameObjectAction(this);
		break;

	case SAVE_GRID:
		pAct = new SaveGridAction(this);
		break;

	case OPEN_GRID:
		pAct = new OpenGridAction(this);
		break;

	case STATUS:	// a click on the status bar ==> no action
		return;
	
	default:
		return;
	}

	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
