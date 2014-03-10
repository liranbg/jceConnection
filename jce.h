#ifndef JCE_H
#define JCE_H

#define dst_host "yedion.jce.ac.il"
#define dst_port 443

#include "sslsocket.h"
#include "Page.h"
#include "user.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class jce
{
public:
	jce();

	~jce()  { delete recieverPage; delete JceConnector; }

private:
	void makeFirstVisit();
	void makeFurtherRequests();

	std::string getGradesPath(std::string fromyear, std::string fromsemester, 
		std::string toyear,std::string tosemester);

	std::string makeRequest(std::string);

	std::string *recieverPage;
	sslsocket *JceConnector;
	user userAcc;

};

#endif