#pragma once
#include "State.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <list>
#include <chrono>

#define CRONO std::chrono::time_point<std::chrono::steady_clock>

class Problem
{
private:
	State* initialState;
	std::vector<State*> usedStates;
	std::list<State*> aStarStates;

	int backtrackingFlag = false;

	bool isStateAlreadyUsed(State* s);
	void printSolutionTrace(State* s, CRONO);
	

public:
	Problem(int lm, int lc, int rm, int rc, int bs, int bp);

	void solveBacktracking(State* currentState, CRONO);
	void solveBacktracking(CRONO);
	bool solveRandom(int maxNumberOfTries, CRONO);
	void solveDFS(int currentDepth, int maxDepth, State* currentState, CRONO);
	void solveDFS(int maxDepth, CRONO);
	void deleteUsedStates();
	static bool compareStates(State* a, State* b);
	void solveAStar(CRONO);
};

