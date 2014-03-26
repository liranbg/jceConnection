#ifndef JCE_HANDLER_H
#define JCE_HANDLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "sslsocket.h"
#include "user.h"

#include "GradePage.h"

#define dst_host "yedion.jce.ac.il"
#define dst_port 443

enum jceErrors {

	ERROR_ON_VALIDATION,
	ERROR_ON_INPUT,
	ERROR_ON_CONNECTING,
	ERROR_ON_OPEN_SOCKET,
	ERROR_ON_GETTING_INFO,
	ERROR_ON_GETTING_GRADES,
	ERROR_ON_SEND_REQUEST

};
class jceHandler
{
public:

	jceHandler(user* const a);
	~jceHandler()  { delete recieverPage; delete JceConnector; }
	void start();

private:

	void makeFirstVisit();
	void makeSecondVisit();
	void makeFurtherRequests();


	//validation steps
	std::string getFirstValidationStep();
	std::string getSecondValidationStep();

	//getting html
	std::string getGradesPath(std::string fromyear, std::string fromsemester, 
		std::string toyear,std::string tosemester);

	//making server requests
	std::string makeRequest(std::string);

	//check if html file contains valid id and hash
	bool checkValidation(std::string &html);

	void printErrorANDabort(jceErrors t);


	std::string * recieverPage;
	sslsocket * JceConnector;
	user * const jceUser; //there is only one user. therefor we need only 1 user in time. we wont change the pointer to other user. and we wont make new user.
	

};

#endif