#include "jceDates.h"
#include <sstream> //to_string function

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}
jceDates::jceDates()
{
	//defaul choises.
	this->fSemester = "0";
	this->fYear = "2010";
	this->tSemester = "2";
	this->tYear = "2014";
}
void jceDates::setDate()
{
	int fy,fs,ty,ts;
	while (true) {
		system("clear");
		std::cout << "\n----------------jce API alpha----------------" << std::endl;
		std::cout << "\tplease specify the date" << std::endl;
		std::cout << "\t\tFrom year: ";
		std::cin >> fy;
		std::cout << "\t\tFrom semester: ";
		std::cin >> fs;
		std::cout << "\t\tTo year: ";
		std::cin >> ty;
		std::cout << "\t\tTo semester: ";
		std::cin >> ts;
		if (!(checkSemesterInput(ts) && checkSemesterInput(fs) 
			&& checkYearInput(fy) && checkYearInput(ty)))
			printf("your input is out of range.\n please try again.");
		else
		{
			this->fSemester = to_string(fs);
			this->fYear = to_string(fy);
			this->tSemester = to_string(ts);
			this->tYear = to_string(ty);
			break;
		}
	}
}

bool jceDates::checkSemesterInput(int num)
{
	if ((num > 3) || (num < 0)) //out of semester range
		return false;
	return true;
}
bool jceDates::checkYearInput(int num)
{
	if ((num > 2020) || (num < 2000)) //out of year range
		return false;
	return true;
	
}