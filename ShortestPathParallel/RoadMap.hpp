// --------------------------------------------------------
// RoadMap.hpp
// Jeremy Campbell
// This class was made to calculate the Floyd-Warshall 
// Algorithm in parallel using OpenMP. 
// --------------------------------------------------------
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <omp.h>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::vector;
using std::min;

class RoadMap
{
public:
	void readRoads();
	void readRoutes();
	void computeShortestLengths();
	void outputResults();
	void printAdjacency();
	void printRoutes();

private:
	// Parallel Vectors (routes and lengths) - the length of 
	// each route is held in the corressponding index in
	// the length vector
	vector<vector<int>> routes;
	vector<double> lengths;
	vector<vector<double>> adjacency;
	double shortestLength = INFINITY;

	template <typename T>
	void print2DVector(vector<vector<T>> &v);
	void computeShortestPaths();
	void fillDistanceToSelf();
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
		if (start >= numLocations || start < 0)
			cerr << "Invalid start location " << start << endl;
		else if (end >= numLocations || end < 0)
			cerr << "Invalid end location " << end << endl;
		else
			cin >> adjacency[start][end];
	}
}

void RoadMap::readRoutes()
{
	int numRoutes = 0;
	cin >> numRoutes;
	routes.resize(numRoutes);
	int totalLocations = adjacency.size();
	for (vector<int> &route : routes)
	{
		int numLocationsInRoute;
		cin >> numLocationsInRoute;
		for (int i = 0; i < numLocationsInRoute; i++)
		{
			int location;
			cin >> location;
			if (location < totalLocations && location >= 0)
				route.push_back(location);
			else
				cerr << "Invalid location " << location << " in route" << endl;
		}
	}
}

void RoadMap::computeShortestLengths()
{
#pragma omp parallel 
	{
		// Set the adjacency matrix so that it contains
		// all the shortest paths to between any 2 locations
		computeShortestPaths();
#pragma omp single 
		{
			lengths.resize(routes.size());
		}
#pragma omp for 
		for (int i = 0; i < routes.size(); i++)
		{
			double total = 0;
			for (int j = 0; j < routes[i].size() - 1; j++)
			{
				// Add up all the distances from each point in the route. 
				total += adjacency[routes[i][j]][routes[i][j + 1]];
			}

			lengths[i] = total;
			// Keep track of the shortest route
#pragma omp critical
			{
				if (total < shortestLength)
				{
					shortestLength = total;
				}
			}
		}
	}
}

// Parallelize
// Floyd-Warshall Algorithm
// Calculates the shortest path between 
// any 2 verticies in a graph
void RoadMap::computeShortestPaths()
{
	fillDistanceToSelf();
	const int locations = adjacency.size();
	for (int k = 0; k < locations; k++)
	{
#pragma omp for 
		for (int i = 0; i < locations; i++)
		{
			for (int j = 0; j < locations; j++)
			{
				adjacency[i][j] = min(adjacency[i][j], adjacency[i][k] + adjacency[k][j]);
			}
		}
	}
}

void RoadMap::fillDistanceToSelf()
{
#pragma omp for 
	for (int i = 0; i < adjacency.size(); i++)
	{
		adjacency[i][i] = 0;
	}
}

void RoadMap::outputResults()
{
	for (double length : lengths)
		cout << length << endl;

	cout << shortestLength << endl;
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