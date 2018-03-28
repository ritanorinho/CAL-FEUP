#include "Application.h"
#include "MutablePriorityQueue.h"

Application ::Application() {
    this->nodeList = {};
    this->roadList = {};
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

void Application ::start() {
    string nodesPath, roadsPath;

    cout << "Insert the nodes path: " << endl;
    getline(cin, nodesPath);
    cout << "Insert the roads path: " << endl;
    getline(cin, roadsPath);

    loadRoads(roadsPath);
    loadNodes(nodesPath);
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
