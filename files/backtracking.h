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

	Battery start;

	map<int, Battery> IDToBattery;
	map<Battery, int> batteryToID;

	vector<vector<int>> dist;
	vector<vector<int>> distAux;
	vector<int> extraTiles;

	vector<int> startStatus;

	vector<iPair> results;
	vector<iPair> foundPath;

public:
	Backtracking(Graph &graph)
	{
		IDToBattery = graph.retrieveIDToBattery();
		batteryToID = graph.retrieveBatteryToID();
		start = graph.retrieveStart();
		dist = graph.retrieveDistances();
		distAux = graph.retrieveDistancesAux();
		extraTiles = graph.retrieveExtraTiles();

		map<int, Battery>::iterator it = IDToBattery.begin();
		for (; it != IDToBattery.end(); it++)
			startStatus.pb(it->second.getCharge());

		int startCharge = startStatus[start.getInputID()];
		startStatus[start.getInputID()] = 0;

		for (auto x: startStatus)
			cout<<x<<" ";
		cout<<"\n";
		results.pb(mp(0,0));
		bool found;

		steady_clock::time_point begin = steady_clock::now();
		found = next(start.getInputID(), startCharge, startStatus, results);
		steady_clock::time_point end = steady_clock::now();

		if (found)
		{
			cout<<"\nDer gefundene Pfad:\n";
			for (auto x: foundPath)
				printf("%d(%d) ", x.first, x.second);
			cout<<"\n";
		}
		else
		{
			cout<<"\nxxxxxxxxxxxxxxxxxxxx\nKein Pfad wurde gefunden.\n";
		}
		
		auto ms = duration_cast<milliseconds>(end - begin);
		auto secs = duration_cast<seconds>(ms);
    	ms -= duration_cast<milliseconds>(secs);
    	auto mins = duration_cast<minutes>(secs);
    	secs -= duration_cast<seconds>(mins);
    	printf("Zeit: %ld min %ld s\n", mins.count(), secs.count());
	}
	~Backtracking(void){}


	bool next(int id, int charge, vector<int>& status, vector<iPair>& result);
	vector<pair<int,int>> checkReachability (int id, int charge, vector<int>& currCharges);


};



#endif