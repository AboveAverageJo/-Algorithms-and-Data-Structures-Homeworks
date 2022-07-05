// TrendTracker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "trendtracker.h"

using namespace std;



// Creates a new Trendtracker tracking no hashtags.
// 
// Must run in O(1) time.
Trendtracker::Trendtracker()
{
	
}

// Inserts a hashtag (tweeted 0 times) into the Trendtracker.
// If the hashtag already is in Trendtracker, does nothing.
// 
// Must run in O(n) time.
void Trendtracker:: insert(string ht)
{

	if (E.size() == 0)
	{
		Entry newEntry;
		newEntry.hashtag = ht;
		newEntry.pop = 0;
		E.push_back(newEntry);
	}

	else
	{

		for (int i = 0; i < E.size(); i++)
		{

			if (ht == E[i].hashtag)
			{
				return;
			}
		}
		Entry newEntry;
		newEntry.hashtag = ht;
		newEntry.pop = 0;
		E.push_back(newEntry);
	}

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
// Must run in O(n) time.
void Trendtracker::tweeted(string ht)
{
	for (int i = 0; i < E.size(); i++)
	{
		if (ht == E[i].hashtag)
		{
			E[i].pop++;
		}
	}
}


// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
// 
// Must run in O(n) time.
int Trendtracker::popularity(string name)
{
	for (int i = 0; i < E.size(); i++)
	{
		if (name == E[i].hashtag)
		{
			return E[i].pop;

		}
	}

	return -1;
}


// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
// 
// Must run in O(n) time.
string Trendtracker::top_trend()
{

	if (E.size() == 0)
	{
		return "";
	}
	else
	{
		Entry mostTW;
		mostTW.hashtag = E[0].hashtag;
		mostTW.pop = E[0].pop;


		for (int i = 0; i < E.size(); i++)
		{
			if (mostTW.pop < E[i].pop)
			{
				mostTW.hashtag = E[i].hashtag;
				mostTW.pop = E[i].pop;
			}
		}

		return mostTW.hashtag;
	}
}


// Fills the provided vector with the 3 most-tweeted hashtags, 
// in order from most-tweeted to least-tweeted.
// 
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(n) time.
void Trendtracker::top_three_trends(vector<string>& T)
{

	while (!(T.empty)())
	{
		T.erase(T.begin());
	}

	vector<Entry> temp;
	temp = E;


	if (E.size() < 3)
	{
		if (E.size() == 2)
		{
			if (E[0].pop > E[1].pop)
			{
				T.push_back(E[0].hashtag);
				T.push_back(E[1].hashtag);
			}
			else
			{
				T.push_back(E[1].hashtag);
				T.push_back(E[0].hashtag);
			}
		}
		else if (E.size() == 1)
		{
			T.push_back(E[0].hashtag);
		}
		else
		{
			//:D
		}
	}

	else
	{
		///////////////////////////////////////////

		Entry first;
		first.hashtag = temp[0].hashtag;
		first.pop = temp[0].pop;

		int c=0;
		for (int i = 0; i < temp.size(); i++)
		{
			if (first.pop < temp[i].pop)
			{
				first.pop = temp[i].pop;
				first.hashtag = temp[i].hashtag;
				c = i;
			}
		}

		T.push_back(first.hashtag);
		temp.erase(temp.begin() + c);
		///////////////////////////////////////////////

		Entry second;
		second.hashtag = temp[0].hashtag;
		second.pop = temp[0].pop;

		int c2=0;
		for (int i = 0; i < temp.size(); i++)
		{
			if (second.pop < temp[i].pop)
			{
				second.pop = temp[i].pop;
				second.hashtag = temp[i].hashtag;
				c2 = i;
			}
		}

		T.push_back(second.hashtag);
		temp.erase(temp.begin() + c2);
		///////////////////////////////////////////

		Entry third;
		third.hashtag = temp[0].hashtag;
		third.pop = temp[0].pop;

		int c3=0;
		for (int i = 0; i < temp.size(); i++)
		{
			if (third.pop < temp[i].pop)
			{
				third.pop = temp[i].pop;
				third.hashtag = temp[i].hashtag;
				c3 = i;
			}
		}

		T.push_back(third.hashtag);
		temp.erase(temp.begin() + c3);


	}

}




// Fills the provided vector with the k most-tweeted hashtags, 
// in order from most-tweeted to least-tweeted.
// 
// If there are fewer than k hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(nk) time.
void Trendtracker::top_k_trends(vector<string>& T, int k)
{
	while (!(T.empty)())
	{
		T.erase(T.begin());
	}

	vector<Entry> temp;
	temp = E;

	if (E.size() < k)
	{
		k = E.size();

		for (int i = 0; i < k; i++)
		{
			Entry first;
			first.hashtag = E[0].hashtag;
			first.pop = E[0].pop;

			int c=0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (first.pop < temp[i].pop)
				{
					first.pop = temp[i].pop;
					first.hashtag = temp[i].hashtag;
					c = i;
				}
			}

			T.push_back(first.hashtag);
			temp.erase(temp.begin() + c);

		}

	}

	else
	{

		for (int i = 0; i < k; i++)
		{
			Entry first;
			first.hashtag = E[0].hashtag;
			first.pop = E[0].pop;

			int c=0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (first.pop < temp[i].pop)
				{
					first.pop = temp[i].pop;
					first.hashtag = temp[i].hashtag;
					c = i;
				}
			}

			T.push_back(first.hashtag);
			temp.erase(temp.begin() + c);

		}


	}

}



