#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <string>

using namespace std;

enum pageException {TITLE_ERROR = 0, CANT_FIND_TABLE_ERROR};

class Page{

public:
	Page(string& html);
	~Page();
	string getString();
	string getTitle();
private:
	void makeText(string& html);
	int findTitle(string& from, int index);
	int runToActualText(string& from, int index);
	void manageTableContent(string& html, int index);
	int stitchText(string& from, string& to, int index);
	bool endOfString(int index, int length);
	string text;
	string title;
};

#endif