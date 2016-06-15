#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "Piece.cpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <map>
#include "Position.h"
#include "PotentialValue.cpp"

using namespace std;

/**
	DumbBoard handles the Model part of the Model-View-Controller relationship.
	It holds some basic business logic, but is primarily just for holding the
	values of the board.
**/

//A class for storing a board and its values
class DumbBoard{
public:
	int size;
	vector<Piece> pieces;

	//Initialize a board
	DumbBoard(int size);

	//Set position x, y to the value
	bool setAt(int x, int y, int value, bool locked);
	//Return the piece at x, y (nullptr if none)
	Piece * getAt(int x, int y);
	//Return the value at x, y (-1 if none)
	int getVAt(int x, int y);
	//Remove piece at x, y
	void removeAt(int x, int y);

	//Check if the board is complete
	bool complete();
	bool legalPut(int x, int y, int v);

	//Find a blank position
	Position findBlank();

	DumbBoard clone();
private:
	bool rowComplete(int y);
	bool columnComplete(int x);
	bool gridComplete(int gx, int gy);

	bool usedInRow(int y, int v);
	bool usedInColumn(int x, int v);
	bool usedInGrid(int x, int y, int v);
};