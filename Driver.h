#pragma once
#ifndef DRIVER_H
#define DRIVER_H

#include "Person.h"

class Driver : public Person {
	string licenseNo;
	string salary;
public:
	void getInfo() override;
	void saveToFile() const;
};

#endif
