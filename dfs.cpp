/*
DFS tree generation and edge classification for Directed Graphs

Input format:
<number of vertices> <number of edges>
Then <number of edges> lines follow. Edge is input as <src vertex> <dest vertex>.
*/

#include <bits/stdc++.h>
using namespace std;

int timer = 0;

enum color {white, gray, black};
vector<color> vertex_color;
vector<int> parent;
vector<int> discovery_time;
vector<int> finish_time;
vector<pair<int, int> > forward_edges;
vector<pair<int, int> > backward_edges;
vector<pair<int, int> > cross_edges;
vector<pair<int, int> > tree_edges;

void dfs_visit (vector<vector<int> > &adj_list, int u) {
	vertex_color[u] = gray;
	discovery_time[u] = ++timer;
	for (auto v : adj_list[u]) {
		if (vertex_color[v] == white) {
			parent[v] = u;
			tree_edges.push_back(make_pair(u, v));
			dfs_visit (adj_list, v);
		} else if (vertex_color[v] == gray) {
			backward_edges.push_back(make_pair(u, v));
		} else {
			if (discovery_time[u] < discovery_time[v]) {
				forward_edges.push_back(make_pair(u, v));
			} else {
				cross_edges.push_back(make_pair(u, v));
			}
		}
	}
	vertex_color[u] = black;
	finish_time[u] = ++timer;
}

void dfs(vector<vector<int> > &adj_list) {
	for (int i=0; i<adj_list.size(); i++) {
		if (vertex_color[i] == white) {
			dfs_visit(adj_list, i);
		}
	}
}

int main() {
	int n_vertices, n_edges; cin >> n_vertices >> n_edges;

	vertex_color.resize(n_vertices, white);
	parent.resize(n_vertices, -1);
	discovery_time.resize(n_vertices, 0);
	finish_time.resize(n_vertices, 0);

	vector<vector<int> > adj_list(n_vertices);
	
	int src, dest;
	for (int i=0; i<n_edges; i++) {
		cin >> src >> dest;
		adj_list[src].push_back(dest);
	}

	dfs(adj_list);

	cout << "Tree edges: \n";
	for (auto x : tree_edges) {
		cout << x.first << " " << x.second << endl;
	}
	cout << "Back edges: \n";
	for (auto x : backward_edges) {
		cout << x.first << " " << x.second << endl;
	}
	cout << "Forward edges: \n";
	for (auto x : forward_edges) {
		cout << x.first << " " << x.second << endl;
	}
	cout << "Cross edges: \n";
	for (auto x : cross_edges) {
		cout << x.first << " " << x.second << endl;
	}

}