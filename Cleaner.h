#pragma once
#ifndef CLEANER_H
#define CLEANER_H

#include "Person.h"

class Cleaner : public Person {
	string dutyHours;
	string salary;
public:
	void getInfo() override;
	void saveToFile() const;
};

#endif
