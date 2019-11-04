#pragma once
#include "State.h"

class Computer
{
private:
	std::list<std::string> possibleAlgorithms = { "best1depth" };
	std::string algorithm;
	State* currentState;

	State* moveBestFromDepth1();

public:
	Computer(std::string algorithm);
	State* getNextMove(State* currentState);
};

