#pragma once
#include "stdafx.h"
#include "DumbBoard.h"
#include <string>
#include <vector>
#include "Piece.cpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <map>

using namespace std;

class Board : public DumbBoard{
public:
	double difficulty;

	Board(int size, double difficulty);

	bool canPut(int x, int y, int value);

	void print();
private:
	void printLine(int size);
	void printCell(char c);

	void generateBoard();
	void genChunk(int offset_x, int offset_y, map<int, vector<int>> * posx, map<int, vector<int>> * posy);

	bool solve(DumbBoard b);

	map<int, vector<int>> populateVector();
};