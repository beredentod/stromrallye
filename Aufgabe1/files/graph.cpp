#include <bits/stdc++.h>
#include "setup.h"
#include "graph.h"


//eine Methode, die das Eingabeformat einer Batterie
//in eine Batterie umwandelt
Battery Graph::convertInput(string data)
{
	vector<int> v;

	size_t pos = 0;
	string token;
	string delimiter = ",";
	while ((pos = data.find(delimiter)) != string::npos) 
	{	
		//es werden die Kommata ausgeschniten
	    token = data.substr(0, pos);
	    v.push_back(stoi(token));
	    data.erase(0, pos + delimiter.length());
	}

	//eine fertige Batterie wird gebildet
	Battery a(v[0],v[1],stoi(data));

	//fie fertige Batterie wird ausgegeben
	return a;
}


//die Mehode, die Informationen aus einer Textdatei einliest
//und im Programm speichert
// $FILENAME - die Eingabedatei
void Graph::readFile (string $FILENAME)
{
	ifstream file($FILENAME);
	string data;

	//es wird geprueft, ob die Datei existiert
	if (file.is_open())
	{
		file>>data;

		//die Breite/Laenge der Matrix wird eingelesen
		boardDimension = stoi(data);

		//die Matrix wird gebildet
		for (int i=0; i<=boardDimension; i++)
		{
			vector<int> v(boardDimension+1);
			board.pb(v);
		}
		
		file>>data;
		//die Startbatterie wird eingelsen
		start = convertInput(data);
		//der Eingabeindex 0 wird der Startbatterie zugeordnet
		start.setInputID(0);
		//ein Brettindex fuer die Startbatterie wird bestimmt
		int boardID = (start.getY()-1) * boardDimension + start.getX()-1;
		//der Brettindex wird der Startbatterie zugeordnet
		start.setBoardID(boardID);

		//die Startbatterie wird in die Map-Container mit ihren
		//Indizes eingefuegt
		batteryToBoardID[start] = boardID;
		boardIDToBattery[boardID] = start;

		batteryToInputID[start] = 0;
		inputIDToBattery[0] = start;


		//die Startbatterie wird in die Menge mit allen Batterien eingefuegt
		batteries.insert(start);
		//die Ladung der Startbatterie wird in der Matrix 
		//auf dem entsprechenden Feld gespeichert
		board[start.getY()][start.getX()] = start.getCharge();

		file>>data;
		//die Anzahl der restlichen Batterien
		int batt = stoi(data);
		for (int i=1; i<=batt; i++)
		{
			file>>data;
			//eine naechste Batterie wird aus der Textdatei eingelesen
			Battery a = convertInput(data);
			//der Ingabeindex wird zugeordnet
			a.setInputID(i);
			//ein Brettindex wird bestimmt
			boardID = (a.getY()-1) * boardDimension + a.getX()-1;
			//der Brettindex wird zugeordnet
			a.setBoardID(boardID);

			//die Batterie wird in die Map-Container mit ihren
			//Indizes eingefuegt
			batteryToBoardID[a] = boardID;
			boardIDToBattery[boardID] = a;
			batteryToInputID[a] = i;
			inputIDToBattery[i] = a;

			//die Batterie wird in die Menge mit allen Batterien eingefuegt
			batteries.insert(a);
			//die Ladung der Batterie wird in der Matrix 
			//auf dem entsprechenden Feld gespeichert
			board[a.getY()][a.getX()] = a.getCharge();
		}

		//die Anzahl der Batterien wird als numBat gespeichert
		numBat = batt;

		//Arrays distances, distancesAux und extraTiles werden gebildet
		for (int i=0; i <= numBat; i++)
		{
			vector<int> v;
			distances.pb(v);
			distancesAux.pb(v);
			extraTiles.pb(0);
		}

		file.close();
	}
	else
		throw runtime_error("Die Datei mit der eingegebenen Nummer wurde nicht gefunden.\n");
}


