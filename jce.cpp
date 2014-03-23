#include "jce.h"


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
	if (JceConnector->isCon())
		makeFirstVisit();
	else
	{
		puts("Error while connecting. is your connection ok?");
		exit(1);
	}
}

bool writeHtmlToFile(string& page)
{
	ofstream myfile ("page.html");
	if (myfile.is_open())
	{
		myfile << page;
		myfile.close();
		return true;
	}
	else 
		cout << "Unable to open file";
	return false;
}
void jce::makeFirstVisit()
{
	if (JceConnector->send(makeRequest(getFirstValidationStep(userAcc.getUsername(),userAcc.getPassword()))))
	{
		puts ("First login validation step...");
		if (!JceConnector->recieve(*recieverPage))
			exit(1);

		puts("\tRecieved data");

		if (!checkValidation(*recieverPage))
		{
			puts("error while validating");
			exit(1);
		}

		//sending second validation step.
		if (!(JceConnector->send(makeRequest(getSecondValidationStep(userAcc.getUserID(),
			userAcc.getHashedPassword())))))
		{
			puts("error while second validation");
			exit(1);
		}
		puts ("stepping out the landing page. second validation step.\n\tthe main html will be here soon.\n");
		if (!(JceConnector->recieve(*recieverPage)))
		{
			puts("error while recieving");
			exit(1);
		}
		puts("\nrecieved");
		if  (!(JceConnector->send(makeRequest(getGradesPath("2013","0","2014","3")))))
		 //change it in GUI (select years, semesters)
		{
			puts("error while requesting grades");
			exit(1);
		}
		puts ("getting rates!");
		if (!(JceConnector->recieve(*recieverPage)))
		{
			puts("error while getting grades");
			exit(1);
		}
		puts ("printing grades!");
				// const char * c =recieverPage->c_str();
				// std::size_t htmlTabINdex = recieverPage->find("<html");
				// c += htmlTabINdex; //getting c into the first <html> index in string
				// std::string pag = to_string(c);

				//writeHtmlToFile(*recieverPage); //writes string into page.html

				//std::cout << pag;

		GradePage* gp = GradePage::createGradeClass(*recieverPage);
		std::cout << gp->getList().size() << " Courses in your Grade Sheet:"<< endl;
		gp->printCourses();
		
			//makeFurtherRequests();
	}
	else
	{
		puts("eror while first validation step");
		exit(1);
	}
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
	if (((userAcc.getUserID()).empty()) || 
		((userAcc.getHashedPassword()).empty()))
	{
		puts("conenction went wrong, reconnect. aborting");
		return false;
	}

	puts("we got our id and hash password");
	return true;
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
void jce::makeFurtherRequests()
{
	std::string parameters;
	puts("\nwrite ur command:");
	std::cin >> parameters;
	std::cout << parameters;
	if (JceConnector->send(makeRequest(parameters)))
	{
		puts("message has been sent");
		if (JceConnector->recieve(*recieverPage))
			puts("\nrecieved");
		for (auto &p : *recieverPage)
		{
			std::cout << p;
		}
	}
	//delete
}