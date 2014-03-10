#ifndef user_H
#define user_H
#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
using namespace std;
class user
{
public:
    user();
    
    void setUsername();
    void setPassword();

    string getPassword();
    string getUsername();

    void setUserID(string& ID);
    void setHashedPassword(string& hashpass);
    string getUserID();
    string getHashedPassword();


private:

    int getch();
    void getPass(string &pass);

    string username;
    string password;

    string hashedPassword;
    string userID;

};
#endif


