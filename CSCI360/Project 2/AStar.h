#ifndef ASTAR_H
#define ASTAR_H
#include "Vector2D.h"
#include "State.h"
#include <math.h>
#include <queue>
#include <set>
#include <list>
#include "PriorityQueue.h"

class AStar {
private:
	State* goal_state;
	Point2D goal_2d;
	std::set<State*, state_set_comparator_p> obstacle_set;
	std::set<State*, state_set_comparator_p> closed_list;
	std::pair<int,int> bounds;
public:
	AStar();
	~AStar();

	// Initialize AStar with known obstacles and the goal state
	AStar(std::vector<Point2D> &obstacles, Point2D goal_2d, float x_bound, float y_bound);

	// Returns a list of State pointers given adjacent nodes
	std::list<State*>* getAdjacent (State* current);

	// Recursive function that searches out the goal state and assigns parents to nodes along the way
	void searchHelper(State* init, PriorityQueue* frontier);

	// Main search function returns a queue of Point 2d with the best path
	std::queue<Point2D*>* getPath(Point2D initial_state, std::vector<Point2D> new_obstacles);

	// Recursively follows the closesd list from the goal and adds the path to the queue
	std::queue<Point2D*>* generatePath();

	void testHelper(bool print_init_state, bool print_c_list, bool print_obstacle_set);


	
};

#endif