#include "tiling.h"
#include "vertex.h"

using namespace std;


class Graph
{

private: 


	unordered_set<Vertex*> AllVer;
	vector<Vertex*> numVer;

	Vertex* start = new Vertex;
	Vertex* sink = new Vertex;

	Vertex*** classGrid;
	char** classCharGrid;

	int classRow;
	int classColumn;

	int countForAmountOnRightSide = 0;

public:

	void makeGraph(string maze)
	{
		int row = 0;
		int column = 0;

		AllVer.insert(start);
		AllVer.insert(sink);
		
		//getting the rows and columns
		for (unsigned int i = 0; i < maze.size(); i++)
		{
			
			if (maze[i] == '\n')
			{
				row++;
				column = 0;
			}
			else if (maze[i] == ' ')
			{
				//making a vertex
				Vertex* v = new Vertex;
				numVer.push_back(v);
				AllVer.insert(v);
			}

			if (maze[i] != '\n')
				column++;
		}


		classRow = row;
		classColumn = (maze.size() / row);

		Vertex*** grid = new Vertex * *[row];
		char** charGrid = new char* [row];

		for (int i = 0; i < row; i++)
		{
			grid[i] = new Vertex * [classColumn];
			charGrid[i] = new char[classColumn];
		}

		classCharGrid = charGrid;
		classGrid = grid;
		/////////////////////////////////////////////////////////
		int count = 0;
		int c = 0;
		bool w = 0;
		bool b = 0;
		//filling vertex* 2D arr and char 2D arr
		for (int i = 0; i <= classRow - 1; i++)
		{

			for (int j = 0; j <= classColumn - 1; j++)
			{
				if (w == 0)
				{
					classCharGrid[i][j] = 'w';
					w = 1;
				}
				else if (b == 0)
				{
					classCharGrid[i][j] = 'b';
					b = 1;
				}

				if (maze[count] == ' ')
				{
					classGrid[i][j] = numVer[c];
					c++;
					count++;
				}
				else
				{
					classGrid[i][j] = nullptr;
					count++;

				}
				if (w == 1 && b == 1)
				{
					w = 0;
					b = 0;
				}
			}
		}

		//checking if white and black are opposite of each other
		for (int i = 0; i < classRow; i++)
		{
			for (int j = 0; j < classColumn; j++)
			{
				int u = i - 1;//up
				int d = i + 1;//down
				int l = j - 1;//left
				int r = j + 1;//right

				if (u >= 0)
				{
					if (classCharGrid[u][j] == classCharGrid[i][j])
					{
						if (classCharGrid[i][j] == 'w')
						{
							classCharGrid[u][j] = 'b';
						}
						else
						{
							classCharGrid[u][j] = 'w';
						}
					}
				}
				if (d <= classRow - 1)
				{
					if (classCharGrid[d][j] == classCharGrid[i][j])
					{
						if (classCharGrid[i][j] == 'w')
						{
							classCharGrid[d][j] = 'b';
						}
						else
						{
							classCharGrid[d][j] = 'w';
						}
					}
				}
				if (l >= 0)
				{
					if (classCharGrid[i][l] == classCharGrid[i][j])
					{
						if (classCharGrid[i][j] == 'w')
						{
							classCharGrid[i][l] = 'b';
						}
						else
						{
							classCharGrid[i][l] = 'w';
						}
					}
				}
				if (r <= classColumn - 1)
				{
					if (classCharGrid[i][r] == classCharGrid[i][j])
					{
						if (classCharGrid[i][j] == 'w')
						{
							classCharGrid[i][r] = 'b';
						}
						else
						{
							classCharGrid[i][r] = 'w';
						}
					}
				}
			}
		}
	}

