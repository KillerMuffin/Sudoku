#include "stdafx.h"
#include "Board.h"

using namespace std;

Board::Board(int size, double difficulty) : DumbBoard(size){
	//Seed random for use in generateBoard later
	srand(time(NULL));
	this->size = size;
	this->difficulty = difficulty;

	seed();
	pair<DumbBoard, int> so = solve(clone());
	pieces = so.first.pieces;

	removeRandom(difficulty);
	for(int i = 0; i < pieces.size(); i++){
		pieces[i].locked = true;
	}
}

//Check if a value can be put in a square (only checks rows and cols)
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

//Prints the board
void Board::print(){
	//Print the first line, in green
	printLine((size + 1) * 4, 10);
	//Loop through the entire grid
	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			//Get the piece at "x" and "y"
			Piece * p = getAt(x,y);
			if(p == nullptr){
				//If the piece does not exist, print an empty cell.
				//If it is a third line, color green
				printCell(' ', (y%3 == 0) ? 10 : 15, 15);
			}else{
				//If the piece does exist, print the number
				//If it is a third line, color green
				//If the piece is locked (i.e. cannot be replaced), make magenta
				printCell((char)(48+p->value), (y%3 == 0) ? 10 : 15, (p->locked) ? 13 : 15);
			}
		}
		//Print the index number
		printCell((char)(48+x+1), 10, 11);
		cout << endl;
		//Print the line. If it is the third line, color green
		printLine((size + 1) * 4, ((x + 1)%3 == 0) ? 10 : 15);
	}
	//Print the index letters
	for(int i = 0; i < size; i++){
		printCell((char)(65+i), (i%3 == 0) ? 10 : 15, 11);
	}
	//Print the last line
	Utils::changeColor(10);
	cout << " |" << endl;
	Utils::changeColor(15);
}
//Print a line of size <size> and color <color>
void Board::printLine(int size, int color){
	Utils::changeColor(color);
	for(int i = 0; i < size; i++){
		cout << '-';
	}
	cout << endl;
	Utils::changeColor(15);
}
//Print a cell ( | c )
void Board::printCell(char c, int line, int cc){
	Utils::changeColor(line);
	cout << " | ";
	Utils::changeColor(cc);
	cout << c;
	//Reset color
	Utils::changeColor(15);
}

//Generate a board
void Board::seed(){
	vector<int> nums;
	for(int i = 1; i <= 9; i++){
		nums.push_back(i);
	}
	random_shuffle(nums.begin(), nums.end());

	int index = 0;
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			setAt(x,y,nums[index++],false);
		}
	}
}
void Board::removeRandom(double percent){
	//Shuffle and remove some percentage of the pieces
	random_shuffle(pieces.begin(), pieces.end());
	pieces.erase(pieces.begin(), pieces.begin() + (pieces.size() * percent));
}

//Solves the board
pair<DumbBoard, int> Board::solve(DumbBoard db){
	//Find the next blank piece
	Position p = db.findBlank();
	if(p.x == -1 && p.y == -1){
		return pair<DumbBoard, int>(db, 1);
	}

	for(int i = 1; i <= 9; i++){
		if(db.legalPut(p.x, p.y, i)){
			db.setAt(p.x, p.y, i, false);

			pair<DumbBoard, int> ret = solve(db);
			if(ret.second > 0){
				return ret;
			}

			db.removeAt(p.x, p.y);
		}
	}

	return pair<DumbBoard, int>(db, 0);
}