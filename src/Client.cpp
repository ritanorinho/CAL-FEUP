//
// Created by Rita Norinho on 07/04/2018.
//

#include "Client.h"
Client::Client(int id, Bicycle bicycle, string paymentMethod, int paymentNumber) {
	this->id = id;
	this->bicycle = bicycle;
	this->paymentMethod = paymentMethod;
	this->paymentNumber = paymentNumber;
}
int Client::getId() {
	return id;
}
Bicycle Client::getBicycle() {
	return bicycle;
}
string Client::getPaymentMethod() {
	return paymentMethod;
}
int Client::getPaymentNumber() {
	return paymentNumber;
}

