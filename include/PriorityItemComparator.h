#ifndef PRIORITY_ITEM_COMPARATOR
#define PRIORITY_ITEM_COMPARATOR

#include "PriorityItem.h"

/** Comparator internally used by the Augmented Priority Queue. */
template<typename StateSpaceType>
class PriorityItemComparator {
	bool operator() (const PriorityItem<StateSpaceType>& a, const PriorityItem<StateSpaceType>& b) {
		return a < b;
	}
};

#endif