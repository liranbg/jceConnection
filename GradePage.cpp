#include "GradePage.h"

GradePage::GradePage(string& html) : Page(html)
{
	cout << "bulding GradePage..." << endl;
	genList();
}

GradePage::~GradePage()
{
	cout << "killing GradePage..." <<endl;
}

list<COURSE*> GradePage::getList()
{
	return this->courses;
}

GradePage* GradePage::createGradeClass(string& html)
{
	try
	{
		GradePage* newInstence = new GradePage(html);
		return newInstence;
	}catch(int err)
	{
		cout << "ERROR: in GradePage@createGradeClass func. number " << err <<endl;
	}	return nullptr;
}

void GradePage::genList()
{
	string name, type, numbers; //numbers = temp text to convert to double
	double points, hours, grade;
	int i=0, temp; //indexes

	while(text[i] != '>')
		i++;
	i++;
		//Actual line with content
	runLine:
	if(text[i] == '>')
		i++;
	if(text[i] == '\t' && text[i+1] == '\t')
	{
		i++;
		goto runLine;
	}
	i++;
		//getting name of course;
	temp = i+1;
	temp = goToNextArg(temp);
	if(!isMoreToList(temp))
		return;
	name = text.substr(i, temp);
		//getting type of course;
	i = temp+1;
	temp = goToNextArg(temp);
	if(!isMoreToList(temp))
		return;
	type = text.substr(i, temp);
		//getting points
	i = temp+1;
	temp = goToNextArg(temp);
	if(!isMoreToList(temp))
		return;
	numbers = text.substr(i, temp);
	points = atof(numbers.c_str());
		//getting hours
	i = temp+1;
	temp = goToNextArg(temp);
	if(!isMoreToList(temp))
		return;
	numbers = text.substr(i, temp);
	hours = atof(numbers.c_str());
		//getting grade
	i = temp+1;
	temp = goToNextArg(temp);
	if(!isMoreToList(temp))
		return;
	numbers = text.substr(i, temp);
	grade = atof(numbers.c_str());

		//adding to list!
		Course c = {name, type, points, hours, grade};

	courses.push_back(&c);

	while(text[i] != '\n')
		i++;
	i++;
	if(!isMoreToList(i))
		return;
	goto runLine;

}

int GradePage::goToNextArg(int index)
{
	while(text[index] != '\t')
		index++;
	return index;
}

bool GradePage::isMoreToList(int index)
{
	if(index > text.length()-1)
		return false;
	return true;
}