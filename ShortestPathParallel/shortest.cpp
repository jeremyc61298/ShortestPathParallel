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
	// Parallel Vectors (routes and lengths) - the length of 
	// each route is held in the corressponding index in
	// the length vector
	vector<vector<int>> routes;
	vector<double> lengths;
	vector<vector<double>> adjacency;

	void readRoads();
	void readRoutes();
	void computeShortestLengths();
	void outputLengths();
};

void RoadMap::readRoads()
{
	int numLocations = 0, numRoads = 0;
	cin >> numLocations >> numRoads;
	adjacency.resize(numLocations, vector<double>(numLocations, INFINITY));

	for (int i = 0; i < numRoads; i++)
	{
		int start, end;
		cin >> start >> end;
		cin >> adjacency[start][end];
	}
}

void RoadMap::readRoutes()
{
	int numRoutes = 0;
	cin >> numRoutes;
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

void RoadMap::computeShortestLengths()
{

}

void RoadMap::outputLengths()
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
	roadMap.readRoads();

#ifdef DEBUG
	print2DVector(roadMap.adjacency);
#endif

	roadMap.readRoutes();

#ifdef DEBUG
	print2DVector(roadMap.routes);
#endif

	// What next?
	//computeShortestLengths(routes, adjacency);
	//outputLengths();
}
