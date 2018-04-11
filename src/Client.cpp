//
// Created by Rita Norinho on 07/04/2018.
//

#include "Client.h"
Client::Client(int id, string paymentMethod, int paymentNumber) {
	this->id = id;
	this->bicycleId = -1;
	this->paymentMethod = paymentMethod;
	this->paymentNumber = paymentNumber;
}
int Client::getId() {
	return id;
}
int Client::getBicycleId() {
	return this->bicycleId;
}
string Client::getPaymentMethod() {
	return this->paymentMethod;
}
int Client::getPaymentNumber() {
	return this->paymentNumber;
}

void Client ::setBicycle(int bicycleId)
{
	this->bicycleId = bicycleId;
}

