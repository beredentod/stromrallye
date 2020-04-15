#include <bits/stdc++.h>
#include "generate.h"
#include "setup.h"

vector<int> Generator::generateOrder()
{
	vector<int> num;
	stack<int> help;
	num.pb(0);

	for (int i=1; i < batNum; i++)
	{
		int situation  = rand()%2;

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

vector<int> Generator::generateDistances(vector<int> &v)
{
	vector<int> num;
	stack<iPair> help;

	for (int i=0; i < v.size()-1; i++)
	{
		int index = v[i];
		int nextIndex = v[i+1];

		int dist = rand()%5 + 1;

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

	return num;
}

vector<int> Generator::generateCharges(vector<int> &v, vector<int> &dist)
{
	vector<int> ch(batNum);
	vector<int> prev(batNum);

	if (!dist.empty())
	{
		for (int i=0; i < v.size(); i++)
		{
			int currID = v[i];
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
			int multip = rand()%3+1; 
			ch[i] += 2*multip;		
		}
		else
		{
			int multip = rand()%3; 
			ch[i] += 2*multip;
		}
	}

	return ch;
}

vector<iPair> Generator::setCoordinates(vector<int> &v, vector<int> &dist)
{	
	vector<bool> vis(batNum);

	vector<iPair> coor(batNum);
	vector<int> prev(batNum);

	set<iPair> used;

	coor[0] = (mp(0,0));
	prev[0] = -1;

	for (int i=1; i < v.size(); i++)
	{
		int currID = v[i];

		if (!vis[currID])
		{
			iPair prevPoint = coor[v[i-1]];
			prev[currID] = v[i-1];

			int currDist = dist[i-1];

			int x,y,neg;

			do
			{
				x = rand()%currDist + 1;
				y = abs(currDist - x);
				neg = rand()%2;

				if (neg == 1)
					x = -x;

				neg = rand()%2;
				if (neg == 1)
					y = -y;

			} while (used.find(mp(x,y)) != used.end());

			coor[currID] = mp(x,y);
			used.insert(mp(x,y));

			vis[currID] = 1;
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

	return coor;
}

void Generator::prepareOutput(vector<int> &ch, vector<iPair> &coor)
{
	//boardDimension
	int maximal = INT_MIN;
	for (auto x: coor)
	{
		maximal = max(maximal, x.first);
		maximal = max(maximal, x.second);
	}
	maximal ++;

	boardDimension = maximal;

	start.setX(coor[0].first);
	start.setY(coor[0].second);
	start.setCharge(ch[0]);

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
