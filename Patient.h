#pragma once
#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"

class Patient : public Person {
	string disease;
	string admitDate;

public:
	void getInfo() override;
	void saveToFile() const;
};

#endif
