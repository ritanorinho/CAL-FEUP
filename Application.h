#ifndef PROJECT1_APPLICATION_H
#define PROJECT1_APPLICATION_H

#include "Road.h"
#include "Node.h"
#include "SubRoad.h"
#include "SharePoint.h"
#include "Bicycle.h"
#include <vector>
#include <fstream>
#include <iostream>

class Application{
private:
    vector<Road> roadList;
    vector<Node> nodeList;
	vector<SubRoad> subRoadList;
	vector<SharePoint> sharePointList;
	vector<Bicycle> bicycleList;
public:
    Application();
    void start();
    void loadRoads(string path);
    Road createRoad(string line);
    void loadNodes(string path);
    Node createNode(string line);
	void loadSubRoads(string path);
	SubRoad createSubRoad(string line);
	void loadSharePoints(string path);
	SharePoint createSharePoint(string line);
	void loadBicycles(string path);
	Bicycle createBicycle(string line);

    void dijkstraShortestPath(Node &origin);
    //
    void listNodes();
    void listRoads();
	void listSubRoads();
	void listSharePoints();
	void listBicycles();


};

#endif //PROJECT1_APPLICATION_H
