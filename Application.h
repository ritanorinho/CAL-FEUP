#ifndef PROJECT1_APPLICATION_H
#define PROJECT1_APPLICATION_H

#include "Road.h"
#include "Node.h"
#include <vector>
#include <fstream>
#include <iostream>

class Application{
private:
    vector<Road> roadList;
    vector<Node> nodeList;
public:
    Application();
    void start();
    void loadRoads(string path);
    Road createRoad(string line);
    void loadNodes(string path);
    Node createNode(string line);
    //
    void listNodes();
    void listRoads();


};

#endif //PROJECT1_APPLICATION_H
