#include "SpaceObj.h"

#include "sfwdraw.h"



SpaceObj::SpaceObj()
{
	x = 1;
	y = 1;

	velx = 0;
	vely = 0;

	mass = 10;

	size = 20;
}


SpaceObj::~SpaceObj()
{
}



void SpaceObj::update()
{
	x += velx;
	y += vely;
}

void SpaceObj::draw()
{
	sfw::drawCircle(x, y, size);
}
