#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Utils.cpp"

using namespace std;

class Highscore{
public:
	int score;
	string name;

	Highscore(string name, int score){
		this->name = name;
		this->score = score;
	}
};

class Highscores{
public:
	string path;
	vector<string> unparsed;

	Highscores(string path){
		this->path = path;

		ifstream score (path);
		if(score.is_open()){
			string line;
			while(getline(score, line)){
				unparsed.push_back(line);
			}
			score.close();
		}
	}

	vector<Highscore> get(int start, int number){
		vector<Highscore> score;
		for(int i = start; i < start + number; i++){
			if(i >= unparsed.size()){return score;}
			score.push_back(strToHighscore(unparsed[i]));
		}
		return score;
	}

	void put(string name, int score){
		for(int i = 0; i < unparsed.size(); i++){
			Highscore hs = strToHighscore(unparsed[i]);
			if(hs.score <= score){
				unparsed.insert(unparsed.begin() + i, highscoreToStr(Highscore(name, score)));
			}
		}
	}

	void save(){
		ofstream oscore (path);
		for(int i = 0; i < unparsed.size(); i++){
			oscore << unparsed[i] << endl;
		}
		oscore.close();
	}
private:
	Highscore strToHighscore(const string str){
		vector<string> s = Utils::split(str, ',');
		return Highscore(s[0], stoi(s[1]));
	}

	string highscoreToStr(Highscore h){
		return h.name+","+ to_string(h.score);
	}
};