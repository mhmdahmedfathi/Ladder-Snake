#include "Input.h"

#include "Output.h"
#include <stdexcept>

//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW) 
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if(Key == 13 )	// ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO) const
{

	//Done///TODO: implement the GetInteger function as described in Input.h file 
	//using function GetString() defined above and function stoi()

	//Input* pLabel =pO->CreateInput();
	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)
	string temp = GetSrting(pO);
	int diceValue;
	try {
		diceValue = stoi(temp);
		return diceValue;
	}
	catch (const std::invalid_argument & e) {
		return - 1;
	}
	
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//


ActionType Input::GetUserAction() const
{	
	int x = -1, y = -1;
	GetPointClicked(x, y); 

	//  ============ GUI in the Design mode ============
	if ( UI.InterfaceMode == MODE_DESIGN )	
	{
		// [1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on


			switch (ClickedItemOrder)
			{
			case ITM_ADD_LADDER: return ADD_LADDER; //Done
			case ITM_ADD_SNAKE: return ADD_SNAKE; //Done
			case ITM_ADD_CARD: return ADD_CARD; //Done
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;//done

			case ITM_EXIT: return EXIT; //Done
			case ITM_COPY_CARD: return COPY_CARD; //Done
			case ITM_CUT_CARD: return CUT_CARD; //Done
			case ITM_PASTE_CARD: return PASTE_CARD; //Done
			case ITM_EDIT_CARD: return EDIT_CARD; //Done
			case ITM_DELETE: return DELETE_OBJECT; //Done 
			case ITM_SAVE_GRID:  return SAVE_GRID; //Done
			case ITM_OPEN_GRID: return OPEN_GRID; //Done

			//Done ///TODO: Add cases for the other items of Design Mode


			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ( (y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;	
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType
			// [1] If user clicks on the Toolbar
		
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int ClickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;
			case ITM_ROLL_DICE: return ROLL_DICE;
			case ITM_NEW_GAME: return NEW_GAME;
			case ITM_INPUT_DICE_VALUE: return INPUT_DICE_VALUE;
			case ITM_EXIT_PLAY: return EXIT_PLAY;
			//done	///TODO: Add cases for the other items of Design Mode


			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;



		//return TO_DESIGN_MODE;	// just for now ==> This should be updated


	}	

}

////////////////////////////////////////////////////////////////////////////////////////// 

//Done
CellPosition Input::GetCellClicked() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	// Get the coordinates of the user click

	CellPosition cellPos;

	if ( UI.InterfaceMode == MODE_DESIGN )	
	{
		if ( y >= UI.ToolBarHeight && y <= (UI.height - UI.StatusBarHeight))
		{
			//Done///TODO: SetHCell and SetVCell of the object cellPost appropriately
			//       using the coordinates x, y and the appropriate variables of the UI_Info Object (UI)
			int hCell=(x - UI.wx) / UI.CellWidth;
			int vCell = (y - UI.wy- UI.ToolBarHeight) / UI.CellHeight;

			
			cellPos.SetVCell(vCell);
			cellPos.SetHCell(hCell);

		}
		else
		{
			cellPos.SetVCell(-1);
			cellPos.SetHCell(-1);

		}
	}

	return cellPos;
}

////////////////////////////////////////////////////////////////////////////////////////// 
