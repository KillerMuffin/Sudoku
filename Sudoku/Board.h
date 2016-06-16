#pragma once
#include "stdafx.h"
#include "Utils.cpp"
#include "DumbBoard.h"
#include <string>
#include <vector>
#include "Piece.cpp"
#include "PIt.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <map>

using namespace std;

/**
	Board is the Controller in the Model-View-Controller relationship.
	It holds the majority of the business logic for the board, including
	generation and display.
**/

//An extension of DumbBoard that contains generation and business logic
class Board : public DumbBoard{
public:
	double difficulty;

	Board(int size, double difficulty);

	bool canPut(int x, int y, int value);

	void print();
private:
	void printLine(int size, int color);
	void printCell(char c, int line, int cc);

	void seed();
	void removeRandom(double percent);

	pair<DumbBoard, int> solve(DumbBoard b);
};