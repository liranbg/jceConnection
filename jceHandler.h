#ifndef JCE_HANDLER_H
#define JCE_HANDLER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "sslsocket.h"
#include "user.h"
#include "jceDates.h"
#include "GradePage.h"
#include "SchedulePage.h"

#define dst_host "yedion.jce.ac.il"
#define dst_port 443



class jceHandler
{
public:
	enum jceOptions
	{
		GET_GRADES_BY_DATES,
		GET_SCHEDULE
	};
	jceHandler(user* const,jceDates* const);
	~jceHandler()  { delete recieverPage; delete JceConnector; }
	bool start();
	bool requestMenu(jceOptions);

private:


	enum jceErrors {
		ERROR_ON_VALIDATION,
		ERROR_ON_INPUT,
		ERROR_ON_CONNECTING,
		ERROR_ON_OPEN_SOCKET,
		ERROR_ON_GETTING_INFO,
		ERROR_ON_GETTING_GRADES,
		ERROR_ON_SEND_REQUEST
	};

	void makeFirstVisit();
	void makeSecondVisit();
	void getGraders();
	void getSchedule();


	//validation steps
	std::string getFirstValidationStep();
	std::string getSecondValidationStep();

	//getting html
	std::string getSchedulePath();
	std::string getGradesPath();

	//making server requests
	std::string makeRequest(std::string);

	//check if html file contains valid id and hash
	bool checkValidation(std::string &html);
	void checkConnection();
	void printErrorANDabort(jceErrors t);


	std::string * recieverPage;
	sslsocket * JceConnector;
	user * const jceUser; //there is only one user. therefor we need only 1 user in time. we wont change the pointer to other user. and we wont make new user.
	jceDates * const jDates;

};

#endif