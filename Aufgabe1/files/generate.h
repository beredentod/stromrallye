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
	int batNum; //number of batteries
	string savePath = "stromrallye.txt";

	random_device rd;

	int boardDimension;
	Battery start;
	set<Battery> batteries; //not including start!
	
	vector<int> generateOrder();
	pair<vector<int>, vector<iPair>> generateDistances(vector<int> &v);
	vector<int> generateCharges(vector<int> &v, vector<int> &dist);
	//vector<iPair> setCoordinates(vector<int> &v, vector<int> &dist);

	void prepareOutput(vector<int> &ch, vector<iPair> &coor);

public:
	Generator(int num): batNum(num)
	{
		if (num < 1)
			throw runtime_error("Die Anzahl der Batterien muss mindestens 1 sein.\n");

		vector<int> order = generateOrder();

		vector<iPair> coordinates;
		vector<int> distances;

		auto res = generateDistances(order);
		distances = res.first;
		coordinates = res.second;

		vector<int> charges = generateCharges(order, distances);

		prepareOutput(charges, coordinates);
	}
	~Generator(void){}

	void save() {save(savePath);}
	void save(string path);

};


#endif