#pragma once
#include <list>
#include <iostream>
class State
{
	// "j" pentru jucator - incepe jos, "c" pentru computer - incepe sus

public:
	char board[6][6];
	State();
	State(State*, int oldx, int oldy, int newx, int newy);
	bool isFinal();
	int score();
	std::list<State*> generateNextStates();
	std::list<State*> generateNextStatesByPosition(int, int);
	void print();

	static bool compareStates(State* a, State* b) {
		return a->score() > b->score();
	}
};

