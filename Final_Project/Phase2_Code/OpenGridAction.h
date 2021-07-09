#pragma once
#include"Action.h"
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
#include "GameObject.h"
#include "CardOne.h"
#include "CardTwo.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"
#include "CardTwelve.h"
#include "CardThirteen.h"
#include "CardFourteen.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>

class OpenGridAction : public Action
{
	ifstream InFile;
	string FileName;


public:
	OpenGridAction(ApplicationManager *pApp);
	~OpenGridAction(void);
	virtual void ReadActionParameters();
	virtual void Execute();
};