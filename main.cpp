#include "main.h"
#include <string>
#include <iostream>

/*
	creating a connection using ssl to JCE students page.
	dst_host and dst_port declared in main.h
	
*/
int main(int argc, char *argv[])
{
	char usr[15];
	char pass[15];
	printf("please write your username: ");
	scanf("%s",usr);
	printf("\nplease write your password: ");
	scanf("%s",pass);
    jce *jc = new jce(usr,pass);
    while (true);
    
}
