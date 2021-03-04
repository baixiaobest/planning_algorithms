#ifndef DSTAR_LITE_H
#define DSTAR_LITE_H

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility> 
#include "DStarUtil.h"
#include "AugmentedPriorityQueue.h"
#include "StateSpaceHash.h"

template<typename StateSpaceType, typename Heuristics>
class DStarLite {
public:
	/** Initial A star search of path from end point to start point. */
	void ComputeInitialPath(StateSpaceType start, StateSpaceType goal);
	/** Recompute the optimal path after edge cost update or robot has moved. */
	void RecomputePath();
	/** Update the edge cost of the map. */
	void UpdateEdgeCost(StateSpaceType edgeStart, StateSpaceType edgeEnd, double cost);
	/** Move the robot along the previously computed path. */
	void MoveTo(StateSpaceType newStart);
	/** Get the optimal path. */
	std::vector<StateSpaceType> GetPath();
private:
	/** Calculate the queue priority for statespace ss. */
	std::pair<double, double> CalculateKey(StateSpaceType ss);
	/** Update the rhs value for the vertex, and decide whether to insert vertex into queue. */
	void UpdateVertex(StateSpaceType ss);
	/** Main search loop. */
	void ComputeShortestPath();
	/** Compute the rhs of a vertex. */
	double ComputeRhs(StateSpaceType ss);
	/** Get the rhs of a vertex. */
	double GetRhs(StateSpaceType ss);
	/** Get the g score of a vertex. */
	double GetGScore(StateSpaceType ss);
	/** Clear all the queue items and maps. */
	void Clear();
	/** Compare two keys. 
	  * Return true if key1 is less than key2, therefore key1 appears before key2 on the queue.
	  */
	bool KeyLessThan(std::pair<double, double> key1, std::pair<double, double> key2);

	StateSpaceType start_;
	StateSpaceType goal_;
	/** Position of the robot the shortest path is computed last time. */
	StateSpaceType Slast_;
	double Km_ = 0;
	/** Computed optimal path. */
	std::vector<StateSpaceType> path_;

	/** A priority queue. */
	AugmentedPriorityQueue<StateSpaceType> queue_;
	
	/** This contains a map from a pair of statespace to cost. 
	  * It only stores the edge cost that has changed from default cost.
	  * Pair of statespace (u, v), u is the predecessor of v.
	  */
	std::unordered_map<std::pair<StateSpaceType, StateSpaceType>, double, StateSpacePairHash<StateSpaceType>>
		changedEdgeCostsMap_;

	/** This contains a set of recently updated edges, they will need to be processed by running UpdateVertex().*/
	std::unordered_set<std::pair<StateSpaceType, StateSpaceType>, StateSpacePairHash<StateSpaceType>>
		recentlyUpdatedEdge_;

	std::unordered_map<StateSpaceType, double, StateSpaceHash<StateSpaceType>> statespaceToRhs_;
	std::unordered_map<StateSpaceType, double, StateSpaceHash<StateSpaceType>> statespaceToGscore_;

	const double EPSILON = 1e-3;
};

#endif
