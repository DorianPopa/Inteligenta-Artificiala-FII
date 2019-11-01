#pragma once
#include <iostream>
#include "State.h"


class Game
{
	std::list<State*> states;

public:
	void playerMove();
	void computerMove();

	void renderBoard();
	State* getCurrentState();
	void mainGameLoop();

};

