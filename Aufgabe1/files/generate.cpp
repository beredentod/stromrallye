#include <bits/stdc++.h>
#include "generate.h"
#include "setup.h"

//die Methode, die eine Reihenfolge mit Eingabeindizes generiert,
//in der die Spilsituation gespielt werden muss, um geloest zu werden
vector<int> Generator::generateOrder()
{
	//ein Array mit der Reihenfolge
	vector<int> num;
	//ein Stapelspeicher fuer die Einfuegen-Situationen
	stack<int> help;

	//es wird die Startbatterie am Ende des Arrays angehaengt
	num.pb(0);

	//ein Generator, der der stetigen Gleichverteilung folgt
    uniform_real_distribution<double> dis(0,1);

    //ein Array fuer die generierten Situationen
	vector<int> generated;
	for (int i=1; i < batNum; i++)
		//die Situationen werden generiert
		generated.pb(round(dis(rd)));

	//es wird die Reihenfolge gebildet
	for (int i=1; i < batNum; i++)
	{
		//die Situation wird aus dem Array generated eingelesen
		int situation = generated[i-1];

		//eine Hinzufuegen-Situation
		if (situation == 0)
		{
			//der naechste Eingabeindex wird am Ende der
			//Reihenfolge angehaengt
			num.pb(i);
			//alle im Stapelspeicher entahltenen Eingabeindizes
			//werden am Ende der Reihenfolge angehaengt
			while (!help.empty())
			{
				num.pb(help.top());
				//Auskellern
				help.pop();
			}
		}
		//eine Einfuegen-Situation
		else if (situation == 1)
		{	
			//der naechste Eingabeindex wird am Ende der
			//Reihenfolge angehaengt
			num.pb(i);
			//der naechste Eingabeindex in den Stapelspeicher eingekellert
			help.push(i);
		}
	}

	//die Reihenfolge wird ausgegeben
	return num;
}


