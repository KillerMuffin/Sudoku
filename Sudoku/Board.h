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
	void findSingleSolution(int max_remove);

	void genChunk(int offset_x, int offset_y);

	pair<DumbBoard, int> solve(DumbBoard b);

	map<int, vector<int>> populateVector();
};