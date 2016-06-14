#include "stdafx.h"
#include "PIt.h"

PatternIterator::PatternIterator(int nc, int nr){
	this->nc = nc;
	this->nr = nr;

	index = 0;
}
int PatternIterator::nextCell(){
	return (index+=nc) % 9;
}
int PatternIterator::nextRow(){
	return (index+=nr) % 9;
}