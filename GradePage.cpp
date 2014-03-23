#include "GradePage.h"
/**
 * Constructor
 */
GradePage::GradePage(string& html) : Page(html)
{
	cout << "bulding GradePage..." << endl;
	genList();
	rowSize = 6;
	colSize = courses.size();
	cout << "finished building the GradePage" << endl;
}

/**
 * DeConstructor
 */
GradePage::~GradePage()
{
	cout << "killing GradePage..." <<endl;
	courses.~list();
	lines.~vector();
	courseArgs.~vector();
}

/**
 * Returns the linked list of courses
 */
list<Course*> GradePage::getList()
{
	return this->courses;
}

/**
 * this method is the only way to get a new obj instence of this class.
 * for more details see the header file.
 * 
 * @param  html - a string with the HTML code
 * @return    GradePage* -  returns a NEW object of a GradePage
 */
GradePage* GradePage::createGradeClass(string& html)
{
	try //the creation of Page.cpp can throw an exception
	{
		GradePage* newInstence = new GradePage(html);
		return newInstence;
	}catch(int err)
	{
		cout << "ERROR: in GradePage @ createGradeClass func. number " << err <<endl;
	}	return nullptr;
}

/**
 * this method will create a linked list of all the courses and there
 * details that are needed.
 */
void GradePage::genList()
{
	bool first = true; // a boolean to make sure we are not getting the HTML title of the menu.
	tokenToLines(); //tokening the text into lines.
	for(string str : lines) // and then tokening every line into args for a single course. and adding it to list.
	{
		tokenToCourseArgs(str, first);
	}
}

/**
 * Using strtok function to cut the Page.cpp text into lines and storing them into a vector.
 */
void GradePage::tokenToLines()
{
	char *tok;
	char* textToTok = strdup(text.c_str());
	tok = strtok(textToTok, "\n");
	while(tok != NULL)
	{
		lines.push_back(string(tok));
		tok = strtok(NULL, "\n");
	}
	free(textToTok); //cleaning memory
	free(tok); // cleaning memory
}

/**
 * this method gets a line of text and cutting it into args via strtok with '\t' as a separator.
 * pushing all the args into a vector, and if there are 8 args, this line actualy contains a course.
 * so we send it forward to linkCourse method.
 * at the end, clearing the vector for the next line to come in.
 * 
 * @param line  - is the line string to chop
 * @param first - a boolean to make sure not to get the title of the HTML table...
 */
void GradePage::tokenToCourseArgs(string& line, bool& first)
{
	char* tok;
	char* cLine = strdup(line.c_str());
	tok = strtok(cLine, "\t");
	while(tok != NULL)
	{
		courseArgs.push_back(string(tok));
		tok=strtok(NULL, "\t");
	}
	if(courseArgs.size() == 8)
	{	if(first)
				first = false;
			else
				linkCourse();
	}
	free(tok);
	free(cLine);
	courseArgs.clear();
}

/**
 * this method will build all the variables we neet to build a Course Obj.
 * build it, and link it to the courses list.
 */
void GradePage::linkCourse()
{
	int serial;
	string name, type, additions;
	double points, hours, grade;
	char* temp;

	additions = courseArgs.back();
	courseArgs.pop_back();

	temp = strdup(courseArgs.back().c_str());
	grade = atof(temp);
	courseArgs.pop_back();

	temp = strdup(courseArgs.back().c_str());
	hours = atof(temp);
	courseArgs.pop_back();

	temp = strdup(courseArgs.back().c_str());
	points = atof(temp);
	courseArgs.pop_back();

	type = courseArgs.back();
	courseArgs.pop_back();

	name = courseArgs.back();
	courseArgs.pop_back();

	temp = strdup(courseArgs.back().c_str());
	serial = atoi(temp);
	courseArgs.pop_back();

	//Now to add to the linked list
	Course* c = new Course(serial, name, type, points, hours, grade, additions);
	courses.push_back(c);	
}

/**
 * Uses the printCourse function in the Course class
 * to print the list of courses.
 */
void GradePage::printCourses()
{
	for(Course* c : courses)
		c->printCourse();
}