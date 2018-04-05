#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class SharePoint {
	int bicycles;
	int currentPrice;
public:
	SharePoint();
	SharePoint(int bicycles, int priceDay);
	int getBicycles() const;
	void setBicycles(int bicycles);
	int getCurrentPrice() const;
	void setCurrentPrice(int currentPrice);
	bool operator==(SharePoint &sp);
};
