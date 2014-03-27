#ifndef JCE_H
#define JCE_H

#include "jceHandler.h"


class jce
{

public:
	jce();
	~jce() { free(handler); }
	void start();


private:
	user userAcc;
	jceDates jDates;
	jceHandler* handler;

};

#endif