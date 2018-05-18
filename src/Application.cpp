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
    string nome_rua,district;
	id = stol(line.substr(0, line.find(';')));
	line = line.erase(0, line.find(';') + 1);
	node1_id = stol(line.substr(0, line.find(';')));
	line = line.erase(0, line.find(';') + 1);
	node2_id= stol(line.substr(0, line.find(';')));
    line = line.erase(0, line.find(';') + 1);
    nome_rua= line.substr(0, line.find(';'));
    line = line.erase(0, line.find(';') + 1);
    district= line.substr(0, line.find(';'));

    VertexData v1_finder(node1_id);
    VertexData v2_finder(node2_id);

    VertexData v1_real = graph.findVertex(v1_finder)->getInfo();
    VertexData v2_real = graph.findVertex(v2_finder)->getInfo();

    double weight = getWeight(v1_real, v2_real);

    graph.addEdge(v1_finder,v2_finder,weight,id,nome_rua,district);
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
                if (isTwoWay[0] == 'T'){
                    double weight = getWeight(edge.getDest()->getInfo(), vector->getInfo());

                    Edge<VertexData> *newEdge = graph.addEdge(edge.getDest()->getInfo(),vector->getInfo(),weight,stol(id), edge.nome_rua,edge.district);
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

void Application :: drawUnableRoads(vector<vector<int>> v)
{
    if (v.size() == 0)
        return;

    int v1, v2;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        v1 = v[i][0];
        v2 = v[i][1];

        Vertex<VertexData> *vert1;

        for (auto vert : this->graph.getVertexSet())
        {
            if (vert->getInfo().getId() == v1)
            {
                vert1 = vert;
                for (int j = 0; j < vert->getAdj().size(); j++ )
                {
                    if (vert1->getAdj()[j].getDest()->getInfo().getId() == v2)
                    {
                        gv->setEdgeColor(vert1->adj[j].graphViewerId,"magenta");
                        gv->setEdgeThickness(vert1->adj[j].graphViewerId, 2);
                    }

                }
            }
        }

    }
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

        if(vertex->getInfo().getSharePoint().getBicycles() != -1 && vertex->getInfo().getSharePoint().getCurrentPrice() != -1 && vertex->getInfo().getSharePoint().getBicycles() < 10){
            gv->setVertexColor(vertex->getInfo().getId(),"red");
        }

        else if (vertex->getInfo().getSharePoint().getBicycles() != -1 && vertex->getInfo().getSharePoint().getCurrentPrice() != -1 &&vertex->getInfo().getSharePoint().getBicycles() >= 10)
            gv->setVertexColor(vertex->getInfo().getId(),"magenta");

        gv->addNode(vertex->getInfo().getId());

    }

    long edgeId = 0;

    for(auto vertex: graph.getVertexSet()){
        for(int j = 0; j < vertex->adj.size(); j++){
            gv->setEdgeLabel(edgeId,vertex->adj[j].nome_rua);

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

    Client c = Client(id,paymentMethod, paymentNumber);
    this->clientList.push_back(c);
}

void Application :: listSharePoints()
{
    cout << endl;
    for (auto v : this->graph.getVertexSet())
    {
        int n = 0;
        if (v->getInfo().getSharePoint().getBicycles() != -1) {
            n = v->getInfo().getSharePoint().getBicycles();
            cout << "SharePoint ID: " << v->getInfo().getId() << "\t Number of Bicycles: " << n << endl;
        }
    }
    cout << endl;
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
                edge.nome_rua = name;

                if (isTwoWay[0] == 'T'){
                    //double weight = getDist(vector->getInfo(),edge.getDest()->getInfo());
                    double weight = 1; //For testing only

                    Edge<VertexData> *newEdge = graph.addEdge(edge.getDest()->getInfo(),vector->getInfo(),weight,id, edge.nome_rua, edge.district);
                    if(newEdge != nullptr){
                        newEdge->nome_rua = name;
                    }
                }
            }
        }
    }
}

