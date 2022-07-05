#pragma once

#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>

using namespace std;

class Autocompleter
{
	// For the mandatory running times below:
	// n is the number of strings in the dictionary.
	// Assume that the length of every string is O(1).

public:

	Autocompleter();


	void insert(string x, int freq);


	int size();


	void completions(string x, vector<string>& T);


	int height()
	{
		return height(root);
	}

private:
	// A helper class that stores a string and a frequency.
	class Entry
	{
	public:
		string s;
		int freq=0;
	};

	// A helper class that implements a binary search tree node.
	class Node
	{
	public:
		Node()
		{
			height = 0;
			left = right = nullptr;
		}

		Node(Entry e)
		{
			this->e = e;
			height = 0;
			left = right = nullptr;
		}

		Entry e;
		int height;
		Node* left;
		Node* right;
	};

	// A convenience method for getting the height of a subtree.
	// Useful for rebalance().
	static int height(Node* root)
	{
		if (root == nullptr)
			return -1;
		return root->height;
	}

	// Root of the binary-search-tree-based data structure
	Node* root;



	int size_recurse(Node* root);


	void completions_recurse(string x, Node* root, vector<Entry>& C);


	void insert_recurse(Entry e, Node*& root);


	void rebalance(Node*& root);


	void right_rotate(Node*& root);
	void left_rotate(Node*& root);
};

#endif
