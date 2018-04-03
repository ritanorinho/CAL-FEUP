#include <iostream>
#include <iomanip>
#include <vector>
#include "Bicycle.h"
#include "SharePoint.h"
using namespace std;

 SharePoint::SharePoint() {

}
 SharePoint::SharePoint(Road road, int priceDay) {
	 this->road = road;
	 this->priceDay = priceDay;

 }
 vector<Bicycle> SharePoint::getBicycles() {
	 return bicycles;

}
 int SharePoint::getPriceDay() {
	 return priceDay;
}
 Road SharePoint::getRoad() {
	 return road;
 }
 void SharePoint::addBicycle(Bicycle bicycle) {
	 bicycles.push_back(bicycle);
 }
 bool SharePoint::operator==(SharePoint &sp) {
	 if (this->road.name == sp.getRoad().name)
		 return true;
	 return false;
 }
