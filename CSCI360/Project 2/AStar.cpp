#include "AStar.h"

AStar::AStar(){}

AStar::AStar(std::vector<Point2D> &obstacles, Point2D goal_2d, float x_bound, float y_bound) {
	this->goal_2d = goal_2d;
	this->goal_state = new State(goal_2d);;
	bounds = std::make_pair((int)x_bound, (int)y_bound);
	// Add in global obstacles
	for (std::vector<Point2D>::iterator i = obstacles.begin(); i != obstacles.end(); ++i) {
		State* current_tate = new State(*i);
		obstacle_set.insert(current_tate);
	}
}
AStar::~AStar() {
	for (std::set<State*>::iterator i = obstacle_set.begin(); i != obstacle_set.end(); ++i)
		delete (*i);
	for (std::set<State*>::iterator i = closed_list.begin(); i != closed_list.end(); ++i)
		delete (*i);
	delete goal_state;
}

// This is whats called by the robot to get its best path
std::stack<Point2D*>* AStar::getPath(Point2D initial_state, std::vector<Point2D> new_obstacles) {
	closed_list.clear();
	for (std::vector<Point2D>::iterator i = new_obstacles.begin(); i != new_obstacles.end(); ++i)
		obstacle_set.insert(new State(*i));
	PriorityQueue* frontier = new PriorityQueue();
	State* init = new State(initial_state, goal_2d, 0, NULL);
	frontier->push(init);
	searchHelper(init, frontier);
	return generatePath();
}

std::stack<Point2D*>* AStar::generatePath() {
	std::stack<Point2D*>* best_path = new std::stack<Point2D*>();
	best_path->push(goal_state->convertTo2D());
	State* seeker = goal_state->getParent();

	while (seeker->getParent()) {
		best_path->push(seeker->convertTo2D());
		seeker = seeker->getParent();
	}
	return best_path;
}

void AStar::searchHelper(State* init, PriorityQueue* frontier) {
	State* consider = frontier->pop();
	closed_list.insert(consider);
	if (*consider == *goal_state) {
		goal_state->setParent(init);
		return;
	}
	// Get Neighbors
	std::list<State*>* adjacent_list = getAdjacent(consider);
	// For all neighbors
	for (std::list<State*>::iterator neighbor = adjacent_list->begin(); neighbor != adjacent_list->end(); ++neighbor) {
		// If its not in the closed list or obstacle list lets check it
		if ((obstacle_set.count(*neighbor) == 0) && (closed_list.count(*neighbor) == 0)) {
			// See if its in the frontier
			if (frontier->contains(**neighbor)) {
				// if it is see if we found a better path
				if (  frontier->find(*(*neighbor))->getG() > ((*neighbor)->getG())) {
					(*neighbor)->setParent(consider);
					frontier->update(*(*neighbor), goal_2d);
				}
			} else
				frontier->push(*neighbor);
		}
	}

	searchHelper(consider,frontier);
}

std::list<State*>* AStar::getAdjacent (State* current) {
	std::list<State*>* list_to_return = new std::list<State*>();
	int x = (int)current->getX();
	int y = (int)current->getY();
	int x_right = x - 1;
	int x_left = x + 1;
	int y_bot = y - 1;
	int y_top = y + 1;


	// Check if on left, if not check if on right
	if (x == ((int)bounds.first - 1))
		x_left--;
	else if (x == 0)
		x_right++;

	// Check if on top bound, if not check if on bottom bound
	if (y == ((int)bounds.second-1))
		y_top--;
	else if (y == 0)
		y_bot++;

	// Loop through bounds
	for (int i = x_right; i <= x_left; ++i) {
		for (int j = y_bot; j <= y_top; ++j) {
			if (!((i == x) && (j == y))) {
				if ((abs(x-i) != 0) && (abs(y-j)!=0) ) {
					// std::cout << "Diag: ( " << i << ", " << j << " )\n";
					list_to_return->push_back(new State(*(new Point2D(i,j)), goal_2d, current->getG()+1.5, current));
				}
				else
					list_to_return->push_back(new State(*(new Point2D(i,j)), goal_2d, current->getG()+1, current));
			}
		}
	}
	return list_to_return;
}

void AStar::testHelper(bool print_init_state, bool print_c_list, bool print_obstacle_set) {
	if (print_init_state) {
		std::cout << "\n--------- Printing Init State ---------\n";
		std::cout << "goal_state = " << *goal_state;
		std::cout << "goal_2d = " << "( " << goal_2d.x << ", " << goal_2d.y << " )\n";
		std::cout << "obstacle_set size = " << obstacle_set.size() << "\n";
		std::cout << "closed_list size = " << closed_list.size() << "\n";
		std::cout << "Bounds = " << "( " << bounds.first << ", " << bounds.second << " )\n";
		std::cout << "---------------------------------------\n";
	}
	if ((closed_list.size() != 0) && print_c_list) {
		std::cout << "\n-------- Printing Closed List -------\n";
		std::cout << "closed_list size = " << closed_list.size() << "\n";
		for (auto x : closed_list)
			std::cout << *x;
		std::cout << "---------------------------------------\n";
	}
	if ((obstacle_set.size() != 0) && print_obstacle_set) {
		std::cout << "\n------- Printing Obstacle Set -------\n";
		std::cout << "obstacle_set size = " << obstacle_set.size() << "\n";
		for (auto x : obstacle_set)
			std::cout << *x;
		std::cout << "---------------------------------------\n";
	}
}