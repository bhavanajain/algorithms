#include <bits/stdc++.h>
using namespace std;

struct node {
	unordered_map<char, node*> children;
	int n_prefixes;
	bool end_of_word;
	node () {
		n_prefixes = 0;
		end_of_word = false;
	}
};

class trie {
	node* root;
public:
	trie () {
		this->root = NULL;
	}
	void insert (string word) {
		if (this->root == NULL) {
			this->root = new node;
		}
		node* temp = this->root;
		for (auto c : word) {
			if (temp->children.find(c) == temp->children.end()) {
				temp->children[c] = new node;
				temp->children[c]->n_prefixes = 1;
			} else {
				temp->children[c]->n_prefixes += 1;
			}
			temp = temp->children[c];
		}
		temp->end_of_word = true;
	}

	string unique_prefix (string word) {
		node* temp = this->root;
		string prefix = "";
		for (auto c: word) {
			prefix += c;
			if (temp->children[c]->n_prefixes > 1) {
				temp = temp->children[c];
			} else {
				break;
			}
		}
		return prefix;
	}
};
