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
		puts("Error while connecting");
		abort();
	}
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
	//making connection short path
	
	std::string parameters = "?appname=BSHITA&prgname=LoginValidation&arguments=-N";
	parameters += userAcc.getUsername();
	parameters += ",-N";
	parameters += userAcc.getPassword();

	if (JceConnector->send(makeRequest(parameters)))
	{
		puts ("First login validation step");
		
		if (JceConnector->recieve(*recieverPage))
			puts("\nRecieved data");
		while (true)
		{
			std::size_t hasspass_position1 = recieverPage->find("-A,-N"); //finds the hashed password
			hasspass_position1 += 5;
			std::size_t hasspass_position2 = recieverPage->find(",-A,-A", hasspass_position1);
			if ((hasspass_position2 != std::string::npos) && (hasspass_position1 != std::string::npos)) {
				std::string hasspass = recieverPage->substr(hasspass_position1,hasspass_position2-hasspass_position1);
				userAcc.setHashedPassword(hasspass);			
			}
			std::size_t id_position1 = recieverPage->find("e=\"-N", 0); //finds the user id
			id_position1 += 5;
			std::size_t id_position2 = recieverPage->find(",-A", id_position1);
			if ((id_position2 != std::string::npos) && (id_position1 != std::string::npos)) {
				std::string hassid = recieverPage->substr(id_position1,id_position2-id_position1);
				userAcc.setUserID(hassid);
			}
			if (((userAcc.getUserID()).empty()) || ((userAcc.getHashedPassword()).empty()))
			{
				puts("conenction went wrong, reconnect. aborting");
				abort();
			}
			else
			{
				puts("we got our id and hash password");
				break; //we found the id and hash
			}
			
		}
		//prgname=LoginValidtion1&Arguments=-N[id],-A,-N[hash],-A,-A
		parameters = "prgname=LoginValidtion1&Arguments=-N";
		parameters += userAcc.getUserID();
		parameters += ",-A,-N";
		parameters += userAcc.getHashedPassword();
		parameters += ",-A,-A";
		if (JceConnector->send(makeRequest(parameters)))
		{
			puts ("stepping out the landing page. the main html will be here soon.");
			if (JceConnector->recieve(*recieverPage))
				puts("\nrecieved");


		}
		if  (JceConnector->send(makeRequest(getGradesPath("2013","0","2014","3")))) //change it in GUI (select years, semesters)
		{
			puts ("getting rates!");
			if (JceConnector->recieve(*recieverPage))
			{
				puts ("printing grades!");

				// const char * c =recieverPage->c_str();
				// std::size_t htmlTabINdex = recieverPage->find("<html");
				// c += htmlTabINdex; //getting c into the first <html> index in string
				// std::string pag = to_string(c);
				
				//writeHtmlToFile(*recieverPage); //writes string into page.html

				//std::cout << pag;
				
				Page p(*recieverPage);
				std::cout << p.getString();
			}
		}
			//makeFurtherRequests();
	}
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