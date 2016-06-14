#include "stdafx.h"
#include "Board.h"

using namespace std;

Board::Board(int size, double difficulty) : DumbBoard(size){
	srand(time(NULL));
	this->size = size;
	this->difficulty = difficulty;
	generateBoard();
}

bool Board::canPut(int x, int y, int value){
	for(int y = 0; y < size; y++){
		if(getVAt(x, y) == value){
			return false;
		}
	}
	for(int x = 0; x < size; x++){
		if(getVAt(x, y) == value){
			return false;
		}
	}
	return true;
}

void Board::print(){
	printLine((size + 1) * 4);
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			Piece * p = getAt(x,y);
			if(p == nullptr){
				printCell(' ');
			}else{
				printCell((char)(48+p->value));
			}
		}
		printCell((char)(48+x+1));
		cout << endl;
		printLine((size + 1) * 4);
	}
	for(int i = 0; i < size; i++){
		printCell((char)(65+i));
	}
	cout << " |" << endl;
}
void Board::printLine(int size){
	for(int i = 0; i < size; i++){
		cout << '-';
	}
	cout << endl;
}
void Board::printCell(char c){
	cout << " | " << c;
}

void Board::generateBoard(){
	vector<int> nums;
	for(int i = 1; i <= size; i++){
		nums.push_back(i);
	}
	random_shuffle(nums.begin(), nums.end());

	int pos = 0;
	for(int y = 0; y < size/3; y++){
		for(int x = 0; x < size/3; x++){
			if(x == 2 && y == 2){
				continue;
			}
			for(int yg = 0; yg < size/3; yg++){
				for(int xg = 0; xg < size/3; xg++){
					setAt((x*3)+xg, (y*3)+yg, nums[pos], true);
					pos++;
					if(pos > 8){pos = 0;}
				}
			}
			pos+=3;
			if(pos > 8){pos-=8;}
		}
		pos+=1;
		if(pos > 8){pos = 0;}
	}
	random_shuffle(pieces.begin(), pieces.end());
	pieces.erase(pieces.begin(), pieces.begin() + (pieces.size() * difficulty));
}
void Board::genChunk(int offset_x, int offset_y, map<int, vector<int>> * posx, map<int, vector<int>> * posy){
	bool failed = true;
	vector<Piece> local_pieces;
	while(failed){
		failed = false;
		vector<int> nums;

		for(int i = 1; i <= size; i++){
			nums.push_back(i);
		}

		random_shuffle(nums.begin(), nums.end());

		for(int x = 0; x < 3; x++){
			for(int y = 0; y < 3; y++){
				bool run = true;
				int pos = 0;
				int count = 0;
				while(run){
					if(canPut((offset_x * 3) + x, (offset_y * 3) + y, nums[pos])){
						run = false;
						//For some strange reason the program throws an vector subscript error unless I add 10 here???
						local_pieces.push_back(Piece((offset_x * 3) + x, (offset_y * 3) + y, nums[pos]));
						nums.erase(nums.begin() + pos);
					}else{
						pos++;
						if(pos >= nums.size()){
							pos = 0;
						}
						count++;
						if(count > nums.size()+5){
							run = false;
							x = 100;
							y = 100;
							failed = true;
							local_pieces.empty();
						}
					}
				}
			}
		}
	}
	pieces.insert(pieces.end(), local_pieces.begin(), local_pieces.end());
}
map<int, vector<int>> Board::populateVector(){
	map<int, vector<int>> r;
	for(int i = 0; i < size; i++){
		vector<int> v;
		for(int j = 0; j < size; j++){
			v.push_back(j);
		}
		r.insert(pair<int, vector<int>>(i, v));
	}

	return r;
}

bool Board::solve(DumbBoard db){
	if(db.complete()){
		return true;
	}else{

	}
}