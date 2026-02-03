#pragma once
#ifndef AMBULANCE_H
#define AMBULANCE_H

#include <string>
#include <iostream>
using namespace std;

class Ambulance {
	int vehicleNo;
	string model, driverName;
	string petrol_price;
public:
	void getInfo();
	void saveToFile() const;
};

#endif
