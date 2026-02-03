#pragma once
#ifndef PERSON_H
#define PERSON_H

#include <string>
using namespace std;

class Person {
protected:
	int id;
	string name;
	int age;
	string gender;

public:
	virtual void getInfo();
	virtual void saveToFile(const string& filename, const string& type, const string& extraInfo) const;
	virtual ~Person() = default;
};

#endif
