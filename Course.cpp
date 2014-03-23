#include "Course.h"

Course::Course(int serial, string name, string type, double points, double hours, double grade, string additions)
{
	this->serialNum = serial;
	this->name = name;
	this->type = type;
	this->points = points;
	this->hours = hours;
	this->grade = grade;
	this->additions = additions;
}

Course::~Course()
{
	
}

void Course::printCourse()
{
	cout << "===== Course =====" << endl;
	cout << "serial: " << this->serialNum <<endl;
	cout << "name: " << this->name <<endl;
	cout << "type: " << this->type <<endl;
	cout << "points: " << this->points <<endl;
	cout << "hours: " << this->hours <<endl;
	cout << "grade: " << this->grade <<endl;
	cout << "additions: " << this->additions <<endl;
	cout <<endl;
}