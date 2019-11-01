#include "Problem.h"
#include <algorithm>

Problem::Problem(int lm, int lc, int rm, int rc, int bs, int bp)
{
	initialState = new State(lm, lc, rm, rc, bs, bp);
	usedStates.empty();
	usedStates.push_back(initialState);
}

bool Problem::isStateAlreadyUsed(State* s)
{
	std::vector<State*>::iterator it;
	for (it = usedStates.begin(); it < usedStates.end(); it++) {
		if (**it == *s)
			return true;
	}
	return false;
}

void Problem::solveBacktracking(State* currentState, CRONO start) 
{
	if (backtrackingFlag == false) {
		usedStates.push_back(currentState);
		if (currentState->isValid()) {
			if (currentState->isFinal()) {
				backtrackingFlag = true;
				printSolutionTrace(currentState, start);
				deleteUsedStates();
			}
			else {
				for (int peopleToMove = 1; peopleToMove <= initialState->getBoatSize(); peopleToMove++) {
					for (int misToMove = 0; misToMove <= peopleToMove; misToMove++) {
						int canToMove = peopleToMove - misToMove;
						State* nextState = currentState->Transition(misToMove, canToMove);
						if (nextState != nullptr) {
							if (!isStateAlreadyUsed(nextState)) {
								nextState->previousState = currentState;
								solveBacktracking(nextState, start);
							}
						}
					}
				}
			}
		}
	}
}

void Problem::solveBacktracking(CRONO start)
{
	backtrackingFlag = false;
	solveBacktracking(this->initialState, start);
}

void Problem::printSolutionTrace(State* lastState, CRONO start) {

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Finished" << std::endl;
	int solutionLength = 1;
	while (!(lastState == initialState)) {
		lastState->printState();
		lastState = lastState->previousState;
		solutionLength++;
	}
	this->initialState->printState();
	std::cout << "Solution Length: " << solutionLength << " States" << std::endl;
	std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;
	std::cout << std::endl << std::endl;

	//exit(0);
}

bool Problem::solveRandom(int maxNumberOfTries, CRONO start)
{
	bool foundSolution = false;
	int invalid = 0;

	srand(time(NULL));

	State* currentState = initialState;

	initialState->previousState = initialState;
	while (maxNumberOfTries > 0) {

		int nrPpsToMove = rand() % initialState->getBoatSize() + 1;
		int misToMove = std::min(rand() % nrPpsToMove + 1, currentState->getMissionary(currentState->getBoatPosition()));
		int canToMove = std::min(nrPpsToMove - misToMove, currentState->getCannibals(currentState->getBoatPosition()));

		State* nextState = currentState->Transition(misToMove, canToMove);
		/*
		if (nextState != nullptr) {
			while (!nextState->isValid()) {
				int nrPpsToMove = rand() % initialState->getBoatSize() + 1;
				int misToMove = std::min(rand() % nrPpsToMove + 1, currentState->getMissionary(currentState->getBoatPosition()));
				int canToMove = std::min(nrPpsToMove - misToMove, currentState->getCannibals(currentState->getBoatPosition()));
				State* nextState = currentState->Transition(misToMove, canToMove);
			}
		}
		*/
		if (nextState != nullptr) {
			if (!isStateAlreadyUsed(nextState)) {
				usedStates.push_back(nextState);
				nextState->previousState = currentState;
				if (nextState->isValid()) {
					if (nextState->isFinal()) {
						foundSolution = true;
						printSolutionTrace(nextState, start);
						deleteUsedStates();
						break;
					}
					currentState = nextState;
				}
			}
		}
		maxNumberOfTries--;
	}
	deleteUsedStates();
	return foundSolution;
}

void Problem::solveDFS(int currentDepth, int maxDepth, State* currentState, CRONO start)
{
	if (backtrackingFlag == false) {
		usedStates.push_back(currentState);
		if (currentState->isValid()) {
			if (currentState->isFinal()) {
				backtrackingFlag = true;
				printSolutionTrace(currentState, start);
				deleteUsedStates();
			}
			else {
				if (currentDepth <= maxDepth) {
					for (int peopleToMove = 1; peopleToMove <= initialState->getBoatSize(); peopleToMove++) {
						for (int misToMove = 0; misToMove <= peopleToMove; misToMove++) {
							int canToMove = peopleToMove - misToMove;
							State* nextState = currentState->Transition(misToMove, canToMove);
							if (nextState != nullptr) {
								if (!isStateAlreadyUsed(nextState)) {
									nextState->previousState = currentState;
									solveDFS(currentDepth + 1, maxDepth, nextState, start);
								}
							}
						}
					}
				}
			}
		}
	}
}

void Problem::solveDFS(int maxDepth, CRONO start)
{
	backtrackingFlag = false;
	solveDFS(1, maxDepth, this->initialState, start);
}

void Problem::deleteUsedStates()
{
	std::vector<State*>::iterator it;
	for (it = usedStates.begin(); it < usedStates.end(); it++) {
		if(*it != initialState)
			delete(*it);
	}
	usedStates.clear();
}

bool Problem::compareStates(State* a, State* b) {
	return a->getC() < b->getC();
}

void Problem::solveAStar(CRONO start)
{
	aStarStates.push_back(this->initialState);
	usedStates.push_back(this->initialState);

	while (!aStarStates.empty()) {
		State* currentState = aStarStates.front();
		aStarStates.pop_front();
		if (currentState->isFinal()) {
			printSolutionTrace(currentState, start);
			deleteUsedStates();
		}
		for (int peopleToMove = 1; peopleToMove <= initialState->getBoatSize(); peopleToMove++) {
			for (int misToMove = 0; misToMove <= peopleToMove; misToMove++) {
				int canToMove = peopleToMove - misToMove;
				State* nextState = currentState->Transition(misToMove, canToMove);
				if (nextState != nullptr) {
					if (nextState->isValid()) {
						if (!isStateAlreadyUsed(nextState)) {
							nextState->previousState = currentState;
							aStarStates.push_back(nextState);
							usedStates.push_back(nextState);
						}
					}
				}
			}
		}
		aStarStates.sort(this->compareStates);
	}
}	