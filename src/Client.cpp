//
// Created by Rita Norinho on 07/04/2018.
//

#include "Client.h"
Client::Client(int id, int bicycleId, string paymentMethod, int paymentNumber) {
	this->id = id;
	this->bicycleId = bicycleId;
	this->paymentMethod = paymentMethod;
	this->paymentNumber = paymentNumber;
}
int Client::getId() {
	return id;
}
int Client::getBicycleId() {
	return bicycleId;
}
string Client::getPaymentMethod() {
	return paymentMethod;
}
int Client::getPaymentNumber() {
	return paymentNumber;
}

