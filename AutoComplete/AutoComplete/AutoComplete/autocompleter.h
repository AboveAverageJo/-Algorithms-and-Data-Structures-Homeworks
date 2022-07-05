#pragma once

#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

class Autocompleter
{
	// For the mandatory running times below:
	// n is the number of strings in the dictionary.
	// Assume that the length of every string is O(1). 

public:

	Autocompleter(string filename);


	int size();


	void completions(string x, vector<string>& T);

private:
	// A helper class that stores a string and a frequency.
	class Entry
	{
	public:
		string s;
		int freq;
	};

	// A helper class that implements a BST node.
	class Node
	{
	public:
		Node()
		{
			left = right = nullptr;
		}

		Node(Entry e)
		{
			this->e = e;
			left = right = nullptr;
		}

		Entry e;
		Node* left;
		Node* right;
	};

	// Root of the binary-search-tree-based data structure
	Node* root;

	Node* construct_recurse(vector<Entry>& E, int l, int r);


	int size_recurse(Node* root);


	void completions_recurse(string x, Node* root, vector<Entry>& T);
};


#endif
