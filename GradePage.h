#ifndef GRADE_PAGE_H
#define GRADE_PAGE_H

#include "Page.h"
#include <list>
#include <vector>
#include <string.h>
#include "Course.h"

using namespace std;

/**
 * Usage: to be able to create a GradePage obj, you will need
 * to do so by using the createGradeClass method.
 * ex: GradePage* gp = GradePage::createGradeClass(*recieverPage);
 * that is why that methos is *static*.
 * you canot use new.
 *
 * if something went wrong while the creation of this class, debug
 * it via the output in the Terminal.
 *
 *
 * 2014.
 * sagi dayan
 */
class GradePage : public  Page
{
	
	public:
		static GradePage* createGradeClass(string& html);
		~GradePage();
		list<Course*> getList();
		int getRows(){return rowSize;}
		int getCols(){return colSize;}
		void printCourses();
	private:
		
		GradePage(string& html);
		void genList();
		list<Course*> courses;
		int rowSize, colSize;
		void tokenToLines();
		void tokenToCourseArgs(string& line, bool& first);
		void linkCourse();
		vector<string> lines;
		vector<string> courseArgs;

};


#endif