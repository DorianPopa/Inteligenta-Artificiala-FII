// AI - Tema Misionari Canibali.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "State.h"
#include "Problem.h"

using namespace std;

int main() {
	int lm, lc, bs, maxDepth;
	srand(time(NULL));
	for (int i = 1; i <= 10; i++) {
		lm = rand() % 15 + 1;
		lc = rand() % 15 + 1;
		bs = rand() % 15 + 1;
		maxDepth = 300;
		Problem* p = new Problem(lm, lc, 0, 0, bs, 1);

		cout << "Iteration: " << i << endl << "STATE IS: " << lm << " " << lc << " 0 0 " << bs << " 1" << endl;
		cout << "-----------------------------------------------------------------" << endl << endl;

		cout << "Back: " << endl;
		auto start = std::chrono::high_resolution_clock::now();
		p->solveBacktracking(start);
		p->deleteUsedStates();

		cout << "Random: " << endl;
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i <= 10; i++)
			if (p->solveRandom(100, start))
				break;
		p->deleteUsedStates();

		cout << "DFS: " << endl;
		start = std::chrono::high_resolution_clock::now();
		p->solveDFS(maxDepth, start);
		p->deleteUsedStates();

		cout << "A*: " << endl;
		start = std::chrono::high_resolution_clock::now();
		p->solveAStar(start);
		p->deleteUsedStates();
	}
	
	/*
	cin >> lm >> lc >> bs >> maxDepth;
	Problem* p1 = new Problem(lm, lc, 0, 0, bs, 1);

	auto start = std::chrono::high_resolution_clock::now();
	cout << "Back: " << endl;
	p1->solveBacktracking(start);
	p1->deleteUsedStates();
	start = std::chrono::high_resolution_clock::now();

	cout << "Random: " << endl;
	for (int i = 0; i <= 10; i++)
		if (p1->solveRandom(100, start))
			break;
	p1->deleteUsedStates();

	cout << "DFS: " << endl;
	start = std::chrono::high_resolution_clock::now();
	p1->solveDFS(maxDepth, start);
	p1->deleteUsedStates();
	
	cout << "A*: " << endl;
	start = std::chrono::high_resolution_clock::now();
	p1->solveAStar(start);
	p1->deleteUsedStates();
	*/

	return 0;
}
