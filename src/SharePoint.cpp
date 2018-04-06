#include <iostream>
#include <iomanip>
#include <vector>
#include "SharePoint.h"
using namespace std;

 SharePoint::SharePoint() {
    bicycles = -1;currentPrice = -1;
}
 SharePoint::SharePoint(int bicycles, int currentPrice, int max_bicycle) {
	 this->bicycles = bicycles;
	 this->currentPrice = currentPrice;
     this->max_bicycle = max_bicycle;
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

bool SharePoint::dropBicycle() {
    if(bicycles < max_bicycle){
        bicycles++;
        return true;
    }
    return false;
}

bool SharePoint::pickBicycle() {
    if(bicycles > 0){
        bicycles--;
        return true;
    }
    return false;
}
