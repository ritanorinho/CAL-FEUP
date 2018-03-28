#include <iostream>
#include <iomanip>
#include <vector>
#include "Bicycle.h"
#include "SharePoint.h"
using namespace std;

 SharePoint::SharePoint() {

}
 vector<Bicycle> SharePoint::getBicycles() {
	 return bicycles;

}
 int SharePoint::getPriceDay() {
	 return priceDay;
}
