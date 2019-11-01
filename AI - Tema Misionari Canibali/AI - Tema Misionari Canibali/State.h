#pragma once
#include <iostream>
#include <functional>

class State
{
private:
	int lm = 0; 
	int lc = 0;
	int rm = 0;
	int rc = 0;
	int bs = 0;
	int bp = 0;

public:
	State(int lm, int lc, int rm, int rc, int bs, int bp);
	int getBoatSize();
	void printState();
	bool isValid();
	bool isFinal();

	State* Transition(int misToMove, int canToMove);
	State* previousState = nullptr;
	bool operator == (State& otherState);
	int getC();

	int getBoatPosition();
	int getMissionary(int boatPosition);
	int getCannibals(int boatPosition);
};

