#ifndef Simulator_h
#define Simulator_h

#include <stdio.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include "Robot.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <stdlib.h>
#endif

#define EMPTY       0
#define OCCUPIED    1
#define TARGET      2
#define OBSTACLE    3
#define DEAD        4
#define HIDDEN_OBSTACLE 5
#define MAX_X       200
#define MAX_Y       200

#define MAKE_HIDDEN_OBSTACLES_KNOWN

/**
 * @class Simulator
 * @brief simulator object
 */
class Simulator
{
private:
    
    int TX, TY; /**< Target location */
    int targetRadiance; /**< radiance of target */
    int numObstacles; /**< number of obstacles */
    std::vector<Point2D> obstacleLocations; /**< locations of obstacles */
    std::vector<Point2D> hiddenObstacleLocations; /**< locations of hidden obstacles */
    int numHiddenObstacles; /**< number of hidden obstacles */
    float radianceArea; /**< how much radiance the target has (how far away it can be seen) */
    bool showHiddenObstacles; /**< show hidden obstacles */
public:
    
    int     SX, SY;  /**< environment size */
    int     AREA[MAX_X][MAX_Y];  /**< pre-allocated 2d array */
    Robot*  robot; /**< pointer to a robot */
    /**
     * @brief constructor
     * @param sx size of environment (x)
     * @param sy size of environment (y)
     */
    Simulator(int sx, int sy ) {
        SX = sx>MAX_X ? MAX_X : sx;
        SY = sy>MAX_Y ? MAX_Y : sy;
        this->clean();
        targetRadiance = 30;
        radianceArea = 5.0;
        showHiddenObstacles = true;
    }

    int getHeight() { return SX; }
    int getWidth() { return SY; }

