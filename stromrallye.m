
//die rekursive Funktion, die alle Moeglichkeiten ausprobiert
// id - Eingabeindex einer Batterie
// charge - die aktuelle Ladung
// status - das Array mit allen Ladungen jeweiliger Batterie; Array C
// result - das Array mit dem aktuellen Pfad vom Ursprung, Array R
bool Backtracking::next 
(int id, int charge, vector<int>& status, vector<iPair> &result)
{
	//das Array mit allen von id aus erreichbaren Batterien; Array N_id
	vector<pair<int,int>> neighbors = 
	checkReachability(id, charge, status);

	//der terminierende Fall
	//wenn die Liste von erreichbaren Batterien leer ist
	if (neighbors.empty())
	{
		//wenn die aktuelle Ladung 0 ist
		if (charge == 0)
		{
			//es word geprueft, ob alle Batterien entladen sind
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			//wenn ja, wird das Ergebnis gefunden
			if (all) 
			{
				//der Pfad mit Ergbenissen wird als foundPath
				//gespeichert
				foundPath = result;
				return 1;
			}

			//wenn nicht, wird 0 ausgegeben
			return 0;
		}
		//wenn es mindestens 2 batteriefreie Felder neben
		//der Batterie id gibt
		if (extraTiles[id] > 1)
		{
			//die restliche aktuelle Ladung wird an
			//den 2 batteriefreien Feldern verbraucht

			//-1 steht fuer ein beliebiges Feld
			//ein letzter Uebergang wird am ende des Arrays
			//result angehaengt
			result.pb(mp(-1, charge));

			//es wird geprueft, ob alle Batterien Entladen sind
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			//wenn ja, wird das Ergebnis gefunden
			if (all) 
			{
				//der Pfad mit Ergbenissen wird als foundPath
				//gespeichert
				foundPath = result;
				return 1;
			}

			//wenn nicht, wird 0 ausgegeben
			return 0;
		}
		//wenn es nur 1 batteriefreies Feld neben
		//der Batterie id gibt
		else if (extraTiles[id] == 1)
		{
			//die restliche aktuelle Ladung wird nur um 1 verkleinert
			//wenn nicht, wird 0 ausgegeben

			//-1 steht fuer ein beliebiges Feld
			//ein letzter Uebergang wird am ende des Arrays
			//result angehaengt
			result.pb(mp(-1, 1));

			//es wird geprueft, ob alle Batterien Entladen sind
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			//wenn ja und wenn die aktuelle Ladung entladen ist,
			//wird das Ergebnis gefunden
			if (all && charge == 0) 
			{
				//der Pfad mit Ergbenissen wird als foundPath
				//gespeichert
				foundPath = result;
				return 1;
			}

			//wenn nicht, wird 0 ausgegeben
			return 0;
		}
		//in allen anderen Faellen
		else
		{
			//ein Array mit allen minimalen Entfernungen der Batterien,
			//die erreicht werden koennen
			vector<iPair> allNeighbors;
			for (int i=1;i<dist[id].size();i++)
			{
				if (dist[id][i] <= charge && dist[id][i] != 0 && i != id)
					allNeighbors.pb(mp(dist[id][i], i));
			}

			//alle gefundenen minimalen Entfernungen werden absteigend sortiert
			sort(allNeighbors.rbegin(), allNeighbors.rend());

			//es wir durch das array mit allen gefunden Entfernungen iteriert
			for (auto x: allNeighbors)
			{
				//wenn eine gefundene Entfernung groesser ist als 2,
				//koennen wir die ganze restliche aktuelle Ladung verbrauchen
				if (x.first > 2)
				{
					//ein letzter Uebergang wird am ende des Arrays
					//result angehaengt
					result.pb(mp(x.second, charge));
					charge = 0;

					//so koennen wir die Iteration abbrechen
					break;
				}
				else
				{
					//ein letzter Uebergang wird am ende des Arrays
					//result angehaengt
					result.pb(mp(x.second, x.first));

					//die restliche aktuelle Ladung wird verbraucht
					charge -= x.first;

					//die folgenden Entfernungen werden nicht groesser,
					//so koennen wir die Iteration abbrechen
					break;
				}		
			}

			//es wird geprueft, ob alle Batterien Entladen sind
			bool all = 1;
			for (auto batt: status)
				if (batt > 0) all = 0;

			//wenn ja und wenn die aktuelle Ladung entladen ist,
			//wird das Ergebnis gefunden
			if (all && charge == 0) 
			{
				//der Pfad mit Ergbenissen wird als foundPath
				//gespeichert
				foundPath = result;
				return 1;
			}

			//wenn nicht, wird 0 ausgegeben
			return 0;
		}
	}

	//der Fall, wenn die Liste nicht leer ist
	for (auto x: neighbors)
	{
		//der Eingabeindex einer erreichbaren Batterie;
		//die erreichbare Batterie
		int neighID = x.first;
		//die minimale Entfernung von der Batterie id zur
		//erreichbaren Batterie
		int minDist = x.second;

		//das Array mit allen moeglichen Entfernungen zur erreichbaren
		//Batterie
		vector<int> neighDistances;
		//die minimale Entfernung wird als eine moegliche Entfernung
		//in das Array eingefuegt
		neighDistances.pb(minDist);

		//wenn die minimale Entfernung mindestens 3 betraegt
		if (minDist > 2)
		{
			//die naechste moegliche Entfernung
			int nextDist = minDist + 2;
			//wir pruefen, ob die Ladung reicht,
			//um die erreichbare Batterie in dieser Entfernung
			//zu erreichen
			while (charge >= nextDist)
			{
				//die neue Entfernung wird in das Array eingefuegt
				neighDistances.pb(nextDist);
				//eine neue Entfernung wird gebildet
				nextDist += 2;
			}
		}
		else
		{	
			//es wird geprueft, ob es eine andere Entfernung
			//von der Batterie id zur erreichbaren Batterie gibt,
			//die groesser ist als 2
			if (distAux[id][neighID] > 2)
			{
				//die naechste moegliche Entfernung
				int nextDist = distAux[id][neighID] + 2;
				//wir pruefen, ob die Ladung reicht,
				//um die erreichbare Batterie in dieser Entfernung
				//zu erreichen
				while (charge >= nextDist)
				{
					//die neue Entfernung wird in das Array eingefuegt
					neighDistances.pb(nextDist);
					//eine neue Entfernung wird gebildet
					nextDist += 2;
				}			
			}
		}
		
		//es wird durch das Array von moeglichen Entfernungen iteriert
		for (auto y: neighDistances)
		{
			//die naechste aktuelle Ladung
			int nextCharge = status[neighID];
			
			//eine Kopie des Arrays status
			vector<int> cpstatus = status;
			//eine Kopie des Arrays result
			vector<iPair> cpresult = result;

			//die aktuelle Ladung wird verbraucht
			cpstatus[neighID] = charge - y;

			//die erreichbare Batterie mit deraktuellen Entfernung
			//wird am Ende des Arrays mit Ergbenissen angehaengt
			cpresult.pb(mp(neighID, y));	

			//ein rekursiver Aufruf mit neighID als naechste Batterie,
			//nextCharge als die naechste aktuelle Ladung,
			//cpstatus als das Array mit allen Ladungen und
			//cpresult als das Array mit den Ergebnissen
			bool found = next(neighID, nextCharge, cpstatus, cpresult);

			if (found)
				return 1; //wenn alle Batterien entladen sind
			else
				cpresult.pop_back(); //das letzte Element aus 
		}
	}

	return 0;
}

//eine Funktion, die die erreichbaren Batterien von einer Batterie 
//ID aus bestimmt
// ID - Eingabeindex einer Batterie
// charge - die aktuelle Ladung
// currCharges - das aktuelle Array C (=status)
vector<pair<int,int>> Backtracking::checkReachability 
(int ID, int charge, vector<int>& currCharges)
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
