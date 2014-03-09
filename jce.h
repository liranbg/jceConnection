#ifndef JCE_H
#define JCE_H

#define dst_host "yedion.jce.ac.il"
#define dst_port 443

#include "sslsocket.h"
#include "Page.h"
#include <iostream>
#include <string>
#include <sstream>

class jce
{
public:
	jce(std::string username,std::string password);

	~jce()  { delete recieverPage; delete JceConnector; }

private:
	void makeFirstVisit();
	void makeFurtherRequests();

	std::string getGradesPath(std::string fromyear, std::string fromsemester, 
		std::string toyear,std::string tosemester);

	std::string makeRequest(std::string);

	std::string username;
	std::string pass;
	std::string hasspass;
	std::string hassid;
	
	std::string *recieverPage;
	sslsocket *JceConnector;

};

#endif