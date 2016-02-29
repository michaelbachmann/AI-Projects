#ifndef Project2_hpp
#define Project2_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"
#include "State.h"
#include "PriorityQueue.h"
#include "AStar.h"

struct point_set_compare {
    bool operator() (const Point2D& lhs, const Point2D& rhs) const {
        return std::make_pair(lhs.x, lhs.y) < std::make_pair(rhs.x, rhs.y);
        // if (lhs.x != rhs.x && lhs.y != rhs.y)
        //     return false;
        // return true;
    }
};

class Project2 {
private:
    std::stack<Point2D*>* currentBestPath;
    std::vector<Point2D> obstacleList;
    std::set<Point2D, point_set_compare> obstacle_set;
    Point2D currentTop;
    AStar* aStar;
    bool first_run;
public:
    /**
     * @brief default constructor
     */
    Project2(Simulator* sim1);
    // void clearQueue(std::queue<Point2D> &q);
    /**
     * @brief get optimal action
     * @param sim1 simulator pointer
     * @param r robot pointer
     * @return optimal action
     */
    RobotAction getOptimalAction(Simulator* sim1, Robot* r1);
    RobotAction convertToAction(const Point2D &curLocation, const Point2D &nextLocation);
    ~Project2();
};

#endif
