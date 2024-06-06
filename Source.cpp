#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <fstream>
#include <string>
#include <map>
using namespace std;

const int INF = 1000000000;
struct vert {
	int x;
	int y;
	int i;
};
struct edge {
	int u;
	int v;

	edge(int u, int v) : u(u), v(v) {}
};

int n;
vector < vector < pair < int, int > > > g;
vector < vector < int > > g1;
vector< pair < int, edge > > e;
vector<vert> v;

vector<pair<int, int>> star_e_rec;
vector<pair<int, int>> star_e;
int recL = INF;

set<int> not_connected;
set<int> connected;

int globalMin = INF;
void solve() {
	random_shuffle(v.begin(), v.end());

	for (int i = 0; i < n; ++i)
		g[i].clear();
	vector<int> d(n);
	star_e_rec.clear();

	for (int i = 0; i < n; ++i) {
		vert vr = v[i];

		for (int j = 0; j < i; ++j) {
			int dist = abs(v[j].x - vr.x) + abs(v[j].y - vr.y);
			g[i].push_back({ j, dist });
			g[j].push_back({ i, dist });
			g1[i][j] = dist;
			g1[j][i] = dist;
		}
	}
	int resL = 0;

	//создаем граф
	for (int i = 0; i < n; ++i) {
		set<int> has;
		while (d[i] < 3) {
			int recU = -1, recD = INF;
			for (int j = 0; j < n; ++j) {
				if (i != j && !has.count(j) && d[j] < 3 && g1[i][j] < recD) {
					recD = g1[i][j];
					recU = j;
				}
			}

			has.insert(recU);
			star_e_rec.push_back({ i, recU });
			d[i]++;
			d[recU]++;

			resL += g1[i][recU];
		}
	}

	if (resL < globalMin) {
		globalMin = resL;

		int maxEdge = 0;
		for (auto e : star_e_rec) {
			maxEdge = max(maxEdge, g1[e.first][e.second]);
		}

		ofstream myfile("solution.txt");
		myfile << "c Вес кубического подграфа = " << resL << ", самое длинное ребро = " << maxEdge << "," << endl;
		myfile << "p edge " << n << " " << star_e_rec.size() << endl;
		for (auto e : star_e_rec)
			myfile << "e " << v[e.first].i + 1 << " " << v[e.second].i + 1 << endl;
	}
}

void gen() {
	freopen("INPUT.TXT", "r", stdin);
	string _; cin >> _; cin >> _;

	cin >> n;
	int x, y;
	srand(time(0));
	g.resize(n, vector < pair < int, int > >());
	g1.resize(n, vector<int>(n));

	for (int i = 0; i < n; ++i) {
		vert vr;
		cin >> vr.x >> vr.y;
		vr.i = i;

		v.push_back(vr);
	}

	while (1)
		solve();
}

int main() {
	gen();
}