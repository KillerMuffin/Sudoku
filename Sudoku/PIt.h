#include "stdafx.h"

using namespace std;

class PatternIterator{
public:
	int index;
	int nc;
	int nr;

	PatternIterator(int nc, int nr);

	virtual int nextCell();
	virtual int nextRow();
};