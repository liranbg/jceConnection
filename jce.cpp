#include "jce.h"

jce::jce() : userAcc()
{
	handler = new jceHandler(&userAcc);

}

void jce::start()
{
	handler->start();
}