	void connectVertices()
	{
		for (int i = 0; i < classRow; i++)
		{
			for (int j = 0; j < classColumn; j++)
			{

				//checking if there's a vertex at the coord
				if (classGrid[i][j] != nullptr)
				{

					int u = i - 1;//up
					int d = i + 1;//down
					int l = j - 1;//left
					int r = j + 1;//right

					//checking if the neighbor at index [u][j] will go out of range
					if (u >= 0)
					{
						//check for neighbor
						if (classGrid[u][j] != nullptr)
						{
							if (classCharGrid[i][j] == 'w')
							{
								classGrid[i][j]->neighs.insert(classGrid[u][j]);
								classGrid[i][j]->weights.insert({ classGrid[u][j],1 });
							}
						}
					}
					if (d <= classRow - 1)
					{
						//check for neighbor
						if (classGrid[d][j] != nullptr)
						{
							if (classCharGrid[i][j] == 'w')
							{
								classGrid[i][j]->neighs.insert(classGrid[d][j]);
								classGrid[i][j]->weights.insert({ classGrid[d][j],1 });
							}
						}

					}

					if (l >= 0)
					{
						//check for neighbor 
						if (classGrid[i][l] != nullptr)
						{
							if (classCharGrid[i][j] == 'w')
							{
								classGrid[i][j]->neighs.insert(classGrid[i][l]);
								classGrid[i][j]->weights.insert({ classGrid[i][l],1 });
							}
						}

					}
					if (r <= classColumn - 1)
					{
						//check for neighbor 
						if (classGrid[i][r] != nullptr)
						{
							if (classCharGrid[i][j] == 'w')
							{
								classGrid[i][j]->neighs.insert(classGrid[i][r]);
								classGrid[i][j]->weights.insert({ classGrid[i][r],1 });
							}
						}

					}
				}
			}
		}

	}

	void connectStartAndSinkToNetwork()
	{
		vector<Vertex*> left;
		vector<Vertex*> right;



		for (int i = 0; i < classRow; i++)
		{
			for (int j = 0; j < classColumn; j++)
			{
				if (classGrid[i][j] != nullptr)
				{
					//adding all vertices on the left side into a vector 
					if (classCharGrid[i][j] == 'w')
					{
						left.push_back(classGrid[i][j]);
						/*cout << classCharGrid[i][j];*/
					}
					//adding all vertices on the right side into a vector
					else if (classCharGrid[i][j] == 'b')
					{
						right.push_back(classGrid[i][j]);
						/*cout << classCharGrid[i][j];*/
					}
					
				}
			}
			cout << endl;
		}
		////displaying the tiles
		//for (int i = 0; i < classRow; i++)
		//{
		//	for (int j = 0; j < classColumn; j++)
		//	{
		//		if (classGrid[i][j] != nullptr)
		//		{
		//			cout << classCharGrid[i][j];
		//		}
		//		else if(classGrid[i][j] == nullptr)
		//		{
		//			cout << ' ';
		//		}
		//	}
		//	cout << endl;
		//}

		// connecting the start to all vertices on the left side
		for (int i = 0; i < left.size(); i++)
		{
			start->neighs.insert(left[i]);
			start->weights.insert({ left[i],1 });
		}
		//connecting all vertices on the right side to sink
		for (int i = 0; i < right.size(); i++)
		{
			right[i]->neighs.insert(sink);
			right[i]->weights.insert({ sink,1 });
			countForAmountOnRightSide++;
		}

	}

