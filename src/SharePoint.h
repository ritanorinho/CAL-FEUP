#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Road.h"
#include "Bicycle.h"

using namespace std;

class SharePoint {

private :
	vector<Bicycle> bicycles;
	int priceDay;
	Road road;



public:
	SharePoint();
	SharePoint(Road road, int priceDay);
	vector<Bicycle> getBicycles();
	int getPriceDay();
	Road getRoad();
	void addBicycle(Bicycle bicycle);
	bool operator==(SharePoint &sp);




};
