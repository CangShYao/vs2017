#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

class student
{
public:
	student();
	student(string number, string name, string profrss, string math, string english, string physical);
	~student();
	string getNumber();
	string getName();
	string getProfess();
	string getMath();
	string getEnglish();
	string getPhysical();
	double getTotal();
	double getDMath();

protected:

private:
	string number;
	string name;
	string profrss;
	string math;
	string english;
	string physical;
	double totalScore;
};