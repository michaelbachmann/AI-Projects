#ifndef TEST_H
#define TEST_H
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <set>
#include "Robot.h"
#include "Vector2D.h"
#include "State.h"
#include "PriorityQueue.h"
#include "AStar.h"
#include <float.h>
// #include "Simulator.h"
// #include "Project2.h"

struct point_set_comparator {
    bool operator() (const Point2D& lhs, const Point2D& rhs) const {
        return (std::make_pair(lhs.x,lhs.y) < std::make_pair(rhs.x,rhs.y));
    }
};

class Test {
private:
    std::set<Point2D, point_set_comparator> obstacle_set;
    Point2D* goalState;
    PriorityQueue* min_heap;
    State* curState;
    AStar* a_star;
    std::vector<Point2D> obs;
public:
	Test();
	~Test();

	// Test AStar
	void test_a_star_adjacent();
	void test_a_star_init();
	// void test_a_star_getPath();

	// Test Priority Queue
	void test_push();
	void test_pop();
	void test_update();
	void test_contains();

	// Test State unctions
	void test_state_comparator_equals();
	void test_state_comparator_order();
	void test_state_2dpoint_compare();

	// Test Point2D Comparator
    void test_point_set_comparator_increasing();
    void test_point_set_comparator_equals();
	
};


#endif