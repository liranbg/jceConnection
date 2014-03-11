#include "Page.h"

Page::Page(string& html)
{
	cout << "bulding page... string size: " << html.length() << endl;
	if(html.empty())
	{
		cout << "ERROR: unable to build Page" << endl;
		return;
	}
	makeText(html);
}

Page::~Page()
{
	cout << "killing Page..." <<endl;
}

void Page::makeText(string& html)
{
	bool titleSearch = true;
	bool actualContent = false;
	string temp = "";
	for (int i = 0; i < html.length() ; i++)
	{
		if(titleSearch)
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
					titleSearch = false;
					this->title = temp;
				}
			}
			temp = "" ; //clear temp BUFFER
		}
		else if(!actualContent)
		{
			if(html[i] == '<')
			{
				i++;
				if(html[i] == '!')
				{
					//!--FileName
					string bodyTag = html.substr(i, 11); //!--FileName

					if(bodyTag == "!--FileName") //check if the tag is body tag
					{
						while(html[i] != '>')
							i++;
						actualContent = true;
					}
				}
			}
		}

		/**
		 * Actual Body Text In String
		 */
		 if(actualContent)
		 {
		 	if(html[i] == '<')
		 	{
				//tr> / td> / th
		 		i++;
				string tableTag = html.substr(i, 2); //legth of "tr/td"
				if(tableTag == "tr")
				{
					temp += "\n"; //new row -> new line
					while(html[i] != '>')
						i++;
					i++;
					i = stitchText(html, temp, i);
					if(i == -1) //EOF
						goto finishBuild;
				}
				else if(tableTag == "td" || tableTag == "th")
				{
					temp += "\t"; // new cell -> tab between data	
					while(html[i] != '>')
						i++;
					i++;
					i = stitchText(html, temp, i);
					if(i == -1) //EOF
						goto finishBuild;
				}
				else
				{
					while(html[i] != '>')
						i++;
				}
			}
		}
	}

	finishBuild:
		this->text = temp;
}

int Page::stitchText(string& from, string& to, int index)
{
	if(from[index] == '<')
		return index;
	
	while(from[index] != '<' && index < from.length())
	{	
		if(from[index] == '&')
		{
		//&nbsp;
			string nbspChr = from.substr(index, 6);
			if(nbspChr == "&nbsp;")
				index += 6;
		}

		if(endOfString(index, from.length()))
				return -1;

		if(from[index] != '\n')
			to += from[index];
		
		index++;
	}

	return index-1;
}

bool Page::endOfString(int index, int length)
{
	if(index < length)
		return false;
	return true;
}

string Page::getString()
{
	return this->text;
}

string Page::getTitle()
{
	return this->title;
}