#ifndef JCE_H
#define JCE_H

#include "jceHandler.h"

enum jceOPTIONS
{
	GET_GRADES_BY_DATES,
	GET_SCHEDULE
};
class jce
{

public:
	jce();
	~jce() {}
	void start();


private:
	jceHandler* handler;
	user userAcc;
};

#endif