//die Methode, die Entfernungen zwischen der Batterien generiert
//Gleichzeitig werden auch die Koordinaten jeder Batterie generiert
// v - das Array mit einer Reihenfolge
pair<vector<int>, vector<iPair>> Generator::generateDistances(vector<int> &v)
{
	//ein Generator, der der stetigen Gleichverteilung folgt
	uniform_int_distribution<int> dis(1,5);

	//ein Array mit den generierten Entfernungen
	vector<int> num;
	//ein Stapelspiehcer fuer die Einfuegen-Situationen,
	//in dem Paare von Index und Entfernung gespeichert werden
	stack<iPair> help;

	//ein Array, in dem die Batterien markiert sind, fuer
	//die Koordinaten bestimmt wurden
	vector<bool> vis;
	//ein Array mit Koordinaten jeder Batterie
	vector<iPair> coor;
	//eine Menge mit allen benutzten Koordinaten
	set<iPair> used;

	//es werden die Arrays vis und coor gebildet
	for (int i = 0; i < batNum; i++)
	{
		vis.pb(0);
		coor.pb(mp(-1,-1));
	}

	//die Startbatterie bekommt die Koordinaten (0,0)
	coor[0] = (mp(0,0));

	//es wird vom ersten zum vorletzen Element in v iteriert
	for (int i=0; i < v.size()-1; i++)
	{
		//der aktuelle Eingabeindex
		int index = v[i];
		//der naechste Eingabeindex
		int nextIndex = v[i+1];

		//eine ganzzahlige Entfernung aus dem Bereich [1,5]
		//wird generiert
		int dist = dis(rd);

		//dist wird als currDist kopiert
		int currDist = dist;

		//wenn der erste Index im Stapelspeicher gleich dem
		//naechsten Index ist
		if (!help.empty() && help.top().first == nextIndex)
			//currDist wird zur ersten Entfernung im Stapelspeicher
			currDist = help.top().second;

		//falls fuer die naechste Batterie noch keine Kooridnaten 
		//generiert wurden
		if (!vis[nextIndex])
		{
			//die Koordinaten der Batterie mit dem aktuellen Index
			iPair prevPoint = coor[index];

			//neue x- und y-Koordinaten
			int x,y;

			//ein Wert, der bestimmt ob alle Koordinaten kombinationen
			//verbraucht wurden
			bool all;

			do
			{
				//ein Array, in dem die bereits generierten
				//Koordinatenkombinationen markiert werden
				vector<bool> free;
				for (int i=0;i<4*currDist;i++)
					free.pb(0);

				//ein Generator, der der stetigen Gleichverteilung folgt
				uniform_int_distribution<int> dis2(0, 4*currDist-1);

				do
				{
					//es wird ein ganzzahliger Wert aus dem Bereich [0, 4*currDist)
					//generiert
					int coorID = dis2(rd);

					//anhand der generierten coorID werden
					//neue Koordinaten bestimmt
					//s. Formel in der Beschreibung
					int quarter = coorID/currDist;
					if (quarter == 0)
					{
						//Fall 1, s. Beschreibung
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);

						//zu den x- und y-Koordinaten 
						//werden die Koordinaten der aktuellen Batterie addiert
						x += prevPoint.first;
						y += prevPoint.second;
					}
					else if (quarter == 1)
					{
						//Fall 2, s. Beschreibung
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						y = -y;

						//zu den x- und y-Koordinaten 
						//werden die Koordinaten der aktuellen Batterie addiert
						x += prevPoint.first;
						y += prevPoint.second;
					}
					else if (quarter == 2)
					{
						//Fall 3, s. Beschreibung
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						x = -x;

						//zu den x- und y-Koordinaten 
						//werden die Koordinaten der aktuellen Batterie addiert
						x += prevPoint.first;
						y += prevPoint.second;
					}
					else if (quarter == 3)
					{
						//Fall 4, s. Beschreibung
						int rest = coorID - currDist*quarter;
						x = rest + 1;
						y = abs(currDist - x);
						x = -x;
						y = -y;

						//zu den x- und y-Koordinaten 
						//werden die Koordinaten der aktuellen Batterie addiert
						x += prevPoint.first;
						y += prevPoint.second;
					}

					//die Koordinatenkombination wird als benutzt markiert
					free[coorID] = 1;

					//es wirde ueberprueft, ob alle Kombinationen benutzt sind
					all = true;
					for (auto x: free)
						if (!x) all = false;

				//die Schleife wird wiederholt, wenn das neu enstandene Koordinatenpaar
				//schon einer anderen Batterie zugeordnet ist
				//auch wird die Schleife wiederholt, wenn in diesem Fall
				//nicht alle Kombinationen ausprobiert wurden
				} while (used.find(mp(x,y)) != used.end() && !all);

				//die neue Entfernung
				dist = currDist;

				//es wird mit einer um 1 groesseren Entfernung ausprobiert
				currDist++;

			} while (all);

			//die Koordinaten werden an der Stelle nextIndex im Array mit 
			//allen Koordinten gespeichert
			coor[nextIndex] = mp(x,y);
			//die Koordinaten werden  in diie Menge mit allen Koordinaten eingefuegt
			used.insert(mp(x,y));

			//es wird markiert, dass es schon fuer nextIndex Koordinaten gibt
			vis[nextIndex] = true;
		} 

		//wenn der erste Index im Stapelspeicher gleich dem
		//naechsten Index ist
		if (!help.empty() && help.top().first == nextIndex)
		{
			//es wird die erste Entfernung aus dem Stapelspeicher
			//am Ende des Arrays mit den Entfernungen angehaengt
			num.pb(help.top().second);

			//Auskellern
			help.pop();
		}
		else
		{	
			//die generierte Entfernung wird am Ende des Arrays
			//mit den Entfernungen angehaengt
			num.pb(dist);

			//dieselbe Entfernung wird mit dem aktuellen Index in den
			//Tapelspeicher eingekellert
			help.push(mp(index, dist));
		}
	}	

	//die kleinste Koordinaten von allen
	int minimal = INT_MAX;
	
	//es wird die kleinste Koordinate von allen bestimm
	for (auto x: coor)
	{
		minimal = min(minimal, x.first);
		minimal = min(minimal, x.second);
	}

	//die kleinste Koordinaten wird mal -1 multizplisiert
	minimal = -minimal;
	//dazu wird 2 addiert
	minimal += 2;

	//alle Koordinaten werden um minimal verschoben
	for (int i=0;i<coor.size();i++)
	{
		coor[i].first += minimal;
		coor[i].second += minimal;
	}

	//das Array mit den Entfernungen und das Array mit den Koordinaten
	//werden ausgegeben
	return mp(num, coor);
}


