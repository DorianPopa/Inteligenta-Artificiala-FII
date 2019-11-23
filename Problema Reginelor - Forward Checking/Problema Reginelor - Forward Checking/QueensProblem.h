#pragma once
#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>

class QueensProblem
{
	int size;
	int X[100];
	std::list<int> D[100];
	bool forward_check(int);
	void copy(std::list<int>[], std::list<int>[]);
public:
	QueensProblem(int);
	void bkt(int);
	void print();
};
