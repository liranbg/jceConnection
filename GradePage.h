#ifndef GRADE_PAGE_H
#define GRADE_PAGE_H

#include "Page.h"
#include <list>

using namespace std;

typedef struct COURSE{
	string name;
	string type;
	double points;
	double hours;
	double grade;
}Course;


class GradePage : public  Page
{
	
	public:
		GradePage* createGradeClass(string& html);
		~GradePage();
		list<COURSE*> getList();
		int getRows(){return rowSize;}
		int getCols(){return colSize;}
	private:
		
		GradePage(string& html);
		void genList();
		list<COURSE*> courses;
		int rowSize, colSize;
		bool isMoreToList(int index);
		int goToNextArg(int index);

};


#endif