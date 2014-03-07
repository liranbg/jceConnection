#ifndef JCE_H
#define JCE_H

#define dst_host "yedion.jce.ac.il"
#define dst_port 443

#include "sslsocket.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class jce
{
public:
	jce(std::string username,std::string password);
	~jce();

private:
	void makeFirstVisit();
	void makeFurtherRequests();
	std::string makeRequest(std::string);

	std::string username;
	std::string pass;
	std::string hasspass;
	std::string hassid;
	
	sslsocket *JceConnector;

};

#endif