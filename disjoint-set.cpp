#include <bits/stdc++.h>
using namespace std;

// Here we will use union-find data structure to detect a cycle in an undirected graph.

class node {
public:
	int parent;
	int rank;
};

class unionfind {
private:
	vector<node> subset;
public:
	unionfind (int n) {
		subset.resize(n);
		for (int i=0; i<n; i++) {
			subset[i].parent = i;
			subset[i].rank = 0;
		}
	}

	int find (int x) {
		// 'path compression' optimization
		if (subset[x].parent != x) {
			subset[x].parent = find (subset[x].parent);
		}
		return subset[x].parent;
	}

	void _union (int x, int y) {
		// 'union by rank' optimization
		int xroot = this->find (x);
		int yroot = this->find (y);

		if (subset[xroot].rank < subset[yroot].rank) {
			subset[xroot].parent = yroot;
		} else if (subset[xroot].rank > subset[yroot].rank) {
			subset[yroot].parent = xroot;
		} else {
			subset[xroot].parent = yroot;
			subset[yroot].rank += 1;
		}

	}

};

int main () {
	int n_vertices, n_edges; cin >> n_vertices >> n_edges;
	vector<pair<int, int> > edges(n_edges);
	int v1, v2;
	for (int i=0; i<n_edges; i++) {
		cin >> v1 >> v2;
		edges[i] = make_pair(v1, v2);
	}
	unionfind A(n_vertices);
	bool detected = false;
	for (auto x : edges) {
		if (A.find(x.first) == A.find(x.second)) {
			cout << "Cycle detected while joining " << x.first << " and " << x.second << endl;
			detected = true;
			break;
		} else {
			A._union (x.first, x.second);
		}
	}
	if (!detected) {
		cout << "No cycle in the graph\n";
	}
	return 0;
}
