#include <iostream>
#include <omp.h>
#include <vector>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

//#define DEBUG

void readRoads(vector<vector<double>> &adjacency, const int numRoads)
{
	for (int i = 0; i < numRoads; i++)
	{
		int start, end;
		cin >> start >> end;
		cin >> adjacency[start][end];
	}
}

void printAdjacency(vector<vector<double>> &adjacency)
{
	for (vector<double> row : adjacency)
	{
		for (double col : row)
		{
			cout << col << " ";
		}
		cout << endl;
	}
}

int main()
{
	int locations, roads;
	cin >> locations >> roads;
	vector<vector<double>> adjacency(locations, vector<double>(locations, INFINITY));
	
	readRoads(adjacency, roads);

#ifdef DEBUG
	printAdjacency(adjacency);
#endif
}
