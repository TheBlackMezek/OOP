#include "Box.h"

#include "sfwdraw.h"



Box::Box()
{
	width = 20;
	height = 10;

	x = 10;
	y = 10;

	enabled = true;
}


Box::~Box()
{
}



void Box::draw()
{
	if (enabled)
	{
		sfw::drawLine(x - width / 2, y - height / 2, x - width / 2, y + height / 2);
		sfw::drawLine(x + width / 2, y - height / 2, x + width / 2, y + height / 2);
		sfw::drawLine(x - width / 2, y - height / 2, x + width / 2, y - height / 2);
		sfw::drawLine(x - width / 2, y + height / 2, x + width / 2, y + height / 2);
	}
}

void Box::draw(float x, float y, float width, float height)
{
	sfw::drawLine(x - width / 2, y - height / 2, x - width / 2, y + height / 2);
	sfw::drawLine(x + width / 2, y - height / 2, x + width / 2, y + height / 2);
	sfw::drawLine(x - width / 2, y - height / 2, x + width / 2, y - height / 2);
	sfw::drawLine(x - width / 2, y + height / 2, x + width / 2, y + height / 2);
}
