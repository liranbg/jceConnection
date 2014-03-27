#include "jce.h"

jce::jce() : userAcc(),jDates()
{
	handler = new jceHandler(&userAcc,&jDates);

}

void jce::start()
{
	if (handler->start())
	{
		int ch;
		do
		{
			system("clear");
			printf("\n----------------jce API alpha----------------\n");
			printf("\tPlease choose as following:\n");
			printf("\t\tShow grades: 1\n");
			printf("\t\tShow scheduale: 2\n");
			printf("\t\tChange dates: 3\n");
			printf("\t\ttype q to quit ");
			switch(ch)
			{
				case '1':
				handler->requestMenu(jceHandler::GET_GRADES_BY_DATES);
				printf("\npress enter to continue...");
				getchar();
				break;
				case '2':
				handler->requestMenu(jceHandler::GET_SCHEDULE);
				printf("\npress enter to continue...");
				getchar();
				break;
				case '3':
				jDates.setDate();
				break;

			}
		}while ((ch = getchar()) != 'q');
		
	}
	else
	{
		printf("\ncouldnt visit");
		exit(1);
	}

}


