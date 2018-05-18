#ifndef PROJECT1_MENUS_H
#define PROJECT1_MENUS_H

#include <iostream>
#include "Application.h"

using namespace std;

class Menu{
private:
    Application app;
    vector<vector<int>> roadsBlocked;
public:
    Menu(Application app);
    void mainMenu();
    void viewMenu();
    void addMenu();
    void returnMenu();
    void nearestPointMenu();
    void distanceOp(int cid);
    void priceOp(int cid);
    void blockRoadMenu();
    vector<vector<int>> getRoadsBlocked();

    int checkIfSharepoint(bool findPath);
};


#endif //PROJECT1_MENUS_H
