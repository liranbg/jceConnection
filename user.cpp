#include "user.h"


user::user() : hashedPassword(""),userID("") 
{

	user::setUsername();
	user::setPassword();
}

int user::getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}


void user::getPass(string &pass) { 
	char ch;
	while(getch() != '\n');
	ch = getch();

   while(ch != 10 && ch != 13){//character 13 is enter
   	if (ch == 10 || ch == 13)
   		break;
   	pass.push_back(ch);
   	cout << '*';
   	ch = getch();
   }
}
void user::setUsername() { 
	cout << "Enter a username:\n";
	cin >> username;
}

void user::setPassword() {
	cout << "Enter a password:\n";
	getPass(password);
	cout << "\n";
}

void user::setUserID(string& ID)
{
	this->userID = ID;
}
void user::setHashedPassword(string& hashpass)
{
	this->hashedPassword = hashpass;
}

string user::getPassword() { return password; };
string user::getUsername() { return username; };
string user::getUserID(){ return userID; }
string user::getHashedPassword(){ return hashedPassword; }
