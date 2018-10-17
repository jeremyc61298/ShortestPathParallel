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

	void readRoads();
	void readRoutes();
	void computeShortestLengths();
	void outputResults();
	void printAdjacency();
	void printRoutes();

private:
	vector<vector<int>> routes;
	vector<double> lengths;
	vector<vector<double>> adjacency;
	vector<vector<double>> adjacencyCopy;
	vector<int> shortestRoute;

	void computeShortestPaths(); 

	template <typename T>
	void print2DVector(vector<vector<T>> &v);
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

// Parallelize?
void RoadMap::computeShortestLengths()
{
	int shortestRouteIndex;
#pragma omp parallel
	{
		// Set the adjacency matrix so that it contains
		// all the shortest paths to between any 2 locations
		computeShortestPaths();
	#pragma omp single 
			{
				lengths.resize(routes.size());
			}
		double shortestLength = INFINITY;
	#pragma omp for 
		for (int i = 0; i < routes.size(); i++)
		{
			double total = 0;
			//cout << "Locations for route " << i << ":";
			for (int j = 0; j < routes[i].size() - 1; j++)
			{
				// Add up all the distances from each point in the route. 
				total += adjacency[routes[i][j]][routes[i][j + 1]];
				//cout << " " << adjacency[routes[i][j]][routes[i][j + 1]];
			}
			//cout << endl;
			lengths[i] = total;
			// Keep track of the shortest route
	#pragma omp critical
			if (total < shortestLength)
			{
				shortestLength = total;
				shortestRouteIndex = i;
			}
		}
	}
	shortestRoute = routes[shortestRouteIndex];
}

// Parallelize
// Floyd-Warshall Algorithm
// Calculates the shortest path between 
// any 2 verticies in a graph
void RoadMap::computeShortestPaths()
{
#pragma omp single
	{
		adjacencyCopy = adjacency;
	}
	const int locations = adjacency.size();
#pragma omp for
	for (int k = 0; k < locations; k++)
	{
		for (int i = 0; i < locations; i++)
		{
			for (int j = 0; j < locations; j++)
			{
				adjacency[i][j] = min(adjacencyCopy[i][j], adjacencyCopy[i][k] + adjacencyCopy[k][j]);
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

// Debug Function
void RoadMap::printAdjacency()
{
	print2DVector(adjacency);
}

// Debug Function
void RoadMap::printRoutes()
{
	print2DVector(routes);
}

template <typename T>
void RoadMap::print2DVector(vector<vector<T>> &v)
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

#ifdef DEBUG
	cout << "New Adjacency Matrix: " << endl;
	cout << "-------------------------------------" << endl;
	roadMap.printAdjacency();
	cout << "-------------------------------------" << endl;
#endif

	roadMap.outputResults();
}
