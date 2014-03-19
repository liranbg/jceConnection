#ifndef GRADE_PAGE_H
#define GRADE_PAGE_H

#include "Page.h"

using namespace std;

class GradePage : public  Page
{

	public:
		GradePage(string& html);
		~GradePage(){cout<<"Killing Grade Page...\n";}
		vector<vector<string>> getTable();
	private:
		void createTable();
};


#endif