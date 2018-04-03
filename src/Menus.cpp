#include "Menus.h"

Menu ::Menu(Application app) {
    this->app = app;
}

void Menu :: mainMenu(){
    cout << "All files loaded correctly. Please choose one of the following options: " << endl << endl;
    cout << "1 - View Data;" << endl;
    cout << "2 - Add Data;" << endl;
    cout << "3 - Return Bicycle;" << endl;
    cout << "4 - Find nearest SharePoint;" << endl;
    cout << "5 - Exit;"<< endl << endl;
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
            exit(0);
    }

}

void Menu ::viewMenu(){

    cout << "--------|| View Menu ||--------" << endl << endl;
    cout << " Please choose one of the following options: " << endl << endl;
    cout << "1 - View Full Graph;" << endl;
    cout << "2 - List Roads;" << endl;
    cout << "3 - List Nodes;" << endl;
    cout << "4 - List SubRoads;" << endl;
    cout << "5 - List SharePoints;"<< endl;
    cout << "6 - List Bicycles; " << endl;
    cout << "7 - List Clients;" << endl;
    cout << "8 - Back to Main Menu" << endl;
    cout << "Option: ";

    string op;
    cin >> op;
    int n = stoi(op);

    switch (n){
        case 1:
            //viewGraph();
            break;
        case 2:
            this->app.listRoads();
            break;
        case 3:
            returnMenu();
            break;
        case 4:
            nearestPointMenu();
            break;
        case 5:
            exit(0);
    }
}

void Menu :: addMenu(){}

void Menu :: returnMenu(){}

void Menu :: nearestPointMenu(){}
