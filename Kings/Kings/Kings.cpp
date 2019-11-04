// Kings.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "State.h"
#include "Game.h"

int main()
{
	Game* game = new Game("minimaxretezat");
	game->mainGameLoop();
	return 0;
}