void Application :: addSubRoad()
{
    long id, node1_id, node2_id;
    string nome_rua, district;

    cout << "SubRoad ID: ";
    cin >> id;
    cout << "First Node ID: ";
    cin >> node1_id;
    cout << "Second Node ID: ";
    cin >> node2_id;
    cout << "Nome Rua: ";
    cin >> nome_rua;
    cout << "District: ";
    cin >> district;

    VertexData v1_finder(node1_id);
    VertexData v2_finder(node2_id);

    VertexData v1_real = graph.findVertex(v1_finder)->getInfo();
    VertexData v2_real = graph.findVertex(v2_finder)->getInfo();

    double weight = getWeight(v1_real, v2_real);

    graph.addEdge(v1_finder,v2_finder,weight,id,nome_rua,district);
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
    cout << "Payment Method: ";
    cin.ignore();
    getline(cin, paymentMethod);
    cout << "Payment Number: ";
    cin >> paymentNumber;

    Client c = Client(id,paymentMethod, paymentNumber);
    this->clientList.push_back(c);
}

void Application ::viewConnectivity() {
    this->graph.isConnected();
}

void Application ::drawGraph(int id, bool price, vector<vector<int>> vect, int num)
{
    //Este VertexData serve apenas para encontrar o VertexData que esta guardado no grafo
    VertexData v_finder(id);

    //Devolve vetor com o caminho ate ao sharepoint mais proximo do no que tem um id igual ao do v_finder (neste caso 11)
    vector<VertexData> nearest = graph.findNearestSharepoint(v_finder);

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
    drawSolution(trimSolution(nearest_list, vect));
    drawUnableRoads(vect);

    this->drop(num, trimSolution(nearest_list, vect)[trimSolution(nearest_list, vect).size() - 1].getId());
}

Graph<VertexData> Application :: getGraph(){
    return this->graph;
}

void Application ::viewGraph(vector<vector<int>> vect) {
    visualizeGraph();
    drawUnableRoads(vect);
}

vector<VertexData> Application ::trimSolution(vector<vector<VertexData>> vect, vector<vector<int>> id_vec) {

    int index = 0;
    vector<int> temp;

    auto it = vect.begin();
      for (; it != vect.end() ; it++){
        if ((*it)[(*it).size() - 1].getSharePoint().getBicycles() >= 10)
            vect.erase(it);
    }


    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[i].size() - 1; j++)
        {
            for (int k = 0; k < id_vec.size(); k++)
            {
                if (vect[i][j].getId() == id_vec[k][0] && vect[i][j+1].getId() == id_vec[k][1]) {
                    temp.push_back(i);
                }
            }
        }
    }



    bool flag0 = false;
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool flag4 = false;
    bool flag5 = false;

    for  (int m = 0; m < temp.size(); m++)
    {
        if (temp[m] == 0)
            flag0 = true;
    }

    for  (int m = 0; m < temp.size(); m++)
    {
        if (temp[m] == 1)
            flag1 = true;
    }

    for  (int m = 0; m < temp.size(); m++)
    {
        if (temp[m] == 2)
            flag2 = true;
    }

    for  (int m = 0; m < temp.size(); m++)
    {
        if (temp[m] == 3)
            flag3 = true;
    }

    for  (int m = 0; m < temp.size(); m++)
    {
        if (temp[m] == 4)
            flag4 = true;
    }

    for  (int m = 0; m < temp.size(); m++)
    {
        if (temp[m] == 5)
            flag5 = true;
    }


    if (!flag0) {
        index = 0;
        return vect[index];
    }
    if (!flag1){
        index = 1;
        return vect[index];
    }
    if (!flag2){
        index = 2;
        return vect[index];
    }
    if (!flag3){
        index = 3;
        return vect[index];
    }
    if (!flag4){
        index = 4;
        return vect[index];
    }
    if (!flag5){
        index = 5;
        return vect[index];
    }

/*    std::set<int> temp2;
    sort(temp.begin(), temp.end());
    for  (int m = 0; m < temp.size(); m++)
    {
        temp2.insert({temp[m]});
    }

    for (auto it2 = temp2.begin(); it2 != temp2.end(); it2++)
    {
        if (*it2 != index)
            break;
        else index++;
    }*/

    return vect[index];

}

