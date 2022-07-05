#include "autocompleter.h"


using namespace  std;



// Creates a dictionary of strings and associated frequencies,
// using the file as a source. The file is promised to have
// the following format:
// 
// string1 freq1
// string2 freq2
// ...
// stringN freqN
//
// where string1 < string2 < ... < stringN 
// 
// Must run in O(n) time.
Autocompleter::Autocompleter(string filename)
{
	vector<Entry> words;
	ifstream infile;
	infile.open(filename);

	while(infile)
	{

		Entry Eword;

		infile >> Eword.s;
		infile >> Eword.freq;
		
		if (Eword.s == "")
		{
			break;
		}
		words.push_back(Eword);
	}

	root = construct_recurse(words,0, words.size()-1);
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
// If x has less than three completions, 
// then T is filled with all completions of x.
		// The completions appear in T from most- to least-frequent.
		// 
		// Must run in O(log(n) + k) time,
// where k is the number of completions of x in the dictionary.
void Autocompleter::completions(string x, vector<string>& T)
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

// Optional helper methods (you'll probably want them).

// Returns the root of a BST containing the elements
// of the portion of a sorted vector E from index l to r.
//
// Should run in O(r-l) time.
Autocompleter::Node*::Autocompleter::construct_recurse(vector<Entry>& E, int l, int r)
{
	if (l > r)
	{
		return nullptr;
	}
	int m = (l + r) / 2;
	Node* root = new Node(E[m]);

	root->left = construct_recurse(E, l, m - 1);
	root->right = construct_recurse(E, m + 1, r);

	return root;
}

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

// Fills T with the three most-frequent completions of x
// that are either:
// -In the BST rooted at root.
// -Already in T.
//
// Should run in O(log(n) + k), where
// -n is the size of the BST rooted at root.
// -k is the number of Entrys in the BST rooted at root
//  whose strings start with x.
void Autocompleter::completions_recurse(string x, Node* root, vector<Entry>& T)
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		if (x == root->e.s.substr(0, x.length()))
		{
			if(T.size() == 0)
			{
				T.push_back(root->e);
			}
			else if(T.size() == 1)
			{
				T.push_back(root->e);
				if (T[0].freq < T[1].freq)
				{
					swap(T[0].freq, T[1].freq);
					swap(T[0].s, T[1].s);
				}
			}
			else if (T.size() == 2)
			{
				for (int i = 0; i < T.size(); i++)
				{
					if (root->e.freq > T[i].freq)
					{
						T.insert(T.begin() + i, root->e);
						break;
					}
				}
				if (T.size() == 2)
				{
					T.push_back(root->e);
				}
			}
			else if (T.size() == 3)
			{
				for (int i = 0; i < T.size(); i++)
				{
					if (root->e.freq > T[i].freq)
					{
						T.insert(T.begin() + i, root->e);
						T.pop_back();
						break;
					}
				}
			}
			completions_recurse(x, root->left, T);
			completions_recurse(x, root->right, T);

		}
		else if(x < root->e.s.substr(0, x.length()))
		{
			completions_recurse(x, root->left, T);
		}
		else if(x > root->e.s.substr(0, x.length()))
		{
			completions_recurse(x, root->right, T);
		}
	}
}