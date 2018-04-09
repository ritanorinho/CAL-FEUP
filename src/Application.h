#ifndef PROJECT1_APPLICATION_H
#define PROJECT1_APPLICATION_H

#include "SharePoint.h"
#include "Graph.h"
#include "VertexData.h"
#include <vector>
#include <fstream>
#include <iostream>

class Application{
    Graph<VertexData> graph;
public:
    Application();
    void start();
    void loadRoads(string path);
    void createRoad(string line);
    void loadNodes(string path);
    void createNode(string line);
	void loadSubRoads(string path);
	void createSubRoad(string line);
	void loadSharePoints(string path);
    void createSharePoint(string line);

    double getWeight(VertexData v1, VertexData v2);

    void visualizeGraph();

    void drawSolution(vector<VertexData> sol);

    GraphViewer *gv;
};

#endif //PROJECT1_APPLICATION_H
