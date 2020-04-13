#pragma once

#ifndef SETUP
#define SETUP

#include<bits/stdc++.h>

using namespace std;


class Battery
{

private:
	int x,y;
	int charge;
	int boardID;
	int inputID;

public:
	Battery(){}
	Battery(int a, int b, int c)
	{
		x = a;
		y = b;
		charge = c;
	}
	~Battery(void){}

	bool operator< (const Battery& b) const
	{
		if (x == b.x)
			return y < b.y;
		else
			return x < b.x;
	}

	void setCoordinates (int a, int b) {x = a; y = b;}
	void setX (int a) {x = a;}
	void setY (int b) {y = b;}
	void setCharge (int c) {charge = c;}
	void setBoardID (int val) {boardID = val;}
	void setInputID (int val) {inputID = val;}
	int getX () {return x;}
	int getY () {return y;}
	int getCharge() {return charge;}
	int getBoardID () {return boardID;}
	int getInputID () {return inputID;}
	pair<int,int> getCoordinates() {return make_pair(x,y);};

};


#endif