#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum pageException {UNKNOWN_ERROR=-1,TITLE_ERROR = 0, CANT_FIND_TABLE_ERROR};

class Page{

public:
	Page(string& html);
	~Page();
	string getString();
	string getTitle();
	virtual vector<vector<string>> getTable() = 0;
protected:
	void makeText(string& html);
	int findTitle(string& from, int index);
	int runToActualText(string& from, int index);
	void manageTableContent(string& html, int index);
	int stitchText(string& from, string& to, int index);
	bool endOfString(int index, int length);
	virtual void createTable() = 0;
	string text;
	string title;
	//Vector in heap memory
	vector<vector<string>>* table = new vector<vector<string>>;
};

#endif