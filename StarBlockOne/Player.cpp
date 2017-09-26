#include "Player.h"


#include "Box.h"



Player::Player()
{
	body.height = 16;
	body.width = 8;
}


Player::~Player()
{
}



void Player::update()
{
	if (enabled)
	{
		body.vely -= 0.1;

		body.y += body.vely;
		body.x += body.velx;
	}
}

void Player::draw()
{
	if (enabled)
	{
		Box::draw(body.x, body.y, body.width, body.height);
	}
}

