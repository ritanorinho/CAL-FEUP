#ifndef PROJECT1_APPLICATION_H
#define PROJECT1_APPLICATION_H

#include <vector>
#include "SharePoint.h"
#include "Graph.h"
#include "VertexData.h"
#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>
#include "Client.h"

class Application{
    Graph<VertexData> graph;
	vector<Client> clientList;
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
	void loadClients();
	void createClient(string line);

    double getDist(VertexData v1, VertexData v2);

	void listSharePoints();
	void listClients();

	void addNode();
	void addRoad();
	void addSubRoad();
	void addSharePoint();
	void addBicycle();
	void addClient();


	void rentBicycle();
    void dropBicycle();
    void applyDiscount();
    void visualizeGraph();
};

#endif //PROJECT1_APPLICATION_H
