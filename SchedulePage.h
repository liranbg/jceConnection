#ifndef S_PAGE_H
#define S_PAGE_H

#include "Page.h"
#include <list>
#include <vector>
#include <string.h>

using namespace std;

class SchedulePage : public Page
{
public:
	static SchedulePage* createSchedulePage(string& html);
	~SchedulePage();

private:
	SchedulePage(string& html);
	

};


#endif