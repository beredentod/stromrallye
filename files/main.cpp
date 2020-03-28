#include<bits/stdc++.h>

using namespace std;

#define iPair pair<int, int>

struct battery
{
	int x, y, charge;
};

struct state
{
	vector<int> vis;
	int charges[150];
	int curch; //current charge
};

int M[150][150];
int S;
int N;

battery start;
vector <battery> batteries;
map<int, int> battery_dist[150];

queue<state> q;

int measureDistance(battery a, battery b)
{
	int dist = 0;
	dist = abs(a.x-b.x);
	dist += abs (a.y - b.y);
	return dist;
}

battery convertInput(string data)
{
	battery a;

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
	a.x = v[0];
	a.y = v[1];
	a.charge = stoi(data);

	return a;
}

pair<int, battery> readFile (string $FILENAME, int m[][150], vector<battery> *b)
{
	fstream file;
	string data;

	file.open($FILENAME, ios::in | ios::out);
	file>>data;

	int n = stoi(data);
	
	file>>data;
	battery st = convertInput(data);
	b->push_back(st);
	m[st.x][st.y] = st.charge;

	file>>data;
	int batt = stoi(data);
	for (int i=0;i<batt;i++)
	{
		file>>data;
		battery a = convertInput(data);
		b->push_back(a);
		m[a.x][a.y] = a.charge;
	}

	file.close();

	return make_pair(n, st);
}

void nextState(state s)
{
	int curr_node = s.vis[s.vis.size()-1];
	int curr_charge = s.curch;

	for (auto x: battery_dist[curr_node])
	{
		if (x.second <= curr_charge)
		{
			state next;
			next.vis = s.vis;
			next.vis.push_back(x.first);
			copy(s.charges, s.charges + N, next.charges);
			next.curch = next.charges[x.first];
			next.charges[x.first] = curr_charge-x.second;

			q.push(next);
		}
	}
}


int main ()
{
	int nummer;
	cin>>nummer;

	string $FILENAME, $OUTPUT;

	$FILENAME = "../input/stromrallye"+to_string(nummer)+".txt";

	auto res = readFile ($FILENAME, M, &batteries);
	S = res.first;
	start = res.second;

	state start_state;
	start_state.vis.push_back(0);
	
	N = batteries.size();

	for (int i=0;i<N;i++)
	{
		start_state.charges[i] = batteries[i].charge;
		for (int j=1;j<N;j++)
		{
			if (i == j)
				continue;

			battery_dist[i].insert(make_pair(j, measureDistance(batteries[i], batteries[j])));
		}
	}

	start_state.curch = start_state.charges[0];

	cout<<"\n";
	for (int i=0;i<N;i++)
	{
		cout<<i<<"->"<<start_state.charges[i]<<"\n";
		for (auto x: battery_dist[i])
			cout<<x.first<<": "<<x.second<<"\n";
		cout<<"\n";
	}

	q.push(start_state);

	/*while (!q.empty())
	{
		state curr = q.front();
		q.pop();

		vector<bool> v(N, 0);

		//cout<<"\nPath: ";
		for (auto x: curr.vis)
		{
			//cout<<x<<" ";
			v[x] = 1;
		}
		//cout<<"\nCurrent charge "<<curr.curch<<"\n";

		bool yes = 1;

		for (int i = 0; i < v.size(); ++i)
		{
			if (!v[i])
				yes = 0;
		}

		if (yes)
		{
			cout<<"Found!\n";
			cout<<"\nPath: ";
			for (auto x: curr.vis)
			{
				cout<<x<<" ";
			}
			cout<<"\nCurrent charge "<<curr.curch<<"\n";			
			break;
		}

		for (int i=1;i<N;i++)
			cout<<i<<"->"<<curr.charges[i]<<"\n";

		nextState(curr);
	}*/

	for (int i=1;i<=N;i++)
	{
		for (int j=1;j<=N;j++)
		{
			if (M[i][j] == 0)
				cout<<"  ";
			else
				cout<<M[i][j]<<" ";
		}
		cout<<"\n";
	}
}