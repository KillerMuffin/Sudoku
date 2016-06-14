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
		Piece n = Piece(x, y, value);
		n.locked = locked;
		pieces.push_back(n);
	}else{
		if(!p->locked){
			p->value = value;
		}else{
			return false;
		}
	}
	return true;
}

PotentialValue DumbBoard::findMostConstrained(){
	vector<PotentialValue> uv = tallyConstrained();
	int in = -1, hv = -1;
	for(int i = 0; i < uv.size(); i++){
		if(uv[i].count() > hv){
			hv = uv[i].count();
			in = i;
		}
	}
	return uv[in];
}
vector<PotentialValue> DumbBoard::tallyConstrained(){
	vector<PotentialValue> uv;
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			uv.push_back(potentialValuesForXY(x,y));
		}
	}

	return uv;
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

PotentialValue DumbBoard::potentialValuesForXY(int x, int y){
	PotentialValue pv = PotentialValue(x,y);
	for(int y = 0; y < size; y++){
		Piece * p = getAt(x,y);
		if(p != nullptr){
			pv.remove(p->value);
		}
	}

	for(int x = 0; x < size; x++){
		Piece * p = getAt(x,y);
		if(p != nullptr){
			pv.remove(p->value);
		}
	}

	int gx = floorf(x/3) * 3;
	int gy = floorf(y/3) * 3;

	for(int x = gx; x < gx+3; x++){
		for(int y = gy; y < gy+3; y++){
			Piece * p = getAt(x,y);
			if(p != nullptr){
				pv.remove(p->value);
			}
		}
	}

	return pv;
}

bool DumbBoard::rowComplete(int y){
	vector<int> nums;
	for(int i = 0; i < size; i++){
		nums.push_back(i);
	}

	for(int x = 0; x < size; x++){
		Piece * p = getAt(x, y);
		if(p == nullptr){return false;}
		nums.erase(find(nums.begin(), nums.end(), p->value));
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
		nums.erase(find(nums.begin(), nums.end(), p->value));
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
			nums.erase(find(nums.begin(), nums.end(), p->value));
		}
	}

	return (nums.size() < 1);
}

DumbBoard DumbBoard::clone(){
	DumbBoard ret = DumbBoard(size);
	for(int i = 0; i < pieces.size(); i++){
		ret.pieces.push_back(pieces[i]);
	}

	return ret;
}