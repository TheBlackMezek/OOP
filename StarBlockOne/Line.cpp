#include "Line.h"

#include "sfwdraw.h"



Line::Line()
{
	startx = 0;
	starty = 0;

	endx = 100;
	endy = 100;

	enabled = true;
}


Line::~Line()
{
}



void Line::draw()
{
	if (enabled)
	{
		sfw::drawLine(startx, starty, endx, endy);
	}
}

void Line::draw(float x1, float y1, float x2, float y2)
{
	sfw::drawLine(x1, y1, x2, y2);
}
