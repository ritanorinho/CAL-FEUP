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

    double weight = getWeight(v1_real, v2_real);

    graph.addEdge(v1_finder,v2_finder,weight,id);
}

double Application::getWeight(VertexData v1, VertexData v2){ //haversine formula + height difference
    int R = 6371000; // earths radius
    double latDiff = v2.getLatitudeRadians() - v1.getLatitudeRadians();
    double longDiff = v2.getLongitudeRadians() - v1.getLongitudeRadians();


    double a = sin(latDiff/2) * sin(latDiff/2) +
            cos(v1.getLatitudeRadians()) * cos(v2.getLatitudeRadians()) *
            sin(longDiff/2) * sin(longDiff/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    double heightDifference = v2.getHeight() - v1.getHeight();

    if(heightDifference > (R * c)){
        return 0;
    }else{
        return (R * c) + heightDifference;
    }
}

void Application::createRoad(string line) {

    string id, name, isTwoWay;

    id = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    name = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    isTwoWay = line.substr(0, line.find(';'));
    
    for(Vertex<VertexData> *vector : graph.getVertexSet()){
        for(auto &edge : vector->getAdj()){
            if(edge.getId() == stol(id)){
                edge.setNome_rua(name);

                if (isTwoWay[0] == 'T'){
                    double weight = getWeight(vector->getInfo(), edge.getDest()->getInfo());

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
	string node_id, bicycle_count, max_bicycle;

	node_id = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    bicycle_count = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    max_bicycle = line.substr(0, line.find(';'));

    int initial_price = 20; //Initial price for all sharepoints

    SharePoint sp(stoi(bicycle_count),initial_price,stoi(max_bicycle));

    VertexData v_finder(stol(node_id));

    Vertex<VertexData> *v = graph.findVertex(v_finder);

    v->getInfo().setSharePoint(sp);
}

void Application::createNode(string line){

    long id;
    double latitudeDegrees, longitudeDegrees, longitudeRadians, latitudeRadians, height;

    id = stol(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    latitudeDegrees = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    longitudeDegrees = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    longitudeRadians = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    latitudeRadians = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    height = stod(line.substr(0, line.find(';')));

    VertexData vertexData(id, latitudeDegrees, longitudeDegrees, longitudeRadians, latitudeRadians, height);
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

    VertexData v_finder(2);

    vector<VertexData> res = graph.findNearestSharepoint(v_finder);

    cout << "Shortest path: " << endl;
    for(auto vd:res){
        cout << vd.getId() << ";";
    }
    cout << endl;

    vector<vector<VertexData>> res_r = graph.findNearestSharepoints(v_finder);

    cout << "List of paths: " << endl;
    for(auto ress:res_r){
        for(auto vd:ress) {
            cout << vd.getId() << ";";
        }
        cout << endl;
    }
    cout << endl;

    visualizeGraph();

    graph.isStronglyConnected();
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

        if(vertex->getInfo().getSharePoint().getBicycles() != -1 && vertex->getInfo().getSharePoint().getCurrentPrice() != -1){
            gv->setVertexColor(vertex->getInfo().getId(),"red");
        }

        gv->addNode(vertex->getInfo().getId());

    }

    long edgeId = 0;

    for(auto vertex: graph.getVertexSet()){
        for(auto edge: vertex->getAdj()){
            gv->setEdgeLabel(edgeId,edge.weight);

            gv->addEdge(edgeId,vertex->getInfo().getId(),edge.getDest()->getInfo().getId(),EdgeType::DIRECTED);
            edgeId++;
        }
    }

    gv->rearrange();
}