#include "jce.h"

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}

jce::jce(std::string username,std::string password)
{
	this->hassid = "";
	this->hasspass = "";
	recieverPage = new std::string("");
	JceConnector = new sslsocket(dst_host, dst_port); //open a new ssl connection to jce
	if (JceConnector->isCon())
	{
		this->username = username;
		this->pass = password;
		makeFirstVisit();
	}
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
void jce::makeFirstVisit()
{
	//making connection short path
	
	std::string parameters = "?appname=BSHITA&prgname=LoginValidation&arguments=-N";
	parameters += username;
	parameters += ",-N";
	parameters += pass;

	if (JceConnector->send(makeRequest(parameters)))
	{
		puts ("First login validation step");
		
		if (JceConnector->recieve(*recieverPage))
			puts("\nRecieved data");

		while (true)
		{
			std::size_t hasspass_position1 = recieverPage->find("-A,-N"); //finds the first position
			hasspass_position1 += 5;
			std::size_t hasspass_position2 = recieverPage->find(",-A,-A", hasspass_position1);
			if ((hasspass_position2 != std::string::npos) && (hasspass_position1 != std::string::npos)) {
				hasspass = recieverPage->substr(hasspass_position1,hasspass_position2-hasspass_position1); 			
			}
			std::size_t id_position1 = recieverPage->find("e=\"-N", 0); //finds the first position
			id_position1 += 5;
			std::size_t id_position2 = recieverPage->find(",-A", id_position1);
			if ((id_position2 != std::string::npos) && (id_position1 != std::string::npos)) {
				hassid = recieverPage->substr(id_position1,id_position2-id_position1);
			}
			if ((hassid.empty()) || (hasspass.empty()))
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
		parameters += hassid;
		parameters += ",-A,-N";
		parameters += hasspass;
		parameters += ",-A,-A";
		if (JceConnector->send(makeRequest(parameters)))
		{
			puts ("stepping out the landing page. the main html will be here soon.");
			if (JceConnector->recieve(*recieverPage))
				puts("\nrecieved");

			Page p(*recieverPage);
			puts(p.getString().c_str()); //printing as text

			// for (auto &p : *recieverPage) printing html
			// {
			// 	std::cout << p;
			// }
			makeFurtherRequests();
		}
	}
}