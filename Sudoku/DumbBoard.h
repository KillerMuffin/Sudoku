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

class DumbBoard{
public:
	int size;
	vector<Piece> pieces;

	DumbBoard(int size);

	bool setAt(int x, int y, int value, bool locked);
	Piece * getAt(int x, int y);
	int getVAt(int x, int y);

	bool complete();
	PotentialValue findMostConstrained();
	vector<PotentialValue> tallyConstrained(); 

	DumbBoard clone();
private:
	PotentialValue potentialValuesForXY(int x, int y);

	bool rowComplete(int y);
	bool columnComplete(int x);
	bool gridComplete(int gx, int gy);
};