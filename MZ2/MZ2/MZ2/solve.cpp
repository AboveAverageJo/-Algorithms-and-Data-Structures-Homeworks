#include <vector>
#include <queue>
#include <iostream>
#include <stdio.h>
#include "minpriorityqueue.h"

using namespace std;

class Maze
{
private:
	class Vertex
	{
	public:
		Vertex(int r, int c)
		{
			row = r;
			col = c;

			marked = false;
			opening = false;
			start = false;
			end = false;
		}

		// Corresponding row and column location in maze
		int row;
		int col;
		int weight;

		bool marked;
		bool opening;
		bool portal;
		bool start;
		bool end;


		// List of neighboring vertices
		vector <pair<Vertex*, int>> neighbors;
		Vertex* breadCrumb;

	};
public:

	int mRow;
	int mCol;

	vector<Vertex*> vRow;
	vector<char> cRow;
	vector<Vertex*> mazeVerts;
	vector<Vertex*> portalVerts;
	vector<vector<Vertex*>> vertLayout;
	vector<vector<char>> charLayout;
	MinPriorityQueue <Vertex*> PQ;

	Vertex* start;
	Vertex* sink;

	Maze(string layout)
	{
		mRow = 0;
		mCol = 0;



		//create 2d vector of vertex *
		for (unsigned int c = 0; c < layout.size(); c++)
		{


			cRow.push_back(layout[c]);

			if (layout[c] != '\n')
			{
				Vertex* nVert = new Vertex(mRow, mCol);
				nVert->weight = INT_MAX;
				// check if vertex is an opening
				if (layout[c] == ' ')
				{
					nVert->opening = true;
					mazeVerts.push_back(nVert);
				}
				else if (isdigit(layout[c]))
				{
					nVert->portal = true;
					nVert->weight = c - '0';
					portalVerts.push_back(nVert);
					mazeVerts.push_back(nVert);
				}
				vRow.push_back(nVert);
				mCol++;
			}
			// check for new line
			if (layout[c] == '\n')
			{
				vertLayout.push_back(vRow);
				vRow.clear();
				charLayout.push_back(cRow);
				cRow.clear();
				mRow++;
				mCol = 0;
			}
		}




	}

	//search the edges of the maze for the start and sink
	void findEntranceExit()
	{
		bool startFound = false;

		for (unsigned int i = 0; i < vertLayout.size(); i++)
		{
			for (unsigned int j = 0; j < vertLayout[0].size(); j++)
			{
				if (i == 0 || i == vertLayout.size() - 1)
				{
					if (charLayout[i][j] == ' ' && !startFound)
					{
						start = vertLayout[i][j];
						startFound = true;
					}
					else if (charLayout[i][j] == ' ')
					{
						sink = vertLayout[i][j];
					}
				}
				else if (j == 0 || j == vertLayout[0].size() - 1)
				{
					if (charLayout[i][j] == ' ' && !startFound)
					{
						start = vertLayout[i][j];
						startFound = true;
					}
					else if (charLayout[i][j] == ' ')
					{
						sink = vertLayout[i][j];
					}
				}
			}
		}
	}

	void connectVertices()
	{
		for (unsigned int i = 0; i < mazeVerts.size() - 1; i++)
		{
			conPortals(mazeVerts[i]);
			conUp(mazeVerts[i]);
			conDown(mazeVerts[i]);
			conLeft(mazeVerts[i]);
			conRight(mazeVerts[i]);
		}
	}

	void conPortals(Vertex* v)
	{
		if (v->portal)
		{
			for (unsigned int i = 0; i < portalVerts.size(); i++)
			{
				if (portalVerts[i] != v && portalVerts[i]->weight == v->weight)
				{
					pair <Vertex*, int> n;
					n.first = portalVerts[i];
					n.second = portalVerts[i]->weight;
					v->neighbors.push_back(n);
				}
			}
		}
	}

	void conUp(Vertex* v)
	{
		if (v->row > 0 && vertLayout[v->row - 1][v->col]->opening)
		{
			// create a pair representing v's top neighbor and the weight between v and that neighbor 
			pair <Vertex*, int> n;
			n.first = vertLayout[v->row - 1][v->col];
			n.second = 1;
			v->neighbors.push_back(n);
		}
	}
	void conDown(Vertex* v)
	{
		if (v->row < vertLayout.size() - 1 && vertLayout[v->row + 1][v->col]->opening)
		{
			// create a pair representing v's bottom neighbor and the weight between v and that neighbor 
			pair <Vertex*, int> n;
			n.first = vertLayout[v->row + 1][v->col];
			n.second = 1;
			v->neighbors.push_back(n);
		}
	}
	void conLeft(Vertex* v)
	{
		if (v->col > 0 && vertLayout[v->row][v->col - 1]->opening)
		{
			// create a pair representing v's left neighbor and the weight between v and that neighbor 
			pair <Vertex*, int> n;
			n.first = vertLayout[v->row][v->col - 1];
			n.second = 1;
			v->neighbors.push_back(n);
		}
	}
	void conRight(Vertex* v)
	{
		if (v->col < vertLayout[0].size() - 1 && vertLayout[v->row][v->col + 1]->opening)
		{
			// create a pair representing v's right neighbor and the weight between v and that neighbor 
			pair <Vertex*, int> n;
			n.first = vertLayout[v->row][v->col + 1];
			n.second = 1;
			v->neighbors.push_back(n);
		}
	}

