#include "Player.h"


#include "Box.h"



Player::Player()
{
	x = 0;
	y = 0;
}


Player::~Player()
{
}



void Player::update()
{
	if (enabled)
	{

	}
}

void Player::draw()
{
	if (enabled)
	{
		Box::draw(x, y, 10, 10);
	}
}

