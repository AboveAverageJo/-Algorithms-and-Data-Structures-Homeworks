#include "autocompleter.h"

using namespace std;

void Autocompleter::insert(string x, int freq)
{
	Node* current = root;

	Entry n;
	n.freq = freq;
	n.x = x;
	//adding the top 3 freqs of all words that come in
	current = current->children[""[0]];
	if (current->top.empty())
	{
		current->top.push_back(n);
	}
	else if (current->top.size() < 3)
	{
		if (current->top.size() == 1)
		{
			current->top.push_back(n);
			if (current->top[0].freq < current->top[1].freq)
			{
				swap(current->top[0], current->top[1]);
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				if (current->top[i].freq < freq)
				{
					current->top.insert(current->top.begin() + i, n);
					break;
				}
			}
			if (current->top.size() == 2)
				current->top.push_back(n);
		}
	}
	
	else
	{
		for (int i = 0; i < 3; i++)
		{
			if (current->top[i].freq < freq)
			{
				current->top.insert(current->top.begin() + i, n);
				current->top.pop_back();
				break;
			}
		}
	}

	
	////////////////////////////////////////////////////////////////////
	for (int i = 0; i < x.length(); i++)
	{
		bool nn = false;

		//making new node if it doesn't exist
		if (current->children[x[i]] == NULL)
		{
			current->children[x[i]] = new Node();
			current = current->children[x[i]];
			nn = true;
		}
		else if (nn == false)
		{
			current = current->children[x[i]];
		}
			//inserting entry in each node
			if (current->top.empty())
			{
				current->top.push_back(n);
			}
			else if (current->top.size() < 3)
			{

				//sorting top 
				if (current->top.size() == 1)
				{
					current->top.push_back(n);
					if (current->top[0].freq < current->top[1].freq)
					{
						swap(current->top[0], current->top[1]);
					}
				}
				else
				{
					for (int i = 0; i < 2; i++)
					{
						if (current->top[i].freq < freq)
						{
							current->top.insert(current->top.begin() + i, n);
							break;
						}
					}
					if (current->top.size() == 2)
						current->top.push_back(n);
				}
			}
			//keeping track of the top 3 entries in each node
			else
			{
				for (int i = 0; i < 3; i++)
				{
					if (current->top[i].freq < freq)
					{
						current->top.insert(current->top.begin() + i, n);
						current->top.pop_back();
						break;
					}
				}
			}

	}
	current->marked = true;
	count = count++;
}

Autocompleter::Autocompleter()
{
	root = new Node();
	root->children[""[0]] = new Node();
	count = 0;
}

// Returns the number of strings in the dictionary.
//
// Must run in O(1) time.
int Autocompleter::size()
{
	return count;
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
//
// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string>& T)
{
	while (!T.empty())
	{
		T.pop_back();
	}

	Node* current = root->children[""[0]];

	if (x == "")
	{
		T.push_back(current->top[0].x);
		T.push_back(current->top[1].x);
		T.push_back(current->top[2].x);
	}
	else
	{
		for (int i = 0; i < x.length(); i++)
		{
			if (current->children[x[i]] == NULL)
				return;

			current = current->children[x[i]];
		}
		for (int i = 0; i < current->top.size(); i++)
		{
			string s = current->top[i].x;
			T.push_back(s);

		}
	}
}

int Autocompleter::number_completions(string x)
{
	Node* current = root->children[""[0]];
	

	for (int i = 0; i < x.length(); i++)
	{
		current = current->children[x[i]];
	}

	return size(current);
}

int Autocompleter::size(Node* p)
{	
	int count =0;

	if (p == NULL)
	{
		return 0;
	}
	else
	{
		if (p->marked == true)
		{
			count++;
		}
		for (int i = 0; i < 256; i++)
		{
			count += size(p->children[i]);
		}
	}
	
	return count;
}