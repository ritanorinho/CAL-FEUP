#include "Application.h"

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

    double dist = sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));

    double heightDifference = v2.getHeight() - v1.getHeight();

    if(heightDifference + dist < 0){
        return 0;
    }else{
        return heightDifference + dist;
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
                    double weight = getWeight(edge.getDest()->getInfo(), vector->getInfo());

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
    double x, y, height;

    id = stol(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    x = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    y = stod(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    height = stod(line.substr(0, line.find(';')));

    VertexData vertexData(id, x, y, height);
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

    loadClients();

}

void Application::drawSolution(vector<VertexData> sol){
    for(auto vertex: sol) {
        gv->setVertexColor(vertex.getId(), "green");
    }

    for(int i = 0; i < sol.size()-1; i++){
        Vertex<VertexData> *v1 = graph.findVertex(sol.at(i));
        Vertex<VertexData> *v2 = graph.findVertex(sol.at(i+1));

        for(int j = 0; j < v1->adj.size(); j++){
            if(v1->adj[j].getDest() == v2){
                gv->setEdgeColor(v1->adj[j].graphViewerId,"green");
                gv->setEdgeThickness(v1->adj[j].graphViewerId, 2);
            }
        }
    }

    gv->rearrange();
}

void Application::orderSolutionByPrice(vector<vector<VertexData>> &sol){
    vector<VertexData> key;
    for (int i = 1, j; i < sol.size(); i++)
    {
        key = sol[i];
        j = i-1;

        while (j >= 0 && sol[j][sol[j].size() - 1].getSharePoint().getCurrentPrice() > key[key.size()-1].getSharePoint().getCurrentPrice())
        {
            sol[j+1] = sol[j];
            j = j-1;
        }
        sol[j+1] = key;
    }
}

void Application::visualizeGraph(){
    int xres = 1440;
    int yres = 900;

    this->gv = new GraphViewer(xres, yres, true);

    gv->createWindow(xres, yres);

    gv->defineVertexColor("blue");
    gv->defineEdgeColor("black");

    for(auto vertex: graph.getVertexSet()){

        if(vertex->getInfo().getSharePoint().getBicycles() != -1 && vertex->getInfo().getSharePoint().getCurrentPrice() != -1){
            gv->setVertexColor(vertex->getInfo().getId(),"red");
        }

        gv->addNode(vertex->getInfo().getId());

    }

    long edgeId = 0;

    for(auto vertex: graph.getVertexSet()){
        for(int j = 0; j < vertex->adj.size(); j++){
            gv->setEdgeLabel(edgeId,to_string(vertex->adj[j].weight));

            vertex->adj[j].graphViewerId = edgeId;

            gv->addEdge(edgeId,vertex->getInfo().getId(),vertex->adj[j].getDest()->getInfo().getId(),EdgeType::DIRECTED);
            edgeId++;
        }
    }

    gv->rearrange();
}


void Application ::loadClients() {
    string path = "clients.txt";
    ifstream ifs;
    ifs.open(path);

    string line;

    if (!ifs.is_open())
    {
        cerr << "Error loading the Clients File" << endl;
    }
    else{
        while(getline(ifs, line)){
            createClient(line);
        }
    }

    ifs.close();

}

void Application ::createClient(string line) {
    int id;
    int  bicycleId;
    string  paymentMethod;
    int paymentNumber;

    id = stoi(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    bicycleId = stoi(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    paymentMethod = line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    paymentNumber = stoi(line.substr(0, line.find(';')));

    Client c = Client(id, bicycleId, paymentMethod, paymentNumber);
    this->clientList.push_back(c);
}

void Application :: listSharePoints()
{
    for (auto v : this->graph.getVertexSet())
    {
        int n = 0;
        if (v->getInfo().getSharePoint().getBicycles() != -1)
            n = v->getInfo().getSharePoint().getBicycles();

        cout << "SharePoint ID: " << v->getInfo().getId() << "\t Number of Bicycles: " << n << endl;
    }
}

void Application :: listClients()
{
    for (int i = 0; i < this->clientList.size(); i++)
    {
        cout << "Client ID: " << this->clientList[i].getId() << "\t Bicycle ID: "<< this->clientList[i].getBicycleId() << "\t Payment Method: "<< this->clientList[i].getPaymentMethod() << "\t Payment Number: " <<this->clientList[i].getPaymentNumber() << endl;
    }
}

void Application :: addNode()
{
    long id;
    double x, y, height;

    cout << "Node ID: ";
    cin >> id;
    cout << "Node X: ";
    cin >> x;
    cout << "Node Y: ";
    cin >> y;
    cout << "Node Height: ";
    cin >> height;

    VertexData vertexData(id, x, y, height);
    this->graph.addVertex(vertexData);

}

void Application :: addRoad()
{
    long id;
    string name, isTwoWay;

    cout << "Road ID: ";
    cin >> id;
    cout << "Road Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Is Two Way? ";
    cin >> isTwoWay;

    for(Vertex<VertexData> *vector : graph.getVertexSet()){
        for(auto &edge : vector->getAdj()){
            if(edge.getId() == id){
                edge.setNome_rua(name);

                if (isTwoWay[0] == 'T'){
                    //double weight = getDist(vector->getInfo(),edge.getDest()->getInfo());
                    double weight = 1; //For testing only

                    Edge<VertexData> *newEdge = graph.addEdge(edge.getDest()->getInfo(),vector->getInfo(),weight,id);
                    if(newEdge != nullptr){
                        newEdge->setNome_rua(name);
                    }
                }
            }
        }
    }
}

void Application :: addSubRoad()
{
    long id, node1_id, node2_id;

    cout << "SubRoad ID: ";
    cin >> id;
    cout << "First Node ID: ";
    cin >> node1_id;
    cout << "Second Node ID: ";
    cin >> node2_id;

    VertexData v1_finder(node1_id);
    VertexData v2_finder(node2_id);

    VertexData v1_real = graph.findVertex(v1_finder)->getInfo();
    VertexData v2_real = graph.findVertex(v2_finder)->getInfo();

    double weight = getWeight(v1_real, v2_real);

    graph.addEdge(v1_finder,v2_finder,weight,id);
}

void Application :: addSharePoint()
{
    string node_id, bicycle_count, max_bicycle;

    cout << "Node ID: ";
    cin >> node_id;
    cout << "Bicycle Count: ";
    cin >> bicycle_count;
    cout << "Maximum Number of Bicycles: ";
    cin >> max_bicycle;

    int initial_price = 20; //Initial price for all sharepoints

    SharePoint sp(stoi(bicycle_count),initial_price,stoi(max_bicycle));

    VertexData v_finder(stol(node_id));

    Vertex<VertexData> *v = graph.findVertex(v_finder);

    v->getInfo().setSharePoint(sp);
}

void Application :: addBicycle()
{
    int id, n;
    cout << "SharePoint ID: ";
    cin >> id;
    cout << "Number of Bicycles: ";
    cin >> n;

    for (auto v : this->graph.getVertexSet())
    {
        if(v->getInfo().getId() == id)
        {
            n += v->getInfo().getSharePoint().getBicycles();
            v->getInfo().getSharePoint().setBicycles(n);
        }
    }
}

void Application :: addClient()
{
    int id;
    int  bicycleId;
    string  paymentMethod;
    int paymentNumber;

    cout << "Client ID: ";
    cin >> id;
    cout << "Bicycle ID: ";
    cin >> bicycleId;
    cout << "Payment Method: ";
    cin.ignore();
    getline(cin, paymentMethod);
    cout << "Payment Number: ";
    cin >> paymentNumber;

    Client c = Client(id, bicycleId, paymentMethod, paymentNumber);
    this->clientList.push_back(c);
}

void Application ::viewConnectivity() {
    this->graph.isConnected();
}

void Application ::drawGraph(int id, bool price)
{
    //Este VertexData serve apenas para encontrar o VertexData que esta guardado no grafo
    VertexData v_finder(id);

    //Devolve vetor com o caminho ate ao sharepoint mais proximo do no que tem um id igual ao do v_finder (neste caso 11)
    vector<VertexData> nearest = graph.findNearestSharepoint(v_finder);

    cout << "Shortest path: " << endl;
    for(auto node:nearest){
        cout << node.getId() << ";";
    }
    cout << endl;

    //Devolve um vetor com todos os caminhos mais proximos para cada um dos sharepoints, ordenado por distancia de forma crescente
    vector<vector<VertexData>> nearest_list = graph.findNearestSharepoints(v_finder);

    //Pega num vetor com todos os caminhos mais proximos para cada um dos sharepoints e reordena-o por ordem crescente de preço
    if (price)
        orderSolutionByPrice(nearest_list);

    cout << "List of paths: " << endl;
    for(auto solution:nearest_list){
        for(auto node:solution) {
            cout << node.getId() << ";";
        }
        cout << endl;
    }
    cout << endl;

    //Recebe um vetor que representa um caminho e assinala-o a verde no grafo
    visualizeGraph();
    drawSolution(nearest);
}
