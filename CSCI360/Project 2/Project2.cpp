#include "Project2.h"

/**
* @brief default constructor
*/
Project2::Project2(Simulator* sim1) {
	// Initialize known Obstacles
	std::vector<Point2D> knownObstacles = sim1->getKnownObstacleLocations();
	for (std::vector<Point2D>::iterator i = knownObstacles.begin(); i != knownObstacles.end(); ++i)
		obstacle_set.insert(*i);
	// Run A* for the first time
    aStar = new AStar(knownObstacles, sim1->getTarget(), sim1->SX, sim1->SY);
    first_run = true;
}

/**
 * @brief get optimal action
 * @param sim simulator pointer
 * @param r robot pointer
 * @return optimal action
 */
RobotAction Project2::getOptimalAction(Simulator* sim1, Robot* r1) {
	std::vector<Point2D> newObstacles = r1->getLocalObstacleLocations();
	if (!newObstacles.empty() || first_run){ // add obstacles to environment knowledge and rerun A*
        if (first_run) // ensure AStar run on first run through
            first_run = false;
		for (std::vector<Point2D>::iterator i = newObstacles.begin(); i != newObstacles.end(); ++i)
			obstacle_set.insert(*i);
        // run astar again
        delete currentBestPath;
        currentBestPath = aStar->getPath(r1->getPosition(), newObstacles);
	}

	//  Since there are no new obstacles continue along our path
	currentTop = *currentBestPath->top();
	currentBestPath->pop();
	return (convertToAction(r1->getPosition(), currentTop));
}

Project2::~Project2(){
	delete aStar;
}



RobotAction Project2::convertToAction(const Point2D &curLocation, const Point2D &nextLocation) {
        // Move the robot according to best move and current location
        if (nextLocation.y < curLocation.y){  // if should move left
            if (nextLocation.x < curLocation.x)  // if should move up
                return MOVE_UP_LEFT;
            else if (nextLocation.x > curLocation.x)  // if should move down
                return MOVE_DOWN_LEFT;
            else
                return MOVE_LEFT;
        } else if (nextLocation.y > curLocation.y) {  // if should move right
            if (nextLocation.x < curLocation.x)  // if should move up
                return MOVE_UP_RIGHT;
            else if (nextLocation.x > curLocation.x)  // if should move down
                return MOVE_DOWN_RIGHT;
            else
                return MOVE_RIGHT;
        } else {
            if (nextLocation.x > curLocation.x)  // if should move down
                return MOVE_DOWN;
            else
                return MOVE_UP;
        }
}
