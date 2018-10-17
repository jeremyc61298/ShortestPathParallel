// -------------------------------------------------
// shortest.cpp
// Jeremy Campbell
// Uses the Floyd-Warshall Algorithm to find the 
// shortest path between two locations in parallel
// using OpenMP. The main logic for this is in 
// the RoadMap class.
// -------------------------------------------------
#include "RoadMap.hpp"

#define DEBUG

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
	cout << "-------------------------------------" << endl << endl;
	cout << "All the routes: " << endl;
	cout << "-------------------------------------" << endl;
	roadMap.printRoutes();
	cout << "-------------------------------------" << endl;
#endif

	roadMap.outputResults();
}
