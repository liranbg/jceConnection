#include "jceHandler.h"
template <typename T>
std::string to_string(T value); //simple method to convert types into string. 


jceHandler::jceHandler(user* const us,jceDates* const jd) : jceUser(us), jDates(jd)
{
	recieverPage = new std::string("");
	JceConnector = new sslsocket(dst_host, dst_port); //open a new ssl connection to jce	
}
bool jceHandler::start()
{
	checkConnection();

	makeFirstVisit();

	makeSecondVisit();

	//if succeed on all visiting, that means everything is clear.
	//
	//what we need to do is make the tests more clean
	return true;
}
bool jceHandler::requestMenu(jceOptions t)
{
	checkConnection();

	switch (t)
	{
		case GET_GRADES_BY_DATES:
		getGraders();
		break;
		case GET_SCHEDULE:
		getSchedule();
		break;
		default:
		return true;
	}
	return false;

}
void jceHandler::makeFirstVisit()
{
	if (JceConnector->send(makeRequest(getFirstValidationStep())))
	{
		puts ("First login validation step");
		if (!JceConnector->recieve(*recieverPage))
			printErrorANDabort(jceHandler::ERROR_ON_GETTING_INFO);

		if (!checkValidation(*recieverPage))
			printErrorANDabort(jceHandler::ERROR_ON_VALIDATION);

		return;
	}
	else
		printErrorANDabort(jceHandler::ERROR_ON_SEND_REQUEST);
	
}
void jceHandler::makeSecondVisit()
{
	puts ("Second login validation step");
	if ((JceConnector->send(makeRequest(getSecondValidationStep()))))
	{
		if (!(JceConnector->recieve(*recieverPage)))
			printErrorANDabort(jceHandler::ERROR_ON_GETTING_INFO);

		return;
	}
	else
		printErrorANDabort(jceHandler::ERROR_ON_SEND_REQUEST);
}

void jceHandler::checkConnection()
{
	if (!JceConnector->isCon())
		printErrorANDabort(jceHandler::ERROR_ON_OPEN_SOCKET);
}
void jceHandler::getSchedule()
{
	
	puts("getting schedule");
	if  (!(JceConnector->send(makeRequest(getSchedulePath()))))
		printErrorANDabort(jceHandler::ERROR_ON_SEND_REQUEST);
	if (!(JceConnector->recieve(*recieverPage)))
	{
		printErrorANDabort(jceHandler::ERROR_ON_GETTING_GRADES);
	}


	
	std::cout << *recieverPage;

}
void jceHandler::getGraders()
{
	puts ("getting rates!");
	if  (!(JceConnector->send(makeRequest(getGradesPath()))))
		printErrorANDabort(jceHandler::ERROR_ON_SEND_REQUEST);

	if (!(JceConnector->recieve(*recieverPage)))
	{
		printErrorANDabort(jceHandler::ERROR_ON_GETTING_GRADES);
	}

	GradePage* gp = GradePage::createGradeClass(*recieverPage);
	std::cout << gp->CoursesAmount() << " Courses in your Grade Sheet"<< endl;
	gp->printCourses();
	cout << "____________" << endl;
	cout << "Your GPA is currently: \033[5;32m" << gp->getAvg() << "\033[0m"<< endl << endl;

}

