#ifndef PROJECT1_APPLICATION_H
#define PROJECT1_APPLICATION_H

#include "Road.h"
#include "Node.h"
#include "SubRoad.h"
#include <vector>
#include <fstream>
#include <iostream>

class Application{
private:
    vector<Road> roadList;
    vector<Node> nodeList;
	vector<SubRoad> subRoadList;
public:
    Application();
    void start();
    void loadRoads(string path);
    Road createRoad(string line);
    void loadNodes(string path);
    Node createNode(string line);
	void loadSubRoads(string path);
	SubRoad createSubRoad(string line);
    void dijkstraShortestPath(Node &origin);
    //
    void listNodes();
    void listRoads();
	void listSubRoads();


};

#endif //PROJECT1_APPLICATION_H
