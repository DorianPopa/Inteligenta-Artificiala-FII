#pragma once
#include "State.h"
#include <algorithm>

class Computer
{
private:
	std::list<std::string> possibleAlgorithms = { "best1depth", "minimax", "minimaxretezat" };
	std::string algorithm;
	State* currentState;

	State* moveBestFromDepth1();
	State* minimax(State* position, int depth, bool maximizingPlayer);
	State* minimaxRetezat(State* position, int depth, bool maximizingPlayer, int alpha, int beta);

public:
	Computer(std::string algorithm);
	State* getNextMove(State* currentState);
};

