#include <bits/stdc++.h>
#include "generate.h"
#include "setup.h"

vector<int> Generator::generateOrder()
{
	vector<int> num;
	stack<int> help;
	num.pb(0);

    uniform_real_distribution<double> dis(0,1);

	vector<int> generated;
	for (int i=1; i < batNum; i++)
		generated.pb(round(dis(rd)));

	for (int i=1; i < batNum; i++)
	{
		int situation = generated[i-1];

		if (situation == 0) //append
		{
			num.pb(i);
			while (!help.empty())
			{
				num.pb(help.top());
				help.pop();
			}
		}

		else if (situation == 1) //insert
		{
			num.pb(i);
			help.push(i);
		}
	}

	return num;
}

pair<vector<int>, vector<iPair>> Generator::generateDistances(vector<int> &v)
{
	uniform_int_distribution<int> dis(1,5);

	vector<int> num;
	stack<iPair> help;

	vector<bool> vis;
	vector<iPair> coor;
	set<iPair> used;

	for (int i =0; i < batNum; i++)
	{
		vis.pb(0);
		coor.pb(mp(-1,-1));
	}

	coor[0] = (mp(0,0));


	for (int i=0; i < v.size()-1; i++)
	{
		int index = v[i];
		int nextIndex = v[i+1];

		int dist = dis(rd);

		int currDist = dist;

		if (!help.empty() && help.top().first == nextIndex)
			currDist = help.top().second;

		if (!vis[nextIndex])
		{
			iPair prevPoint = coor[index];
			int x,y;
			bool all;

			do
			{
				vector<bool> free;
				for (int i=0;i<4*currDist;i++)
					free.pb(0);

				uniform_int_distribution<int> dis2(0, 4*currDist-1);

				do
				{
					int coorID = dis2(rd);

					int quarter = coorID/currDist;
					if (quarter == 0)
					{
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						x += prevPoint.first;
						y += prevPoint.second;
					}
					else if (quarter == 1)
					{
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						y = -y;
						x += prevPoint.first;
						y += prevPoint.second;
					}
					else if (quarter == 2)
					{
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						x = -x;
						x += prevPoint.first;
						y += prevPoint.second;
					}
					else if (quarter == 3)
					{
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						x = -x;
						y = -y;
						x += prevPoint.first;
						y += prevPoint.second;
					}

					free[coorID] = 1;

					all = true;
					for (auto x: free)
						if (!x) all = false;

				} while (used.find(mp(x,y)) != used.end() && !all);

				dist = currDist;
				currDist++;

			} while (all);

			coor[nextIndex] = mp(x,y);
			used.insert(mp(x,y));

			vis[nextIndex] = true;
		} 

		if (!help.empty() && help.top().first == nextIndex)
		{
			num.pb(help.top().second);
			help.pop();
		}
		else
		{
			num.pb(dist);
			help.push(mp(index, dist));
		}
	}	

	int minimal = INT_MAX;
	
	for (auto x: coor)
	{
		minimal = min(minimal, x.first);
		minimal = min(minimal, x.second);
	}

	minimal = -minimal;
	minimal += 2;

	for (int i=0;i<coor.size();i++)
	{
		coor[i].first += minimal;
		coor[i].second += minimal;
	}

	return mp(num, coor);
}

vector<int> Generator::generateCharges(vector<int> &v, vector<int> &dist)
{
	vector<int> ch;
	vector<int> prev;
	for (int i=0;i<batNum;i++)
	{
		ch.pb(0);
		prev.pb(0);
	}

	uniform_int_distribution<int> dis(0,2);

	if (!dist.empty())
	{
		for (int i=0; i < v.size(); i++)
		{
			int currDist = dist[i];

			if (ch[v[i]] == 0)
			{
				ch[v[i]] = currDist;
				if (v[i] != 0)
					prev[v[i]] = v[i-1];
			}
			else
				ch[prev[v[i]]] += currDist;
		}
	}

	for (int i=0; i < ch.size(); i++)
	{
		if (ch[i] == 0)
		{
			int multip = dis(rd) + 1; 
			ch[i] += 2*multip;	
		}
		else
		{
			int multip = dis(rd); 
			ch[i] += 2*multip;
		}
	}

	return ch;
}

//diese Methode speichert die generierten Ladungen und Koordinaten
//in der Menge batteries
// ch - das Array mit Ladungen
// coor - das Array mit Koordinaten
void Generator::prepareOutput(vector<int> &ch, vector<iPair> &coor)
{
	//es wird die maximale Koordinate von allen gesucht
	int maximal = INT_MIN;
	for (auto x: coor)
	{
		maximal = max(maximal, x.first);
		maximal = max(maximal, x.second);
	}
	//wir vergroessern die maximale Koordinate um 1
	maximal ++;

	//die maximale Koordinate wird zu der Laenge der Matrix
	boardDimension = maximal;

	//wir speichern die Koordinaten und die Ladung der Startbatterie
	//unter start
	start.setX(coor[0].first);
	start.setY(coor[0].second);
	start.setCharge(ch[0]);

	//wir fuegen in das Array batteries alle restlichen Batterien ein
	for (int i=1; i<coor.size(); i++)
	{
		Battery b;
		b.setX(coor[i].first);
		b.setY(coor[i].second);
		b.setCharge(ch[i]);
		batteries.insert(b);
	}
}

void Generator::save(string path)
{
	ofstream file(path);

	file << boardDimension << "\n";
	file << start.getX() << "," << start.getY() << "," << start.getCharge() << "\n";
	file << batteries.size() << "\n";
	for (auto x: batteries)
		file << x.getX() << "," << x.getY() << "," << x.getCharge() << "\n";

	file.close();

	cout << "\n\nEine txt-Datei \"" << path << "\" wurde erstellt.\n";
}	
