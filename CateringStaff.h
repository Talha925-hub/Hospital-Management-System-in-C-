#pragma once
#ifndef CATERINGSTAFF_H
#define CATERINGSTAFF_H

#include "Person.h"

class CateringStaff : public Person {
	string role;
	string salary;
public:
	void getInfo() override;
	void saveToFile() const;
};

#endif
