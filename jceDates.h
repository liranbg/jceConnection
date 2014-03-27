#ifndef JCE_DATES_H
#define JCE_DATES_H

#include <iostream>

class jceDates
{
	public:
	jceDates();
	~jceDates() {};
	void setDate();
	std::string getFYear() { return this->fYear;}
	std::string getTYear() { return this->tYear;}
	std::string getFSemester() { return this->fSemester;}
	std::string getTSemester() { return this->tSemester;}

	private:
		std::string fYear; //from
		std::string fSemester;

		std::string tYear; //to
		std::string tSemester;

		bool checkSemesterInput(int);
		bool checkYearInput(int);


};

#endif