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
	string outputName;
	string savePath = "./";

	Battery start;
	set<Battery> batteries;

	vector<int> order;
	vector<int> distances;
	vector<int> charges;

	vector<int> generateOrder();
	vector<int> generateDistances();

public:
	Generator(string filename, int num): batNum(num), outputName(filename)
	{
		srand (time(NULL));
		if (num < 1)
			throw runtime_error("Die Anzahl der Batterien muss mindestens 1 sein.\n");

		order = generateOrder();
	}
	~Generator(void){}

	void save() {save(savePath + outputName);}
	void save(string path);

};


#endif