//die Methode, die Ladungen fuer jeweilige Batterie generiert
// v - ein Array mit der Reihenfolge
// dist - ein Array mit den Entfernungen zwischen den Indizes in der Reihenfolge
vector<int> Generator::generateCharges(vector<int> &v, vector<int> &dist)
{
	//ein Array mit den Ladungen
	vector<int> ch;
	//ein Array mit den Vorgaengern jeder Batterie
	vector<int> prev;

	//die beiden Arrays werden gebildet
	for (int i=0;i<batNum;i++)
	{
		ch.pb(0);
		prev.pb(0);
	}

	//ein Generator, der der stetigen Gleichverteilung folgt
	uniform_int_distribution<int> dis(0,2);

	//es werden die minimalen Ladungen bestimmt

	//wenn das Array mit den Entfernungen nicht leer ist
	if (!dist.empty())
	{
		//es wird durch das Array mit der Reihenfolge iteriert
		for (int i=0; i < v.size(); i++)
		{
			//die aktuelle Entfernung
			int currDist = dist[i];

			//wenn die Ladung des aktuellen Eingabeindex
			//0 betraegt
			if (ch[v[i]] == 0)
			{
				//die Ladung an der Stelle des aktuellen
				//Indexx wird als currDist gespiechert
				ch[v[i]] = currDist;

				//wenn der Index anders als 0 ist,
				//wir sein Vorgaenger gespeichert
				if (v[i] != 0)
					prev[v[i]] = v[i-1];
			}
			else
				//es wird an der Stelle des Vorgaengers vom aktuellen 
				//Eingabeindes die Ladung um currDist vergroessert
				ch[prev[v[i]]] += currDist;
		}
	}

	//es wird durch das Array von Ladungen iteriert
	for (int i=0; i < ch.size(); i++)
	{
		//wenn die iterierte Ladung 0 betraegt
		if (ch[i] == 0)
		{
			//es wird ein ganzzahliger Wert zwsichen 0 und 2
			//generiert und dazu wird 1 addiert
			int multip = dis(rd) + 1; 

			//das Produkt 2 * multip wird zur
			//iterierten Ladung addiert
			ch[i] += 2*multip;	
		}
		else
		{
			//es wird ein ganzzahliger Wert zwsichen 0 und 2
			//generiert
			int multip = dis(rd); 

			//das Produkt 2 * multip wird zur
			//iterierten Ladung addiert
			ch[i] += 2*multip;
		}
	}

	//das Array mit den Ladungen wird ausgegeben
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


//die Methode, die die generierten Informationen in einer Textdatei speichert
// path - die Datei, in der die generierte Spielsituation gespeichert wird
void Generator::save(string path)
{
	ofstream file(path);

	//die Spielsituation wird im von BWINF vorgeschlagenen Format gespeichert
	file << boardDimension << "\n";
	file << start.getX() << "," << start.getY() << "," << start.getCharge() << "\n";
	file << batteries.size() << "\n";
	for (auto x: batteries)
		file << x.getX() << "," << x.getY() << "," << x.getCharge() << "\n";

	file.close();

	cout << "\n\nEine txt-Datei \"" << path << "\" wurde erstellt.\n";
}	
