#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Point.h"
#include "Edge.h"
#include <fstream>
using namespace std;

class Util {
	public:
		Util();
		void openFile(string);
		void closeFile();
		void GAddPointGraph(Point);
		void GAddLineGraph(Edge);
		void GAddSegmentGraph(Edge);

		vector<Point>Gpoints;
		vector<Edge>Glines;
		vector<Edge>Gsegments;
		vector<string> readFile();
	private:
		fstream file;
};

Util::Util() {
	
}
void Util::openFile(string filename) {
	file.open(filename + ".csv");
}
void Util::closeFile() {
	file.close();
}
void Util::GAddPointGraph(Point P) {
	Gpoints.push_back(P);
}
void Util::GAddLineGraph(Edge L) {
	Glines.push_back(L);
}
void Util::GAddSegmentGraph(Edge E) {
	Gsegments.push_back(E);
}
vector<string> Util::readFile() {
	vector<string>Data;
	string line;
	if (file.is_open())	{

		while (getline(file, line)) {
			Data.push_back(line);
		}
		return Data;
	}
}