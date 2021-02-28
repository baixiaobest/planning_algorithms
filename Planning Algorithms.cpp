// Planning Algorithms.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "include/DStarLite.h"
#include "include/AugmentedPriorityQueue.h"
#include "include/GridStateSpace.h"

using namespace std;

int main()
{
	DStarLite dstarLite;
	dstarLite.ComputeShortestPath();
	AugmentedPriorityQueue<GridStateSpace> q;
	GridStateSpace ss(0, 2);
	q.Emplace(ss, 1, 2);
	std::cout << q.Size() << std::endl;
	return 0;
}
