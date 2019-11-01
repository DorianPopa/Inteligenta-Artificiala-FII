#include "State.h"


State::State(int lm, int lc, int rm, int rc, int bs, int bp)
{
	this->lm = lm;
	this->lc = lc;
	this->rm = rm;
	this->rc = rc;
	this->bs = bs;
	this->bp = bp;
}

int State::getBoatSize()
{
	return this->bs;
}

void State::printState()
{
	std::cout << "State: " << lm << ' ' << lc << ' ' << rm << ' ' << rc << ' ' << bp << '\n';
}

bool State::isValid()
{
	if (rc > rm) if (rm > 0) return false;
	if (lc > lm) if (lm > 0) return false;
	return true;
}

bool State::isFinal()
{
	if (lm == 0 && lc == 0) return true;
	return false;
}

State* State::Transition(int misToMove, int canToMove)
{
	if (this->bp == 1) {
		int misLeft = this->lm - misToMove;
		int canLeft = this->lc - canToMove;
		int misRight = this->rm + misToMove;
		int canRight = this->rc + canToMove;
		if (misLeft >= 0 && canLeft >= 0) {
			State* nextState = new State(misLeft, canLeft, misRight, canRight, this->bs, 2);
			return nextState;
		}
	}
	else if (this->bp == 2) {
		int misLeft = this->lm + misToMove;
		int canLeft = this->lc + canToMove;
		int misRight = this->rm - misToMove;
		int canRight = this->rc - canToMove;
		if (misRight >= 0 && canRight >= 0) {
			State* nextState = new State(misLeft, canLeft, misRight, canRight, this->bs, 1);
			return nextState;
		}
	}
	return nullptr;
}

bool State::operator ==(State& otherState)
{
	if (this->lm == otherState.lm && 
		this->lc == otherState.lc && 
		this->rm == otherState.rm && 
		this->rc == otherState.rc && 
		this->bp == otherState.bp
		)	
		return true;
	return false;
}

int State::getC() {
	return lm + lc;
}

int State::getBoatPosition()
{
	return this->bp;
}

int State::getMissionary(int boatPosition)
{
	if (bp == 1)
		return lm;
	else
		return rm;
}

int State::getCannibals(int boatPosition)
{
	if (bp == 1)
		return lc;
	else
		return rc;
}

