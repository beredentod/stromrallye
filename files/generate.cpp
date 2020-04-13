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

vector<int> Generator::generateDistances()
{
	vector<int> num;
	stack<iPair> help;

	help,push(mp(order[0], 0));

	for (int i=1; i < order.size(); i++)
	{
		int index = order[i];
		int nextIndex = order[i+1];

		int dist = rand()%5 + 1;

		num.pb(dist);
	}	


	return num;
}
 