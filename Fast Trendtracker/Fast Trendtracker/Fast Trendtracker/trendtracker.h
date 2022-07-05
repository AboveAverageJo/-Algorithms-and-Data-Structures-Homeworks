#pragma once

#ifndef TRENDTRACKER_H
#define TRENDTRACKER_H

#include <cassert>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Trendtracker
{


public:

	Trendtracker(string filename);


	int size();


	void tweeted(string ht);


	int popularity(string name);


	string top_trend();


	void top_three_trends(vector<string>& T);

	

private:
	// A simple class representing a hashtag and 
	// the number of times it has been tweeted.
	class Entry
	{
	public:
		string hashtag;
		int pop;
	};


	int search(string ht);


	// Entries sorted (lexicographically) by hashtag.
	vector<Entry> E;

	// Stores indices of the (up to) three most-tweeted
	// entries in E.
	vector<int> S;
};

#endif 

