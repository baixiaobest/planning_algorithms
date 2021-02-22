#ifndef PRIORITY_ITEM_H
#define PRIORITY_ITEM_H

#include <pair>

template<typename StateSpaceType>
class PriorityItem {
public:
	PriorityItem& SetPriority(std::pair priority) { 
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

	std::pair GetPriority() { return priority_; };

	int GetId() { return id_; };

	StateSpaceType GetStateSpace{ return stateSpace_; };

private:
	/** Pirority is f score and rhs score. */
	std::pair priority_;
	/** ID of this item, this will be used to invalidate outdated item. */
	int id_;
	StateSpaceType stateSpace_;
};

#endif