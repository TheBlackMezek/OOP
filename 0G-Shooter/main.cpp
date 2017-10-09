

#include "sfwdraw.h"



int main()
{

	sfw::initContext(800, 600, "0G Shooter");

	sfw::setBackgroundColor(BLACK);

	while (sfw::stepContext())
	{
		sfw::drawCircle(10, 10, 10);
	}

	return 0;
}