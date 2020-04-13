#include <bits/stdc++.h>
#include "setup.h"
#include "graph.h"

Battery Graph::convertInput(string data)
{
	vector<int> v;

	size_t pos = 0;
	string token;
	string delimiter = ",";
	while ((pos = data.find(delimiter)) != string::npos) 
	{
	    token = data.substr(0, pos);
	    v.push_back(stoi(token));
	    data.erase(0, pos + delimiter.length());
	}

	Battery a(v[0],v[1],stoi(data));

	return a;
}

void Graph::readFile (string $FILENAME)
{
	ifstream file;
	string data;

	file.open($FILENAME);
	file>>data;

	boardDimension = stoi(data);

	for (int i=0; i<=boardDimension; i++)
	{
		vector<int> v(boardDimension+1);
		board.pb(v);
	}
	
	file>>data;
	start = convertInput(data);
	start.setInputID(0);
	int boardID = (start.getY()-1) * boardDimension + start.getX()-1;
	start.setBoardID(boardID);

	batteryToBoardID[start] = boardID;
	boardIDToBattery[boardID] = start;
	batteryToInputID[start] = 0;
	inputIDToBattery[0] = start;

	batteries.insert(start);
	board[start.getY()][start.getX()] = start.getCharge();


	file>>data;
	int batt = stoi(data);
	for (int i=1; i<=batt; i++)
	{
		file>>data;
		Battery a = convertInput(data);
		a.setInputID(i);
		boardID = (a.getY()-1) * boardDimension + a.getX()-1;
		a.setBoardID(boardID);

		batteryToBoardID[a] = boardID;
		boardIDToBattery[boardID] = a;
		batteryToInputID[a] = i;
		inputIDToBattery[i] = a;

		batteries.insert(a);
		board[a.getY()][a.getX()] = a.getCharge();
	}

	numBat = batt;

	for (int i=0; i <= numBat; i++)
	{
		vector<int> v;
		distances.pb(v);
		distancesAux.pb(v);
		extraTiles.pb(0);
	}

	file.close();
}

void Graph::determineConnections()
{
	for (int i=1 ; i <= boardDimension; i++)
	{
		for (int j=1; j <= boardDimension; j++)
		{
			//int currBoardID = (i-1) * (boardDimension) + j-1;
			vector<iPair> neighbors;

			//oben
			if (i != 1)
			{
				int neighBoardID = (i-2) * (boardDimension) + j-1;
				int neighCharge = board[i-1][j];

				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//unten
			if (i != boardDimension)
			{
				int neighBoardID = (i) * (boardDimension) + j-1;
				int neighCharge = board[i+1][j];

				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//links
			if (j != 1)
			{
				int neighBoardID = (i-1) * (boardDimension) + j-2;
				int neighCharge = board[i][j-1];

				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//rechts
			if (j != boardDimension)
			{
				int neighBoardID = (i-1) * (boardDimension) + j;
				int neighCharge = board[i][j+1];

				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			nodes.pb(neighbors);
		}
	}
}

void Graph::BFS(Battery b)
{
	vector<int> battDistances(numBat+1);
	vector<int> battdistancesAux(numBat+1);

	int currInputID = b.getInputID();

	queue<iPair> q;
	q.push(mp(b.getBoardID(), 0));

	vector<bool> vis (boardDimension * boardDimension);
	vis[b.getBoardID()] = 1;

	while (!q.empty())
	{
		int currBoardID = q.front().first;
		int currDist = q.front().second;

		q.pop();

		for (int i=0; i<nodes[currBoardID].size(); i++)
		{
			int neighBoardID = nodes[currBoardID][i].first;
			int neighCharge = nodes[currBoardID][i].second;

			if (!vis[neighBoardID])
			{
				if (neighCharge > 0)
				{
					Battery neighborB = boardIDToBattery.find(neighBoardID)->second;
					int currNeighInputID = neighborB.getInputID();

					if (battDistances[currNeighInputID] == 2 || battDistances[currNeighInputID] == 1)
					{
						if (battdistancesAux[currNeighInputID] > 0)
						{
							if (currDist+1 < battdistancesAux[currNeighInputID])
								battdistancesAux[currNeighInputID] = currDist+1;
						}
						else
							battdistancesAux[currNeighInputID] = currDist+1;
					}
					else
					{
						battDistances[currNeighInputID] = currDist+1;
						if (currDist+1 > 2)
							vis[neighBoardID] = 1;
					}
				}
				else
				{
					q.push(mp(neighBoardID, currDist+1));
					vis[neighBoardID] = 1;
				}
			}	
		}
	}

	distances[currInputID].swap(battDistances);
	distancesAux[currInputID].swap(battdistancesAux);
}

bool Graph::checkOneTile(Battery b)
{
	int currBoardID = b.getBoardID();

	for (int i=0; i<nodes[currBoardID].size(); i++)
	{
		int neighCharge = nodes[currBoardID][i].second;

		if (neighCharge == 0)
			return 1;	
	}
	return 0;
}


bool Graph::checkTwoTiles(Battery b)
{
	int currBoardID = b.getBoardID();

	for (int i=0; i<nodes[currBoardID].size(); i++)
	{
		int neighBoardID = nodes[currBoardID][i].first;
		int neighCharge = nodes[currBoardID][i].second;

		if (neighCharge == 0)
		{
			for (int j=0; j<nodes[neighBoardID].size(); j++)
			{
				int neighCharge2 = nodes[neighBoardID][j].second;

				if (neighCharge2 == 0)
					return 1;
			}
		}
	}
	return 0;
}

/*vector<int> Graph::checkReachability (Battery b)
{
	int charge = b.getCharge();
	int ID = b.getInputID();

	vector<int> reach;

	for (int i=1;i<distances[ID].size();i++)
	{
		if (i == ID)
		{
			if (charge%2==0 && extraTiles[ID] > 0)
				reach.pb(i);
		}
		else
		{
			if (distances[ID][i] <= charge && distances[ID][i] != 0)
			{
				reach.pb(i);
				/*if (distances[ID][i] < 3)
				{
					if (distancesAux[ID][i] > 0)
						cout<<"There is another way from "<<ID<<" to "<<i<<" of cost "<<distancesAux[ID][i]<<"\n";
					else
						cout<<"There is no other way from "<<ID<<" to "<<i<<"\n";
				}
			}
		}
	}

	return reach;
}
*/