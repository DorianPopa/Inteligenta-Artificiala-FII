#pragma once

#include <iostream>
#include <cstdlib>

using namespace std;

bool used[1000000];
int previous[1000000];

int computeUsed(int lm, int lc, int rm, int rc, int bp) {
	return (((((lm * 10) + lc) * 10 + rm) * 10) + rc) * 10 + bp;
}

void printState(int lm, int lc, int rm, int rc, int bp) {
	cout << lm << ' ' << lc << ' ' << rm << ' ' << rc << ' ' << bp << '\n';
}

bool valid(int lm, int lc, int rm, int rc) {
	if (rc > rm) if (rm > 0) return false;
	if (lc > lm) if (lm > 0) return false;
	return true;
}

bool finala(int lm, int lc, int rm, int rc) {
	if (lm == 0 && lc == 0) return true;
	return false;
}

void done(int fm, int fc) {
	int numba;
	int lm = 0, lc = 0, rm = fm, rc = fc, bp = 2;
	while (lm < fm || lc < fc) {
		numba = previous[computeUsed(lm, lc, rm, rc, bp)];
		if (numba < 10000) cout << '0';
		cout << numba << '\n';
		lm = numba / 10000;
		lc = numba / 1000 % 10;
		rm = numba / 100 % 10;
		rc = numba / 10 % 10;
		bp = numba % 10;
	}
	cout << "succeS1\n";
}

void bt(int lm, int lc, int rm, int rc, int bs, int bp) {
	used[computeUsed(lm, lc, rm, rc, bp)] = 1;
	if (valid(rm, rc, lm, lc)) {
		//printState(lm,lc,rm,rc,bp);
		if (finala(lm, lc, rm, rc)) {
			done(rm, rc);
		}
		else {
			for (int i = 1; i <= bs; i++) {						// nr de oameni total de mutat
				for (int j = 0; j <= i; j++) {					// nr de misionari de mutat
					if (bp == 1) {								// daca barca e pe stanga
						if (lm - j >= 0 && lc - i + j >= 0)		// daca mai raman misionari dupa ce muta j si mai raman canibali dupa ce muta i - j
							if (!used[computeUsed(lm - j, lc - i + j, rm + j, rc + i - j, 2)]) {		// daca nu a mai fost starea noua
								previous[computeUsed(lm - j, lc - i + j, rm + j, rc + i - j, 2)] = computeUsed(lm, lc, rm, rc, 1);	// starea dinaintea starii noi e starea curenta
								bt(lm - j, lc - i + j, rm + j, rc + i - j, bs, 2);						// back pentru starea noua
							}
					}
					else {
						if (rm - j >= 0 && rc - i + j >= 0)
							if (!used[computeUsed(lm + j, lc + i - j, rm - j, rc - i + j, 1)]) {
								previous[computeUsed(lm + j, lc + i - j, rm - j, rc - i + j, 1)] = computeUsed(lm, lc, rm, rc, 2);
								bt(lm + j, lc + i - j, rm - j, rc - i + j, bs, 1);
							}
					}
				}

			}
		}
	}
}

int solve_bogdan(int lm, int lc, int bs) {
	bt(lm, lc, 0, 0, bs, 1);
	return 0;
}
