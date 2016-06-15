#include "stdafx.h"
#include "Board.h"

using namespace std;

Board::Board(int size, double difficulty) : DumbBoard(size){
	//Seed random for use in generateBoard later
	srand(time(NULL));
	this->size = size;
	this->difficulty = difficulty;

	seed();
	findSingleSolution((size * size) * difficulty);
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
	//Populate a vector with numbers 1 to 9
	vector<int> nums;
	for(int i = 1; i <= size; i++){
		nums.push_back(i);
	}
	//Shuffle the vector
	random_shuffle(nums.begin(), nums.end());

	PatternIterator pi = PatternIterator(1,4);
	switch(rand() % 4){
	case(0):
		pi = PatternIterator(1,1);
		break;
	case(1):
		pi = PatternIterator(4,1);
		break;
	case(2):
		pi = PatternIterator(2,2);
		break;
	}

	for(int x = 0; x < size; x++){
		for(int y = 0; y < size; y++){
			setAt(x,y,nums[pi.nextCell()],true);
		}
		pi.nextRow();
	}
}
void Board::removeRandom(double percent){
	//Shuffle and remove some percentage of the pieces
	random_shuffle(pieces.begin(), pieces.end());
	pieces.erase(pieces.begin(), pieces.begin() + (pieces.size() * percent));
}

void Board::findSingleSolution(int max_remove){
	random_shuffle(pieces.begin(), pieces.end());

	int removed = 0;
	int solve_amount = 0;

	while(solve_amount < 2 && removed <= max_remove){
		pieces.erase(pieces.begin(), pieces.begin() + 1);
		removed++;

		pair<DumbBoard, int> solution = solve(clone());
		if(solution.second > 1){
			return;
		}
	}
}

//Generate a chunk (3x3 grid) of the board
void Board::genChunk(int offset_x, int offset_y){
	vector<int> nums;
	for(int i = 1; i <= size; i++){
		nums.push_back(i);
	}

	random_shuffle(nums.begin(), nums.end());

	int index = 0;
	for(int x = (offset_x*3); x < (offset_x*3)+3; x++){
		for(int y = (offset_y*3); y < (offset_y*3)+3; y++){
			setAt(x,y,nums[index],true);
			index++;
		}
	}
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

pair<DumbBoard, int> Board::solve(DumbBoard db){
	if(db.complete()){
		return pair<DumbBoard, int>(db, 1);
	}else{
		for(int x = 0; x < size; x++){
			for(int y = 0; y < size; y++){
				for(int i = 1; i <= size; i++){
					if(db.legalPut(x,y,i)){
						db.setAt(x,y,i,true);

						pair<DumbBoard, bool> rdb = solve(db);
						if(rdb.second == true){
							return rdb;
						}

						db.removeAt(x,y);
					}
				}
			}
		}
	}

	return pair<DumbBoard, int>(db, 0);
}