#ifndef PRIORITY_ITEM_COMPARATOR
#define PRIORITY_ITEM_COMPARATOR

#include "PriorityItem.h"

class PriorityItemComparator {
	bool operator() (const PriorityItem& a, const PriorityItem& b) {
		return a < b;
	}
};

#endif