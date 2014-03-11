#include "Page.h"

Page::Page(string& html)
{
	cout << "bulding page... string size: " << html.length() << endl;
	if(html.empty())
	{
		cout << "ERROR: unable to build Page" << endl;
		return;
	}
	try{
		makeText(html);
	}catch(int err)
	{
		switch(err)
		{
			case TITLE_ERROR:
				cout << "ERROR: cant find page title" << endl;
				break;
			case CANT_FIND_TABLE_ERROR:
				cout << "ERROR: cant locate actual data in page" << endl;
				break;
			default:
				cout << "ERROR: unknown" << endl;
				break;
		}
	}
}

Page::~Page()
{
	cout << "killing Page..." <<endl;
}

void Page::makeText(string& html)
{
	int index = 0;
	index = findTitle(html, index);
	if(index == -1)
		throw TITLE_ERROR;
	index = runToActualText(html, index);
	if(index == -1)
		throw CANT_FIND_TABLE_ERROR;
	manageTableContent(html, index);
}

int Page::findTitle(string& from, int index)
{
	cout << "**** in findTitle ****" << endl; //** DEBUG **
	string temp;
	while(index < from.length())
	{
		if(from[index] == '<')
		{
			//title>
			index++;
			string titleTag = from.substr(index, 5); //legth of title
			if(titleTag == "title") //check if the tag is title
			{
				while(from[index] != '>')
					index++;
				index++;
				while(from[index] != '<')
				{
					temp += from[index];
					index++;
				}
				this->title = temp; //sets the title
				return index;
			}
		}

		index++;
	}
	return -1;			
}

int Page::runToActualText(string& from, int index)
{
	cout << "**** in runToActualText ****" << endl;   //**DEBUG**
	cout << "**** index: "<< index <<" ****" << endl; //**DEBUG**
	while(index < from.length())
	{
		if(from[index] == '<')
		{
			index++;
			if(from[index] == '!')
			{
				//!--FileName
				string bodyTag = from.substr(index, 11); //!--FileName

				if(bodyTag == "!--FileName") //check if the tag is body tag
				{
					while(from[index] != '>')
						index++;
					return index;
				}
			}
		}
		index++;
	}
	return -1;
}

void Page::manageTableContent(string& html, int index)
{
	cout << "**** in manageTableContent ****" << endl;//** DEBUG **
	cout << "**** index: "<< index <<" ****" << endl; //** DEBUG **
		/**
		 * Actual Body Text In String
		 */
	string temp;
	for (int i = index; i < html.length(); i++)
	{
		if(html[i] == '<')
		 {
			//<tr> / <td> / <th>
			string tableTag = html.substr(i, 4); //legth of "tr/td"
			if(tableTag == "<tr>")
			{
				temp += "\n"; //new row -> new line
				i = stitchText(html, temp, i+4);
				if(i == -1) //EOF
					goto finishBuild;
			}
			else if(tableTag == "<td>" || tableTag == "<th>")
			{
				temp += "\t"; // new cell -> tab between data	
				i = stitchText(html, temp, i+4);
				if(i == -1) //EOF
					goto finishBuild;
			}
			else if(tableTag == "<td ") // a Year title (in grades table)
			{
				temp += "\t";
				while(html[i] != '>')
					i++;
				i = stitchText(html, temp, i);
			}
		}
		
	}

	finishBuild:
		this->text = temp;
}

int Page::stitchText(string& from, string& to, int index)
{
	if(from[index] == '<')
	{
		string bTag = from.substr(index, 3);
			if(bTag != "<b>")
				return index;
	}

	index += 2;
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