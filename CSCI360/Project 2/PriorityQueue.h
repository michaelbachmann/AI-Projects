#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE
#include <set>
#include "State.h"
#include "Vector2D.h"

class PriorityQueue {
private:
	// std::set<State,state_priority_comparator> min_heap;
	std::set<State*,state_priority_comparator_p> min_heap;
public:
	PriorityQueue();
	~PriorityQueue();
	State* peek();
	State* pop();
	void push(State* state);
	bool contains(const State& state);
	bool empty() const;
	// Call find and store, update value, remove from set, add new value
	void update(State& state, const Point2D& goal);
	void printQueue();
	// Returns null if not found
	State* find(const State& state);


};

#endif