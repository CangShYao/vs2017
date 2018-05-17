#include "Student.h"

student::student()
{
}

student::student(string number, string name, string profrss, string math, string english, string physical)
{
	this->number = number;
	this->name = name;
	this->profrss = profrss;
	this->math = math;
	this->english = english;
	this->physical = physical;
	double intMath, intEnglish, intPhysical;
	if (math == "")
		intMath = 0;
	else
		intMath = atof(math.c_str());
	if (english == "")
		intEnglish = 0;
	else
		intEnglish = atof(english.c_str());
	if (physical == "")
		intPhysical = 0;
	else
		intPhysical = atof(physical.c_str());
	totalScore = intMath + intEnglish + intPhysical;
}

student::~student()
{
}

string student::getNumber()
{
	return number;
}

string student::getName()
{
	return name;
}

string student::getProfess()
{
	return profrss;
}

string student::getMath()
{
	return math;
}

string student::getEnglish()
{
	return english;
}

string student::getPhysical()
{
	return physical;
}

double student::getTotal()
{
	return totalScore;
}

double student::getDMath()
{
	return atof(math.c_str());
}
