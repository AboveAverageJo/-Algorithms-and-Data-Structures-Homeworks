#pragma once

#ifndef TRENDTRACKER_H
#define TRENDTRACKER_H

#include <vector>
#include <string>

using namespace std;

class Trendtracker
{
	// For the mandatory running times below:
	// n is the number of hashtags in the Trendtracker.

public:

	Trendtracker();


	void insert(string ht);



	int size();


	void tweeted(string ht);


	int popularity(string name);


	string top_trend();


	void top_three_trends(vector<string>& T);


	void top_k_trends(vector<string>& T, int k);

private:
	// A simple class representing a hashtag and 
	// the number of times it has been tweeted.
	class Entry
	{
	public:
		string hashtag;
		int pop;
	};


	// Entries containing each hashtag and its popularity.
	vector<Entry> E;
};

#endif 

