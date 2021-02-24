#ifndef AUGEMENTED_PRIORITY_QUEUE_H
#define AUGEMENTED_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <limits>
#include <unordered_map>
#include <tuple>
#include "PriorityItem.h"
#include "PriorityItemComparator.h"

/**
 * AugmentedPriorityQueue is based on std::priority_queue with additional properties.
 * Property 1: Uniqueness: Items in the queue are unique in terms of their corresponding statespace.
 *	No item of same statespace will exist simultaneously in the queue.
 * Property 2: Updatable: Item in the queue can be updated with different priority.
 * Property 3: Deletable: Item in the queue can be deleted.
 * Property 4: Lexicographical priorities: Priority is a pair of values, ordered by lexicographical order.
 * Implementation:
 * In actual implementation, the underlying std priority queue does not have the property of 1, 2, 3. To obtain
 * the above properties, a separte unordered_map is used to keep track of valid items in the std priority queue.
 * And each item in the queue has an unique id. unordered_map maintains mapping from statespace to this unique id.
 * Therefore an item is considered INVALID if unordered_map does not contain the id of that item. The key of the
 * unordered_map is unique, thus obtaining property 1 uniqueness. Since unordered_map is updatable and deletable,
 * property 2 and property 3 are obtained.
 */
template<typename StateSpaceType>
class AugmentedPriorityQueue {
public:
	/** Item/container for interfacing AugmentedPriorityQueue. Statespace and its two priorities values.*/
	using Container = std::tuple<StateSpaceType, double, double>;

	/** Priority queue is empty, return true. */
	bool Empty() const;

	/** Size of the queue. */
	std::size_t Size() const;

	/** Top of priority queue. 
	 *  If the priority queue is effectively empty, Top function has undefined behavior.
	 */
	Container Top();

	/** Push new and non duplicate item into the queue. 
	 *  item: The item containing state space and priority.
	 *  Throw error if item of same statespace is already in the queue.
	 */
	void Push(const Container& item);

	/** Pop top item from the queue. */
	void Pop();

	/** Update the priority value of an item. Throw error if there is no existing item in the queue.
	 *  item: contains the statespace and the updated priority.
	 */
	void Update(const Container& item);

	/** Delete an item that has corresponding statespace.
	 *  statespace: statespace of the item you want to delete.
	 */
	void Delete(StateSpaceType statespace);

	/** Check if queue contains item of corresponding statespace. 
	 *  statespace: statespace of the item in the queue.
	 */
	bool HasItem(StateSpaceType statespace) const;

private:
	/** Names of the Container tuple. */
	enum ContainerItemName {STATE_SPACE, PRIORITY1, PRIORITY2};

	/** Type of item that gets pushed to priority queue. */
	using PriorityItemType = PriorityItem<StateSpaceType>;

	/** Priority queue that stores priority item.*/
	std::priority_queue<PriorityItemType, std::vector<PriorityItemType>, PriorityItemComparator<StateSpaceType>>
		priorityQueue_;

	/** A map from statespace to id of the priority item. 
	 *  Each statespace at most has one corresponding item in priority queue.
	 *  In actual implementation, there will be duplicate item in the queue, having
	 *  a map can prevent the hassel of deleting item from the queue.*/
	std::unordered_map<StateSpaceType, int> statespaceToId_;

	/** Next id that will be assigned to new item pushed to the queue. 
	 *  Each priority item will be uniquely identified by their id.
	 */
	int currentId_ = 0;

	/** Maximum id that can be assigned to the priority item. 
	 *  After all number is assigned, id starts from 0 again. 
	 */
	constexpr int MAX_ID = INT_MAX - 1;
};

#endif