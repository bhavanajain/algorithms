#include <bits/stdc++.h>
using namespace std;

template<typename T>
class node {
public:
	T key;
	node* left;
	node* right;
	node* parent;
	node (T key, node* left = NULL, node* right = NULL, node* parent = NULL) {
		this->key = key;
		this->left = left;
		this->right = right;
		this->parent = parent;
	}
};

template<typename T>
class binary_search_tree {
private:
	node<T>* root;

public:
	binary_search_tree() {
		this->root = NULL;
	}

	bool isempty() {
		return (this->root == NULL);
	}
	
	bool search (T key) {
		if (this->isempty()) {
			return false;
		}
		node<T>* result = search_util (this->root, key);
		return (result->key == key);
	}

	node<T>* search_util (node<T>* curr, T key) {
		if (curr->key == key) {
			return curr;
		} else if (curr->key < key) {
			return (curr->right == NULL) ? curr : search_util(curr->right, key);
		} else {
			return (curr->left == NULL) ? curr : search_util(curr->left, key);
		}
	}

	node<T>* insert_util (node<T>* curr, node<T>* temp) {
		if (curr->key < temp->key) {
			if (curr->right != NULL) {
				return insert_util (curr->right, temp);
			} else {
				curr->right = temp;
				temp->parent = curr;
			}
		} else {
			if (curr->left != NULL) {
				return insert_util (curr->left, temp);
			} else {
				curr->left = temp;
				temp->parent = curr;
			}
		}
		return temp;
	}
	
	// Note: Duplicates are allowed while inserting
	node<T>* insert(T key) {
		node<T>* temp = new node<T>(key);
		if (this->isempty()) {
			this->root = temp;
			return temp;
		}
		return insert_util (this->root, temp);
	}
	
	void inorder() {
		cout << "In-order Traversal ==> ";
		inorder_util(this->root);
		cout << endl;
	}
	void inorder_util (node<T>* temp) {
		if (temp != NULL) {
			inorder_util (temp->left);
			cout << temp->key << " ";
			inorder_util (temp->right);
		}
	}

	void preorder() {
		cout << "Pre-order Traversal ==> ";
		preorder_util (this->root);
		cout << endl;
	}
	void preorder_util (node<T>* temp) {
		if (temp != NULL) {
			cout << temp->key << " ";
			preorder_util (temp->left);
			preorder_util (temp->right);
		}
	}

	void postorder() {
		cout << "Post-order Traversal ==> ";
		postorder_util (this->root);
		cout << endl;
	}
	void postorder_util (node<T>* temp) {
		if (temp != NULL) {
			postorder_util (temp->left);
			postorder_util (temp->right);
			cout << temp->key << " ";
		}
	}

	int find_height_util (node<T>* temp) {
		if (temp == NULL) {
			return 0;
		} else {
			return 1 + max (find_height_util (temp->left), find_height_util (temp->right));
		}
	}

	int find_height () {
		return find_height_util (this->root);
	}

	void remove_leaf (node<T>* temp) {
		if (temp->left == NULL && temp->right == NULL) {
			if (temp->parent) {
				if (temp->parent->left == temp) {
					temp->parent->left = NULL;
				} 
				else {
					temp->parent->right = NULL;
				}
			} else {
				this->root = NULL;
			}
			free (temp);
		} 	
	}

	node<T>* remove (T key) {
		node<T>* result = search_util (this->root, key);
		if (result->key == key) {
			return remove (result);
		}
		return this->root;
	}

	node<T>* remove (node<T>* target) {
		if (target->left && target->right) {
			node<T>* pred = find_predecessor (target);
			target->key = pred->key;
			return remove (pred);
		} else if (target->left || target->right) {
			node<T>* child = (target->left != NULL) ? target->left : target->right;
			if (target->parent == NULL) {
				this->root = child;
				child->parent = NULL;
			} else if (target->parent->left == target) {
				target->parent->left = child;
				child->parent = target->parent;
			} else {
				target->parent->right = child;
				child->parent = target->parent;
			}
			free (target);
		} else {
			remove_leaf (target);
		}
		return this->root;	
	}
	
	node<T>* find_minimum () {
		return minimum_util (this->root);
	}
	node<T>* minimum_util (node<T>* temp) {
		while (temp->left != NULL)
			temp = temp->left;
		return temp;
	}

	node<T>* find_maximum () {
		return maximum_util (this->root);
	}
	node<T>* maximum_util (node<T>* temp) {
		while (temp->right != NULL)
			temp = temp->right;
		return temp;
	}

	// returns NULL if predecessor / successor does not exist (in the tree, ofcourse)
	node<T>* find_predecessor (T x) {
		node<T>* result = search_util (this->root, x);
		if (result->key < x) {
			return result;
		} 
		return find_predecessor (result);
	}
	node<T>* find_predecessor (node<T>* temp) {
		if (temp->left != NULL) {
			return maximum_util (temp->left);
		} else {
			node<T>* p = temp->parent;
			while (p && p->left == temp) {
				temp = p;
				p = p->parent;			
			}
			return p;
		}
	}
	node<T>* find_successor (T x) {
		node<T>* result = search_util (this->root, x);
		if (result->key > x) {
			return result;
		}
		return find_successor (result);
	}
	node<T>* find_successor (node<T>* temp) {
		if (temp->right != NULL) {
			return minimum_util (temp->right);
		} else {
			node<T>* p = temp->parent;
			while (p && p->right == temp) {
				temp = p;
				p = p->parent;
			}
			return p;
		}
	}
};
