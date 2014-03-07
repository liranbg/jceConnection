#include <iostream>
#include <string>

using namespace std;

class Page{

public:
	Page(string html);
	~Page();
	string getString();
	string getTitle();
private:
	void makeText(string html);
	string text;
	string title;
	bool haseTable;
};