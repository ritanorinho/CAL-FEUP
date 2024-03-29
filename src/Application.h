#ifndef PROJECT1_APPLICATION_H
#define PROJECT1_APPLICATION_H

#include "SharePoint.h"
#include "Graph.h"
#include "VertexData.h"
#include "Client.h"
#include <vector>
#include <fstream>
#include <iostream>
#include<set>
#include "GraphViewer/graphviewer.h"

class Application {
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

	double getWeight(VertexData v1, VertexData v2);

	void viewGraph(vector<vector<int>> vect);

	void visualizeGraph();

	void viewConnectivity();

	void drawGraph(int id, bool price, vector<vector<int>>, int num);

	void drawSolution(vector<VertexData> sol);

	void drawUnableRoads(vector<vector<int>> v);

	GraphViewer *gv;

	void orderSolutionByPrice(vector<vector<VertexData>> &sol);

	void listSharePoints();

	void listClients();

	void addNode();

	void addRoad();

	void addSubRoad();

	void addSharePoint();

	void addBicycle();

	void addClient();


	void applyDiscount();

	vector<VertexData> trimSolution(vector<vector<VertexData>> vect, vector<vector<int>> id_vec);

	Graph<VertexData> getGraph();

	void listPrice();

	void listInfo();

	void checkClient();

	void rent();

	void drop(int c_id, int n_id);

	vector<Client> getClientList();

    int findIfSharePoint(string basic_string, string basicString, bool findPath);
};


#endif //PROJECT1_APPLICATION_H
