#pragma once
#include "State.h"
#include <algorithm>

class Computer
{
private:
	std::list<std::string> possibleAlgorithms = { "best1depth", "minimax" };
	std::string algorithm;
	State* currentState;

	State* moveBestFromDepth1();
	State* minimax(State* position, int depth, bool maximizingPlayer);

public:
	Computer(std::string algorithm);
	State* getNextMove(State* currentState);
};

