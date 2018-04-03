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
