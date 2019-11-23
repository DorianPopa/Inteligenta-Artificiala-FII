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
		State* chestie = minimax(currentState, 5, true);
		while (chestie->previousState != currentState)
			chestie = chestie->previousState;
		return chestie;
	}
	else if (algorithm == "minimaxretezat") {
		int desiredDepth = 0;
		State* chestie = minimaxRetezat(currentState, 8, true, INT_MIN, INT_MAX);
		while (chestie->previousState != currentState)
			chestie = chestie->previousState;
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
	if (depth == 0)
		return position;

	if (maximizingPlayer) {
		if (position->isFinal('j'))
			return position;
		State* maxEval = new State();
		maxEval->setScore(INT_MIN);
		for (auto possibleNextState : position->generateNextStates('c')) {
			possibleNextState->previousState = position;
			State* eval = minimax(possibleNextState, depth - 1, false);
			int evalInt = eval->score();
			int maxEvalInt = maxEval->varScore;
			if (evalInt > maxEvalInt) {
				maxEval = eval;
			}		
		}
		return maxEval;
	}
	else {
		if (position->isFinal('c'))
			return position;
		State* minEval = new State();
		minEval->setScore(INT_MAX);
		for (auto possibleNextState : position->generateNextStates('j')) {
			possibleNextState->previousState = position;
			State* eval = minimax(possibleNextState, depth - 1, true);
			if (eval->score() < minEval->varScore) {
				minEval = eval;
			}
		}
		return minEval;
	}
}

State* Computer::minimaxRetezat(State* position, int depth, bool maximizingPlayer, int alpha, int beta)
{
	if (depth == 0)
		return position;

	if (maximizingPlayer) {
		if (position->isFinal('j'))
			return position;
		State* maxEval = new State();
		maxEval->setScore(INT_MIN);
		for (auto possibleNextState : position->generateNextStates('c')) {
			possibleNextState->previousState = position;
			State* eval = minimaxRetezat(possibleNextState, depth - 1, false, alpha, beta);
			int evalInt = eval->score();
			int maxEvalInt = maxEval->varScore;
			if (evalInt > maxEvalInt) {
				maxEval = eval;
			}
			alpha = std::max(alpha, evalInt);
			if (beta <= alpha)
				break;
		}
		return maxEval;
	}
	else {
		if (position->isFinal('c'))
			return position;
		State* minEval = new State();
		minEval->setScore(INT_MAX);
		for (auto possibleNextState : position->generateNextStates('j')) {
			possibleNextState->previousState = position;
			State* eval = minimaxRetezat(possibleNextState, depth - 1, true, alpha, beta);
			int evalInt = eval->score();
			int minEvalInt = minEval->varScore;
			if (evalInt < minEvalInt) {
				minEval = eval;
			}
			beta = std::min(beta, evalInt);
			if (beta <= alpha)
				break;
		}
		return minEval;
	}
}

