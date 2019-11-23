#include "QueensProblem.h"

QueensProblem::QueensProblem(int n)
{
	size = n;
	for (int i = 0; i < size; i++) X[i] = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 1; j <= size; j++) {
			D[i].push_back(j);
		}
	}
}

void QueensProblem::bkt(int k) {
	if (k == size)
		print();
	else {
		std::list<int> Dcopy[100];
		copy(Dcopy, D);
		for (auto it = Dcopy[k].begin(); it != Dcopy[k].end(); it++) {
			X[k] = *it;
			if (forward_check(k))
				bkt(k + 1);
			copy(D, Dcopy);
		}
	}
}

bool QueensProblem::forward_check(int k) {
	for (int i = k + 1; i < size; i++) {
		D[i].remove(X[k] - i + k);
		D[i].remove(X[k]);
		D[i].remove(X[k] + i - k);
		if (D[i].size() == 0) return false;
	}
	return true;
}

void QueensProblem::copy(std::list<int> dst[], std::list<int> src[]) {
	for (int i = 0; i < size; i++) {
		dst[i].clear();
		for (auto it = src[i].begin(); it != src[i].end(); it++) {
			dst[i].push_back(*it);
		}
	}
}

void QueensProblem::print() {
	for (int i = 0; i < size; i++) std::cout << X[i] << ' ';
	std::cout << '\n';
	exit(0);
}
