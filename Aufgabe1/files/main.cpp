#include<bits/stdc++.h>
#include "setup.h"
#include "graph.h"
#include "backtracking.h"
#include "generate.h"

using namespace std;

int main ()
{

	cout<< "Möchten Sie ein Beispiel lösen oder generieren? (l - lösen, g - generieren): ";
	string rep;
	cin>>rep;

	if (rep == "g" || rep == "G")
	{
		cout << "Geben Sie bitte die Anzahl der Batterien (mind. 1): ";
		int num;
		cin>>num;

		Generator gen(num);

		cout << "Geben Sie bitte eine Nummer für das generierte Beispiel: ";
		int nummer = 1000;
		cin>>nummer;

		string $PATH = "../output/stromrallye"+to_string(nummer)+".txt";
		gen.save($PATH);
	}
	else if (rep == "l" || rep == "L")
	{
		int nummer;
		cout << "Geben Sie bitte die Nummer des Beispiels ein: ";
		cin>>nummer;

		cout << "Schräge Übergänge erlauben? (j/n): ";
		cin >> rep;

		if (rep == "j" || rep == "J")
		{
			string $FILENAME = "../input/stromrallye"+to_string(nummer)+".txt";
			Graph G($FILENAME, true);
			Backtracking back(G);
		}
		else if (rep == "n" || rep == "N")
		{
			string $FILENAME = "../input/stromrallye"+to_string(nummer)+".txt";
			Graph G($FILENAME);
			Backtracking back(G);
		}
		else
		{
			cout << "Eingabe nicht erkannt. Schräge Übergänge ausgeschaltet.\n";
			string $FILENAME = "../input/stromrallye"+to_string(nummer)+".txt";
			Graph G($FILENAME);
			Backtracking back(G);
		}
	}


	return 0;
}