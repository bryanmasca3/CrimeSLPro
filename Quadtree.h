#pragma once
#include "Edge.h"
#include "Point.h"
#include "Quad.h"
#include "Util.h"
#include <queue> 
#include <vector>
#include <algorithm>
#include <math.h> 
using namespace std;

class QuadTree {
	public:

		QuadTree(Point, Point);
		~QuadTree();

		bool IsEmpty();
		void Split(Quad*);
		void Destroy(Quad*);
		bool Insert(Edge);
		bool _Insert(Quad*, Edge);
		void AddCrimeToSegment(Crime);
		float DistancePoint(Node*, Point);
		Edge KNN(Point, int);

		Quad* root;

		struct CompareRect {
			bool operator() (Quad* r1, Quad* r2) {
				return r1->point_distance > r2->point_distance;
			}
		};
		struct CompareEdgesD {
			bool operator()(Edge& p1, Edge& p2) {

				return p1.minDistance < p2.minDistance;
			}
		};
		vector<Edge> getGlines();
		vector<Edge> getGsegments();
		Util Graphics;
	private:
		Point topLeft;
		Point botRight;

};
QuadTree::QuadTree(Point A, Point B) {

	this->topLeft = A;
	this->botRight = B;
	root = new Quad(A, B);

}
QuadTree::~QuadTree() {
	Destroy(root);
}
vector <Edge> QuadTree::getGlines() {
	return Graphics.Glines;
}
vector <Edge> QuadTree::getGsegments() {
	return Graphics.Gsegments;
}
bool QuadTree::IsEmpty() {
	return (root == NULL) ? true : false;
}

void QuadTree::Destroy(Quad* r) {

	if (r != NULL) {
		Destroy(r->topLeftTree);
		Destroy(r->topRightTree);
		Destroy(r->botLeftTree);
		Destroy(r->botRightTree);
		delete r;
	}
}
void QuadTree::Split(Quad* r) {

	long double mid_x = (r->botRight.getX() + r->topLeft.getX()) / 2;
	long double mid_y = (r->botRight.getY() + r->topLeft.getY()) / 2;

	r->topLeftTree = new Quad(r->topLeft, Point(mid_x, mid_y));
	r->botRightTree = new Quad(Point(mid_x, mid_y), r->botRight);
	r->topRightTree = new Quad(Point((mid_x), r->topLeft.getY()), Point(r->botRight.getX(), mid_y));
	r->botLeftTree = new Quad(Point(r->topLeft.getX(), mid_y), Point(mid_x, r->botRight.getY()));

	Graphics.GAddLineGraph(Edge(Point(mid_x, r->topLeft.getY()), Point(mid_x, r->botRight.getY())));
	Graphics.GAddLineGraph(Edge(Point(r->topLeft.getX(), mid_y), Point(r->botRight.getX(), mid_y)));

	for (auto p : r->Segment) {

		if (r->topLeftTree->InBoundary(p.A->getLat(), p.A->getLong()) || r->topLeftTree->InBoundary(p.B->getLat(), p.B->getLong())) { r->topLeftTree->Segment.push_back(p); }
		if (r->topRightTree->InBoundary(p.A->getLat(), p.A->getLong()) || r->topRightTree->InBoundary(p.B->getLat(), p.B->getLong())) { r->topRightTree->Segment.push_back(p); }
		if (r->botLeftTree->InBoundary(p.A->getLat(), p.A->getLong()) || r->botLeftTree->InBoundary(p.B->getLat(), p.B->getLong())) { r->botLeftTree->Segment.push_back(p); }
		if (r->botRightTree->InBoundary(p.A->getLat(), p.A->getLong()) || r->botRightTree->InBoundary(p.B->getLat(), p.B->getLong())) { r->botRightTree->Segment.push_back(p); }

	}

	r->Segment.clear();
}

bool QuadTree::Insert(Edge a) {

	_Insert(root, a);
	Graphics.GAddSegmentGraph(Edge(Point(stof(a.A->getLat()), stof(a.A->getLong())), Point(stof(a.B->getLat()), stof(a.B->getLong()))));
	return true;

}
bool QuadTree::_Insert(Quad* r, Edge E) {


	if (!(r->InBoundary(E.A->getLat(), E.A->getLong()) || r->InBoundary(E.B->getLat(), E.B->getLong()))) { return false; }

	if (r->topLeftTree == NULL) {
		r->Segment.push_back(E);
		if (r->Segment.size() > r->n) {
			Split(r);
			return true;
		}
	}
	else {

		if (_Insert(r->topLeftTree, E)) {}
		if (_Insert(r->topRightTree, E)) {}
		if (_Insert(r->botLeftTree, E)) {}
		if (_Insert(r->botRightTree, E)) {}

	}
	return false;
}

Edge QuadTree::KNN(Point a, int k) {

	priority_queue <Quad*, vector<Quad*>, CompareRect> RectsByPriority;

	vector <Edge> PointsByPriority;
	
	Quad* r = root;

	RectsByPriority.push(r);

	while (!RectsByPriority.empty()) {

		Quad* e = RectsByPriority.top();


		if (PointsByPriority.size() >= k && (RectsByPriority.top()->point_distance > PointsByPriority[k].minDistance)) {
			break;
		}

		if (e->IsLeaf()) {
			for (auto p : e->Segment) {

				p.Proyection(a);
				PointsByPriority.push_back(p);
				sort(PointsByPriority.begin(), PointsByPriority.end(), CompareEdgesD());
			}
			RectsByPriority.pop();
		}
		else if (!e->IsLeaf()) {

			Quad* h = e;
			RectsByPriority.pop();
			h->topLeftTree->DistQuadToPoint(a);
			RectsByPriority.push(h->topLeftTree);
			h->topRightTree->DistQuadToPoint(a);
			RectsByPriority.push(h->topRightTree);
			h->botLeftTree->DistQuadToPoint(a);
			RectsByPriority.push(h->botLeftTree);
			h->botRightTree->DistQuadToPoint(a);
			RectsByPriority.push(h->botRightTree);
		}
	}
	Edge nearest_elements = PointsByPriority[0];

	return nearest_elements;
}
float QuadTree::DistancePoint(Node *A, Point B) {
	return sqrt((stod(A->getLat()) - B.getX()) * (stod(A->getLat()) - B.getX()) + (stod(A->getLong()) - B.getY()) * (stod(A->getLong()) - B.getY()));
}
void QuadTree::AddCrimeToSegment(Crime C) {

	Point CrimeLatLong(stod(C.getLat()), stod(C.getLong()));
	Edge NeartsEdge= KNN(CrimeLatLong,1);

	float distA=DistancePoint(NeartsEdge.A, CrimeLatLong);
	float distB = DistancePoint(NeartsEdge.B, CrimeLatLong);

	(distA < distB) ? NeartsEdge.A->addCrime(C) : NeartsEdge.B->addCrime(C);

}