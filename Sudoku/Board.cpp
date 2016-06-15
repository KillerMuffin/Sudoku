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

//Removes pieces until a certain threshold has been reached, or there is more than one solution
void Board::findSingleSolution(int max_remove){
	//Shuffle pieces
	random_shuffle(pieces.begin(), pieces.end());

	//Number removed
	int removed = 0;

	while(removed <= max_remove){
		//Store first so changes can be reverted
		Piece temp = pieces[0];
		//Erase at start of vector
		pieces.erase(pieces.begin(), pieces.begin() + 1);
		removed++;

		//Check number of solutions
		pair<DumbBoard, int> solution = solve(clone());
		//If more than one solution, undo last and end
		if(solution.second > 1){
			pieces.push_back(temp);
			return;
		}
	}
}

//Solves the board
pair<DumbBoard, int> Board::solve(DumbBoard db){
	//If the board is complete, return the board
	if(db.complete()){
		return pair<DumbBoard, int>(db, 1);
	}

	//Find the next blank piece
	Position p = db.findBlank();
	//This theoretically should never happen, but is here just in case
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