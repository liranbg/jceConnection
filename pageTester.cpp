#include <iostream>
#include "Page.h"
#include <string>
#include <fstream>
#include <streambuf>

int main(int argc, char const *argv[])
{


	std::ifstream t("htmlPage.html");
	std::string str;

	t.seekg(0, std::ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());

	Page p(str);
	cout << "Page Title: " << p.getTitle() << endl;
	cout << "************ Page Text ************" << endl;
	cout << p.getString() << endl;
	cout << "************ END OF PAGE TEXT ***********" <<endl;

	return 0;
}