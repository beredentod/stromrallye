#include <bits/stdc++.h>
#include "setup.h"
#include "graph.h"
#include "backtracking.h"

//eine Funktion, die uns hilft, ein Array von tuple absteigend zu sortieren
bool sortdesc(const tuple<int, int, int>& a,  const tuple<int, int, int>& b) 
{ 
    return (get<0>(a) > get<0>(b)); 
} 


//die rekursive Funktion, die alle Moeglichkeiten ausprobiert
// id - Eingabeindex einer Batterie
// charge - die aktuelle Ladung
// status - das Array mit allen Ladungen jeweiliger Batterie; Array C
// result - das Array mit dem aktuellen Pfad vom Ursprung, Array R
bool Backtracking::next (int id, int charge, vector<int>& status, vector<iPair> &result)
{
	//das Array mit allen von id aus erreichbaren Batterien; Array N_id
	vector<pair<int,int>> neighbors = checkReachability(id, charge, status);

	//der terminierende Fall
	//wenn die Liste von erreichbaren Batterien leer ist
	if (neighbors.empty())
	{
		if (charge == 0)
		{
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

	//der Fall, wenn die Liste nicht leer ist
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
				int nextDist = distAux[id][neighID] + 2;
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


//eine Funktion, die die erreichbaren Batterien von einer Batterie ID aus bestimmt
// ID - Eingabeindex einer Batterie
// charge - die aktuelle Ladung
// currCharges - das aktuelle Array C (=status)
vector<pair<int,int>> Backtracking::checkReachability (int ID, int charge, vector<int>& currCharges)
{
	//ein Array mit Eingabeindizes mit minimalen Entfernungen
	vector<pair<int,int>> reach;
	//ein Array, das zu sortieren wird
	vector<tuple<int, int, int>> poss;

	for (int i=1;i<dist[ID].size();i++)
	{
		//der Fall mit Schleifen
		if (i == ID)
		{
			//es wird ueberprueft, ob eine Schleife gemacht werden kann
			if (extraTiles[ID] > 0 && charge >= 2)
				reach.pb(mp(i, extraTiles[ID]));
		}
		else
		{
			//es wird ueberprueft, ob eine Batterie i erreicht werden kann
			if (dist[ID][i] <= charge && dist[ID][i] != 0 && currCharges[i] > 0)
				poss.pb(make_tuple(currCharges[i], i, dist[ID][i]));
		}
	}

	//poss wird absteigend sortiert
	sort(poss.begin(), poss.end(), sortdesc);

	//nur die Eingabeindizes und die minimalen Entfernungen werden gespeichert
	for (auto x: poss)
		reach.pb(mp(get<1>(x), get<2>(x)));

	//das Array mit allen erreichbaren Batterien wird ausgegeben
	return reach;
}
