#include "solve.h"
#include <string>
using namespace std;

class MZ1_Graph
{
private:
	class Vertex
	{
	public:
		Vertex(int r, int c)
		{
			row = r;
			col = c;

		}

		//hash table under the hood.
		unordered_map<string, Vertex*> vertexSet;


		// Corresponding row and column location in maze
		int row;
		int col;

		// List of neighboring vertices
		vector<Vertex*> neighbors;

	};

public:
	//Algorithm tools
	unordered_map<Vertex*, Vertex*> breadCrumbs;

	vector<Vertex*> numVer;

	Vertex* start = nullptr;
	Vertex* end = nullptr;

	int classRow=0;
	int classColumn=0;

	Vertex*** classGrid = nullptr;
	char** classCharGrid;

	void makeTwoDArr(string maze)
	{
		int row = 0;
		int column = 0;

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
				Vertex* coord = new Vertex(row, column);
				numVer.push_back(coord);

			}

			if (maze[i] != '\n')
				column++;
		}

		classRow = row;
		classColumn = (maze.size() / row);

		///making the 2D array
		Vertex*** grid = new Vertex * *[row];
		char** charGrid = new char* [row];

		for (int i = 0; i < row; i++)
		{
			grid[i] = new Vertex * [classColumn];
			charGrid[i] = new char[classColumn];
		}

		classGrid = grid;
		classCharGrid = charGrid;
	}

	void FilltwoDArr(string m)
	{
		int count = 0;

		//row = left to right
		//columns = up and down
		//adding every circle

		//filling char* 2D arr
		for (int i = 0; i <= classRow-1; i++)
		{
			for (int j = 0; j <= classColumn-1; j++)
			{
				classCharGrid[i][j] = m[count];
				count++;
			}
		}
		//filling vertex* 2D arr
		int count2 = 0;
		for (int i = 0; i <= classRow-1; i++)
		{

			for (int j = 0; j <= classColumn-1; j++)
			{

				if (classCharGrid[i][j] == ' ')
				{
					classGrid[i][j] = numVer[count2];
					count2++;

				}
				else
				{
					classGrid[i][j] = nullptr;
				}
				
			}
		}


		//looking for start vertex and end vertex 
		for (int i = 0; i <= classRow - 1; i++)
		{
			for (int j = 0; j <= classColumn - 1; j++)
			{
				if (i == 0 || i == classRow - 1)
				{
					if (classCharGrid[i][j] == ' ')
					{
						if (start == nullptr)
							start = classGrid[i][j];
						else if (start != nullptr)
							end = classGrid[i][j];
					}

				}
				else if (j == 0 || j == classColumn - 2)
				{
					if (classCharGrid[i][j] == ' ')
					{
						if (start == nullptr)
							start = classGrid[i][j];
						else if (start != nullptr)
							end = classGrid[i][j];
					}
				}
			}
		}
	}

	void connectTheVertices()
	{
		/////////////////////////////////////////////////////////
			//connecting the vertices
		for (int i = 0; i < classRow; i++)
		{
			for (int j = 0; j < classColumn; j++)
			{

				//checking if there's a vertex at the coord
				if (classCharGrid[i][j] == ' ')
				{

					int u = i - 1;//up
					int d = i + 1;//down
					int l = j - 1;//left
					int r = j + 1;//right

					//checking if the neighbor at index [u][j] will go out of range
					if (u >= 0)
					{
						//check for neighbor
						if (classCharGrid[u][j] == ' ')
						{
							classGrid[i][j]->neighbors.push_back(classGrid[u][j]);
						}
					}
					if (d <= classRow-1)
					{
						//check for neighbor
						if (classCharGrid[d][j] == ' ')
						{
							classGrid[i][j]->neighbors.push_back(classGrid[d][j]);
						}

					}

					if (l >= 0)
					{
						//check for neighbor 
						if (classCharGrid[i][l] == ' ')
						{
							classGrid[i][j]->neighbors.push_back(classGrid[i][l]);
						}

					}
					if (r <= classColumn-1)
					{
						//check for neighbor 
						if (classCharGrid[i][r] == ' ')
						{
							classGrid[i][j]->neighbors.push_back(classGrid[i][r]);
						}

					}
				}
			}
		}
	}


	void breadthFirstSearch(Vertex * s)
	{
		//Variables, tools, etc.
		queue<Vertex*> Q;
		unordered_set<Vertex*> marked;


		//step 1: Mark s, put it in Q
		marked.insert(s);
		Q.push(s);

		//step 2: The BFS loop!
		while (!Q.empty())
		{
			//2.1 Remove top item from Q
			Vertex* x = Q.front();
			Q.pop();

			//2.2 For each unvisited neighbor y of x,
			//mark y, put in Q
			for (unsigned int i = 0; i < x->neighbors.size(); i++)
			{
				Vertex* y = x->neighbors[i];
				if (marked.find(y) == marked.end())
				{
					marked.insert(y);
					Q.push(y);

					//augmentations:
					breadCrumbs[y] = x;
				}
			}
		}
	}

	string shortestPath()
	{
		//step 1:
		breadthFirstSearch(start);

		//step 2: Use the breadcrumbs computed in bfs
		//to trace back a path from s to t:
		vector<pair<int, int>> output;
		string outputStg = "";
		Vertex* current = end;
		//pushing coords into pair vector
		while (current != start)
		{
			pair<int, int> coord(current->row, current->col);
			output.push_back(coord);
			current = breadCrumbs[current];
		}

		classCharGrid[start->row][start->col] = 'o';
		//adding 'o' to the right path
		for (unsigned int i = 0; i < output.size(); i++)
		{
			classCharGrid[output[i].first][output[i].second] = 'o';
		}
		//adding correct maze into a new string
		for (int i = 0; i < classRow; i++)
		{
			for (int j = 0; j < classColumn; j++)
			{
				outputStg += classCharGrid[i][j];
			}
		}


		return outputStg;
	}

	void deleteArr()
	{
		for (int i = 0; i < classRow-1; i++) {
			for (int j = 0; j < classColumn-1; j++) {
				delete classGrid[i][j];
			}
			delete[] classGrid[i];
		}
		delete[] classGrid;
		classGrid = NULL;

		for (int i = 0; i < classRow-1; i++)
			delete[] classCharGrid[i];
		delete[] classCharGrid;
	}
};
string solve(string maze)
{
	MZ1_Graph bruh;
	bruh.makeTwoDArr(maze);
	bruh.FilltwoDArr(maze);
	bruh.connectTheVertices();

	maze = bruh.shortestPath();

	bruh.deleteArr();

	return maze;	
}