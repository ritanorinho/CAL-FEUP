#pragma once

#include <iostream>
#include <iomanip>
#include "Bicycle.h"

using namespace std;

class Client {
private:
	int id;
	Bicycle bicycle;
	string  paymentMethod;
	int paymentNumber;

public:
	Client(int id, Bicycle bicycle, string paymentMethod, int paymentNumber);
	int getId();
	Bicycle getBicycle();
	string getPaymentMethod();
	int getPaymentNumber();
	bool operator==(Client &cl);

};