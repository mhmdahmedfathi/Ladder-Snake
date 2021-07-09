#pragma once
#include"Action.h"
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include "Ladder.h"
#include "Snake.h"
#include "Card.h"
class SaveGridAction : public Action
{
	string FileName;
public:
	SaveGridAction(ApplicationManager* pApp);
	~SaveGridAction(void);
	virtual void ReadActionParameters();
	virtual void Execute();
};

