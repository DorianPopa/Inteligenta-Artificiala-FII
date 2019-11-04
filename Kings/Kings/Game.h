#pragma once
#include <iostream>
#include "State.h"
#include "Computer.h"


class Game
{
private:
	Computer* theBot;
	std::list<State*> states;
	
	void playerMove();
	void computerMove();

	void renderBoard();
	State* getCurrentState();

public:

	Game(std::string solverType);
	void mainGameLoop();

	static void printRekt();
};

