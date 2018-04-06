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
	SharePoint(int bicycles, int priceDay, int max_bicycle);
	int getBicycles() const;
	bool dropBicycle();
	bool pickBicycle();
	void setBicycles(int bicycles);
	int getCurrentPrice() const;
	void setCurrentPrice(int currentPrice);
    int max_bicycle;
};
