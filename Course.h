#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>

#define	COURSE_FEALDS	7

using namespace std;
/**
 * A simple Course Class to contain all the Course Args,
 * and printing them if needed.
 *
 * to create a course Object, pass all needed Args.
 * use getters to get valuse of course.
 */
class Course{

public:
	Course(int serial, string name, string type, double points, double hours, double grade, string additions);
	~Course();
	void printCourse();  
	int getSerialNum(){return this->serialNum;}
	string getName(){return this->name;}
	string getType(){return this->type;}
	double getPoints(){return this->points;}
	double getHours(){return this->hours;}
	double getGrade(){return this->grade;}
	string getAddidtions(){return this->additions;}
private:
	int serialNum;
	string name;
	string type;
	double points;
	double hours;
	double grade;
	string additions;
};



#endif