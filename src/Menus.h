#ifndef PROJECT1_MENUS_H
#define PROJECT1_MENUS_H

#include <iostream>
#include "Application.h"

using namespace std;

class Menu{
private:
    Application app;
public:
    Menu(Application app);
    void mainMenu();
    void viewMenu();
    void addMenu();
    void returnMenu();
    void nearestPointMenu();
    void distanceOp();
    void priceOp();
};


#endif //PROJECT1_MENUS_H
