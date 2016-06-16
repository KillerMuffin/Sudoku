#include "stdafx.h"
#include "DumbBoard.h"

DumbBoard::DumbBoard(int size){
	this->size = size;
}

Piece * DumbBoard::getAt(int x, int y){
	for(int i = 0; i < pieces.size(); i++){
		if(pieces[i].x == x && pieces[i].y == y){
			return &pieces[i];
		}
	}
	return nullptr;
}

int DumbBoard::getVAt(int x, int y){
	Piece * p = getAt(x, y);
	return (p != nullptr) ? p->value : -1;
}

bool DumbBoard::setAt(int x, int y, int value, bool locked){
	Piece * p = getAt(x, y);
	if(p == nullptr){
		//Create piece
		Piece n = Piece(x, y, value);
		n.locked = locked;
		pieces.push_back(n);
		
		//Get reference to piece
		Piece * c = &(pieces[pieces.size()-1]);
		//Get left position if not at top left
		if(x != 0 && y != 0){
			Piece * l;
			if(x != 0){
				//If can move back one, get l from position x-1
				l = getAt(x-1,y);
			}else{
				//If cannot move back one, move up a row and get from right
				l = getAt(size-1,y-1);
			}
			//Link pieces
			if(l != nullptr){
				l->right = c;
				c->left = l;
			}
		}else{
			//If the position is at the top left, loop to right
			Piece * r = getAt(size - 1, size - 1);
			if(r != nullptr){
				r->right = c;
				c->left = r;
			}
		}
		//Get right position if not at bottom right
		if(x != size-1 && y != size-1){
			Piece * r;
			if(x != size-1){
				//If can move forward one, get l from position x+1
				r = getAt(x+1,y);
			}else{
				//If cannot move forward one, move down a row and get from left
				r = getAt(0,y+1);
			}
			//Link pieces
			if(r != nullptr){
				r->left = c;
				c->right = r;
			}
		}
	}else{
		if(!p->locked){
			p->value = value;
		}else{
			return false;
		}
	}
	return true;
}

void DumbBoard::removeAt(int x, int y){
	for(int i = 0; i < pieces.size(); i++){
		if(pieces[i].x == x && pieces[i].y == y){
			//Remove linked references
			pieces[i].left->right = nullptr;
			pieces[i].right->left == nullptr;
			//Erase from vector
			pieces.erase(pieces.begin() + i);
			return;
		}
	}
}

bool DumbBoard::complete(){
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			if(!rowComplete(y) || !columnComplete(x)){
				return false;
			}
		}
	}

	for(int x = 0; x < size/3; x++){
		for(int y = 0; y < size/3; y++){
			if(!gridComplete(x, y)){
				return false;
			}
		}
	}
	return true;
}

bool DumbBoard::rowComplete(int y){
	vector<int> nums;
	for(int i = 0; i < size; i++){
		nums.push_back(i);
	}

	for(int x = 0; x < size; x++){
		Piece * p = getAt(x, y);
		if(p == nullptr){return false;}
		if(find(nums.begin(), nums.end(), p->value) != nums.end()){
			nums.erase(find(nums.begin(), nums.end(), p->value));
		}
	}

	return (nums.size() < 1);
}
bool DumbBoard::columnComplete(int x){
	vector<int> nums;
	for(int i = 0; i < size; i++){
		nums.push_back(i);
	}

	for(int y = 0; y < size; y++){
		Piece * p = getAt(x, y);
		if(p == nullptr){return false;}
		if(find(nums.begin(), nums.end(), p->value) != nums.end()){
			nums.erase(find(nums.begin(), nums.end(), p->value));
		}
	}

	return (nums.size() < 1);
}
bool DumbBoard::gridComplete(int gx, int gy){
	vector<int> nums;
	for(int i = 0; i < size; i++){
		nums.push_back(i);
	}

	for(int x = 0; x < size/3; x++){
		for(int y = 0; y < size/3; y++){
			Piece * p = getAt((gx*3)+x, (gy*3)+y);
			if(p == nullptr){return false;}
			if(find(nums.begin(), nums.end(), p->value) != nums.end()){
				nums.erase(find(nums.begin(), nums.end(), p->value));
			}
		}
	}

	return (nums.size() < 1);
}

bool DumbBoard::legalPut(int x, int y, int v){
	return (!usedInColumn(y,v) && !usedInRow(x,v) && !usedInGrid(x,y,v));
}
bool DumbBoard::usedInColumn(int y, int v){
	for(int x = 0; x < size; x++){
		Piece * p = getAt(x, y);
		if((p != nullptr) && (p->value == v)){
			return true;
		}
	}

	return false;
}
bool DumbBoard::usedInRow(int x, int v){
	for(int y = 0; y < size; y++){
		Piece * p = getAt(x, y);
		if((p != nullptr) && (p->value == v)){
			return true;
		}
	}

	return false;
}
bool DumbBoard::usedInGrid(int x, int y, int v){
	int gx = floorf(x/3)*3;
	int gy = floorf(y/3)*3;

	for(int x = 0; x < size/3; x++){
		for(int y = 0; y < size/3; y++){
			Piece * p = getAt(gx+x, gy+y);
			if((p != nullptr) && (p->value == v)){
				return true;
			}
		}
	}

	return false;
}

Position DumbBoard::findBlank(){
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			if(getAt(x,y) == nullptr){
				return Position(x,y);
			}
		}
	}
	return Position(-1,-1);
}

DumbBoard DumbBoard::clone(){
	DumbBoard ret = DumbBoard(size);
	for(int i = 0; i < pieces.size(); i++){
		ret.pieces.push_back(pieces[i]);
	}

	return ret;
}