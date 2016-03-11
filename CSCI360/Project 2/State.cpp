#include "State.h"

State::State(){
	x = y = gValue = fValue = hValue = 0;
	parent = NULL;
}

State::State(const Point2D& location){
	x = location.x;
	y = location.y;
	gValue = fValue = hValue = 0;
	parent = NULL;
}

State::State(const Point2D& location, const Point2D& goal, double gValue, State* parent) {
	x = location.x;
	y = location.y;
	// this->gValue = ++gValue;
	this->gValue = gValue;
	this->parent = parent;
	calculateH(goal);
	calculateF();
}

void State::updateState(double gValue, const Point2D& goal) {
	// this->gValue = ++gValue;
	this->gValue = gValue;

	calculateH(goal);
	calculateF();
}

State* State::getParent() const{
	return parent;
}
void State::setParent(State* parent) {
	this->parent = parent;
}

State::~State(){

}

std::ostream& operator<<(std::ostream& os, const State& state)
{
    os << "State: (" << state.getX() <<  ", " << state.getY() << ") ... { G = ";
    os << state.getG() << ", H = " << state.getH() << ", F = " << state.getF() << " } ... Parent = (";
    if (state.getParent())
    	os << state.getParent()->getX() << " , "<<state.getParent()->getY();
    os << " )\n";
    return os;
}

bool State::equalsPoint(const Point2D& point) {
	if ((this->x == point.x) && (this->y == point.y))
		return true;
	return false;
}

void State::calculateH(const Point2D& goal) {
	hValue = sqrtf( pow( (goal.x - x), 2) + pow( (goal.y - y), 2) );
}

Point2D* State::convertTo2D() {
	return (new Point2D(this->x, this->y));
}


void State::calculateF() { fValue = gValue + hValue; }

const double State::getF() const { return fValue; }

const double State::getG() const { return gValue; }

const double State::getH() const { return hValue; }

const float State::getX() const { return x; }

const float State::getY() const { return y; }

bool State::operator==(const State &other) const {
	if (this->x == other.getX() && this->y == other.getY())
		return true;
	return false;
}