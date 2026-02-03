#pragma once
#ifndef SECURITYGUARD_H
#define SECURITYGUARD_H

#include "Person.h"

class SecurityGuard : public Person {
	string dutyHours;
	string salary;
public:
	void getInfo() override;
	void saveToFile() const;
};

#endif
