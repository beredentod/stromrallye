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
