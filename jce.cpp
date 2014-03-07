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
	this->hasspass="";
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

	//prgname=LoginValidtion1&Arguments=-N302539556,-A,-N013145836517240,-A,-A
	//prgname=LoginValidtion1&Arguments=-N302539556,-A,-N016406877497933,-A,-A
	
	std::string parameters;
	puts("\nwrite ur command:");
	std::cin >> parameters;
	std::cout << parameters;

	if (JceConnector->send(makeRequest(parameters)))
	{
		puts ("message has been sent");
		std::vector<std::string> reciever;
		if (JceConnector->recieve((reciever)))
			puts("\nrecieved");
		for (auto &p : reciever)
		{
			std::cout << p;
		}
	}
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
		puts ("First connection has been sent");
		std::vector<std::string> reciever;
		if (JceConnector->recieve((reciever)))
			puts("\nrecieved");

		for (auto &p : reciever)
		{
			std::size_t hasspass_position1 = p.find("-A,-N"); //finds the first position
			hasspass_position1 += 5;
			std::size_t hasspass_position2 = p.find(",-A,-A", hasspass_position1);
			if ((hasspass_position2 != std::string::npos) && (hasspass_position1 != std::string::npos)) {
				hasspass = p.substr(hasspass_position1,hasspass_position2-hasspass_position1); 			
			}
			std::size_t id_position1 = p.find("e=\"-N", 0); //finds the first position
			id_position1 += 5;
			std::size_t id_position2 = p.find(",-A", id_position1);
			if ((id_position2 != std::string::npos) && (id_position1 != std::string::npos)) {
				hassid = p.substr(id_position1,id_position2-id_position1);
			}
			if ((hassid.empty()) || (hasspass.empty()))
			{
				puts("conenction went wrong, reconnect. aborting");
				abort();
			}
			
		}
		//prgname=LoginValidtion1&Arguments=-N302539556,-A,-N016406877497933,-A,-A
		parameters = "prgname=LoginValidtion1&Arguments=-N";
		parameters += hassid;
		parameters += ",-A,-N";
		parameters += hasspass;
		parameters += ",-A,-A";
		if (JceConnector->send(makeRequest(parameters)))
		{
			puts ("stepping out the landing page. the main html will be here soon.");
			std::vector<std::string> reciever;
			if (JceConnector->recieve((reciever)))
				puts("\nrecieved");
			for (auto &p : reciever)
			{
				std::cout << p;
			}
			makeFurtherRequests();
		}
	}
}