	bool MaxFlowAns()
	{
		int x = max_flow(start, sink, AllVer);

		if (x == start->neighs.size() && start->neighs.size() == countForAmountOnRightSide)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	// Finds a (shortest according to edge length) augmenting path
	// from s to t in a graph with vertex set V.
	// Returns whether there is an augmenting path.
	bool augmenting_path(Vertex* s, Vertex* t, unordered_set<Vertex*> V, vector<Vertex*>& P)
	{
		// Check that s and t aren't nullptr
		if (s == nullptr || t == nullptr)
		{
			cerr << "augmenting_path() was passed nullptr s or t." << endl;
			abort();
		}

		// Check that s and t are in the graph
		if (V.find(s) == V.end() || V.find(t) == V.end())
		{
			cerr << "augmenting_path() was passed s or t not in V." << endl;
			abort();
		}

		// Check that every vertex has valid neighs/weights.
		for (Vertex* v : V)
			for (Vertex* vn : v->neighs)
				if (v->weights.find(vn) == v->weights.end())
				{
					cerr << "augmenting_path() was passed invalid vertex." << endl;
					abort();
				}

		// Since augmenting paths should have the fewest edges,
		// not the minimum weight, run BFS.
		queue<Vertex*> Q;
		Q.push(s);

		unordered_set<Vertex*> R;
		R.clear();
		R.insert(s);

		unordered_map<Vertex*, Vertex*> prev;

		while (!Q.empty())
		{
			Vertex* cur = Q.front();
			Q.pop();

			for (Vertex* nei : cur->neighs)
			{
				// Must have positive edge weight
				if (cur->weights[nei] == 0)
					continue;

				if (R.find(nei) == R.end())
				{
					Q.push(nei);
					R.insert(nei);
					prev[nei] = cur;
				}
			}
		}

		// If BFS never reached t
		if (R.find(t) == R.end())
			return false;

		// Reconstruct shortest path backwards
		P.clear();
		P.push_back(t);
		while (P[P.size() - 1] != s)
			P.push_back(prev[P[P.size() - 1]]);

		// Reverse shortest path
		for (unsigned int i = 0; i < P.size() / 2; ++i)
			swap(P[i], P[P.size() - 1 - i]);

		return true;
	}

	// Returns the maximum flow from s to t in a weighted graph with vertex set V.
	// Assumes all edge weights are non-negative.
	int max_flow(Vertex* s, Vertex* t, unordered_set<Vertex*> V)
	{
		// If s or t is invalid.
		if (s == nullptr || t == nullptr)
		{
			cerr << "max_flow() was passed nullptr s or t." << endl;
			abort();
		}

		// If s or t is not in the vertex set.
		if (V.find(s) == V.end() || V.find(t) == V.end())
		{
			cerr << "max_flow() was passed s or t not in V." << endl;
			abort();
		}

		// Check that every vertex has valid neighs/weights.
		for (Vertex* v : V)
			for (Vertex* vn : v->neighs)
				if (v->weights.find(vn) == v->weights.end())
				{
					cerr << "max_flow() was passed invalid vertex." << endl;
					abort();
				}

		// Create a deep copy of V to use as the residual graph
		unordered_set<Vertex*> resV;
		unordered_map<Vertex*, Vertex*> C; // Maps vertices in V to copies in resV
		for (Vertex* vp : V)
		{
			Vertex* rp = new Vertex;
			resV.insert(rp);
			C[vp] = rp;
		}
		for (Vertex* vp : V)
			for (Vertex* np : vp->neighs)
			{
				C[vp]->neighs.insert(C[np]);
				C[vp]->weights[C[np]] = vp->weights[np];
			}
		// Add any missing necessary "back" edges. 
		for (Vertex* vp : V)
			for (Vertex* np : vp->neighs)
			{
				if (C[np]->neighs.find(C[vp]) == C[np]->neighs.end())
				{
					C[np]->neighs.insert(C[vp]);
					C[np]->weights[C[vp]] = 0;
				}
			}

		// Run Edmonds-Karp
		while (true)
		{
			// Find an augmenting path
			vector<Vertex*> P;
			if (!augmenting_path(C[s], C[t], resV, P))
				break;
			// Update residual graph
			for (unsigned int i = 0; i < P.size() - 1; ++i)
			{
				--((*(resV.find(P[i])))->weights[P[i + 1]]);
				++((*(resV.find(P[i + 1])))->weights[P[i]]);
			}
		}

		// Compute actual flow amount
		int flow = 0;
		for (Vertex* snp : C[s]->neighs)
			flow += 1 - C[s]->weights[snp];

		// Delete residual graph
		for (Vertex* vp : resV)
			delete vp;

		return flow;
	}

};


bool has_tiling(string floor)
{
	Graph tile;
	tile.makeGraph(floor);
	tile.connectVertices();
	tile.connectStartAndSinkToNetwork();

	return tile.MaxFlowAns();
}
