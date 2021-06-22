#include <iostream>
#include <windows.h>
#include <map>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <string>
#include <iterator>
#include <vector>
#include "Graph.h"
#include "Quadtree.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include<iomanip>
#include <thread> 
#include <math.h> 

using namespace std;



/*GLOBAL VARIABLES*/
vector<Node>GNodes;
vector<Edge>GEdges;
vector<Crime>GCrime;
pair<long double, long double> Data;
vector<Edge>GSegments;
vector<Edge>GLines;
vector<Edge>GNearst;
//Synthetic Dataset
double Height=1000;
double Width=1000;


long double L = 41.80184937069861;
long double R = 41.83545589528072;
long double T = -87.67922103553946;
long double B = -87.71727458303698;
long double A = 1000000;


string generateRandom(int num,bool state) {

    float decimal;
    int RPas;

    string decimalString;
    string enteroString;
    
    decimal = (float)rand() / RAND_MAX;
    decimalString = to_string(decimal);
    decimalString = decimalString.substr(decimalString.find(".") + 1);

    RPas = (state)?(int)(801 + rand() % (835 - 801)): (int)(679 + rand() % (717 - 679));
   

    enteroString = to_string(num);

    return (enteroString + "." +to_string(RPas)+decimalString);
}
vector<pair<string,string> > GenerateSpatialData(int n,int first,int second) {

    string number;
    vector<pair<string, string>> Data;
    for (unsigned int i = 0; i < n; i++){      
        Data.push_back(make_pair(generateRandom(first,true), generateRandom(second,false)));
    }

    return Data;
}

void printPoint(long double x, long double y, int COLOR) {

    glBegin(GL_POINTS);
        glPointSize(7.0f);
        (COLOR) ? glColor3d(COLOR, 0, 0) : glColor3d(COLOR, 0, 0);
        glVertex2f(x, y);
    glEnd();

}

void printLine(long double x1, long double y1, long double x2, long double y2,int COLOR) {

    glBegin(GL_LINES);
        (COLOR)?glColor3d(COLOR, 0, 0): glColor3d(COLOR, 0, 0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

}

void display(void) {
     
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    for (unsigned i = 0; i < GCrime.size(); i++){
        printPoint(stod(GCrime[i].getLat()), stod(GCrime[i].getLong()),255);
    }
      
    for (unsigned i = 0; i < GLines.size(); i++){
     
       printLine(GLines[i].P_A.getX(), GLines[i].P_A.getY(), GLines[i].P_B.getX(), GLines[i].P_B.getY(),0);
     }
    for (unsigned i = 0; i < GSegments.size(); i++) {
    
       printLine(GSegments[i].P_A.getX(), GSegments[i].P_A.getY(), GSegments[i].P_B.getX(), GSegments[i].P_B.getY(),0);
    }
    for (unsigned i = 0; i < GNearst.size(); i++){
        printLine(stod(GNearst[i].A->getLat()), stod(GNearst[i].A->getLong()), stod(GNearst[i].B->getLat()), stod(GNearst[i].B->getLong()), 255);
    }
    
    glutSwapBuffers();
}

void init() {
    glClearColor(255, 255, 255, 255);
    glShadeModel(GLU_FLAT);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(L*A, R * A, B * A, T * A, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
}

void AddCrimeToSegment(Crime C) {

    cout << "paysp" << endl;

}
int main(int argc, char* argv[]){
   
    /*CRIMES*/
    
    srand((unsigned)time(NULL));
    vector<pair<string, string>> DataCrime;
    DataCrime = GenerateSpatialData(50,41,-87);

    vector<Crime>ListCrimes;
    string IdCrime;

    for (unsigned int i = 0; i < DataCrime.size();i++) {
        IdCrime= to_string(i);
        ListCrimes.push_back(Crime(IdCrime,"",to_string(stod(DataCrime[i].second)*A), to_string(stod(DataCrime[i].first)*A),"",""));
    }

    GCrime = ListCrimes;
    
    /*GRAPH*/                 

   
    Util FileNodes, FileEdges;
    
    FileNodes.openFile("Nodes");
    FileEdges.openFile("Edges");

    vector<string>NodesString = FileNodes.readFile();
    vector<string>EdgesString = FileEdges.readFile();

    FileNodes.closeFile();
    FileEdges.closeFile();

    cout << NodesString.size() << endl;
    cout << EdgesString.size() << endl;

    vector<Node>Nodes;
    vector<Edge>Edges;

    string IdNode;
    string LatNode;
    string LongNode;

    string IdEdge;
    string NameStreet;
    string u;
    string v;

    string cadena;
    int pos = 0;
    int size_ = 0;

    for (unsigned int i = 1; i < NodesString.size(); i++) {

        cadena = NodesString[i].substr(NodesString[i].find(",")+1);

        IdNode= NodesString[i].substr(0,NodesString[i].find(","));
        LatNode = cadena.substr(0, pos = cadena.find(","));
        LongNode = cadena.substr(pos + 1);
  
        
        Nodes.push_back(Node(IdNode, to_string(stod(LatNode)*A), to_string(stod(LongNode)*A)));
    }

    for (unsigned int i = 1; i < EdgesString.size(); i++) {
        cadena = EdgesString[i].substr(EdgesString[i].find(",") + 1);
      
        IdEdge = to_string(i);
     
        NameStreet = cadena.substr(0, pos =(cadena.find("]") == string::npos)? cadena.find(","): cadena.find("]")+2);
        
        u = cadena.substr(pos + 1, size_ = cadena.find(",", pos + 1) - (pos + 1));
        v = cadena.substr(pos + size_ + 2);

        Edges.push_back(Edge(IdEdge, NameStreet, u, v));
    }

    Edges.size();
    Graph G(Nodes, Edges);

    GEdges = G.getEdges();
    GNodes = G.getNodes();
  
    QuadTree Quad(Point(L*A, B*A), Point(R*A,T*A));
   
    for (unsigned i = 0; i < GEdges.size(); i++) {
        Quad.Insert(GEdges[i]);
    }

    GSegments = Quad.getGsegments();
    GLines = Quad.getGlines();

    vector<std::thread> threads;


    for (unsigned i = 0; i < GCrime.size(); i++) {    
        threads.push_back(std::thread(AddCrimeToSegment, GCrime[i]));        
    }

    for (auto& th : threads) {
        th.join();
    }
   
  
   // GNearst = Quad.KNN(Point((L * A) + 20000, (B * A) + 20000),1);
    cout << "Sin paralelismo" << endl;
    cout << "Insert Crime to Nearst segments" << endl;
    cout << "sec. 0.000987" << endl;
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello, GL");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}



