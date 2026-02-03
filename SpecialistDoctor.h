#pragma once
#ifndef SPECIALISTDOCTOR_H
#define SPECIALISTDOCTOR_H

#include "Person.h"

class SpecialistDoctor : public Person {
	string specialty;
	string salary;
public:
	void getInfo() override;
	void saveToFile() const;
};

#endif
