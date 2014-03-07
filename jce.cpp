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
void jce::makeFirstVisit()
{
	//making connection short path
	std::string parameters = "?appname=BSHITA&prgname=LoginValidation&arguments=-N";
	parameters += username;
	parameters += ",-N";
	parameters += pass;
	if (JceConnector->send(makeRequest(parameters)))
	{
		puts ("message has been sent");
		std::vector<std::string> reciever;
		JceConnector->recieve((reciever));
		for (std::vector<std::string>::iterator i = reciever.begin(); i != reciever.end(); ++i)
		{
			std::cout << *i;
			//printing the html
		}
		puts("\nrecieved");
	}

	//prgname=LoginValidtion1&Arguments=-N302539556,-A,-N013145836517240,-A,-A
}