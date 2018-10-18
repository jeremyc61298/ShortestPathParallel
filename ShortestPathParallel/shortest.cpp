// -------------------------------------------------
// shortest.cpp
// Jeremy Campbell
// Uses the Floyd-Warshall Algorithm to find the 
// shortest path between two locations in parallel
// using OpenMP. The main logic for this is in 
// the RoadMap class.
// -------------------------------------------------
#include "RoadMap.hpp"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

//#define DEBUG

int main()
{
	RoadMap roadMap;
	roadMap.readRoads();
	roadMap.readRoutes();

	auto startTime = high_resolution_clock::now();
	roadMap.computeShortestLengths();
	auto endTime = high_resolution_clock::now();

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
	
	auto totalTime = duration_cast<milliseconds>(endTime - startTime);
	cerr << "Total Parallel Time: " << totalTime.count() << "ms" << endl;
}
