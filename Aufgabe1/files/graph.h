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

	int boardDimension;
	vector<vector<int>> board;

	int numBat;
	set<Battery> batteries;
	Battery start;

	vector<vector<iPair>> nodes;

	vector<vector<int>> distances;
	vector<vector<int>> distancesAux;

	vector<int> extraTiles; 

	map<Battery, int> batteryToBoardID;
	map<int, Battery> boardIDToBattery;

	map<Battery, int> batteryToInputID;
	map<int, Battery> inputIDToBattery;

	void readFile (string $FILENAME);
	Battery convertInput(string data);

	void determineConnections();
	void BFS(Battery b);
	bool checkOneTile(Battery b);
	bool checkTwoTiles(Battery b);

	void preprocess()
	{
		determineConnections();
		
		for (auto x: batteries)
		{
			BFS(x);

			if (checkOneTile(x))
				extraTiles[x.getInputID()] = 1;
			if (checkTwoTiles(x))
				extraTiles[x.getInputID()] = 2;
		}		
	}

public:
	Graph(string filename)
	{
		readFile(filename);
		preprocess();
	}
	~Graph(void){}

	Battery 			retrieveStart()			{return start;}
	vector<vector<int>> retrieveDistances() 	{return distances;}
	vector<vector<int>> retrieveDistancesAux() 	{return distancesAux;}
	vector<int>			retrieveExtraTiles()	{return extraTiles;}
	map<Battery, int>	retrieveBatteryToID() 	{return batteryToInputID;}
	map<int, Battery>	retrieveIDToBattery() 	{return inputIDToBattery;}
};

#endif 