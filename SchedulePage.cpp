#include "SchedulePage.h"


SchedulePage::SchedulePage(string& html) : Page(html)
{
	cout << "bulding SchedulePage..." << endl;

	cout << "finished building the SchedulePage" << endl;
}

SchedulePage* SchedulePage::createSchedulePage(string &html)
{
	try //the creation of Page.cpp can throw an exception
	{
		SchedulePage* newInstence = new SchedulePage(html);
		return newInstence;
	}catch(int err)
	{
		cout << "ERROR: in SchedulePage @ createSchedulePage func. number " << err <<endl;
		return NULL;
	}
}

SchedulePage::~SchedulePage()
{
	cout << "killing SchedulePage..." <<endl;
}