std::string jceHandler::getSchedulePath()
{
	std::string string = "PRGNAME=Bitsua_maarechet_shaot&ARGUMENTS=TZ,UNIQ,MisparSheilta,R1C1,R1C2&";
	string += "TZ=" + jceUser->getUserID()+ "&";
	string += "UNIQ=" + jceUser->getHashedPassword() + "&";
	string += "MisparSheilta=3&";
	string += "R1C1=" + jDates->getTYear() + "&";
	string += "R1C2=" + jDates->getTSemester();
	return string; 

}
std::string jceHandler::getGradesPath()
{
	std::string string = "PRGNAME=HADPASAT_MISMAHIM_LETALMID&ARGUMENTS=TZ,-N4,R1C2,R1C4,R1C1,R1C3,-A,-A,R1C5,-A,UNIQ&";
	string += "TZ=" + jceUser->getUserID() + "&";
	string += "UNIQ=" + jceUser->getHashedPassword() + "&";
	string += "R1C2=" + jDates->getFYear() + "&";
	string += "R1C1=" + jDates->getTYear() + "&";
	string += "R1C3=" + jDates->getTSemester() + "&";
	string += "R1C4=" + jDates->getFSemester() + "&";
	string += "R1C5=0";
	return string;
}
std::string jceHandler::makeRequest(std::string parameters)
{
	std::string msg;
	msg = "POST /yedion/fireflyweb.aspx HTTP/1.1\r\n";
	msg += "Host: " + to_string(dst_host) + "\r\n";
	msg += "Content-Type: application/x-www-form-urlencoded\r\n";
	msg += "Content-Length: " + to_string(parameters.length()) + "\r\n";
	msg += "Proxy-Connection: Keep-Alive\r\n";
	msg += "Accept-Charset: utf-8";
	msg += "Accept: text/plain\r\n";
	msg += "Connection: Keep-Alive\r\n";
	msg += "\r\n";
	msg += parameters;
	return msg;
}
std::string jceHandler::getFirstValidationStep()
{
	std::string parameters = "?appname=BSHITA&prgname=LoginValidation&arguments=-N";
	parameters += jceUser->getUsername();
	parameters += ",-N";
	parameters += jceUser->getPassword();
	return parameters;
}
std::string jceHandler::getSecondValidationStep()
{
	std::string parameters = "prgname=LoginValidtion1&Arguments=-N";
	parameters += jceUser->getUserID();
	parameters += ",-A,-N";
	parameters += jceUser->getHashedPassword();
	parameters += ",-A,-A";
	return parameters;
}
bool jceHandler::checkValidation(std::string &html)
{
	//finds the hashed password
	std::size_t hasspass_position1 = recieverPage->find("-A,-N"); 
	hasspass_position1 += 5;
	std::size_t hasspass_position2 = recieverPage->find(",-A,-A", hasspass_position1);
	if ((hasspass_position2 != std::string::npos) && (hasspass_position1 != std::string::npos))
	{
		std::string hasspass = recieverPage->substr(hasspass_position1,hasspass_position2-hasspass_position1);
		jceUser->setHashedPassword(hasspass);			
	}
	//finds the user id
	std::size_t id_position1 = recieverPage->find("e=\"-N", 0); 
	id_position1 += 5;
	std::size_t id_position2 = recieverPage->find(",-A", id_position1);
	if ((id_position2 != std::string::npos) && (id_position1 != std::string::npos))
	{
		std::string hassid = recieverPage->substr(id_position1,id_position2-id_position1);
		jceUser->setUserID(hassid);
	}
	if (((jceUser->getUserID()).empty()) || ((jceUser->getHashedPassword()).empty()))
		return false;

	return true;
}
void jceHandler::printErrorANDabort(jceErrors t)
{
	switch(t)
	{
		case ERROR_ON_VALIDATION:
		{
			printf("validation error\n");
			break;
		}
		case ERROR_ON_CONNECTING:
		{
			printf("No connection\n");
			break;
		}

		case ERROR_ON_INPUT:
		{
			printf("you must have an input\n");
			break;
		}
		case ERROR_ON_OPEN_SOCKET:
		{
			printf("socket error. check your Internet connection\n");
			break;
		}
		case ERROR_ON_GETTING_INFO:
		{
			printf("cant retrieve information. please reload\n");
			break;
		}
		case ERROR_ON_GETTING_GRADES:
		{
			printf("cant retrieve grade page\n");
			break;
		}
		case ERROR_ON_SEND_REQUEST:
		{
			printf("cant make request with sockets. wtf?");
		}
	}
	exit(1);
}
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}