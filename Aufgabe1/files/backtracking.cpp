#include <bits/stdc++.h>
#include "setup.h"
#include "graph.h"
#include "backtracking.h"

bool sortdesc(const tuple<int, int, int>& a,  const tuple<int, int, int>& b) 
{ 
    return (get<0>(a) > get<0>(b)); 
} 

bool Backtracking::next (int id, int charge, vector<int>& status, vector<iPair> &result)
{
	vector<pair<int,int>> neighbors = checkReachability(id, charge, status);

	if (neighbors.empty())
	{
		if (extraTiles[id] > 1)
		{
			result.pb(mp(-1, charge));
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			if (all) 
			{
				foundPath = result;
				return 1;
			}

			return 0;
		}
		else if (extraTiles[id] == 1)
		{
			result.pb(mp(-1, 1));
			charge --;
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			if (all && charge == 0) 
			{
				foundPath = result;
				return 1;
			}

			return 0;
		}
		else
		{
			vector<iPair> allNeighbors;
			for (int i=1;i<dist[id].size();i++)
			{
				if (dist[id][i] <= charge && dist[id][i] != 0 && i != id)
					allNeighbors.pb(mp(dist[id][i], i));
			}

			sort(allNeighbors.rbegin(), allNeighbors.rend());

			for (auto x: allNeighbors)
			{
				if (x.first > 2)
				{
					result.pb(mp(x.second, charge));
					charge = 0;
					break;
				}
				else
				{
					result.pb(mp(x.second, x.first));
					charge -= x.first;
					break;
				}		
			}

			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			if (all && charge == 0) 
			{
				foundPath = result;
				return 1;
			}
			return 0;
		}
	}

	for (auto x: neighbors)
	{
		int neighID = x.first;
		int minDist = x.second;

		vector<int> neighDistances;
		neighDistances.pb(minDist);

		if (minDist > 2)
		{
			int nextDist = minDist + 2;
			while (charge >= nextDist)
			{
				neighDistances.pb(nextDist);
				nextDist += 2;
			}
		}
		else
		{
			if (distAux[id][neighID] > 2)
			{
				int nextDist = minDist + 2;
				while (charge >= nextDist)
				{
					neighDistances.pb(nextDist);
					nextDist += 2;
				}			
			}
		}
		
		for (auto y: neighDistances)
		{
			int nextCharge = status[neighID];
			
			vector<int> cpstatus = status;
			vector<iPair> cpresult = result;

			cpstatus[neighID] = charge - y;
			cpresult.pb(mp(neighID, y));

			bool found = next(neighID, nextCharge, cpstatus, cpresult);

			if (found)
				return 1;
			else
				cpresult.pop_back();
		}
		
	}

	return 0;
}

vector<pair<int,int>> Backtracking::checkReachability (int ID, int charge, vector<int>& currCharges)
{
	vector<pair<int,int>> reach;
	vector<tuple<int, int, int>> poss;

	for (int i=1;i<dist[ID].size();i++)
	{
		if (i == ID)
		{
			if (extraTiles[ID] > 0 && charge >= 2)
				reach.pb(mp(i, extraTiles[ID]));
		}
		else
		{
			if (dist[ID][i] <= charge && dist[ID][i] != 0 && currCharges[i] > 0)
				poss.pb(make_tuple(currCharges[i], i, dist[ID][i]));
		}
	}

	sort(poss.begin(), poss.end(), sortdesc);

	for (auto x: poss)
		reach.pb(mp(get<1>(x), get<2>(x)));

	return reach;
}

