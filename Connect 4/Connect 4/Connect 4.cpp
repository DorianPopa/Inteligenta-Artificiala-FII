// Connect 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"
#include "State.h"

int main()
{
	State* state = new State();
	if (state->isFinal())
		std::cout << "DA";
	return 0;
}

