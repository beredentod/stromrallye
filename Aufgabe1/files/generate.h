#pragma once

#ifndef GENERATE
#define GENERATE

#include <bits/stdc++.h>
#include <random>
#include "setup.h"

#define pb push_back
#define iPair pair<int,int>
#define mp make_pair

using namespace std;

class Generator
{
private:
	//die Anzahl der Batterien auuser der Startbatterie
	int batNum;
	//der Name der Datei, unter der die Textdatei gespeichert wird,
	//wenn kein anderer Name eingegeben wird
	string savePath = "stromrallye1000.txt";

	//der Generator von Zufallszahlen
	random_device rd;

	//die Laenge/Breite der Matrix
	int boardDimension;
	//die Startbatterie
	Battery start;
	//die Menge mit allen Batterien ausser der Startbatterie
	set<Battery> batteries;
	
	//die Methode, die eine Reihenfolge generiert, in der die Spielsituation
	//geloest wird
	vector<int> generateOrder();

	//die Methode, die Entfernungen zwischen Eingabeindizes in der
	//Reihenfolge v generiert
	//Dazu werden auch Koordinaten von Batterien generiert
	pair<vector<int>, vector<iPair>> generateDistances(vector<int> &v);

	//die Methode, die Ladungen fuer Batterien generiert
	// v - ein Array mit einee Reihengolge
	// dist - ein Array mit Entfernungen zwischen den  
	vector<int> generateCharges(vector<int> &v, vector<int> &dist);

	//die Arrays werden auf die Ausgabe vobereitet
	// ch - ein Array mit Ladungen
	// coor - ein Array mit Kooridnaten
	void prepareOutput(vector<int> &ch, vector<iPair> &coor);

public:
	//Konstuktor
	// num - die Anzahl der zu generierenden Batterien
	Generator(int num): batNum(num) 
	{
		//falls der Benutzer 0 eingegeben hat
		if (num < 1)
			throw runtime_error("Die Anzahl der Batterien muss mindestens 1 sein.\n");

		//eine generierte Reihenfolge
		vector<int> order = generateOrder();

		//Arrays fuer die Koordinaten und Entfernungen
		vector<iPair> coordinates;
		vector<int> distances;

		//Koordinaten und Entfernungen werden generiert
		auto res = generateDistances(order);
		distances = res.first;
		coordinates = res.second;
		
		//ein Array mit generierten Ladungen
		vector<int> charges = generateCharges(order, distances);

		//die Arrays charges und coordinates werden auf die Ausgabe vorbereitet
		prepareOutput(charges, coordinates);
	}
	~Generator(void){} //Detruktor

	//die Methoden, die die generierten Informationen in einer
	//Textdatei spiechern
	void save() {save(savePath);}
	void save(string path);
};


#endif