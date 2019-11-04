#include "Computer.h"

Computer::Computer(std::string desiredAlgorithm)
{
	for (auto alg : possibleAlgorithms) {
		if (alg == desiredAlgorithm) {
			algorithm = desiredAlgorithm;
			break;
		}
	}
	if (algorithm.empty())
		exit(0);
}

State* Computer::getNextMove(State* currentState)
{
	if (currentState == nullptr)
		return nullptr;

	this->currentState = currentState;
	if (algorithm == "best1depth")
		return moveBestFromDepth1();
	else
		return nullptr;
}


State* Computer::moveBestFromDepth1()
{
	std::list<State*> newStates = currentState->generateNextStates();
	newStates.sort(State::compareStates);
	return newStates.front();
}

