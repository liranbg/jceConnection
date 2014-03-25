#include "jce.h"

//simple method to convert types into string. 
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

jce::jce() : userAcc()
{
	recieverPage = new std::string("");
	JceConnector = new sslsocket(dst_host, dst_port); //open a new ssl connection to jce

	if (!JceConnector->isCon())
		printErrorANDabort(ERROR_ON_OPEN_SOCKET);

	makeFirstVisit();
}

void jce::makeFirstVisit()
{
	if (JceConnector->send(makeRequest(getFirstValidationStep(userAcc.getUsername(),userAcc.getPassword()))))
	{
		puts ("First login validation step");

		if (!JceConnector->recieve(*recieverPage))
			printErrorANDabort(ERROR_ON_GETTING_INFO);

		if (!checkValidation(*recieverPage))
			printErrorANDabort(ERROR_ON_VALIDATION);

		makeSecondVisit();
	}

	else
		printErrorANDabort(ERROR_ON_SEND_REQUEST);
	
}
void jce::makeSecondVisit()
{
	puts ("Second login validation step");
	if ((JceConnector->send(makeRequest(getSecondValidationStep(userAcc.getUserID(), userAcc.getHashedPassword())))))
	{
		if (!(JceConnector->recieve(*recieverPage)))
			printErrorANDabort(ERROR_ON_GETTING_INFO);

		makeFurtherRequests();
	}
	else
		printErrorANDabort(ERROR_ON_SEND_REQUEST);
}
bool jce::checkValidation(std::string &html)
{
	//finds the hashed password
	std::size_t hasspass_position1 = recieverPage->find("-A,-N"); 
	hasspass_position1 += 5;
	std::size_t hasspass_position2 = recieverPage->find(",-A,-A", hasspass_position1);
	if ((hasspass_position2 != std::string::npos) && (hasspass_position1 != std::string::npos))
	{
		std::string hasspass = recieverPage->substr(hasspass_position1,hasspass_position2-hasspass_position1);
		userAcc.setHashedPassword(hasspass);			
	}
	//finds the user id
	std::size_t id_position1 = recieverPage->find("e=\"-N", 0); 
	id_position1 += 5;
	std::size_t id_position2 = recieverPage->find(",-A", id_position1);
	if ((id_position2 != std::string::npos) && (id_position1 != std::string::npos))
	{
		std::string hassid = recieverPage->substr(id_position1,id_position2-id_position1);
		userAcc.setUserID(hassid);
	}
	if (((userAcc.getUserID()).empty()) || ((userAcc.getHashedPassword()).empty()))
		return false;

	return true;
}

void jce::makeFurtherRequests()
{
	puts ("getting rates!");
	if  (!(JceConnector->send(makeRequest(getGradesPath("2013","0","2014","3"))))) //change it in GUI (select years, semesters)
		printErrorANDabort(ERROR_ON_SEND_REQUEST);

	if (!(JceConnector->recieve(*recieverPage)))
	{
		printErrorANDabort(ERROR_ON_GETTING_GRADES);
	}

	GradePage* gp = GradePage::createGradeClass(*recieverPage);
	std::cout << gp->CoursesAmount() << " Courses in your Grade Sheet"<< endl;
	gp->printCourses();

}
std::string jce::getFirstValidationStep(std::string username, std::string password)
{
	std::string parameters = "?appname=BSHITA&prgname=LoginValidation&arguments=-N";
	parameters += username;
	parameters += ",-N";
	parameters += password;
	return parameters;
}
std::string jce::getSecondValidationStep(std::string id,std::string hash)
{
	std::string parameters = "prgname=LoginValidtion1&Arguments=-N";
	parameters += id;
	parameters += ",-A,-N";
	parameters += hash;
	parameters += ",-A,-A";
	return parameters;
}
std::string jce::getGradesPath(std::string fromyear, std::string fromsemester, 
	std::string toyear,std::string tosemester)
{
	std::string string = "PRGNAME=HADPASAT_MISMAHIM_LETALMID&ARGUMENTS=TZ,-N4,R1C2,R1C4,R1C1,R1C3,-A,-A,R1C5,-A,UNIQ&";
	string += "TZ=" + userAcc.getUserID() + "&";
	string += "UNIQ=" + userAcc.getHashedPassword() + "&";
	string += "R1C2=" + fromyear + "&";
	string += "R1C1=" + toyear + "&";
	string += "R1C3=" + tosemester + "&";
	string += "R1C4=" + fromsemester + "&";
	string += "R1C5=0";
	return string;
}
std::string jce::makeRequest(std::string parameters)
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
void jce::printErrorANDabort(jceErrors t)
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
			printf("socket error. check your internet connection\n");
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
