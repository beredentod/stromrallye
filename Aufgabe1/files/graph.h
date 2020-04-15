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

		/*for (int i = 1; i <= board.size(); i++)
		{
			for (int j=1; j < board[i].size();j++)
				cout<<board[i][j]<<" ";
			cout<<"\n";
		}*/

		/*for (auto x: batteries)
		{
			vector<int> v = checkReachability(x);
			reachable[x.getInputID()].swap(v);
		}*/

		/*for (int i=0;i<reachable.size();i++)
		{
			cout<<i<<":\t";
			for (auto x: reachable[i])
				cout<<x<<" ";
			cout<<"\n";
		}
		cout<<"\n\n";*/

		/*cout<<"\t";
		for (int j=0;j<batteries.size();j++)
			cout<<j<<" ";
		cout<<"\n";

		for (int i=0;i<distances.size();i++)
		{
			cout<<i<<":\t";
			for (int j=0;j<distances[i].size();j++)
			{
				cout <<distances[i][j]<<" ";
			}
			cout<<"\n";
		}*/
	}
	~Graph(void){}

	//vector<int> checkReachability(Battery b);

	Battery 			retrieveStart()			{return start;}
	vector<vector<int>> retrieveDistances() 	{return distances;}
	vector<vector<int>> retrieveDistancesAux() 	{return distancesAux;}
	vector<int>			retrieveExtraTiles()	{return extraTiles;}
	map<Battery, int>	retrieveBatteryToID() 	{return batteryToInputID;}
	map<int, Battery>	retrieveIDToBattery() 	{return inputIDToBattery;}
};

#endif 