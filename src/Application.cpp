#include "Application.h"
#include "GraphViewer/graphviewer.h"

Application::Application() : graph(){}

void Application::loadRoads(string path) {
    ifstream ifs;
    ifs.open(path);

    string line;

    if (!ifs.is_open()){
        cerr << "Error loading the Roads File" << endl;
    }
    else{
        while(getline(ifs, line)){
            createRoad(line);
        }
    }

    ifs.close();
}

void Application::loadNodes(string path) {
    ifstream ifs;
    ifs.open(path);

    string line;

    if (!ifs.is_open())
    {
        cerr << "Error loading the Nodes File" << endl;
    }
    else{
        while(getline(ifs, line)){
            createNode(line);
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
			createSubRoad(line);
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
			createSharePoint(line);
		}
	}
    ifs.close();
}

void Application::createSubRoad(string line) {
	long id, node1_id, node2_id;
	id = stol(line.substr(0, line.find(';')));
	line = line.erase(0, line.find(';') + 1);
	node1_id = stol(line.substr(0, line.find(';')));
	line = line.erase(0, line.find(';') + 1);
	node2_id= stol(line.substr(0, line.find(';')));

    VertexData v1_finder(node1_id);
    VertexData v2_finder(node2_id);

    VertexData v1_real = graph.findVertex(v1_finder)->getInfo();
    VertexData v2_real = graph.findVertex(v2_finder)->getInfo();

    double weight = getDist(v1_real,v2_real);

    graph.addEdge(v1_finder,v2_finder,weight,id);
}

double Application::getDist(VertexData v1, VertexData v2){ //haversine formula
    int R = 6371000; // earths radius
    double latDiff = v2.getLatitudeRadians() - v1.getLatitudeRadians();
    double longDiff = v2.getLongitudeRadians() - v1.getLongitudeRadians();


    double a = sin(latDiff/2) * sin(latDiff/2) +
            cos(v1.getLatitudeRadians()) * cos(v2.getLatitudeRadians()) *
            sin(longDiff/2) * sin(longDiff/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
}

void Application::createRoad(string line) {

    string id, name, isTwoWay;

    id = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    name = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    isTwoWay = line.substr(0, line.find(';'));

    vector<string> dupped;

    for(Vertex<VertexData> *vector : graph.getVertexSet()){
        for(auto &edge : vector->getAdj()){
            if(edge.getId() == stol(id)){
                edge.setNome_rua(name);

                if (isTwoWay[0] == 'T'){
                    double weight = getDist(vector->getInfo(),edge.getDest()->getInfo());

                    Edge<VertexData> *newEdge = graph.addEdge(edge.getDest()->getInfo(),vector->getInfo(),weight,stol(id));
                    if(newEdge != nullptr){
                        newEdge->setNome_rua(name);
                    }
                }
            }
        }
    }
}


void Application::createSharePoint(string line) {
	string node_id, bicycle_count;

	node_id = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    bicycle_count = line.substr(0, line.find(';'));

    int initial_price = 20; //Initial price for all sharepoints

    SharePoint sp(stoi(bicycle_count),initial_price);

    VertexData v_finder(stol(node_id));

    Vertex<VertexData> *v = graph.findVertex(v_finder);

    v->getInfo().setSharePoint(sp);
}

void Application :: createNode(string line){

    long id;
    double latitudeDegrees, longitudeDegrees, longitudeRadians, latitudeRadians;

    id = stol(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    latitudeDegrees = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    longitudeDegrees = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    longitudeRadians = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    latitudeRadians = stod(line.substr(0, line.find(';')));

    VertexData vertexData(id, latitudeDegrees, longitudeDegrees, longitudeRadians, latitudeRadians);
    this->graph.addVertex(vertexData);
}

void Application::start() {
	string nodesPath, roadsPath, subRoadsPath,sharePointsPath,bicyclesPath;

    cout << "Insert the nodes path [nodes.txt]: " << endl;
    getline(cin, nodesPath);
    if(nodesPath == ""){
        nodesPath = "nodes.txt";
    }
    loadNodes(nodesPath);
    cout << nodesPath << " loaded" << endl;

    cout << "Insert the subRoads path [subRoads.txt]: " << endl;
    getline(cin, subRoadsPath);
    if(subRoadsPath == ""){
        subRoadsPath = "subRoads.txt";
    }
    loadSubRoads(subRoadsPath);
    cout << subRoadsPath << " loaded" << endl;

    cout << "Insert the roads path [roads.txt]: " << endl;
    getline(cin, roadsPath);
    if(roadsPath == ""){
        roadsPath = "roads.txt";
    }
    loadRoads(roadsPath);
    cout << roadsPath << " loaded" << endl;

    cout << "Insert the sharePoints path [sharePoints.txt]: " << endl;
	getline(cin,sharePointsPath);
    if(sharePointsPath == ""){
        sharePointsPath = "sharePoints.txt";
    }
    loadSharePoints(sharePointsPath);
    cout << sharePointsPath << " loaded" << endl;

    visualizeGraph();
}

void Application::visualizeGraph(){
    int xres = 1440;
    int yres = 900;
    GraphViewer *gv = new GraphViewer(xres, yres, true);
    gv->createWindow(xres, yres);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    double maxLat = -1;
    double minLat = -1;
    double maxLong = -1;
    double minLong = -1;

    for(auto vertex: graph.getVertexSet()){
        if(maxLat == -1 || vertex->getInfo().getLatitudeDegrees() > maxLat){
            maxLat = vertex->getInfo().getLatitudeDegrees();
        }
        if(minLat == -1 || vertex->getInfo().getLatitudeDegrees() < minLat){
            minLat = vertex->getInfo().getLatitudeDegrees();
        }
        if(maxLong == -1 || vertex->getInfo().getLongitudeDegrees() > maxLong){
            maxLong = vertex->getInfo().getLongitudeDegrees();
        }
        if(minLong == -1 || vertex->getInfo().getLongitudeDegrees() < minLong){
            minLong = vertex->getInfo().getLongitudeDegrees();
        }
    }

    for(auto vertex: graph.getVertexSet()){
        /*gv->addNode(vertex->getInfo().getId(),xres * (vertex->getInfo().getLatitudeDegrees() - minLat)/(maxLat-minLat),
                                              yres * (vertex->getInfo().getLongitudeDegrees() - minLong)/(maxLong-minLong));*/
        gv->addNode(vertex->getInfo().getId());

        if(vertex->getInfo().getSharePoint().getBicycles() != -1 && vertex->getInfo().getSharePoint().getBicycles() != -1){
            gv->setVertexColor(vertex->getInfo().getId(),"red");
        }
    }

    long edgeId = 0;

    for(auto vertex: graph.getVertexSet()){
        for(auto edge: vertex->getAdj()){
            gv->addEdge(edgeId,vertex->getInfo().getId(),edge.getDest()->getInfo().getId(),EdgeType::DIRECTED);
            edgeId++;

            gv->setEdgeLabel(edgeId,edge.getNome_rua());
        }
    }

    gv->rearrange();
}

/* void Application::dijkstraShortestPath(Node *origin, Node *end) {

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
}*/
