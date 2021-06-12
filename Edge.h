#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Point.h"
using namespace std;

class Edge {
	public:
		Edge(string, string, string, string);
		Edge(string, string, string, string, Node*, Node*);
		Edge(Node*, Node*);
		Edge(Point, Point);
		Node* A;
		Node* B;
		string getId();
		string getNameStreet();
		string getU();
		string getV();
		long double minDistance;
		void Proyection(Point&);
		Point P_A;
		Point P_B;

	private:
		string Id;
		string NameStreet;
		string u;
		string v;
};
Edge::Edge(string id, string NameStreet, string u, string v) {
	this->Id = id;
	this->NameStreet = NameStreet;
	this->u = u;
	this->v = v;
	this->minDistance = 0;
}

Edge::Edge(string id, string NameStreet, string u, string v, Node* A, Node* B) {
	this->Id = id;
	this->NameStreet = NameStreet;
	this->u = u;
	this->v = v;
	this->A = A;
	this->B = B;
	this->minDistance = 0;
}
Edge::Edge(Point A, Point B) {
	this->P_A = A;
	this->P_B = B;
	this->minDistance = 0;
}
string Edge::getId() {
	return Id;
}
string Edge::getNameStreet() {
	return NameStreet;
}
string Edge::getU() {
	return u;
}
string Edge::getV() {
	return v;
}
Edge::Edge(Node* A, Node* B) {
	this->A = A;
	this->B = B;
}
void Edge::Proyection(Point& P) {

	long double XFirst = stof(this->A->getLat());
	long double YFirst = stof(this->A->getLong());

	long double XEnd = stof(this->B->getLat());
	long double YEnd = stof(this->B->getLong());

	long double XMid = (XFirst + XEnd) / 2;
	long double YMid = (YEnd + YEnd) / 2;

	long double DFirst = sqrt(pow(P.getX() - XFirst, 2) + pow(P.getY() - YFirst, 2));
	long double DMid = sqrt(pow(P.getX() - XMid, 2) + pow(P.getY() - YMid, 2));
	long double DEnd = sqrt(pow(P.getX() - XEnd, 2) + pow(P.getY() - YEnd, 2));

	this->minDistance = min(min(DFirst, DMid), DEnd);
}


