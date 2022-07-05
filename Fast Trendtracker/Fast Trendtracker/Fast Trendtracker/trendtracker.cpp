#include "trendtracker.h"
#include <algorithm>
using namespace std;


// For the mandatory running times below:
// n is the number of hashtags in the Trendtracker.




	// Creates a Trendtracker containing hashtags 
	// found in the provided file.
	// The file is promised to have the following format: 
	// 
	// string1 
	// string2 
	// ...
	// stringN 
	//
	// where string1 < string2 < ... < stringN 
	// 
	// Must run in O(n) time.
Trendtracker::Trendtracker(string filename)
{
	ifstream infile;
	
	infile.open(filename);

	for (int i = 1; i < 4; i++)
	{
		S.push_back(i);
	}

	while (infile)
	{
		Entry has;
		string htg;
		infile >> htg;

		if (htg == "")
		{
			return;
		}
		else
		{
			has.hashtag = htg;
			has.pop = 0;
			E.push_back(has);
		}
	}





	infile.close();
}

// Return the number of hashtags in the Trendtracker.
//
// Must run in O(1) time.
int Trendtracker::size()
{
	return E.size();
}

// Adds 1 to the total number times a hashtag has been tweeted.
// If the hashtag does not exist in TrendTracker, does nothing.
//
// Must run in O(log(n)) time.
void Trendtracker::tweeted(string ht)
{
	int popu = search(ht);
	if (popu == -1)
	{
		return;
	}
	else if (E.size() == 1)
	{
		E[popu].pop++;
		S.pop_back();
		S.pop_back();
		

	}
	
	else
	{
		
		E[popu].pop++;

		bool y = false;
		for (int i = 0; i < 3; i++)
		{
			//if popu is in S then just sort, no insert
			if (E[popu].hashtag == E[S[i]].hashtag)
			{
				y = true;
				break;
			}
		}

		if (y == true)
		{
			if (E[S[0]].pop == E[popu].pop)
			{
				return;
			}
			else if (E[S[0]].pop < E[S[1]].pop)
			{
				swap(S[0], S[1]);
			}
			else 
			{
				if (E[S[2]].pop > E[S[0]].pop)
				{
					swap(S[2], S[0]);
					swap(S[1], S[2]);
				}
				else if (E[S[2]].pop > E[S[1]].pop)
				{
					swap(S[2], S[1]);
				}
			}
		}
		else if (y == false)
		{
			for (int i = 0; i < 3; i++)
			{
				if (E[popu].pop > E[S[i]].pop)
				{
					S.insert(S.begin() + i, popu);
					S.pop_back();
					return;
				}
			}
		}
		
	}
}


// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
// 
// Must run in O(log(n)) time.
int Trendtracker::popularity(string name)
{
	if (!(E.empty)())
	{
		int popu = search(name);
		if (popu == -1)
		{
			return -1;
		}
		else
		{
			return E[popu].pop;
		}
	}
	else
	{
		return -1;
	}

}



// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
// 
// Must run in O(1) time.
string Trendtracker::top_trend()
{
	if (!(E.empty)())
	{
		if (S.size() == 1)
		{
			return E[0].hashtag;
		}
		else
		{
			return E[S[0]].hashtag;
		}
		
	}

	else
	{
		return "";
	}


}



	// Fills the provided vector with the 3 most-tweeted hashtags, 
	// in order from most-tweeted to least-tweeted.
	// 
	// If there are fewer than 3 hashtags, then the vector is filled
	// with all hashtags (in most-tweeted to least-tweeted order).
	//
	// Must run in O(1) time.
	void Trendtracker::top_three_trends(vector<string>& T)
	{


		if (E.size() == 0)
		{
			
		}
		else if (E.size() == 1)
		{
			T.resize(1);
			T[0] = E[0].hashtag;
			
		}
		else if (E.size() == 2)
		{
			T.resize(2);
			T[0] = E[S[0]].hashtag;
			T[1] = E[S[1]].hashtag;
			
		}
		else
		{
			T.resize(3);
			T[0] = E[S[0]].hashtag;
			T[1] = E[S[1]].hashtag;
			T[2] = E[S[2]].hashtag;

		}

		

	}

	// Optional helper method.
// Returns the index of E containing an Entry with hashtag ht.
// If no such hashtag is found, returns -1. 
// 
// Should run in O(log(n)).
	int Trendtracker::search(string ht)
	{
		int left = 0;
		int right = E.size() - 1;
		int mid = (left + right) / 2;

		while (left <= right)
		{
			if (E[mid].hashtag == ht)
			{
				return mid;
			}
			else
			{
				if (E[mid].hashtag < ht)
				{
					left = mid + 1;
					mid = (left + right) / 2;
				}
				else
				{
					right = mid - 1;
					mid = (left + right) / 2;
				}
			}
		}
		return -1;
	}