void Application ::listPrice() {
    cout << endl;
    for (auto v : this->graph.getVertexSet())
    {
        int n = 0;
        if (v->getInfo().getSharePoint().getBicycles() != -1) {
            n = v->getInfo().getSharePoint().getCurrentPrice();
            cout << "SharePoint ID: " << v->getInfo().getId() << "\t Price: " << n << endl;
        }
    }
    cout << endl;
}

void Application ::listInfo() {
    cout << endl;
    for (auto v : this->graph.getVertexSet())
    {
        cout << "Vertex ID: " << v->getInfo().getId() << "\t Height: " <<  v->getInfo().getHeight() <<"\t X: " <<  v->getInfo().x <<"\t Y: " <<  v->getInfo().y << endl;
    }
    cout << endl;
}

void Application ::rent()
{
    int client_id;
    int node_id;

    cout << "Client ID: ";
    cin >> client_id;

    bool flag = false;
    for (int i = 0; i < this->clientList.size(); i++)
    {
        if (client_id == clientList[i].getId())
            flag = true;
    }

    if (!flag)
    {
        cout << "No client with such ID";
        return;
    }

    cout << "Share Point ID :";
    cin >> node_id;

    for (auto v : this->graph.getVertexSet())
    {
        if (v->getInfo().getId() == node_id)
        {
            if (v->getInfo().getSharePoint().getBicycles() > 0)
            {
                v->getInfo().getSharePoint().setBicycles(v->getInfo().getSharePoint().getBicycles() - 1);

                for (int k = 0; k < this->clientList.size(); k++)
                {
                    if (client_id == clientList[k].getId())
                        clientList[k].setBicycle(1);
                }
            }
        }

    }
    cout << endl;
}

void Application :: drop(int c_id, int n_id)
{
    for (int k = 0; k < this->clientList.size(); k++)
    {
        if (c_id == clientList[k].getId())
            clientList[k].setBicycle(-1);
    }

    for (auto v : this->graph.getVertexSet())
    {
        if (v->getInfo().getId() == n_id)
            v->getInfo().getSharePoint().setBicycles(v->getInfo().getSharePoint().getBicycles() + 1);
    }
}

vector<Client> Application ::getClientList(){
    return this->clientList;
}

void Application::applyDiscount() {
    double height=0;
    int i =0;
    for (auto it : graph.getVertexSet()){
        cout <<it->getInfo().getSharePoint().getBicycles() << endl;
        if (it->getInfo().getSharePoint().getBicycles() < 3)
            it->getInfo().getSharePoint().setCurrentPrice(it->getInfo().getSharePoint().getCurrentPrice()*0.7);
        i++;
        height+=it->getInfo().getHeight();
    }
    height=height/i;
    for (auto it : graph.getVertexSet()) {
        if (it->getInfo().getHeight() > height)
            it->getInfo().getSharePoint().setCurrentPrice(it->getInfo().getSharePoint().getCurrentPrice() * 0.75);
    }
}

void Application::findIfSharePoint(string rua1, string rua2) {

    cout << "Select algorithm: " << endl << endl;
    cout << "1 - Perfect match; " << endl;
    cout << "2 - Approximate match; " << endl;
    cout << "3 - Smart match (combines perfect and approximate); " << endl;
    int choice;
    cin >> choice;

    Edge<VertexData> edge1;
    Edge<VertexData> edge2;

    if(choice == 1){
        edge1 = graph.findPerfectMatch(rua1);
        edge2 = graph.findPerfectMatch(rua2);
    }else if(choice == 2){
        edge1 = graph.findApproximateMatch(rua1);
        edge2 = graph.findApproximateMatch(rua2);
    }else if(choice == 3){
        edge1 = graph.findBestMatch(rua1);
        edge2 = graph.findBestMatch(rua2);
    }else{
        findIfSharePoint(rua1,rua2);
    }

    if(edge1.getId() == -1 || edge2.getId() == -1){
        cout << "Could not find edge" << endl;
        return;
    }

    Vertex<VertexData> *vertex = graph.findIntersection(edge1,edge2);

    if(vertex == NULL){
        cout << "Could not find intersection for given street names" << endl;
        return;
    }

    if(vertex->getInfo().getSharePoint().getBicycles() < 0){
        cout << "Vertex is not a sharepoint" << endl;
    }else{
        cout << "Vertex is a sharepoint" << endl;
    }
}
