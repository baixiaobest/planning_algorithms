#ifndef PRIORITY_ITEM_H
#define PRIORITY_ITEM_H

#include <utility>

/** This is the item that pushed into Augmented Priority Queue. It is only internally used by Augmented Priority Queue */
template<typename StateSpaceType>
class PriorityItem {
public:
	PriorityItem& SetPriority(std::pair<double, double> priority) { 
		priority_ = priority; 
		return *this;
	};

	PriorityItem& SetId(int id) {
		id_ = id;
		return *this;
	}

	PriorityItem& SetStateSpace(const StateSpaceType& stateSpace) {
		stateSpace_ = stateSpace;
		return *this;
	}

	/** 
	 * The priority of the two items are lexicographical order, we compare the
	 * first item in priority, then compare the second item in priority.
	 */
	bool operator< (const PriorityItem& other) const {
		return priority_.first < other.first
			|| priority_.first == other.first && priority_.second < other.second;
	};

	std::pair<double, double> GetPriority() const { return priority_; };

	int GetId() const { return id_; };

	StateSpaceType GetStateSpace() const { return stateSpace_; };

private:
	/** Pirority is f score and rhs score. */
	std::pair<T, T> priority_;
	/** ID of this item, this will be used to invalidate outdated item. */
	int id_;
	/** A state space object that inherits from StateSpace class. */
	StateSpaceType stateSpace_;
};

#endif