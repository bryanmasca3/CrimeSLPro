#pragma once
#include "Point.h"
#include "Edge.h"
using namespace std;

class Quad{
	public:
		Quad(Point, Point);
		~Quad();
		int n;
		Point topLeft;
		Point botRight;

		Quad* topLeftTree;
		Quad* topRightTree;
		Quad* botLeftTree;
		Quad* botRightTree;
		
		long double point_distance;	
		vector<Edge>Segment;

		bool IsLeaf();
		bool InBoundary(string, string);
		void DistQuadToPoint(Point);
	private:

};

Quad::Quad(Point A, Point B){

	this->topLeftTree = NULL;
	this->topRightTree = NULL;
	this->botLeftTree = NULL;
	this->botRightTree = NULL;
	this->n = 4;
	this->topLeft = A;
	this->botRight = B;
	this->point_distance = 0;
}

Quad::~Quad() {

}
bool Quad::InBoundary(string Lat, string Long) {

	bool R(stod(Lat) >= topLeft.getX() &&
		stod(Lat) < botRight.getX() &&
		stod(Long) >= topLeft.getY() &&
		stod(Long) < botRight.getY());
	return R;
};
void Quad::DistQuadToPoint(Point a) {


	if ((a.getX()) > this->topLeft.getX() && a.getX() < this->botRight.getX()) {
		this->point_distance = abs(a.getY() - this->topLeft.getY());

	}
	else if (a.getY() > this->topLeft.getY() && a.getY() < this->botRight.getY()) {
		this->point_distance = abs(a.getX() - this->topLeft.getX());

	}
	else if (a.getX() < this->topLeft.getX() && a.getY() < this->topLeft.getY()) {
		a.DistanceOfTwo(this->topLeft);
		this->point_distance = a.minDistance;

	}
	else if (a.getX() < this->topLeft.getX() && a.getY() > this->topLeft.getY()) {
		Point swcorner(topLeft.getX(), botRight.getY());
		a.DistanceOfTwo(swcorner);
		this->point_distance = a.minDistance;
	}
	else if (a.getX() > this->botRight.getX() && a.getY() < this->topLeft.getY()) {
		Point necorner(botRight.getX(), topLeft.getY());
		a.DistanceOfTwo(necorner);
		this->point_distance = a.minDistance;

	}
	else if (a.getX() > this->botRight.getX() && a.getY() > this->botRight.getY()) {
		Point secorner(botRight.getX(), botRight.getY());
		a.DistanceOfTwo(secorner);
		this->point_distance = a.minDistance;
	}
}
bool Quad::IsLeaf() {
	return (this->topLeftTree == NULL);
};