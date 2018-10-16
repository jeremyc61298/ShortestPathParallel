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

struct RoadMap
{
	vector<vector<int>> routes;
	vector<vector<double>> adjacency;

	void readRoads(const int numLocations, const int numRoads);
	void readRoutes(const int numRoutes);
};

void RoadMap::readRoads(const int numLocations, const int numRoads)
{
	adjacency.resize(numLocations, vector<double>(numLocations, INFINITY));
	for (int i = 0; i < numRoads; i++)
	{
		int start, end;
		cin >> start >> end;
		cin >> adjacency[start][end];
	}
}

void RoadMap::readRoutes(const int numRoutes)
{
	routes.resize(numRoutes);
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

void computeShortestLengths(vector<vector<int>> &routes, vector<vector<double>> adjacency)
{

}

void outputLengths()
{

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
	RoadMap roadMap;
	int numLocations, numRoads;
	cin >> numLocations >> numRoads;
	roadMap.readRoads(numLocations, numRoads);

#ifdef DEBUG
	print2DVector(roadMap.adjacency);
#endif

	int numRoutes = 0;
	cin >> numRoutes;
	roadMap.readRoutes(numRoutes);

#ifdef DEBUG
	print2DVector(roadMap.routes);
#endif

	// What next?
	//computeShortestLengths(routes, adjacency);
	//outputLengths();
}
