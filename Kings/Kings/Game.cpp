#include "Game.h"

Game::Game(std::string solverType)
{
	theBot = new Computer(solverType);
}

State* Game::getCurrentState() {
	return states.back();
}

void Game::renderBoard() {
	getCurrentState()->print();
	std::cout << std::endl << "---------" << std::endl;
}

void Game::playerMove() {
	int fromX, fromY, toX, toY;
	std::cout << "Input (initial coords)(final coords): ";
	std::cin >> fromX >> fromY >> toX >> toY;

	State* newState = new State(states.back(), fromX, fromY, toX, toY);
	if (newState != nullptr)
		states.push_back(newState);
}

void Game::computerMove() {
	states.push_back(theBot->getNextMove(getCurrentState()));
}

void Game::mainGameLoop()
{
	char currentPlayer = 'j';
	State* initialState = new State();
	//initialState->setBoard();
	states.push_back(initialState);
	while(true) {
		renderBoard();
		currentPlayer = 'j';
		playerMove();
		if (getCurrentState()->isFinal('j'))
			break;
		currentPlayer = 'c';
		renderBoard();
		computerMove();
		if (getCurrentState()->isFinal('c'))
			break;
	}
	renderBoard();
	if(currentPlayer == 'j')
		std::cout << "Player won! gj" << std::endl;
	else if(currentPlayer == 'c')
		std::cout << "Git gud m8" << std::endl;
}
