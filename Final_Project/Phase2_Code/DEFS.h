#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.
enum type { ladder, snake, card };

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode

	ADD_LADDER,		// Add Ladder Action
	ADD_SNAKE,		// Add Snake Action	
	ADD_CARD,		// Add Card Action	
    EXIT,
	TO_PLAY_MODE,		// Go to Play Mode

	COPY_CARD,
	CUT_CARD,
	PASTE_CARD,
	EDIT_CARD,
	DELETE_OBJECT,
	SAVE_GRID,
	OPEN_GRID,

	//  [2] Actions of Play Mode

	TO_DESIGN_MODE,	// Go to Design Mode
	ROLL_DICE,		// Roll Dice Action
	NEW_GAME,
	INPUT_DICE_VALUE,
	EXIT_PLAY,
	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,				// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,			// Inside Grid Area
	STATUS 				// Inside StatusBar Area
};

#endif