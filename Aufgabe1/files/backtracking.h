#pragma once

#ifndef BACKTRACKING
#define BACKTRACKING

#include<bits/stdc++.h>

#define pb push_back
#define iPair pair<int,int>
#define mp make_pair

using namespace std;
using namespace chrono;

class Backtracking
{
private:

	//die Startbatterie s
	Battery start;

	//Map-Containers fur Zuordnung der IDs mit Objekten von Battery
	//hilft bei der Bestimmung von Koordinaten jeweiliger Batterie
	map<int, Battery> IDToBattery;
	map<Battery, int> batteryToID;

	//die Matrix A aus der Beschreibung
	//beinhaltet die minimalen Entfernungen zwischwn zwei Batterien
	vector<vector<int>> dist;

	//die Matrix A' aus der Beschreibung
	//beinhaltet die Entfernungen zwischen zwei Batterien,
	//wenn die entsprechende Entfernung in dist kleiner ist als 3
	vector<vector<int>> distAux;

	//das Array T aus der Beschreibung
	//beinhaltet die Anzahl der batteriefreien Felder
	//neben einer Batterie
	vector<int> extraTiles;
	
	//ein array fuer die Ausgabe, wenn ein Pfad gefunden wird
	vector<iPair> foundPath;

	//eine Funktion,
	//die alle benoetigten Arrays aus einem Graphen abruft
	void retrieveAll(Graph &graph)
	{
		IDToBattery = graph.retrieveIDToBattery();
		batteryToID = graph.retrieveBatteryToID();
		start = graph.retrieveStart();
		dist = graph.retrieveDistances();
		distAux = graph.retrieveDistancesAux();
		extraTiles = graph.retrieveExtraTiles();		
	}

	//die rekursive Funktion, die alle Moeglichkeiten untersucht
	bool next(int id, int charge, vector<int> &status, vector<iPair> &result);

	//eine Funktion, die die Erreichbarkeit von Batterien
	//von einer Batterie id aus ueberprueft
	vector<pair<int,int>> checkReachability (int id, int charge, vector<int> &currCharges);

public:
	Backtracking(Graph &graph)
	{
		//die benoetigten Arrays werden aus dem Graphen abgerufen
		retrieveAll(graph);

		//das Array mit den Ladungen jeder Batterie; in der Beschreibung - Array C
		vector<int> startStatus;
		map<int, Battery>::iterator it = IDToBattery.begin();
		for (; it != IDToBattery.end(); it++)
			startStatus.pb(it->second.getCharge());

		//die erste aktuelle Ladung
		int startCharge = startStatus[start.getInputID()];
		startStatus[start.getInputID()] = 0;

		//das Array mit dem Pfad vom Ursprung; in der Beschreibung - Array R
		vector<iPair> results;
		//das erste Element, also die Startbatterie, wird eingefuegt
		results.pb(mp(0,0));

		//die Zeit wird gemessen
		steady_clock::time_point begin = steady_clock::now();
		//Lauf der rekursiven Funktion
		bool found = next(start.getInputID(), startCharge, startStatus, results);
		steady_clock::time_point end = steady_clock::now();

		//wenn ein Pfad gefunden wird
		if (found)
		{
			cout<<"\nDer gefundene Pfad:\n0 ";

			for (auto x: foundPath)
			{
				//Format: x (y)
				// x - Eingabeindex einer Batterie
				// y - gemachte Schritten, um Batterie x zu erreichen
				if (x.first != 0)
					printf("→  %d(%d) ", x.first, x.second);
			}
		}
		else
			cout<<"\nxxxxxxxxxxxxxxxxxxxx\nKein Pfad wurde gefunden.";
		
		//das Format der Zeit wird angepasst
		auto ms = duration_cast<milliseconds>(end - begin);
		auto secs = duration_cast<seconds>(ms);
    	ms -= duration_cast<milliseconds>(secs);
    	auto mins = duration_cast<minutes>(secs);
    	secs -= duration_cast<seconds>(mins);

    	//Ausgabe der Zeit
    	printf("\nZeit: %ld min %ld s\n", mins.count(), secs.count());
	}
	~Backtracking(void){}//Destruktor
};



#endif