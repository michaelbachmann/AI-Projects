#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {

}

PriorityQueue::~PriorityQueue(){

}

State* PriorityQueue::pop() {
	State* firstElement = *min_heap.begin();
	min_heap.erase(min_heap.begin());
	return firstElement;
}

State* PriorityQueue::peek() {
	State* firstElement = *min_heap.begin();
	return firstElement;
}

void PriorityQueue::push(State* state) {
	min_heap.insert(state);
}

bool PriorityQueue::contains(const State& state) {
	for (std::set<State*>::iterator i = min_heap.begin(); i != min_heap.end(); ++i) {
		if (*(*i) == state)
			return true;
	}
	return false;
}

bool PriorityQueue::empty() const {
	return min_heap.empty();
}

void PriorityQueue::printQueue() {
	for (auto x : min_heap)
		std::cout << *x;
}

// Call find and store, update value, remove from set, add new value
void PriorityQueue::update(State& state, const Point2D& goal) {
	std::set<State*>::iterator it = min_heap.end();
	for (std::set<State*>::iterator i = min_heap.begin(); i != min_heap.end(); ++i) {
		if (*(*i) == state) {
			it = i;
			break;
		}
	}
	if (it != min_heap.end()) {
		// State stateToUpdate = *(*it);
		State* ptr = &state;
		// stateToUpdate.updateState(gValue, goal);
		min_heap.erase(it);
		min_heap.insert(ptr);
	}
}

// Returns null if not found
State* PriorityQueue::find(const State& state) {
	std::set<State*>::iterator it = min_heap.end();
	for (std::set<State*>::iterator i = min_heap.begin(); i != min_heap.end(); ++i) {
		if (*(*i) == state) {
			it = i;
			break;
		}
	}
	return *it;
}