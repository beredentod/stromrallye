#include <bits/stdc++.h>
#include "setup.h"
#include "graph.h"
#include "backtracking.h"

bool Backtracking::next (int id, int charge, vector<int>& status, vector<iPair> &result)
{
	/*printf("\n---------------------\nCurrent battery: %d -> %d\n", id, charge);
	cout<<"Current charges:\n";
	for (auto x: status)
		cout<<x<<" ";
	cout<<"\nCurrent path: ";
	for (auto x: result)
		printf("%d(%d) ", x.first, x.second);
	cout<<"\n\n";*/
	
	vector<pair<int,int>> neighbors = checkReachability(id, charge, status);

	if (neighbors.empty())
	{
		//cout<<"No neighbors\nxxxxxxxxxxxx\n";
		if (extraTiles[id] > 0)
		{
			//cout<<"Using the remaining tiles from "<<id<<"\n";
			result.pb(mp(-1, charge));
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			if (all) 
			{
				/*cout<<"All\n";
				for (auto x: result)
					printf("%d(%d) ", x.first, x.second);
				cout<<"\n";*/

				foundPath = result;

				return 1;
			}

			return 0;
		}
		//cout<<"\n";

		return 0;
	}

	//cout<<"Neighbors:\n";
	for (auto x: neighbors)
	{
		int neighID = x.first;

		vector<int> neighDistances;
		neighDistances.pb(x.second);

		//cout<<id<<" -> "<<neighID<<" ("<<neighDistances[0];

		//TODO: nie zapomniec o distAux!
		int nextDist = neighDistances[0] + 2;
		int i = 1;
		while (charge >= nextDist)
		{
			neighDistances.pb(nextDist);

			//cout<<", ";
			//cout<<neighDistances[i];

			nextDist+=2;
			i++;
		}
		//cout<<")\n";
	}
	//cout<<"\n";

	for (auto x: neighbors)
	{
		int neighID = x.first;

		vector<int> neighDistances;
		neighDistances.pb(x.second);

		//TODO: nie zapomniec o distAux!
		int nextDist = neighDistances[0] + 2;
		int i = 1;
		while (charge >= nextDist)
		{
			neighDistances.pb(nextDist);
			nextDist+=2;
		}
		
		for (auto y: neighDistances)
		{
			//printf("Current battery: %d -> %d\n", id, charge);
			//cout<<"Going from "<<id<<" to "<<neighID<<" with distance "<<y<<"\n"; 
			int nextCharge = status[neighID];
			
			vector<int> cpstatus = status;
			vector<iPair> cpresult = result;

			cpstatus[neighID] = charge - y;
			cpresult.pb(mp(neighID, y));

			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			if (all) 
			{
				/*cout<<id<<": ";
				cout<<"All\n";
				for (auto v: cpresult)
					printf("%d(%d) ", v.first, v.second);
				cout<<"\n";*/

				foundPath = cpresult;
				return 1;
			}
			//if (id == 0)

			bool found = next(neighID, nextCharge, cpstatus, cpresult);
			if (found)
			{
				return 1;
			}
			else
			{
				cpresult.pop_back();
			}
		}
		
	}

	return 0;
}

vector<pair<int,int>> Backtracking::checkReachability (int ID, int charge, vector<int>& currCharges)
{
	vector<pair<int,int>> reach;

	for (int i=1;i<dist[ID].size();i++)
	{
		if (i == ID)
		{
			if (extraTiles[ID] > 0 && charge > 1 && charge >= 2)
				reach.pb(mp(i, extraTiles[ID]));
		}
		else
		{
			if (dist[ID][i] <= charge && dist[ID][i] != 0 && currCharges[i] > 0)
			{
				reach.pb(mp(i, dist[ID][i]));
				/*if (dist[ID][i] < 3)
				{
					if (distAux[ID][i] > 0)
						cout<<"There is another way from "<<ID<<" to "<<i<<" of cost "<<distAux[ID][i]<<"\n";
					else
						cout<<"There is no other way from "<<ID<<" to "<<i<<"\n";
				}*/
			}
		}
	}

	return reach;
}