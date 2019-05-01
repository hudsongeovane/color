#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

bool compare(pair< int,set<int> > a, pair< int, set<int> > b) {
	return a.second.size() > b.second.size();
}

bool haveNeighborWithColorX(vector< pair< int,set<int> > > & listas, vector<int> & colors, int v, int color) {
	for(int i = 0; i < listas.size(); i++) {
		if (listas[i].first == v) {
			for(set<int>::iterator x = listas[i].second.begin(); x != listas[i].second.end(); x++) {
				if (colors[(*x)] == color) return true;
			}
			return false;
		}
	}
	cout << "ERROR!" << endl;
	return false;
}

void printSet(set<int> & s) {
	for(set<int>::iterator x = s.begin(); x != s.end(); x++) {
		cout << *x << " ";
	}
	cout << endl;
}
void printSol(vector<int> & s) {
	int maximum = 0;
	for(vector<int>::iterator x = s.begin(); x != s.end(); x++) {
		cout << *x << " ";
		maximum = max(maximum,*x);
	}
	cout << endl;
	cout << "Number of Colors: " << maximum << endl;
}

int main() {
	char a;
	int n, m, c;
	cin >> a >> n >> m >> c;
	cout << n << endl;
	vector<int> grau(n,0);
	vector< pair< int,set<int> > > listas;

	for(int i = 0; i < n; i++) {
		listas.push_back(make_pair(i,set<int>()));
	}
	int from, to;
	while(cin >> a >> from >> to) {
		from--; to--;
		listas[from].second.insert(to);
		listas[to].second.insert(from);
	}

	for(int i = 0; i < n; i++) {
		grau[i] = listas[i].second.size();
	}
	vector<int> colors(n,0);	

	map<int,int> l;
	l[0] = 1;

	sort(listas.begin(),listas.end(),compare);
	//NOW THE BROWN ALGORITHM
	colors[listas[0].first] = 1;
	int i = 1, k = n, q = 1;
	bool updateU = true;
	vector< set<int> > Ui(n,set<int>());
	while (i > 0) {
		if (updateU) {
			Ui[i].clear();
			for(int ii=1; ii <= q+1; ii++) {
				if (!haveNeighborWithColorX(listas,colors,listas[i].first,ii)) { Ui[i].insert(ii); }
			}
		}
		int j;
		if (Ui[i].size() == 0) {
			i--;
			q = l[i];
			updateU = false;
		}
		else {
			j = *(Ui[i].begin());
			colors[listas[i].first] = j;
			Ui[i].erase(j);
			if (j < k) {
				if (j > q) {
					q++;
				}
				if (i == n-1) {
					printSol(colors);
					k = q;
					j = 999999;
					for(int ii = 0; ii < n; ii++) {
						if (colors[listas[ii].first] == k) { j = min(j,ii); }
					}
					i = j-1;
					q = k-1;
					updateU = false;
				}
				else {
					l[i] = q;
					i = i+1;
					updateU = true;
				}
			}
			else {
				i--;
				q = l[i];
				updateU = false;
			}
		}
	}
	cout << k << endl;
	cout << "Number of Optimal Solution:" << c << endl;
}

