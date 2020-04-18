#pragma once

#ifndef SETUP
#define SETUP

#include<bits/stdc++.h>

using namespace std;

class Battery
{

private:
	//die x-- und y--Koordinaten
	int x,y;
	//die Ladung
	int charge;
	//der Brettindex
	int boardID;
	//der Eingabeindex
	int inputID;

public:
	Battery(){} //Konstruktor ohne Eingabe
	Battery(int a, int b, int c) //Konstruktor mit Eingabe
	{
		x = a;
		y = b;
		charge = c;
	}
	~Battery(void){} //Destruktor

	//um Sortieren zu ermoeglichen
	bool operator< (const Battery& b) const
	{
		if (x == b.x)
			return y < b.y;
		else
			return x < b.x;
	}

	//setzt die Koordinaten
	void setCoordinates (int a, int b) {x = a; y = b;}
	//setzt die x--Koordinate
	void setX (int a) {x = a;}
	//setzt die y--Koordinate
	void setY (int b) {y = b;}
	//setzt die Ladung
	void setCharge (int c) {charge = c;}
	//setzt den Brettindex
	void setBoardID (int val) {boardID = val;}
	//setzt den Eingabeindex
	void setInputID (int val) {inputID = val;}
	//gibt die x--Koordinate aus
	int getX () {return x;}
	//gibt die y--Koordinate aus
	int getY () {return y;}
	//gibt die Ladung aus
	int getCharge() {return charge;}
	//gibt den Brettindex aus
	int getBoardID () {return boardID;}
	//gibt den Eingabeindex aus
	int getInputID () {return inputID;}
	//gibt die Koordinaten aus
	pair<int,int> getCoordinates() {return make_pair(x,y);};

};


#endif