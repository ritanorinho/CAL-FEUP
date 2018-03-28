#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include "Bicycle.h"

using namespace std;

class SharePoint {

private :
	vector<Bicycle> bicycles;
	int priceDay;

public:
	SharePoint();
	vector<Bicycle> getBicycles();
	int getPriceDay();



};
