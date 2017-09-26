#include "Player2.h"

#include "sfwdraw.h"

#include "Box.h"



Player2::Player2()
{
	x = 10;
	y = 10;

	size = 20;

	enabled = true;
}


Player2::~Player2()
{
}



void Player2::update()
{
	if (sfw::getKey('I'))
	{
		y += 2;
	}
	if (sfw::getKey('K'))
	{
		y -= 2;
	}
	if (sfw::getKey('J'))
	{
		x -= 2;
	}
	if (sfw::getKey('L'))
	{
		x += 2;
	}


	if (y + size < 0)
	{
		y = 600 + size;
	}
	else if (y - size > 600)
	{
		y = size - size;
	}

	if (x + size < 0)
	{
		x = 800 + size;
	}
	else if (x - size > 800)
	{
		x = size - size;
	}
}

void Player2::draw()
{
	if (enabled)
	{
		//sfw::drawCircle(x, y, size);
		Box::draw(x, y, size, size);
	}
}
