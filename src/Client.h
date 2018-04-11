
//
// Created by Rita Norinho on 07/04/2018.
//
#pragma once
#include <iostream>
#include <iomanip>

using namespace std;

class Client {
private:
    int id;
    int  bicycleId;
    string  paymentMethod;
    int paymentNumber;

public:
    Client(int id,string paymentMethod, int paymentNumber);
    int getId();
    int getBicycleId();
    string getPaymentMethod();
    int getPaymentNumber();
    void setBicycle(int id);

};