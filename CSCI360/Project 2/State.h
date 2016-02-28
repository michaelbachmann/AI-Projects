#ifndef STATE_H
#define STATE_H
#include "Vector2D.h"
#include <iostream>
#include <math.h>
#include <utility>

// State class
class State {
private:
	State* parent;
	float x, y, hValue, fValue;
	int gValue;

public:
	State();
	State(const Point2D& location);
	State(const Point2D& location, const Point2D& goal, int gValue, State* parent);
	// State(const Point2D& location, const Point2D& goal, int gValue);
	~State();

	void calculateF();
	void calculateH(const Point2D& goal);
	friend std::ostream& operator<<(std::ostream& os, const State& state);
	const int getG() const;
	const float getX() const;
	const float getY() const;
	const float getH() const;
	const float getF() const;
	void updateState(int gValue,const Point2D& goal);
	bool equalsPoint(const Point2D& point);
	State* getParent();
	void setParent(State* parent);
	Point2D* convertTo2D();

	bool operator==(const State &other) const;
	// bool operator<(State other) const;
};

struct state_set_comparator {
	bool operator() (const State& lhs, const State& rhs) const {
		return (std::make_pair(lhs.getX(), lhs.getY()) < std::make_pair(rhs.getX(), rhs.getY()));
		// if (lhs.getX() < rhs.getX() && (lhs.getY() < rhs.getY()))
		// 	return true;
		// else return false;
	}
};

struct state_set_comparator_p {
	bool operator() (const State *lhs, const State *rhs) const {
		// return (std::make_pair(lhs->getX(),lhs->getY()) < std::make_pair(rhs->getX(),rhs->getY()));
		return (std::make_pair(lhs->getX(), lhs->getY()) < std::make_pair(rhs->getX(), rhs->getY()));

		// return (std::make_pair(lhs->getX(), rhs->getX()) < std::make_pair(lhs->getY() < rhs->getY()));
		// if (lhs->getX() < rhs->getX() && (lhs->getY() < rhs->getY()))
		// 	return true;
		// else return false;
	}
};

struct state_priority_comparator {
	bool operator()(const State& lhs, const State& rhs) {
		if (lhs.getF() == rhs.getF())
			return lhs.getG() > rhs.getG();
		return lhs.getF() < rhs.getF(); 
	}
};

struct state_priority_comparator_p {
	bool operator()(const State* lhs, const State* rhs) {
		if (lhs->getF() == rhs->getF())
			return lhs->getG() > rhs->getG();
		return lhs->getF() < rhs->getF(); 
	}
};

#endif