//diese Methode findet Nachbarfleder jedes Feldes
//Kanten im Graphen werden bestimmt
void Graph::determineConnections()
{
	//es wird durch jedes Feld in der Matrix iteriert
	for (int i=1 ; i <= boardDimension; i++)
	{
		for (int j=1; j <= boardDimension; j++)
		{
			//das Array mit den Nachbarn vom Feld (i,j)
			vector<iPair> neighbors;

			//der Nachbar oben
			if (i != 1)
			{
				//der Brettindex des Nachbarn
				int neighBoardID = (i-2) * (boardDimension) + j-1;
				//die Ladung des Nachbarn
				int neighCharge = board[i-1][j];

				//der Nachbar mit der Ladung wird in das Array eingefuegt 
				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//der Nachbar unten
			if (i != boardDimension)
			{
				//der Brettindex des Nachbarn
				int neighBoardID = (i) * (boardDimension) + j-1;
				//die Ladung des Nachbarn
				int neighCharge = board[i+1][j];

				//der Nachbar mit der Ladung wird in das Array eingefuegt 
				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//der Nachbar links
			if (j != 1)
			{
				//der Brettindex des Nachbarn
				int neighBoardID = (i-1) * (boardDimension) + j-2;
				//die Ladung des Nachbarn
				int neighCharge = board[i][j-1];

				//der Nachbar mit der Ladung wird in das Array eingefuegt 
				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//der Nachbar rechts
			if (j != boardDimension)
			{
				//der Brettindex des Nachbarn
				int neighBoardID = (i-1) * (boardDimension) + j;
				//die Ladung des Nachbarn
				int neighCharge = board[i][j+1];

				//der Nachbar mit der Ladung wird in das Array eingefuegt 
				neighbors.pb(mp(neighBoardID, neighCharge));
			}

			//wenn schraege Uebergaenge erlaubt sind
			if (slant)
			{
				//die Nachbarn oben
				if (i != 1)
				{
					//der Nachbar oben links
					if (j != 1)
					{
						//der Brettindex des Nachbarn
						int neighBoardID = (i-2) * (boardDimension) + j-2;
						//die Ladung des Nachbarn
						int neighCharge = board[i-1][j-1];

						//der Nachbar mit der Ladung wird in das Array eingefuegt 
						neighbors.pb(mp(neighBoardID, neighCharge));
					}

					//der Nachbar oben rechts	
					if (j != boardDimension)
					{
						//der Brettindex des Nachbarn
						int neighBoardID = (i-2) * (boardDimension) + j;
						//die Ladung des Nachbarn
						int neighCharge = board[i-1][j+1];

						//der Nachbar mit der Ladung wird in das Array eingefuegt 
						neighbors.pb(mp(neighBoardID, neighCharge));
					}								
				}

				//die Nachbarn unten
				if (i != boardDimension)
				{
					//der Nachbar unten links
					if (j != 1)
					{
						//der Brettindex des Nachbarn
						int neighBoardID = (i) * (boardDimension) + j-2;
						//die Ladung des Nachbarn
						int neighCharge = board[i+1][j-1];

						//der Nachbar mit der Ladung wird in das Array eingefuegt 
						neighbors.pb(mp(neighBoardID, neighCharge));
					}

					//der Nachbar unten rechts	
					if (j != boardDimension)
					{
						//der Brettindex des Nachbarn
						int neighBoardID = (i) * (boardDimension) + j;
						//die Ladung des Nachbarn
						int neighCharge = board[i+1][j+1];

						//der Nachbar mit der Ladung wird in das Array eingefuegt 
						neighbors.pb(mp(neighBoardID, neighCharge));
					}								
				}
			}

			//das Array mit den Nachbarn wird am Ende des Arrays nodes
			//angehaengt
			//neighbors wird an der Stelle gespiehcert, die
			//dem Brettindex entspricht
			nodes.pb(neighbors);
		}
	}
}


//die Methode die einen BFS-Algorithmus aus dem Feld der Batterie b
//laufen laesst
//die minimalen Entfernungen von b zu anderen Batterien werden bestimmt
void Graph::BFS(Battery b)
{
	//das Array mit den minimalen Entfernungen zu anderen Batterien
	vector<int> battDistances(numBat+1);
	//das Array mit den minimalen Entfernungen zu anderen Batterien,
	//wenn battDistances[i] < 3
	vector<int> battDistancesAux(numBat+1);

	//der Eingabeindex von b
	int currInputID = b.getInputID();

	//eine Warteschlange, die ein Paar
	//pair<Brettindex, Entfernung> enthaelt
	queue<iPair> q;

	//die Batterie b wird mit Entfernung 0 in die 
	//Warteschlange eingekellert
	q.push(mp(b.getBoardID(), 0));

	//das Array, in dem die besuschten Knoten markiert werden
	vector<bool> vis (boardDimension * boardDimension);

	//die Batterie b wird als besucht markiert
	vis[b.getBoardID()] = 1;

	//so lange es noch Brettindizes in der Schlange gibt
	while (!q.empty())
	{
		//der erste Brettindex aus der Warteschlange, das aktuelle Feld
		int currBoardID = q.front().first;
		//die Entfernung aus b zum Feld currBoardID, die aktuelle Entfernung
		int currDist = q.front().second;

		//das erste Paar wird ausgekellert
		q.pop();

		//es wird durch alle Nachbarn von currBoardID iteriert
		for (int i=0; i<nodes[currBoardID].size(); i++)
		{
			//der Brettindex eines Nachbarn vom aktuellen Felds
			int neighBoardID = nodes[currBoardID][i].first;
			//die Ladung auf dem Nachbarfeld
			int neighCharge = nodes[currBoardID][i].second;

			//falls das Nachbarfeld noch nicht besucht wurde
			if (!vis[neighBoardID])
			{
				//falls das Nachbarfeld eine Batterie besitzt
				if (neighCharge > 0)
				{
					//die Batterie auf dem Nachbarfeld wird gefunden
					Battery neighborB = boardIDToBattery.find(neighBoardID)->second;
					//der Eingabeindex der Batterie wird gespeichert
					int currNeighInputID = neighborB.getInputID();

					//falls die minimale Entfernung vom aktuellen Feld zum Nachbarfeld 
					//bereits gefunden wurde und kleiner ist als 3
					if (battDistances[currNeighInputID] == 2 || battDistances[currNeighInputID] == 1)
					{
						//wenn eine Entfernung vom aktuellen Feld zum Nachbarfeld
						//schon existiert
						if (battDistancesAux[currNeighInputID] > 0)
						{
							//wenn die aktuelle Entfenung kleiner ist als
							//die Entfernung in battDistancesAux,
							//wird diese Entfernung aktualisiert
							if (currDist+1 < battDistancesAux[currNeighInputID])
								battDistancesAux[currNeighInputID] = currDist+1;
						}
						else
							//die Entfernung in battDistancesAux wird als currDist+1
							//gespeichert
							battDistancesAux[currNeighInputID] = currDist+1;
					}
					else
					{
						//die minimale Entfernung vom aktuellen Feld zum Nachbarfeld
						//wird als currDist+1 gespeichert
						battDistances[currNeighInputID] = currDist+1;
						//nur wenn diese neue Entfernung groesser ist als 2,
						//wird das Feld als besucht markiert
						if (currDist+1 > 2)
							vis[neighBoardID] = 1;
					}
				}
				else
				{	//der Brettindex des Nachbarn wird mit einer um 1 vergroesserten 
					//Entfernung in die Warteschlange eingekellert
					q.push(mp(neighBoardID, currDist+1));
					//das Nachbarfeld wird als besucht markiert
					vis[neighBoardID] = 1;
				}
			}	
		}
	}

	//die Entfernunge werden an der Stelle des Eingabeindex gespeichert
	distances[currInputID].swap(battDistances);
	distancesAux[currInputID].swap(battDistancesAux);
}


//die Methode prueft, ob es neben der Batterie b
//ein batteriefreies Feld gibt
bool Graph::checkOneTile(Battery b)
{
	//der Brettindex des Feldes, auf dem b liegt 
	int currBoardID = b.getBoardID();

	//es wird durch die Nachbarn vom Feld von b iteriert
	for (int i=0; i<nodes[currBoardID].size(); i++)
	{
		//die Ladung des Nachbarfeldes
		int neighCharge = nodes[currBoardID][i].second;

		//wenn es mindestens ein Feld gibt, dessen Ladung 0 ist,
		//wird 1 ausgegeben
		if (neighCharge == 0)
			return 1;	
	}

	//Andernfalls wird 0 ausgegeben
	return 0;
}


//die Methode prueft, ob es neben der Batterie b
//zwei nacheinander folgende batteriefreien Felder gibt
bool Graph::checkTwoTiles(Battery b)
{
	//der Brettindex des Feldes, auf dem b liegt 
	int currBoardID = b.getBoardID();

	//es wird durch die Nachbarn vom Feld von b iteriert
	for (int i=0; i<nodes[currBoardID].size(); i++)
	{
		//der Brettindex des Nachbarfeldes
		int neighBoardID = nodes[currBoardID][i].first;
		//die Ladung des Nachbarfeldes
		int neighCharge = nodes[currBoardID][i].second;

		//wenn das  Nachbarfeld batteriefrei ist
		if (neighCharge == 0)
		{
			//es wird durch die Nachbarn vom Nachbarn von b iteriert
			for (int j=0; j<nodes[neighBoardID].size(); j++)
			{
				//die Ladung des Nachbarn vom Nachbarn von b
				int neighCharge2 = nodes[neighBoardID][j].second;

				//wenn dieser Nachbar keine Batterie besitzt,
				//wird 1 ausgegeben
				if (neighCharge2 == 0)
					return 1;
			}
		}
	}

	//Andernfalls wird 0 ausgegeben
	return 0;
}
