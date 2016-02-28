#ifndef Project2_hpp
#define Project2_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"
#include "AStar.h"

struct point_set_compare {
    bool operator() (const Point2D& lhs, const Point2D& rhs) const {
        if (lhs.x != rhs.x && lhs.y != rhs.y)
            return false;
        return true;
    }
};

class Project2 {
private:
    std::queue<Point2D> currentBestPath;
    // std::vector<Point2D> obstacleList;
    // std::set<Point2D, point_set_compare> obstacle_set;
    Point2D currentTop;
    AStar* aStar;
public:
    /**
     * @brief default constructor
     */
    Project2(Simulator* sim1);
    void clearQueue(std::queue<Point2D> &q);
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
