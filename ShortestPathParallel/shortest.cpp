// -------------------------------------------------
// shortest.cpp
// Jeremy Campbell
// Uses the Floyd-Warshall Algorithm to find the 
// shortest path between two locations in parallel
// using OpenMP.
// -------------------------------------------------
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

void readRoutes(vector<vector<int>> &routes)
{
	for (vector<int> &route : routes)
	{
		int numLocations;
		cin >> numLocations;
		for (int i = 0; i < numLocations; i++)
		{
			int location;
			cin >> location;
			route.push_back(location);
		}
	}
}

template <typename T>
void print2DVector(vector<vector<T>> &v)
{
	// Const rational reference for speed
	for (const vector<T> &row : v)
	{
		for (T col : row)
		{
			cout << col << " ";
		}
		cout << endl;
	}
}

int main()
{
	int numLocations, numRoads;
	cin >> numLocations >> numRoads;
	vector<vector<double>> adjacency(numLocations, vector<double>(numLocations, INFINITY));
	readRoads(adjacency, numRoads);

#ifdef DEBUG
	print2DVector(adjacency);
#endif

	int numRoutes = 0;
	cin >> numRoutes;
	vector<vector<int>> routes(numRoutes);
	readRoutes(routes);

#ifdef DEBUG
	print2DVector(routes);
#endif

}
