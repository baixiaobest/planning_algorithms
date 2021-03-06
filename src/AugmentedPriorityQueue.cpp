#include "../include/AugmentedPriorityQueue.h"
#include "../include/GridStateSpace.h"
#include <utility>
#include <stdexcept>

template<typename StateSpaceType>
bool AugmentedPriorityQueue<StateSpaceType>::Empty() const {
	return statespaceToId_.empty();
}

template<typename StateSpaceType>
std::size_t AugmentedPriorityQueue<StateSpaceType>::Size() const {
	return statespaceToId_.size();
}

template<typename StateSpaceType>
typename AugmentedPriorityQueue<StateSpaceType>::Container AugmentedPriorityQueue<StateSpaceType>::Top() {
	if (statespaceToId_.size() == 0) {
		throw std::out_of_range("AugmentedPriorityQueue::Top(): Queue is already empty.");
	}
	AugmentedPriorityQueue<StateSpaceType>::Container container;
	while (!priorityQueue_.empty()) {
		// Get first item from the queue.
		PriorityItem<StateSpaceType> topItem = priorityQueue_.top();
		StateSpaceType statespace = topItem.GetStateSpace();
		int id = topItem.GetId();
		// Check if the item is valid item, meaning not deleted or updated.
		auto it = statespaceToId_.find(statespace);
		if (it != statespaceToId_.end() && it->second == id) {
			std::pair<double, double> priority = topItem.GetPriority();
			std::get<STATE_SPACE>(container) = statespace;
			std::get<PRIORITY1>(container) = priority.first;
			std::get<PRIORITY2>(container) = priority.second;
			break;
		}
		// When the item is invalid (deleted, or priority is updated) next iteration continues.
		priorityQueue_.pop();
	}
	
	return container;
}

template<typename StateSpaceType>
void AugmentedPriorityQueue<StateSpaceType>::Push(const Container& item) {
	auto it = statespaceToId_.find(std::get<STATE_SPACE>(item));
	if (it != statespaceToId_.end()) {
		throw std::invalid_argument(
			"AugmentedPriorityQueue::Push: Statespace of the item to be pushed already exist in the queue.");
	}

	statespaceToId_.emplace(std::get<STATE_SPACE>(item), currentId_);

	PriorityItemType qItem;
	qItem.SetId(currentId_)
		.SetStateSpace(std::get<STATE_SPACE>(item))
		.SetPriority(std::make_pair(std::get<PRIORITY1>(item), std::get<PRIORITY2>(item)));
	priorityQueue_.push(qItem);

	currentId_ = (currentId_ + 1) % MAX_ID;
}

template<typename StateSpaceType>
void AugmentedPriorityQueue<StateSpaceType>::Emplace(
	StateSpaceType statespace, 
	double priority1, 
	double priority2) 
{
	Container item = std::make_tuple(statespace, priority1, priority2);
	Push(item);
}

template<typename StateSpaceType>
void AugmentedPriorityQueue<StateSpaceType>::Pop() {
	while (!priorityQueue_.empty()) {
		PriorityItem<StateSpaceType> topItem = priorityQueue_.top();
		StateSpaceType statespace = topItem.GetStateSpace();
		int id = topItem.GetId();
		auto it = statespaceToId_.find(statespace);
		if (it != statespaceToId_.end() && it->second == id) {
			priorityQueue_.pop();
			statespaceToId_.erase(it);
			break;
		}
		priorityQueue_.pop();
	}
}

template<typename StateSpaceType>
void AugmentedPriorityQueue<StateSpaceType>::Update(StateSpaceType statespace, double priority1, double priority2) {
	auto it = statespaceToId_.find(statespace);
	if (it == statespaceToId_.end()) {
		throw std::invalid_argument(
			"AugmentedPriorityQueue::Update: statespace of the item not in the queue, it cannot be updated.");
	}

	// Replace old item id with new one.
	statespaceToId_.erase(it);
	statespaceToId_.emplace(statespace, currentId_);

	// Push updated item to queue.
	PriorityItemType qItem;
	qItem.SetId(currentId_)
		.SetStateSpace(statespace)
		.SetPriority(std::make_pair(priority1, priority2));
	priorityQueue_.push(qItem);

	currentId_ = (currentId_ + 1) % MAX_ID;
}

template<typename StateSpaceType>
void AugmentedPriorityQueue<StateSpaceType>::Delete(StateSpaceType statespace)
{
	auto it = statespaceToId_.find(statespace);
	if (it != statespaceToId_.end()) {
		statespaceToId_.erase(it);
	}
}

template<typename StateSpaceType>
bool AugmentedPriorityQueue<StateSpaceType>::Contains(StateSpaceType statespace) const {
	auto it = statespaceToId_.find(statespace);
	return it != statespaceToId_.end();
}

template<typename StateSpaceType>
void AugmentedPriorityQueue<StateSpaceType>::Clear() {
	priorityQueue_ = std::priority_queue<PriorityItemType, std::vector<PriorityItemType>, PriorityItemComparator<StateSpaceType>>();
	statespaceToId_.clear();
	currentId_ = 0;
}

template class AugmentedPriorityQueue<GridStateSpace>;