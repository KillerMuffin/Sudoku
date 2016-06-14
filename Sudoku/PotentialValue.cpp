#include "stdafx.h"
#include "Position.h"
#include <vector>

class PotentialValue : public Position{
public:
	vector<int> pv;
	
	PotentialValue(int x, int y, vector<int> pv) : Position(x,y){
		this->pv = pv;
	}
	PotentialValue(int x, int y) : Position(x,y){
		for(int i = 0; i < 9; i++){
			pv.push_back(i);
		}
	}

	void remove(int v){
		for(int i = 0; i < pv.size(); i++){
			if(pv[i] == v){
				pv.erase(pv.begin() + i );
				return;
			}
		}
	}

	int count(){
		return pv.size();
	}

	bool possible(int v){
		for(int i = 0; i < pv.size(); i++){
			if(pv[i] == v){
				return true;
			}
		}
		return false;
	}
};