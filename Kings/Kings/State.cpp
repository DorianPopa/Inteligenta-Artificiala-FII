#include "State.h"


State::State()
{
	for (int i = 0; i < 6; i++) {
		board[0][i] = 'b';
		board[i][0] = 'b';
		board[5][i] = 'b';
		board[i][5] = 'b';
	}

	for (int i = 2; i < 4; i++) {
		for (int j = 1; j < 5; j++) {
			board[i][j] = '0';
		}
	}

	for (int i = 1; i < 5; i++) {
		board[1][i] = 'c';
		board[4][i] = 'j';
	}

	varScore = INT_MIN;
	previousState = nullptr;
}

void State::setBoard() {
	char board[6][6] = { 'b', 'b', 'b', 'b', 'b', 'b',
					'b', 'j', 'j', 'j', '0', 'b',
					'b', '0', '0', '0', '0', 'b',
					'b', '0', 'j', '0', 'c', 'b',
					'b', 'c', 'c', 'c', '0', 'b',
					'b', 'b', 'b', 'b', 'b', 'b'
	};

	memcpy(this->board, board, sizeof(board));
}

State::State(State* state, int oldx, int oldy, int newx, int newy) {

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			this->board[i][j] = state->board[i][j];
		}
	}

	if ((state->board[oldx][oldy] == 'j' && state->board[newx][newy] != 'c') ||
		(state->board[oldx][oldy] == 'c' && state->board[newx][newy] != 'j'))
		std::swap(board[oldx][oldy], board[newx][newy]);

	varScore = INT_MIN;
	previousState = nullptr;
}

bool State::isFinal(char player) {
	if(player == 'j')
		for (int i = 1; i < 5; i++) {
			if (board[1][i] != 'j') return false;
		}
	else
		for (int i = 1; i < 5; i++) {
			if (board[4][i] != 'c') return false;
		}
	return true;
}

int State::score() {
	if (varScore != INT_MIN && varScore != INT_MAX)
		return varScore;

	int totalComputer = 0;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			if (board[i][j] == 'c') {
				totalComputer += i;
			}
		}
	}

	int totalPlayer = 0;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			if (board[i][j] == 'j') {
				totalPlayer += (5 - i);
			}
		}
	}
	varScore = totalComputer - totalPlayer;
	return varScore;
}

std::list<State*> State::generateNextStates(char player) {

	std::list<State*> lista;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			if (board[i][j] == player) {
				std::list<State*> newLista = generateNextStatesByPosition(i, j);
				for (std::list<State*>::iterator it = newLista.begin(); it != newLista.end(); it++) {
					lista.push_back((*it));
				}
			}
		}
	}
	return lista;
}

std::list<State*> State::generateNextStatesByPosition(int xs, int ys) {
	std::list<State*> lista;
	int xd[] = { -1, -1, -1,  0,  0,  1,  1,  1 };
	int yd[] = { -1,  0,  1, -1,  1, -1,  0,  1 };
	int newx, newy;
	for (int i = 0; i < 8; i++) {
		newx = xs + xd[i];
		newy = ys + yd[i];
		if (board[newx][newy] == '0') {
			State* newState = new State(this, xs, ys, newx, newy);
			lista.push_back(newState);
		}
	}
	return lista;
}

void State::print() {
	for (int i = 1; i < 5; i++) {
		std::cout << i << " ";
		for (int j = 1; j < 5; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << '\n';
	}

	std::cout << "  ";
	for (int j = 1; j < 5; j++) {
		std::cout << j << " ";
	}
	std::cout << std::endl;
}

void State::setScore(int score)
{
	varScore = score;
}
