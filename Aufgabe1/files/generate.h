#pragma once

#ifndef GENERATE
#define GENERATE

#include <bits/stdc++.h>
#include "setup.h"

#define pb push_back
#define iPair pair<int,int>
#define mp make_pair

using namespace std;

class Generator
{
private:
	int batNum; //number of batteries
	string savePath = "stromrallye.txt";

	int boardDimension;
	Battery start;
	set<Battery> batteries; //not including start!
	
	vector<int> generateOrder();
	vector<int> generateDistances(vector<int> &v);
	vector<int> generateCharges(vector<int> &v, vector<int> &dist);
	vector<iPair> setCoordinates(vector<int> &v, vector<int> &dist);

	void prepareOutput(vector<int> &ch, vector<iPair> &coor);

public:
	Generator(int num): batNum(num)
	{
		srand (time(NULL));
		if (num < 1)
			throw runtime_error("Die Anzahl der Batterien muss mindestens 1 sein.\n");

		vector<int> order = generateOrder();
		for (auto x: order)
			cout<<x<<" ";
		cout<<"\n";
		vector<int> distances = generateDistances(order);
		for (auto x: distances)
			cout<<x<<" ";
		cout<<"\n";
		vector<int> charges = generateCharges(order, distances);
		for (auto x: charges)
			cout<<x<<" ";
		cout<<"\n";
		vector<iPair> coordinates = setCoordinates(order, distances);
		for (int i=0;i<coordinates.size();i++)
			printf("%d: (%d, %d)\n", i, coordinates[i].first, coordinates[i].second);

		prepareOutput(charges, coordinates);
	}
	~Generator(void){}

	void save() {save(savePath);}
	void save(string path);

};


#endif