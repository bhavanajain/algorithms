#include <bits/stdc++.h>
using namespace std;

// Kruskal returns MST class
class MST {
private:
	vector<pair<int, int> > edges;
	int total_wt;
	int max_size;
public:
	MST (int max_size) {
		total_wt = 0;
		this->max_size = max_size;
	}
	void add (pair<int, int> edge, int weight) {
		if (this->isfull()) {
			cout << "The MST has reached its maximum size\n";
			return;
		}
		edges.push_back(edge);
		total_wt += weight;
	}

	bool isfull () {
		return (edges.size() == max_size);
	}
	void print () {
		cout << "Edges: \n";
		for (auto x : edges) {
			cout << x.first << " " << x.second << endl;
		}
		cout << "Total weight: " << total_wt << endl;
	}
};

struct node {
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

	void _print () {
		for (int i=0; i<subset.size(); i++) {
			cout << i << " " << subset[i].parent << " " << subset[i].rank << endl;
		}
	}
};

MST kruskal (multimap<int, pair<int, int> > &weights_edges, int n_vertices) {
	unionfind A(n_vertices);
	MST B (n_vertices-1);
	for (auto x : weights_edges) {
		int weight = x.first;
		pair<int, int> edge = x.second;
		if (A.find(edge.first) != A.find(edge.second)) {
			A._union (edge.first, edge.second);
			B.add(edge, weight);
			if (B.isfull())
				break;
		}
	}
	return B;
}

int main() {
	int n_vertices, n_edges; cin >> n_vertices >> n_edges;
	multimap<int, pair<int, int> > weights_edges;
	int src, dest, weight;
	for (int i=0; i<n_edges; i++) {
		cin >> src >> dest >> weight;
		weights_edges.insert(make_pair(weight, make_pair (src, dest)));
	}
	cout << "Minimum spanning tree: \n";
	MST B = kruskal (weights_edges, n_vertices);
	B.print();
	return 0;
}