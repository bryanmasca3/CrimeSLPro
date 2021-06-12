#pragma once
#include <math.h> 
using namespace std;

class Point {
	public:
		Point();
		Point(long double, long double);
		long double minDistance;
		long double getX();
		long double getY();
		void DistanceOfTwo(Point &);
	private:
		long double x;
		long double y;
};
Point::Point() {
	this->minDistance = 0;
	this->x = 0;
	this->y = 0;
}
Point::Point(long double x, long double y) {
	this->x = x;
	this->y = y;
	this->minDistance = 0;
}
long double Point::getX() {
	return this->x;
}
long double Point::getY() {
	return this->y;
}
void Point::DistanceOfTwo(Point& that) {

	this->minDistance = sqrt((that.x - this->x) * (that.x - this->x) + (that.y - this->y) * (that.y - this->y));
}