	void relax(Vertex* a, Vertex* b, int index)
	{
		// compare the sum of vertex a's weight and the weight between a,b to vertex b's weight
		if (a->weight + a->neighbors[index].second < b->weight)
		{
			b->weight = a->weight + a->neighbors[index].second;
			///////////////////////////////////////////////////////////////////////////////////////////////////////this is where error occurs
			PQ.decrease_key(b, b->weight);
			b->breadCrumb = a;

			cout << "Vertex ";
			printVertex(b);
			cout << " has a breadcrumb ";
			printVertex(a);
			cout << endl;


		}
	}

	void Dijkstra(Vertex* v)
	{
		// set all vertex weights to infinity
		for (unsigned int i = 0; i < mazeVerts.size(); i++)
		{
			mazeVerts[i]->weight = INT_MAX;
		}
		// set start weight to zero
		start->weight = 0;

		// for each vertex, push it into the priority queue with its weight
		for (unsigned int i = 0; i < mazeVerts.size(); i++)
		{
			////////////////////////////
			cout << endl;
			cout << "pushing vertex ";
			printVertex(mazeVerts[i]);
			cout << "with weight ";
			printWeight(mazeVerts[i]);
			cout << endl;
			///////////////////////////

			PQ.push(mazeVerts[i], mazeVerts[i]->weight);
		}
		// while the priority queue is not empty, extract the minimum and relax its neigbors
		while (!PQ.empty())
		{
			pair<Vertex*, int> x = PQ.extractMin();

			/////////////////////////////
			cout << endl;
			cout << "the extracted min vertex is ";
			printVertex(x.first);
			cout << endl;
			/////////////////////////////

			for (unsigned int i = 0; i < x.first->neighbors.size(); i++)
			{
				Vertex* y = x.first->neighbors[i].first;
				relax(x.first, y, i);

				///////////////////////
				cout << endl;
				cout << "X weight is ";
				printWeight(x.first);
				cout << "Y weight is ";
				printWeight(y);
				cout << endl;
				///////////////////////
			}
		}

	}

	string shortestPath()
	{
		//step 1:
		Dijkstra(start);

		vector<pair<int, int>> output;
		Vertex* current = sink;
		string outputString;

		while (current != start)
		{
			pair<int, int> coordinates(current->row, current->col);
			output.push_back(coordinates);

			cout << "go from vertex ";
			printVertex(current);
			cout << " to vertex ";
			printVertex(current->breadCrumb);
			cout << endl;

			current = current->breadCrumb;
		}
		//cout << "the path coordinates are " << endl;
		for (unsigned int i = 0; i < output.size(); i++)
		{
			charLayout[output[i].first][output[i].second] = 'o';
			//cout << output[i].first << output[i].second << endl;
		}
		charLayout[start->row][start->col] = 'o';
		//printLayout();

		for (unsigned int i = 0; i < charLayout.size(); i++)
		{
			for (unsigned int j = 0; j < charLayout[0].size(); j++)
			{
				outputString += charLayout[i][j];
			}
		}

		return outputString;
	}


	//Print Functions
	void printNeighbors(Vertex* v)
	{
		cout << "Vertex at " << v->row << ", " << v->col << " has neighbors at:";
		for (unsigned int i = 0; i < v->neighbors.size(); i++)
		{
			cout << v->neighbors[i].first->row << ", " << v->neighbors[i].first->col << endl;
		}
	}
	void printLayout()
	{
		for (unsigned int i = 0; i < charLayout.size(); i++)
		{
			for (unsigned int j = 0; j < charLayout[0].size(); j++)
			{
				cout << charLayout[i][j];
			}
		}
	}
	//Print Vertex v's coordinates
	void printVertex(Vertex* v)
	{
		cout << v->row << ", " << v->col;
	}
	//Print Vertex v's weights
	void printWeight(Vertex* v)
	{
		cout << v->weight << endl;
	}
	//Print all neighbor weights for each vertex

	void printNeighborWeights()
	{
		for (unsigned int i = 0; i < mazeVerts.size(); i++)
		{
			for (unsigned int j = 0; j < mazeVerts[i]->neighbors.size(); j++)
			{
				cout << "There is a weight of ";
				cout << mazeVerts[i]->neighbors[j].second;
				cout << " between vertex ";
				printVertex(mazeVerts[i]);
				cout << " and vertex ";
				printVertex(mazeVerts[i]->neighbors[j].first);
				cout << endl;
			}
		}
	}
};



string solve(string layout)
{
	Maze m1(layout);
	m1.findEntranceExit();
	m1.connectVertices();
	m1.printNeighborWeights();
	return m1.shortestPath();
}

