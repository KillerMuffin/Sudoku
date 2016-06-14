// Sudoku.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include "Position.h"
#include "Utils.cpp"
#include "Highscore.cpp"

class Sudoku{
public:
	Sudoku(double difficulty){
		Board b = Board(9, difficulty);

		int start = time(NULL);
		int count = 0;

		while(!b.complete()){
			count++;
			b.print();
			cout << "Select a position: " << endl;
			string p;
			cin >> p;

			Position pos = parsePosition(p);

			cout << "Input a value:" << endl;
			int v;
			cin >> v;

			if(v < 1 || v > 9){
				Utils::cls();
				cout << "Invalid input!" << endl;
				Utils::clp();
			}

			if(!b.setAt(pos.x, pos.y, v, false)){
				Utils::cls();
				cout << "Failed to put piece there!" << endl;
				Utils::clp();
			}

			Utils::cls();
		}

		int end = time(NULL);
		int score = ((start - end) / 60) + count;

		cout << "Congratulations! You won!" << endl;
		cout << "Score: " << score << endl;

		cout << "Enter a name:" << endl;
		string name;
		cin >> name;

		Highscores hs = Highscores("scores.fml");
		hs.put(name, score);

		cout << "Score saved!" << endl;
		Utils::pau();
	}

	Position parsePosition(string s){
		if(Utils::isLetter(s[0])){
			int x = Utils::toLower(s[0]) - 97;
			int y = stoi(s.substr(1)) - 1;

			return Position(y,x);
		}else{
			int x = Utils::toLower(s[s.size() - 1]) - 97;
			int y = stoi(s.substr(0, s.size()-1)) - 1;

			return Position(y,x);
		}
	}
};

void showHighscore(){
	Highscores hs = Highscores("scores.fml");
	vector<Highscore> h = hs.get(0, 5);
	
	Utils::cls();

	cout << "Highscores:" << endl;
	if(h.size() > 0){
		for(int i = 0; i < h.size(); i++){
			cout << h[i].name << ": " << to_string(h[i].score) << endl;
		}
	}else{
		cout << "You have no highscores!" << endl;
	}
	
	Utils::pau();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream intro ("intro.txt");
	if(intro.is_open()){
		string line;
		while(getline(intro, line)){
			cout << line << endl;
		}
		intro.close();
	}else{
		cout << "Failed to open file. Continuing anyway..." << endl;
	}
	Utils::clp();

	cout << "Select difficulty:" << endl;
	cout << "[0] High Scores" << endl;
	cout << "[1] Easy" << endl;
	cout << "[2] Medium" << endl;
	cout << "[3] Hard" << endl;
	string in = "";
	cin >> in;

	if(in == "0"){
		showHighscore();
	}else if(in == "1"){
		Utils::cls();
		Sudoku(0.5);
	}else if(in == "2"){
		Utils::cls();
		Sudoku(0.75);
	}else{
		Utils::cls();
		Sudoku(0.9);
	}

	return 0;
}