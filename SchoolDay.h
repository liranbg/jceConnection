#ifndef S_DAY_H
#define S_DAY_H

#include <list>
#include <string>
#include <iostream>


using namespace std;

typedef struct CourseTime{
	string name;
	int startTime;
	int endTime;
	string room;
}CourseTime;

class SchoolDay{

public:
	SchoolDay();
	~SchoolDay();
	void addCourse(string& name, int start_time, int hoursLong, string& room);
	void printDay();
private:
	list<CourseTime*> schedule;

};




#endif