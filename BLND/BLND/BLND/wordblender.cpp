#include "wordblender.h"
#include <string>

WordBlender::WordBlender(string filename, int max_word_count)
{
	// create table of strings (26^4) columns 
	//rows is max_word_count
	string** table = new string* [max_word_count];
	
	for (int i = 0; i < 456976; i++)
	{
		table[i] = new string[max_word_count];
	}
	
	//opening file
	ifstream words;
	words.open("filename");
	string w;
	if (words.is_open())
	{
		while (!words.eof())
		{
			//adding each word in the file on the first column
			words >> w;
			table[IndexForWord(w)][0] = w;
		}
	}
	words.close();


	//filling rest of the table
	for (int i = 1; i < max_word_count; i++)
	{
		for (int j = 0; j < 456976; j++)
		{
			//
			table[i][j] = subWordBlend(i, j, table, max_word_count);
		}
	}


}


string subWordBlend(int index, int wcount, string** t, int max_word_count)
{
	string sub = "";
	int indexForNewWord = 0;

	for (int k = 0; k < max_word_count; k++)
	{
		string x = t[index][wcount].substr(0,2);
		string y = t[index][k].substr(y.size()-2, y.size());

		if (x == y)
		{
			string sub1 = x + y;
			indexForNewWord = IndexForWord(sub1);

			sub = t[index][k].erase(y.size()-2, y.size());
		}
	}
	string sub1 = "";
	for (int a = 0; a < max_word_count; a++)
	{
		if (t[indexForNewWord][wcount + 1] != "")
		{
			sub1 = t[indexForNewWord][wcount + 1].erase(0, 2);
		}

	}

	return sub + sub1;

}

string WordBlender::blend(string first_word, string last_word, int word_count)
{





}


int IndexForWord(string s)
{
	int first = int(s.at(0) - 97);
	int mid = int(s.at(s.size() / 2) - 97);
	int secLast = int(s.at(s.size() - 2) - 97);
	int last = int(s.at(s.size() - 1) - 97);

	int index = (first * (pow(26, 3))) + (mid * (pow(26, 2))) + (secLast * (pow(26, 1))) + (last * (pow(26, 0)));

	return index;
}









