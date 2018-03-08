#include "binary_search_tree.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
	binary_search_tree<string> A;
	A.inorder();
	A.insert ("monkey");
	A.insert ("giraffe");
	A.insert ("giraffe");
	A.insert ("bear");
	A.insert ("ant");
	A.insert ("cat");
	A.insert ("dog");
	A.insert ("panther");
	A.insert ("zebra");
	A.inorder();
	A.remove ("monkey");
	A.inorder();
	A.remove ("giraffe");
	A.inorder();
	A.remove ("giraffe");
	A.inorder();
	A.remove ("dog");
	A.inorder();
	A.remove ("cat");
	A.inorder();
	A.remove ("bear");
	A.inorder();
	A.remove ("ant");
	A.inorder();
	A.remove ("panther");
	A.inorder();
	A.remove ("zebra");
	A.inorder();

	return 0;
}