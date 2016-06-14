#pragma once
#include "stdafx.h"

class Piece{
public:
	int x;
	int y;
	int value;
	bool locked;

	Piece * left;
	Piece * right;

	Piece(int x, int y, int value){
		this->x = x;
		this->y = y;
		this->value = value;
	}
	Piece(){}
};