    /**
     * @brief get the hidden obstacle locations at a certain point
     * @return hidden obstacle locations
     */
    std::vector<Point2D> getLocalObstacleLocations(Point2D p, bool hiddenOnly = false) {
        // Point2D p = Point2D(r->X, r->Y);
        Point2D p1 = Point2D(p.x + 1, p.y);
        Point2D p2 = Point2D(p.x - 1, p.y);
        Point2D p3 = Point2D(p.x, p.y + 1);
        Point2D p4 = Point2D(p.x, p.y - 1);
        Point2D p5 = Point2D(p.x + 1, p.y + 1);
        Point2D p6 = Point2D(p.x + 1, p.y - 1);
        Point2D p7 = Point2D(p.x - 1, p.y + 1);
        Point2D p8 = Point2D(p.x - 1, p.y - 1);
        std::vector<Point2D> pointsToCheck;
        pointsToCheck.push_back(p1); pointsToCheck.push_back(p2); pointsToCheck.push_back(p3);
        pointsToCheck.push_back(p4); pointsToCheck.push_back(p5); pointsToCheck.push_back(p6);
        pointsToCheck.push_back(p7); pointsToCheck.push_back(p8);
        
        std::vector<Point2D> obs;
        for (int i=0; i<pointsToCheck.size(); i++) {
            if (pointsToCheck[i].x >= 0 && pointsToCheck[i].y >= 0 &&
                pointsToCheck[i].x < this->SX && pointsToCheck[i].y < this->SY &&
                (AREA[(int)pointsToCheck[i].x][(int)pointsToCheck[i].y] == HIDDEN_OBSTACLE ||
                (!hiddenOnly && AREA[(int)pointsToCheck[i].x][(int)pointsToCheck[i].y] == OBSTACLE))) {
                obs.push_back(Point2D(pointsToCheck[i].x, pointsToCheck[i].y));

#ifdef MAKE_HIDDEN_OBSTACLES_KNOWN
                AREA[(int)pointsToCheck[i].x][(int)pointsToCheck[i].y] = OBSTACLE;
#endif
            }
        }
        
        return obs;
    }
//    std::vector<Point2D> getHiddenObstacleLocations() {
//        return hiddenObstacleLocations;
//    }
    /**
     * @brief get the locations of the obstacles
     * @return obstacle locations
     */
    std::vector<Point2D> getKnownObstacleLocations() {
        return obstacleLocations;
    }
    /**
     * @brief create random obstacles in the environment
     * @param num number of obstacles
     */
    void createRandomObstacles(int num) {
        // int x_1, x_2, x_3, x_4, x_5, x_6, y_1, y_2, y_3, y_4, y_5, y_6;
        // x_1 = 9;
        // x_2 = 7;
        // x_3 = 6;
        // x_4 = 3;
        // x_5 = 0;
        // x_6 = 0;

        // y_1 = 35;
        // y_2 = 23;
        // y_3 = 20;
        // y_4 = 34;
        // y_5 = 2;
        // y_6 = 6;
        // obstacleLocations.push_back(Point2D(x_1,y_1));
        // obstacleLocations.push_back(Point2D(x_2,y_2));
        // obstacleLocations.push_back(Point2D(x_3,y_3));
        // obstacleLocations.push_back(Point2D(x_4,y_4));
        // obstacleLocations.push_back(Point2D(x_5,y_5));
        // obstacleLocations.push_back(Point2D(x_6,y_6));
        // AREA[x_1][y_1] = OBSTACLE;
        // AREA[x_2][y_2] = OBSTACLE;
        // AREA[x_3][y_3] = OBSTACLE;
        // AREA[x_4][y_4] = OBSTACLE;
        // AREA[x_5][y_5] = OBSTACLE;
        // AREA[x_6][y_6] = OBSTACLE;

        for (int i=0; i<num; i++) {
            int ox = rand()%SX;
            int oy = rand()%SY;
            while ((ox == TX && oy == TY) || (ox == this->getRobot()->X && oy == this->getRobot()->Y)) {
                ox = rand()%SX;
                oy = rand()%SY;
            }
            AREA[ox][oy] = OBSTACLE;
            obstacleLocations.push_back(Point2D(ox, oy));
        }
    }
    /**
     * @brief create random obstacles in the environment
     * @param num number of obstacles
     */
    void createRandomHiddenObstacles(int num) {
        // int x_1, x_2, x_3, x_4, y_1, y_2, y_3, y_4;
        // x_1 = 0;
        // x_2 = 5;
        // x_3 = 5;
        // x_4 = 3;

        // y_1 = 9;
        // y_2 = 27;
        // y_3 = 31;
        // y_4 = 12;


        // hiddenObstacleLocations.push_back(Point2D(x_1,y_1));
        // hiddenObstacleLocations.push_back(Point2D(x_2,y_2));
        // hiddenObstacleLocations.push_back(Point2D(x_3,y_3));
        // hiddenObstacleLocations.push_back(Point2D(x_4,y_4));
        // AREA[x_1][y_1] = HIDDEN_OBSTACLE;
        // AREA[x_2][y_2] = HIDDEN_OBSTACLE;
        // AREA[x_3][y_3] = HIDDEN_OBSTACLE;
        // AREA[x_4][y_4] = HIDDEN_OBSTACLE;


        for (int i=0; i<num; i++) {
            int ox = rand()%SX;
            int oy = rand()%SY;
            while ((ox == TX && oy == TY) || (ox == this->getRobot()->X && oy == this->getRobot()->Y)) {
                ox = rand()%SX;
                oy = rand()%SY;
            }
            AREA[ox][oy] = HIDDEN_OBSTACLE;
            hiddenObstacleLocations.push_back(Point2D(ox, oy));
        }
    }
    /**
     * @brief clear the environment
     */
    void clean() {
        for (int x=0; x<SX; x++) {
            for (int y=0; y<SY; y++) {
                AREA[x][y] = EMPTY;
            }
        }
    }
    /**
     * @brief display the environment on the terminal
     */
    void display() {
        //printf("\033c"); // clear the terminal screen
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
        for (int x=0; x<SX; x++) {
            for (int y=0; y<SY; y++) {
                if (AREA[x][y]==EMPTY)
                    printf(".");
                else if (AREA[x][y]==TARGET)
                    printf("$");
                else if (AREA[x][y] == DEAD)
                    printf("X");
                else if (AREA[x][y] == OBSTACLE)
                    printf("#");
                else if (AREA[x][y] == HIDDEN_OBSTACLE)
                {
                    if (showHiddenObstacles)
                        printf("H");
                    else
                        printf("#");
                }
                else printf("O");
            }
            printf("\n");
        }
    }
    /**
     * @brief get the target
     * @return target position
     */
    Point2D getTarget() {
        return Point2D(TX,TY);
    }
    /**
     * @brief set target
     * @param tx target x coordinate
     * @param ty target y coordinate
     */
    void setTarget(int tx, int ty) {
        TX = tx;
        TY = ty;
        AREA[tx][ty] = TARGET;
    }
    /**
     * @brief set robot
     * @param r robot
     * @param x x coord of robot
     * @param y y coord of robot
     */
    void setRobot(Robot* r, int x, int y) {
        r->movePosition(x,y);
        robot = r;
        AREA[r->X][r->Y] = OCCUPIED;
    }
    /**
     * @brief get radiance of the target
     * @return radiance of target
     */
    int getTargetRadiance() {
        int X1 = TX - robot->X;
        int Y1 = TY - robot->Y;
        if (X1 == 0 && Y1 == 0) {
            return 1;
        } else {
            return -1;
        }
    }
    /**
     * @brief get radiance of the target
     * @return radiance of target
     */
    int getTargetDistance() {
        int X1 = TX - robot->X;
        int Y1 = TY - robot->Y;
        if (sqrt(X1*X1 + Y1*Y1) < radianceArea) {
            return sqrt(X1*X1 + Y1*Y1);
        } else {
            return -1;
        }
    }
    /**
     * @brief test for robot death
     * @param x x coordinate
     * @param y y coordinate
     * @return is robot dead (true) or alive (false)
     */
    bool testForRobotDeath(int x, int y) {
        return (AREA[x][y] == DEAD);
    }
    /**
     * @brief has robot found target?
     * @return true if yes, false otherwise
     */
    bool robotFoundTarget() {
        return (robot->X==TX && robot->Y==TY);
    }
    /**
     * @brief get the robot
     * @return pointer to robot
     */
    Robot* getRobot() {
        return this->robot;
    }
    /**
     * @brief is the environment occupied at (x,y)
     * @param x x coordinate of position
     * @param y y coordinate of position
     */
    bool isOccupied(int x, int y) {
        return (AREA[x][y]==OCCUPIED);
    }
    /**
     * @brief is there an obstacle at (x,y)
     * @param x x coordinate of position
     * @param y y coordinate of position
     */
    bool isInCollision(int x, int y) {
        return (AREA[x][y]==OBSTACLE  || AREA[x][y] == HIDDEN_OBSTACLE);
    }
    /**
     * @brief move the robot
     */
    void moveRobot()
    {
        Robot* r = this->getRobot();
        
        int x1 = r->X;
        int y1 = r->Y;
        
        
        int x2, y2;
        
        Vector2D d = r->getForce();  // get the force on robot
        double deg = d.getTheta();  // calculate the force direction
        if (deg>-22.5 && deg<=22.5)           { r->VX = 1;  r->VY = 0;
        } else if (deg>22.5 && deg<=67.5)     { r->VX = 1;  r->VY = 1;
        } else if (deg>67.5 && deg<=112.5)    { r->VX = 0;  r->VY = 1;
        } else if (deg>112.5 && deg<=157.5)   { r->VX = -1; r->VY = 1;
        } else if (deg<=-22.5 && deg>-67.5)   { r->VX = 1;  r->VY = -1;
        } else if (deg<=-67.5 && deg>-112.5)  { r->VX = 0;  r->VY = -1;
        } else if (deg<=-112.5 && deg>-157.5) { r->VX = -1; r->VY = -1;
        } else {                                r->VX = -1; r->VY = 0; }
        
        
        bool didMove = true;
        if (d.x != 0 || d.y != 0) {
            x2 = x1 + r->VX;
            x2 = x2 < 0 ? 0 : x2;
            x2 = x2 > SX ? SX : x2;
            y2 = y1 + r->VY;
            y2 = y2 < 0 ? 0 : y2;
            y2 = y2 > SY ? SY : y2;
            if (this->isOccupied(x2, y2) || x2>=this->SX || y2>=this->SY || x2<0 || y2<0) {
                didMove = false;
            }
        } else {
            x2 = x1;
            y2 = y1;
            didMove = false;
        }
        
        if (didMove) {
            r->movePosition(x2, y2);
            AREA[x1][y1] = EMPTY;       // empty the last position
            if (!isInCollision(x2, y2)) {
                AREA[x2][y2] = OCCUPIED;    // occupy the new position
            } else {
                AREA[x2][y2] = DEAD;
            }
        }
    }
};


#endif /* Simulator_h */
