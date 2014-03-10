#ifndef user_H
#define user_H
#include <string>
#include <stdio.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "jce.h"
using namespace std;
class user
{
public:
    user();
    void setUsername();
    void setPassword();
    string getPassword();
    string getUsername();
private:
    int getch();
    void getPass(string &pass);
    string username;
    string password;
    jce* connection;
};
#endif


