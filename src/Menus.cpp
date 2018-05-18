#include "Menus.h"

Menu ::Menu(Application app) {
    this->app = app;
}

void Menu :: mainMenu(){
    cout << "All files loaded correctly. Please choose one of the following options: " << endl << endl;
    cout << "1 - View Data;" << endl;
    cout << "2 - Add Data;" << endl;
    cout << "3 - Rent Bicycle;"<< endl;
    cout << "4 - Find nearest SharePoint;" << endl;
    cout << "5 - Block Road;"<< endl;
    cout << "6 - Check if Sharepoint" << endl;
    cout << "7 - Exit;" << endl << endl;
    cout << "Option: ";

    string op;
    cin >> op;
    int n = stoi(op);

    switch (n){
        case 1:
            viewMenu();
            break;
        case 2:
            addMenu();
            break;
        case 3:
            returnMenu();
            break;
        case 4:
            nearestPointMenu();
            break;
        case 5:
            blockRoadMenu();
            break;
        case 6:
            checkIfSharepoint(false);
            break;
        case 7:
            exit(0);
    }

}

void Menu ::viewMenu(){

    cout << "--------|| View Menu ||--------" << endl << endl;
    cout << " Please choose one of the following options: " << endl << endl;
    cout << "1 - View Full Graph;" << endl;
    cout << "2 - View Graph's Connectivity;" << endl;
    cout << "3 - List Clients;" << endl;
    cout << "4 - List Bicycles;" << endl;
    cout << "5 - List Prices;" << endl;
    cout << "6 - List Vertex Info;" << endl;
    cout << "7 - Back to Main Menu" << endl;
    cout << "Option: ";

    string op;
    cin >> op;
    int n = stoi(op);

    switch (n){
        case 1:
            this->app.viewGraph(this->roadsBlocked);
            viewMenu();
            break;
        case 2:
            //Devolve true se o grafo estiver connectado
            this->app.viewConnectivity();
            viewMenu();
            break;
        case 3:
            this->app.listClients();
            viewMenu();
            break;
        case 4:
            this->app.listSharePoints();
            viewMenu();
            break;
        case 5:
            this->app.applyDiscount();
            this->app.listPrice();
            viewMenu();
            break;
        case 6:
            this->app.listInfo();
            viewMenu();
            break;
        case 7:
            this->mainMenu();
            break;
    }
}

void Menu :: addMenu(){

    cout << "--------|| Add Menu ||--------" << endl << endl;
    cout << " Please choose one of the following options: " << endl << endl;
    cout << "1 - Add Node;" << endl;
    cout << "2 - Add Road;" << endl;
    cout << "3 - Add SubRoad;" << endl;
    cout << "4 - Set New SharePoint;" << endl;
    cout << "5 - Add Bicycle;" << endl;
    cout << "6 - Add Client;"<< endl;
    cout << "7 - Back to Main Menu" << endl;
    cout << "Option: ";

    string op;
    cin >> op;
    int n = stoi(op);

    switch (n){
        case 1:
            this->app.addNode();
            addMenu();
            break;
        case 2:
            this->app.addRoad();
            addMenu();
            break;
        case 3:
            this->app.addSubRoad();
            addMenu();
            break;
        case 4:
            this->app.addSharePoint();
            addMenu();
            break;
        case 5:
            this->app.addBicycle();
            addMenu();
            break;
        case 6:
            this->app.addClient();
            addMenu();
            break;
        case 7:
            this->mainMenu();
            break;
    }

}

void Menu :: returnMenu(){
    cout << "--------|| Rent Bicycle Menu ||--------" << endl << endl;
    this->app.rent();
    this->mainMenu();
}

void Menu :: nearestPointMenu(){
    cout << "--------|| Find Nearest Point Menu ||--------" << endl << endl;

    int id;

    cout << "User ID: ";
    cin >> id;


    bool flag = false;
    for (int i = 0; i < this->app.getClientList().size(); i++)
    {
        if (this->app.getClientList()[i].getId() == id)
            flag = true;
    }

    if (!flag){
        cout << "No client with such ID" << endl;
        return;
    }

    int num = 0;
    for (int i = 0; i < this->app.getClientList().size(); i++)
    {
        if (this->app.getClientList()[i].getId() == id)
            if (this->app.getClientList()[i].getBicycleId() == -1) {
                cout << "First you have to rent a bike" << endl;
                return;
            } else
                num = this->app.getClientList()[i].getBicycleId();

    }


    cout << " Please choose one of the following options to optimize your travel: " << endl << endl;
    cout << "1 - Distance and Topology;" << endl;
    cout << "2 - Price;" << endl;
    cout << "3 - Back to Main Menu" << endl;
    cout << "Option: ";

    string op;
    cin >> op;
    int n = stoi(op);

    switch (n){
        case 1:
            distanceOp(num);
            this->mainMenu();
            break;
        case 2:
            priceOp(num);
            this->mainMenu();
            break;
        case 3:
            this->mainMenu();
            break;
    }
}

void Menu :: blockRoadMenu(){
    int id1, id2;
    cout << "--------|| Block Road Menu ||--------" << endl << endl;
    cout << " Please choose th two nodes of the road you want to block: " << endl << endl;
    cout << "First Node: " << endl;
    cin >> id1;
    cout << "Second Node: " << endl;
    cin >> id2;
    bool flag = false;

    for (auto v : this->app.getGraph().getVertexSet())
    {
        if (v->getInfo().getId() == id1) {
            for (auto e: v->getAdj()) {
                if (e.getDest()->getInfo().getId() == id2)
                    flag = true;
            }
        }
    }

    if (flag)
    {
        vector<int> r;
        r.push_back(id1);
        r.push_back(id2);
        this->roadsBlocked.push_back(r);
    }
    else{
        cout << endl <<"Error: The nodes you just chose do not form a valid road" << endl;
    }
    this->mainMenu();
}

void Menu ::distanceOp(int cid) {
    int id = checkIfSharepoint(true);
    if (id == -1)
        return;

    cout << "Calculating the best path ... " << endl;

    this->app.drawGraph(id, false, this->roadsBlocked, cid);

}

void Menu ::priceOp(int cid) {
    int id = checkIfSharepoint(true);
    if (id == -1)
        return;
    cout << "Calculating the best path ... " << endl;

    this->app.applyDiscount();
    this->app.drawGraph(id, true, this->roadsBlocked, cid);
}

vector<vector<int>> Menu ::getRoadsBlocked() {
    return this->roadsBlocked;
}

int Menu::checkIfSharepoint(bool findPath) {
    string rua1, rua2;

    cout << "Insert the name of the first street: " << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin,rua1);
    cout << "Insert the name of the second street: " << endl;
    getline(cin,rua2);

    int n = 0;
    n = this->app.findIfSharePoint(rua1,rua2, findPath); //False significa que apenas vai ver se é sharepoint | True faz o caminho
    if (n == -1)
        this->mainMenu();
    return n;
}
