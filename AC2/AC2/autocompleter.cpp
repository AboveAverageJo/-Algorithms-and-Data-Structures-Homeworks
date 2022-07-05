#include "autocompleter.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

// Creates a new Autocompleter with an empty dictionary.
//
// Must run in O(1) time.
Autocompleter::Autocompleter()
{
	root = NULL;
}


// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(log(n)) time.
void Autocompleter::insert(string x, int freq)
{
	Entry e;
	e.s = x;
	e.freq = freq;

	insert_recurse(e, root);
}


// Returns the number of strings in the dictionary
// of possible completions.
//
// Must run in O(n) time.
int Autocompleter::size()
{
	return size_recurse(root);
}


// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
//
// Must run in O(log(n) + k) time,
// where k is the number of completions of x in the dictionary.
void Autocompleter::completions(string x, vector <string>& T)
{
	vector<Entry> top3;

	completions_recurse(x, root, top3);

	if (top3.size() == 0)
	{
		T.resize(0);
	}
	else if (top3.size() == 1)
	{
		T.resize(1);
		T[0] = top3[0].s;
	}
	else if (top3.size() == 2)
	{
		T.resize(2);
		T[0] = top3[0].s;
		T[1] = top3[1].s;
	}
	else
	{
		T.resize(3);
		T[0] = top3[0].s;
		T[1] = top3[1].s;
		T[2] = top3[2].s;
	}
}


// Optional helper methods (you'll probably want them)

// Returns the size of the binary tree rooted at root.
//
// Should run in O(n) time.
int Autocompleter::size_recurse(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + size_recurse(root->left) + size_recurse(root->right);
	}
}


// Fills C with the completions of x in the BST rooted at root.
//
// Should run in O(log(n) + k), where
// -n is the size of the BST rooted at root.
// -k is the number of Entrys in the BST rooted at root
//  whose strings start with x.
void Autocompleter::completions_recurse(string x, Node* root, vector<Entry>& C)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (x == root->e.s.substr(0, x.length()))
		{
			if (C.size() == 0)
			{
				C.push_back(root->e);
			}
			else if (C.size() == 1)
			{
				C.push_back(root->e);
				if (C[0].freq < C[1].freq)
				{
					swap(C[0].freq, C[1].freq);
					swap(C[0].s, C[1].s);
				}
			}
			else if (C.size() == 2)
			{
				for (int i = 0; i < C.size(); i++)
				{
					if (root->e.freq > C[i].freq)
					{
						C.insert(C.begin() + i, root->e);
						break;
					}
				}
				if (C.size() == 2)
				{
					C.push_back(root->e);
				}
			}
			else if (C.size() == 3)
			{
				for (int i = 0; i < C.size(); i++)
				{
					if (root->e.freq > C[i].freq)
					{
						C.insert(C.begin() + i, root->e);
						C.pop_back();
						break;
					}
				}
			}
			completions_recurse(x, root->left, C);
			completions_recurse(x, root->right, C);

		}
		else if (x < root->e.s.substr(0, x.length()))
		{
			completions_recurse(x, root->left, C);
		}
		else if (x > root->e.s.substr(0, x.length()))
		{
			completions_recurse(x, root->right, C);
		}
	}
}


// Inserts an Entry into an AVL tree rooted at root.
//
// Should run in O(log(n)) time.
void Autocompleter::insert_recurse(Entry e, Node*& root)
{
	if (root == NULL)
	{
		root = new Node(e);
		return;
	}
	else
	{
		if (root->e.s < e.s)
		{
			insert_recurse(e, root->right);
		}
		else if (root->e.s > e.s)
		{
			insert_recurse(e, root->left);
		}
		else if (root->e.s == e.s)
		{
			return;
		}
		root->height = max(height(root->left), height(root->right)) + 1;

		rebalance(root);


	}
}


// Rebalances the AVL tree rooted at root.
// Helpful for insert().
// Should be called on every node visited during
// the search in reverse search order.
//
// Should run in O(1) time.
void Autocompleter::rebalance(Node*& root)
{
	if (abs(height(root->left) - height(root->right)) == 2)
	{

		int l = height(root->left);
		int r = height(root->right);


		if (l > r)
		{

			if (height(root->left->left) > height(root->left->right))
			{
				right_rotate(root);
			}
			else
			{
				left_rotate(root->left);
				right_rotate(root);
			}

		}
		else if (r > l)
		{

			if (height(root->right->right) > height(root->right->left))
			{
				left_rotate(root);
			}
			else
			{
				right_rotate(root->right);
				left_rotate(root);
			}

		}
	}
}

// Perform left and right rotations around the root
// of an AVL tree (helpful for implementing rebalance).
//
// Should run in O(1) time.
void Autocompleter::right_rotate(Node*& root)
{
	Node* a = root;
	Node* b = root->left;
	Node* br = b->right;

	root = b;
	b->right = a;
	a->left = br;

	a->height = max(height(root->left), height(root->right)) + 1;
	b->height = max(height(root->left), height(root->right)) + 1;
}

void Autocompleter::left_rotate(Node*& root)
{
	Node* a = root;
	Node* b = root->right;
	Node* bl = b->left;


	root = b;
	b->left = a;
	a->right = bl;

	a->height = max(height(root->left), height(root->right)) + 1;
	b->height = max(height(root->left), height(root->right)) + 1;
}