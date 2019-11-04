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
	else if (algorithm == "minimax") {
		int desiredDepth = 0;
		//std::cout << "Enter the desired minmaxDepth: ";
		//std::cin >> desiredDepth;
		State* chestie = minimax(currentState, 4, true);
		chestie->print();
		return chestie;
	}
		
	else
		return nullptr;
}


State* Computer::moveBestFromDepth1()
{
	std::list<State*> newStates = currentState->generateNextStates('c');
	newStates.sort(State::compareStates);
	return newStates.front();
}

State* Computer::minimax(State* position, int depth, bool maximizingPlayer)
{
	if (depth == 0 || position->isFinal())
		return position;

	if (maximizingPlayer) {
		State* maxEval = new State();
		maxEval->setScore(INT_MIN);
		for (auto possibleNextState : position->generateNextStates('c')) {
			State* eval = minimax(possibleNextState, depth - 1, false);
			int evalInt = eval->score();
			int maxEvalInt = maxEval->varScore;
			if (evalInt > maxEvalInt)
				maxEval = eval;
		}
		return maxEval;
	}

	else {
		State* minEval = new State();
		minEval->setScore(INT_MAX);
		for (auto possibleNextState : position->generateNextStates('j')) {
			State* eval = minimax(possibleNextState, depth - 1, true);
			if (eval->score() < minEval->varScore)
				minEval = eval;
		}
		return minEval;
	}
}

