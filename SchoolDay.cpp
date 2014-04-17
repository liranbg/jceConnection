#include "SchoolDay.h"

SchoolDay::SchoolDay()
{
	cout << "Building Day" << endl;
}

SchoolDay::~SchoolDay()
{
	cout << "Killing Day" << endl;
}

void SchoolDay::addCourse(string& name, int start_time, int hoursLong, string& room)
{
	CourseTime c = {name, start_time, start_time+hoursLong, room};
	schedule.push_back(&c);
	schedule.sort();
}

void SchoolDay::printDay()
{
	for(CourseTime* c : schedule)
	{
		cout << "-----------" << endl;
		cout << c->name << endl;
		cout << c->startTime << "---" << c->endTime << endl;
		cout << c->room << endl;
	}
}