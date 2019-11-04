#pragma once
#include <list>
#include <iostream>
class State
{
	// "j" pentru jucator - incepe jos, "c" pentru computer - incepe sus

public:
	char board[6][6];
	int varScore;
	State* previousState;

	State();
	State(State*, int oldx, int oldy, int newx, int newy);
	bool isFinal(char player);
	int score();
	std::list<State*> generateNextStates(char player);
	std::list<State*> generateNextStatesByPosition(int, int);
	void print();
	void setScore(int score);
	void setBoard();

	static bool compareStates(State* a, State* b) {
		return a->score() > b->score();
	}
};

