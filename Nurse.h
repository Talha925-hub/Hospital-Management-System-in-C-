#pragma once

#include "Person.h"

class Nurse : public Person {
	string shift;
	string salary;

public:
	void getInfo() override;
	void saveToFile() const;
};


