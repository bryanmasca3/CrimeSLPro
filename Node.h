#pragma once
#include "Crime.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
	public:
		Node();
		Node(string, string, string);
		Node(string, string);
		void addCrime(Crime);
		vector<Crime> getListCrimes();
		string getId();
		string getLat();
		string getLong();
		void setLat(string);
		void setLong(string);
	private:
		string Long;
		string Lat;
		string Id;
		vector<Crime>ListCrimes;

};
Node::Node() {
	this->Id = "";
	this->Long = "";
	this->Lat = "";
}
Node::Node(string Id, string Lat, string Long) {
	this->Id = Id;
	this->Long = Long;
	this->Lat = Lat;
}
Node::Node(string Lat, string Long) {
	this->Long = Long;
	this->Lat = Lat;
}
vector<Crime> Node::getListCrimes() {
	return this->ListCrimes;
}
void Node::addCrime(Crime Crime) {
	ListCrimes.push_back(Crime);
}
string Node::getLat() {
	return this->Lat;
}
string Node::getLong() {
	return this->Long;
}
void Node::setLat(string Lat) {
	this->Lat = Lat;
}
void Node::setLong(string Long) {
	this->Long = Long;
}
string Node::getId() {
	return this->Id;
}
