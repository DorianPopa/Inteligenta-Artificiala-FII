#pragma once

constexpr auto BOARD_SIZE = 7;
class State
{
private:
	const int size = BOARD_SIZE;
	int board[BOARD_SIZE][BOARD_SIZE] = 
	{	
			0, 0, 0, 0, 0, 0, 0,					
			0, 0, 0, 0, 1, 0, 0,								
			0, 0, 0, 1, 0, 0, 0,								
			0, 0, 1, 0, 0, 0, 0,								
			0, 1, 0, 0, 0, 0, 0,								
			0, 0, 0, 0, 0, 0, 0,								
			0, 0, 0, 0, 0, 0, 0
	};
public:
	bool isFinal();
	bool isValid();
	State* Transition(int pozX, int pozY);
};

