#pragma once

#include "Person.h"

class Receptionist : public Person {
	string shift;
	string salary;

public:
	void getInfo() override;
	void saveToFile() const;
};


