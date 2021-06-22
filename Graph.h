#pragma once
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <stdlib.h> 
#include <queue> 
#include <math.h> 
#include "Node.h"

#include "Edge.h"
using namespace std;

class Graph{
	public:
		Graph(vector<Node>, vector<Edge>);
		vector<Node> getNodes();
		vector<Edge>& getEdges();

	private:
		void insertNode(string, string, string);
		void insertEdge(string, string, string,string);
		vector<Node> V;
		map<string, Node> HashNodes;
		vector<Edge> E;
};

/**/
Graph::Graph(vector<Node> V, vector<Edge> E){



	for (unsigned i = 0; i < V.size(); i++) {
		insertNode(V[i].getId(), V[i].getLat(), V[i].getLong());
	}

	for (unsigned i = 0; i < E.size(); i++) {
		insertEdge(E[i].getId(), E[i].getNameStreet(), E[i].getU(), E[i].getV());
	}
}
vector<Node> Graph::getNodes() {
	return this->V;
}
vector<Edge>&  Graph::getEdges() {
	return this->E;
}
void Graph::insertNode(string Id,string Lat,string Long) {

	this->V.push_back(Node(Id, Lat, Long));
	this->HashNodes.insert(pair<string, Node>(Id, Node(Id, Lat, Long)));

}
void Graph::insertEdge(string id, string NameStreet, string u, string v) {

	this->E.push_back(Edge(id, NameStreet, u, v, &HashNodes[u], &HashNodes[v]));

}

