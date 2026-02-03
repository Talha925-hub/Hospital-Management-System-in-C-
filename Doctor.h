#pragma once

#include "Person.h"

class Doctor : public Person {
	string department;
	string salary;

public:
	void getInfo() override;
	void saveToFile() const;
};


