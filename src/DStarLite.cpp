#include "../include/DStarLite.h"
#include "../include/GridStateSpace.h"
#include "../include/GridStateSpaceHeuristics.h"
#include <limits>

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::ComputeInitialPath(StateSpaceType start, StateSpaceType goal) {
	Clear();
	start_ = start;
	Slast_ = start;
	// goal is the starting poiont of the search
	goal_ = goal;
	statespaceToRhs_.emplace(goal_, 0.0);
	auto key = CalculateKey(goal_);
	queue_.Emplace(goal_, key.first, key.second);
	ComputeShortestPath();
}

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::RecomputePath() {
	// Start point has moved, update km.
	if (Slast_ != start_) {
		Heuristics heuristics;
		Km_ += heuristics(Slast_, start_);
		Slast_ = start_;
	}
	// Edge costs have changed, update vertices affected by the edge change.
	for (auto edge : recentlyUpdatedEdge_) {
		UpdateVertex(edge.first);
	}
	recentlyUpdatedEdge_.clear();
	ComputeShortestPath();
}

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::UpdateEdgeCost(StateSpaceType edgeStart, StateSpaceType edgeEnd, double cost) {
	auto edgePair = std::make_pair(edgeStart, edgeEnd);
	changedEdgeCostsMap_[edgePair] = cost;
	recentlyUpdatedEdge_.insert(edgePair);
}

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::MoveTo(StateSpaceType newStart) {
	// Check whether new start point is on the path point.
	bool onPath = false;
	for (const auto& point : path_) {
		if (point == newStart) {
			onPath = true;
			break;
		}
	}
	if (!onPath) {
		throw std::out_of_range("DStarLite::MoveTo(): newStart needs to be on the computed path.");
	}
	start_ = newStart;
}

template<typename StateSpaceType, typename Heuristics>
std::vector<StateSpaceType> DStarLite<StateSpaceType, Heuristics>::GetPath() {
	return path_;
}

/*****************************************Private Functions***********************************************/

template<typename T>
bool ApproximatelyEqual(T a, T b, T epsilon) {
	return std::abs(a - b) < epsilon;
}

template<typename StateSpaceType, typename Heuristics>
std::pair<double, double> DStarLite<StateSpaceType, Heuristics>::CalculateKey(StateSpaceType ss) {
	Heuristics heuristics;
	return std::make_pair(
		std::min(GetGScore(ss), GetRhs(ss)) + heuristics(start_, ss) + Km_,
		std::min(GetGScore(ss), GetRhs(ss)));
}

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::UpdateVertex(StateSpaceType ss) {
	// Update the rhs.
	if (ss != goal_) {
		statespaceToRhs_[ss] = ComputeRhs(ss);
	}
	if (queue_.Contains(ss)) {
		queue_.Delete(ss);
	}
	// If current vertex is incosistent, push it to the queue.
	if (ApproximatelyEqual(GetGScore(ss), GetRhs(ss), EPSILON)) {
		auto key = CalculateKey(ss);
		queue_.Emplace(ss, key.first, key.second);
	}
}

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::ComputeShortestPath() {
	auto topItem = queue_.Top();
	auto topKey = std::make_pair(std::get<1>(topItem), std::get<2>(topItem));
	while (KeyLessThan(topKey, CalculateKey(start_)) 
		|| !ApproximatelyEqual(GetRhs(start_), GetGScore(start_), EPSILON))
	{
		AugmentedPriorityQueue<StateSpaceType>::Container topItem = queue_.Top();
		StateSpaceType topState = std::get<0>(topItem);
		auto oldKey = std::make_pair(std::get<1>(topItem), std::get<2>(topItem));
		queue_.Pop();

		auto topKey = CalculateKey(topState);
		// Top item has outdated key.
		if (KeyLessThan(oldKey, topKey)) {
			queue_.Emplace(topState, topKey.first, topKey.second);
		}
		// Top item is overconsitent.
		else if (GetGScore(topState) - GetRhs(topState) > EPSILON) {
			statespaceToGscore_[topState] = GetRhs(topState);
			auto predecessorsVec = topState.GetPredecessors();
			for (const auto& predeceossorPair : predecessorsVec) {
				StateSpaceType predecessor = dynamic_cast<StateSpaceType&>(*(predeceossorPair.first));
				UpdateVertex(predecessor);
			}
		}
		// Top item is underconsistent.
		else {
			statespaceToGscore_[topState] = std::numeric_limits<double>::infinity();
			UpdateVertex(topState);
			auto predecessorsVec = topState.GetPredecessors();
			for (const auto& predeceossorPair : predecessorsVec) {
				StateSpaceType predecessor = dynamic_cast<StateSpaceType&>(*(predeceossorPair.first));
				UpdateVertex(predecessor);
			}
		}
	}
}

template<typename StateSpaceType, typename Heuristics>
double DStarLite<StateSpaceType, Heuristics>::ComputeRhs(StateSpaceType ss) {
	auto successorsVec = ss.GetSuccessors();
	double rhs = std::numeric_limits<double>::infinity();
	for (const auto& successorPair : successorsVec) {
		StateSpaceType successor = dynamic_cast<StateSpaceType&>(*(successorPair.first));
		double cost = successorPair.second;
		// Check if the cost has been updated.
		auto it = changedEdgeCostsMap_.find(std::make_pair(ss, successor));
		if (it != changedEdgeCostsMap_.end()) {
			cost = it->second;
		}
		double gscore = GetGScore(successor);
		if (!isinf(gscore) && !isinf(cost)) {
			rhs = std::min(rhs, cost + GetGScore(successor));
		}
	}
	return rhs;
}

template<typename StateSpaceType, typename Heuristics>
double DStarLite<StateSpaceType, Heuristics>::GetRhs(StateSpaceType ss) {
	auto it = statespaceToRhs_.find(ss);
	if (it != statespaceToRhs_.end()) {
		return it->second;
	}
	return std::numeric_limits<double>::infinity();
}

template<typename StateSpaceType, typename Heuristics>
double DStarLite<StateSpaceType, Heuristics>::GetGScore(StateSpaceType ss) {
	auto it = statespaceToGscore_.find(ss);
	if (it != statespaceToGscore_.end()) {
		return it->second;
	}
	return std::numeric_limits<double>::infinity();
}

template<typename StateSpaceType, typename Heuristics>
void DStarLite<StateSpaceType, Heuristics>::Clear() {
	queue_.Clear();
	changedEdgeCostsMap_.clear();
	recentlyUpdatedEdge_.clear();
	statespaceToRhs_.clear();
	statespaceToGscore_.clear();
}

template<typename StateSpaceType, typename Heuristics>
bool DStarLite<StateSpaceType, Heuristics>::KeyLessThan(
	std::pair<double, double> key1, std::pair<double, double> key2) 
{
	return (key2.first - key1.first) > EPSILON 
		|| ApproximatelyEqual(key1.first, key2.first, EPSILON) && (key2.second - key1.second) > EPSILON;
}

template class DStarLite<GridStateSpace, GridStateSpaceHeuristics>;