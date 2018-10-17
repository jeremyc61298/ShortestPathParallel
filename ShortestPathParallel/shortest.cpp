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
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::min;

#define DEBUG

struct RoadMap
{
	// Parallel Vectors (routes and lengths) - the length of 
	// each route is held in the corressponding index in
	// the length vector
	vector<vector<int>> routes;
	vector<double> lengths;
	vector<vector<double>> adjacency;
	vector<int> shortestRoute;

	void readRoads();
	void readRoutes();
	void computeShortestLengths();
	void outputResults();

private:
	void computeShortestPaths(); 
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
	// Set the adjacency matrix so that it contains
	// all the shortest paths to between any 2 locations
	computeShortestPaths();
	lengths.resize(routes.size());
	double shortestLength = INFINITY;
	int shortestRouteIndex;

	for (int i = 0; i < routes.size(); i++)
	{
		double total = 0;
		cout << "Numbers for route " << i << ": ";
		for (int j = 0; j < routes[i].size() - 1; j++)
		{
			// Add up all the distances from each point in the route. 
			total += adjacency[routes[i][j]][routes[i][j+1]];
			cout << adjacency[routes[i][j]][routes[i][j + 1]] << " ";
		}
		lengths[i] = total;
		cout << endl;
		// Keep track of the shortest route
		if (total < shortestLength)
		{
			shortestLength = total;
			shortestRouteIndex = i;
		}
	}

	shortestRoute = routes[shortestRouteIndex];
}

// Floyd-Warshall Algorithm
// Calculates the shortest path between 
// any 2 verticies in a graph
void RoadMap::computeShortestPaths()
{
	const int locations = adjacency.size();
	for (int k = 0; k < locations; k++)
	{
		for (int i = 0; i < locations; i++)
		{
			for (int j = 0; j < locations; j++)
			{
				adjacency[i][j] = min(adjacency[i][j], adjacency[i][k] + adjacency[k][j]);
			}
		}
	}
}

void RoadMap::outputResults()
{
	for (double length : lengths)
		cout << length << endl;

	for (int location : shortestRoute)
		cout << location << " ";

	cout << endl;
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
	roadMap.readRoutes();
	roadMap.computeShortestLengths();

	cout << "New Adjacency Matrix: " << endl;
	cout << "-------------------------------------" << endl;
#ifdef DEBUG
	print2DVector(roadMap.adjacency);
#endif
	cout << "-------------------------------------" << endl;
	
	roadMap.outputResults();
}
