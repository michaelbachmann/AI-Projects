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
	float x, y;
	double hValue, fValue;
	double gValue;

public:
	State();
	State(const Point2D& location);

	State(const Point2D& location, const Point2D& goal, double gValue, State* parent);
	~State();

	void calculateF();
	void calculateH(const Point2D& goal);
	friend std::ostream& operator<<(std::ostream& os, const State& state);
	const double getG() const;
	const float getX() const;
	const float getY() const;
	const double getH() const;
	const double getF() const;
	void updateState(double gValue,const Point2D& goal);
	bool equalsPoint(const Point2D& point);
	State* getParent() const;
	void setParent(State* parent);
	Point2D* convertTo2D();

	bool operator==(const State &other) const;
};

struct state_set_comparator {
	bool operator() (const State& lhs, const State& rhs) const {
		return (std::make_pair(lhs.getX(), lhs.getY()) < std::make_pair(rhs.getX(), rhs.getY()));
	}
};

struct state_set_comparator_p {
	bool operator() (const State *lhs, const State *rhs) const {
		return (std::make_pair(lhs->getX(), lhs->getY()) < std::make_pair(rhs->getX(), rhs->getY()));
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
		if (lhs->getF() == rhs->getF()) {
			if (lhs->getG() > rhs->getG())
				return lhs->getG() > rhs->getG();
			return true;
		}
		return lhs->getF() < rhs->getF(); 
	}
};

#endif