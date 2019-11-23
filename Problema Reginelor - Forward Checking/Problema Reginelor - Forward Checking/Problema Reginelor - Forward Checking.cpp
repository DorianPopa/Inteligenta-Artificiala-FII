// ProblemaReginelor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "QueensProblem.h"

int main()
{
	int n;
	std::cin >> n;
	QueensProblem* qpinstance = new QueensProblem(n);
	qpinstance->bkt(0);
}
