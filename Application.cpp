#include "Application.h"
#include "MutablePriorityQueue.h"

Application ::Application() {
    this->nodeList = {};
    this->roadList = {};
	this->subRoadList = {};
}
void Application ::loadRoads(string path) {
    ifstream ifs;
    ifs.open(path);

    string line;

    if (!ifs.is_open()){
        cerr << "Error loading the Roads File" << endl;
    }
    else{
        while(getline(ifs, line)){
            this->roadList.push_back(createRoad(line));
        }
    }

    ifs.close();
}

void Application ::loadNodes(string path) {
    ifstream ifs;
    ifs.open(path);

    string line;

    if (!ifs.is_open())
    {
        cerr << "Error loading the Nodes File" << endl;
    }
    else{
        while(getline(ifs, line)){
            this->nodeList.push_back(createNode(line));
        }
    }

    ifs.close();
}
void Application::loadSubRoads(string path) {
	ifstream ifs;
	ifs.open(path);
	
	string line;
	if (!ifs.is_open()) {
		cerr << "Error loading SubRoads File" << endl;
	}
	else {
		while (getline(ifs, line)) {
			this->subRoadList.push_back(createSubRoad(line));
		}
	}
	ifs.close();

}
void Application::loadSharePoints(string path) {
	ifstream ifs;
	ifs.open(path);

	string line;

	if (!ifs.is_open()) {
		cerr << "Error loading the Roads File" << endl;
	}
	else {
		while (getline(ifs, line)) {
			this->sharePointList.push_back(createSharePoint(line));
		}
	}


}
SubRoad Application::createSubRoad(string line) {
	string id, node1_id, node2_id;
	id = line.substr(0, line.find(';'));
	line = line.erase(0, line.find(';') + 1);
	node1_id = line.substr(0, line.find(';'));
	line = line.erase(0, line.find(';') + 1);
	node2_id= line.substr(0, line.find(';'));
	SubRoad sR= SubRoad(stoi(id), stoi(node1_id), stoi(node2_id));
	return sR;
}

Road Application ::createRoad(string line) {

    string id, name, isTwoWay;
    bool twoWay = false;

    id = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    name = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    isTwoWay = line.substr(0, line.find(';'));
    if (isTwoWay[0] == 'T')
        twoWay = true;

    Road r = Road(stoi(id), name, twoWay);
    return r;
}
SharePoint Application::createSharePoint(string line) {
	string id, name, isTwoWay,price;
	bool twoWay = false;

	id = line.substr(0, line.find(';'));
	line = line.erase(0, line.find(';') + 1);
	name = line.substr(0, line.find(';'));
	line = line.erase(0, line.find(';') + 1);
	isTwoWay = line.substr(0, line.find(';'));
	if (isTwoWay[0] == 'T')
		twoWay = true;
	Road r = Road(stoi(id), name, twoWay);
	line = line.erase(0, line.find(';') + 1);
	price = line.substr(0, line.find(';'));
	SharePoint sP = SharePoint(r, stoi(price));
	return sP;


}
Node Application :: createNode(string line){

    string id, latitudeDegrees, longitudeDegrees, longitudeRadians, latitudeRadians;

    id = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    latitudeDegrees = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    longitudeDegrees = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    longitudeRadians = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    latitudeRadians = line.substr(0, line.find(';'));

    Node n = Node(stol(id), stod(latitudeDegrees), stod(longitudeDegrees), stod(longitudeRadians), stod(latitudeRadians));
    return n;
}

// Test Functions

void Application ::listNodes() {
    for (int i = 0; i < this->nodeList.size(); i++)
    {
        cout << "ID: " << this->nodeList[i].id << endl;
        cout << "latitudeDegrees: " << this->nodeList[i].latitudeDegrees << endl;
        cout << "longitudeDegrees: " << this->nodeList[i].longitudeDegrees << endl;
        cout << "longitudeRadians: " << this->nodeList[i].longitudeRadians << endl;
        cout << "latitudeRadians: " << this->nodeList[i].latitudeRadians << endl;
    }
}

void Application ::listRoads() {
    for (int i = 0; i < this->roadList.size(); i++)
    {
        cout << "ID: " << this->roadList[i].id << endl;
        cout << "name: " << this->roadList[i].name << endl;
        cout << "isTwoWay: " << this->roadList[i].isTwoWay << endl;
    }
}
void Application::listSubRoads() {
	for (int i = 0; i < this->subRoadList.size(); i++) {
	
		cout << "ID: " << this->subRoadList[i].id << endl;
		cout << "Node 1 id" << this->subRoadList[i].node1_id << endl;
		cout << "Node 2 id" << this->subRoadList[i].node2_id << endl;
	}
}
void Application::listSharePoints() {
	for (int i = 0; i < this->sharePointList.size(); i++) {

		cout << "ID: " << this->sharePointList[i].getRoad().id<< endl;
		cout << "Street Name: " << this->sharePointList[i].getRoad().name << endl;
		cout << "isTwoWay: " << this->sharePointList[i].getRoad().isTwoWay << endl;
		cout << "Price: "<< this->sharePointList[i].getPriceDay() << endl;

	}
}

void Application ::start() {
	string nodesPath, roadsPath, subRoadsPath,sharePointsPath;

    cout << "Insert the nodes path: " << endl;
    getline(cin, nodesPath);
    cout << "Insert the roads path: " << endl;
    getline(cin, roadsPath);
	cout << "Insert the subRoads path: " << endl;
	getline(cin, subRoadsPath);
	cout << "Insert the sharePoints path: " << endl;
	getline(cin,sharePointsPath);

    loadRoads(roadsPath);
    loadNodes(nodesPath);
	loadSubRoads(subRoadsPath);
	loadSharePoints(sharePointsPath);
}

void Application::dijkstraShortestPath(Node *origin, Node *end) {

    int inf = 999999999;

    MutablePriorityQueue<Node> q;

    for(auto v : this->nodeList){
        v.dist = inf;
        v.path = nullptr;
        v.queueIndex = -1;
    }

    origin->dist = 0;
    origin->queueIndex = 0;
    q.insert(origin);

    while(!q.empty()){
        Node *v = q.extractMin();
        for(auto edge : v->adj){ //TODO - Decide how edges will be stored in the graph
            Node *w = edge.dest;
            if(w->dist > (v->dist + edge.weight)){
                double oldDist = w->dist;
                w->dist = v->dist + edge.weight;
                w->path = v;
                if(oldDist == inf){
                    q.insert(w);
                }else{
                    q.decreaseKey(w);
                }
            }
        }
    }
}
