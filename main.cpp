#include "main.h"
#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    user *curr_user = new user(); 
    jce *jc = new jce(curr_user->getUsername(),curr_user->getPassword());
    while (true);
    
}
