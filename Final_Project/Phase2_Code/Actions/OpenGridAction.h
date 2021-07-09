#pragma once

#include"Action.h"
#include "../GameObjects/Ladder.h"
#include "../GameObjects/Snake.h"
#include "../GameObjects/GameObject.h"
#include "../GameObjects/Cards/Card.h"
#include "../GameObjects/Cards/CardOne.h"
#include "../GameObjects/Cards/CardTwo.h"
#include "../GameObjects/Cards/CardNine.h"
#include "../GameObjects/Cards/CardTen.h"
#include "../GameObjects/Cards/CardEleven.h"
#include "../GameObjects/Cards/CardTwelve.h"
#include "../GameObjects/Cards/CardThirteen.h"
#include "../GameObjects/Cards/CardFourteen.h"

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