#include "Player.h"

#include "sfwdraw.h"



Player::Player()
{
	x = 10;
	y = 10;

	size = 20;

	enabled = true;
}


Player::~Player()
{
}



void Player::update()
{
	if (sfw::getKey('W'))
	{
		y += 2;
	}
	if (sfw::getKey('S'))
	{
		y -= 2;
	}
	if (sfw::getKey('A'))
	{
		x -= 2;
	}
	if (sfw::getKey('D'))
	{
		x += 2;
	}

	if (sfw::getMouseButton(0))
	{
		x = sfw::getMouseX();
		y = sfw::getMouseY();
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

void Player::draw()
{
	if (enabled)
	{
		sfw::drawCircle(x, y, size);
	}
}
