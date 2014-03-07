#include "Page.h"

Page::Page(string html)
{
	cout << "bulding page..." << endl;
	makeText(html);
}

Page::~Page()
{
	cout << "killing Page..." <<endl;
}


void Page::makeText(string html)
{
	bool foundTitle = false;
	bool inBody = false;
	string temp = "";
	for (int i = 0; i < html.length() ; i++)
	{
		if(!foundTitle)
		{
			if(html[i] == '<')
			{
				//title>
				i++;
				string titleTag = html.substr(i, 5); //legth of title
				if(titleTag == "title") //check if the tag is title
				{
					while(html[i] != '>')
						i++;
					i++;
					while(html[i] != '<')
					{
						temp += html[i];
						i++;
					}
					foundTitle = true;
					this->title = temp;
				}
			}
			temp = "" ; //clear temp BUFFER
		}
		else
		{
			if(html[i] == '<')
			{
				//body>
				i++;
				string bodyTag = html.substr(i, 4); //legth of "body"
				if(bodyTag == "body") //check if the tag is body tag
				{
					while(html[i] != '>')
						i++;
					i++;
					inBody = true;
				}
			}
		}
		
		if(inBody)
		{
			if(html[i] == '>')
			{
				i++;
				while(html[i] != '<')
				{
					temp += html[i];
					i++;
				}
			}
		}
	}

	this->text = temp;
}


string Page::getString()
{
	return this->text;
}

string Page::getTitle()
{
	return this->title;
}