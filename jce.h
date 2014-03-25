#ifndef JCE_H
#define JCE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "sslsocket.h"
#include "user.h"
#include "Page.h"
#include "GradePage.h"

#define dst_host "yedion.jce.ac.il"
#define dst_port 443

enum jceErrors {
	VALIDATION_ERROR,
	OKOK,
	SOCKET_ERROR,
	NO_INPUT_ERROR
};
class jce
{
public:
	jce();

	~jce()  { delete recieverPage; delete JceConnector; }

private:
	void makeFirstVisit();
	void makeFurtherRequests();

	//validation steps
	std::string getFirstValidationStep(std::string username,std::string password);
	std::string getSecondValidationStep(std::string id,std::string hash);

	//getting html
	std::string getGradesPath(std::string fromyear, std::string fromsemester, 
		std::string toyear,std::string tosemester);

	//making server requests
	std::string makeRequest(std::string);

	//check if html file contains valid id and hash
	bool checkValidation(std::string &html);

	std::string *recieverPage;
	sslsocket *JceConnector;
	user userAcc;

};

#endif