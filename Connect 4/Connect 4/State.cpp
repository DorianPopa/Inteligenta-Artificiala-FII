#include "State.h"

bool State::isFinal() {
	int column[BOARD_SIZE] = {};
	int inARow = 1;
	for (int lin = BOARD_SIZE - 1; lin >= 0 ; lin--) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			if (col > 0) {
				if (board[lin][col - 1] == board[lin][col] && board[lin][col] != 0)
					inARow++;
				else
					inARow = 1;
			}
			if (inARow >= 4)
				return true;
			if (lin == 0) {
				column[col] = board[lin][col];
			}
			else {
				if (column[col] * board[lin][col] <= 0) {
					column[col] = board[lin][col];
				}
				else {
					column[col] += board[lin][col];
				}
			}
			if (column[col] >= 4 || column[col] <= -4)
				return true;
		}
	}

	// rosu
	for (int linieStart = BOARD_SIZE / 2; linieStart < BOARD_SIZE; linieStart++) {
		int lin = linieStart;
		int col = 0;
		inARow = 1;
		while (col <= linieStart) {
			if (lin != linieStart && col != 0) {
				if (board[lin][col] == board[lin + 1][col - 1] && board[lin][col] != 0 )
					inARow++;
				else
					inARow = 1;
			}
			if (inARow == 4)
				return true;
			lin--;
			col++;
		}
	}

	// verde
	for (int coloanaStart = 1; coloanaStart <= BOARD_SIZE / 2; coloanaStart++) {
		int lin = BOARD_SIZE - 1;
		int col = coloanaStart;
		inARow = 1;
		while (col < BOARD_SIZE) {
			if (lin != BOARD_SIZE - 1 && col != coloanaStart) {
				if (board[lin][col] == board[lin + 1][col - 1] && board[lin][col] != 0)
					inARow++;
				else
					inARow = 1;
			}
			if (inARow == 4)
				return true;
			lin--;
			col++;
		}
	}

	// albastru
	for (int coloanaStart = 0; coloanaStart <= BOARD_SIZE / 2; coloanaStart++) {
		int col = coloanaStart;
		int lin = 0;
		inARow = 1;
		while (col < BOARD_SIZE) {
			if (col != coloanaStart && lin != 0) {
				if (board[lin][col] == board[lin - 1][col - 1] && board[lin][col] != 0)
					inARow++;
				else
					inARow = 1;
			}
			if (inARow == 4)
				return true;
			lin++;
			col++;
		}
	}

	// mov
	for (int linieStart = 1; linieStart <= BOARD_SIZE / 2; linieStart++) {
		int col = 0;
		int lin = linieStart;
		inARow = 1;
		while (lin < BOARD_SIZE) {
			if (col != 0 && lin != linieStart) {
				if (board[lin][col] == board[lin - 1][col - 1] && board[lin][col] != 0)
					inARow++;
				else
					inARow = 1;
			}
			if (inARow == 4)
				return true;
			lin++;
			col++;
		}
	}

	return false;
}
