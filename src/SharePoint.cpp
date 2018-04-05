#include <iostream>
#include <iomanip>
#include <vector>
#include "SharePoint.h"
using namespace std;

 SharePoint::SharePoint() {
    bicycles = -1;currentPrice = -1;
}
 SharePoint::SharePoint(int bicycles, int currentPrice) {
	 this->bicycles = bicycles;
	 this->currentPrice = currentPrice;
 }

int SharePoint::getBicycles() const {
    return bicycles;
}

void SharePoint::setBicycles(int bicycles) {
    SharePoint::bicycles = bicycles;
}

int SharePoint::getCurrentPrice() const {
    return currentPrice;
}

void SharePoint::setCurrentPrice(int currentPrice) {
    SharePoint::currentPrice = currentPrice;
}
