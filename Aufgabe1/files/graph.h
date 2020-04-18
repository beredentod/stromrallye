#pragma once

#ifndef GRAPH
#define GRAPH

#include<bits/stdc++.h>

#define pb push_back
#define iPair pair<int,int>
#define mp make_pair

using namespace std;

class Graph
{
private:

	//die Laenge/Breite der Matrix
	//Seiten Leange l in der Beschreibung
	int boardDimension;
	//die Matrix M
	vector<vector<int>> board;

	//die Anzahl von Batterien
	int numBat;
	//alle Batterien
	set<Battery> batteries;
	//die Startbatterie
	Battery start;

	//die Variable, die schraege Uebergaenge erlaubt
	bool slant;

	//alle Knoten (alle Felder in der Matrix)
	//Format pair<id, Ladung>
	vector<vector<iPair>> nodes;

	//die minimalen Entfernungen zwischen zwei Batterien
	vector<vector<int>> distances;
	//die minimalen Entfernungen (mindestens 3), wenn dist[i][j] < 3
	vector<vector<int>> distancesAux;
	//das Array mit batterienfreien Feldern
	vector<int> extraTiles; 

	//Map-Cotainer: Batterie -> Brettindex
	map<Battery, int> batteryToBoardID;
	//Map-Cotainer: Brettindex -> Batterie
	map<int, Battery> boardIDToBattery;

	//Map-Cotainer: Batterie -> Eingabeindex
	map<Battery, int> batteryToInputID;
	//Map-Cotainer: Eingabeindex -> Batterie
	map<int, Battery> inputIDToBattery;

	//die Methode, die die Textdatei einliest
	void readFile (string $FILENAME);

	//eine Methode, die die Texteingabe in eine Batterie umwandelt
	//Eingabeformat: "x,y,ladung"
	Battery convertInput(string data);


	//die Methode in der jedem Knoen seine Nachbarn
	//zugeordnet werden
	void determineConnections();

	//die Methode, die den Breitensuche-Algorithmus aus einer
	//Batterie laufen laesst
	void BFS(Battery b);

	//eine Methode, die ueberprueft, ob es neben Batterie b
	//ein batteriefreies Feld gibt
	bool checkOneTile(Battery b);

	//eine Methode, die ueberprueft, ob es neben Batterie b
	//zwei batteriefreie Felder gibt (zwei in Tiefe)
	bool checkTwoTiles(Battery b);

	//Vorbereitung der Arrays
	void preprocess()
	{
		//die Kanten zwischen Knoten werden bestimmt
		determineConnections();
		
		for (auto x: batteries)
		{
			//an jeder Batterie laesst man BFS laufen
			BFS(x);

			//die batteriefreien Feldern neben jeder Batterie
			//werden bestimmt
			if (checkOneTile(x))
				extraTiles[x.getInputID()] = 1;
			if (checkTwoTiles(x))
				extraTiles[x.getInputID()] = 2;
		}		
	}

public:
	//Konstruktor
	// filename - der Name der Textdatei
	// s - die Option der schraegen Uebergaenge
	Graph(string filename, bool s = false): slant(s)
	{
		//die Textdatei wird eingelesen
		readFile(filename);

		//alle benoetigten Arrays werden vorbereitet
		preprocess();
	}
	~Graph(void){} //Destruktor

	//diese Arrays werden in der Klasse Backtracking abgerufen
	Battery 			retrieveStart()			{return start;}
	vector<vector<int>> retrieveDistances() 	{return distances;}
	vector<vector<int>> retrieveDistancesAux() 	{return distancesAux;}
	vector<int>			retrieveExtraTiles()	{return extraTiles;}
	map<Battery, int>	retrieveBatteryToID() 	{return batteryToInputID;}
	map<int, Battery>	retrieveIDToBattery() 	{return inputIDToBattery;}
};

#endif 