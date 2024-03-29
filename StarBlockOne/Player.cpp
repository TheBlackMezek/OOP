#include "Player.h"


#include "sfwdraw.h"

#include "Box.h"



Player::Player()
{
	body.height = 16;
	body.width = 8;

	walkForce = 0;
}


Player::~Player()
{
}



void Player::update()
{
	if (enabled)
	{
		/*if (walkForce)
		{
			body.velx -= walkForce;
		}*/

		//walkForce = 0;
		if (walkForce < 0)
		{
			walkForce += 0.1;
			if (walkForce > 0)
			{
				walkForce = 0;
			}
		}
		else if (walkForce > 0)
		{
			walkForce -= 0.1;
			if (walkForce < 0)
			{
				walkForce = 0;
			}
		}



		bool walking = false;

		if (sfw::getKey('W') && body.grounded)
		{
			//body.y += 2;
			body.grounded = false;
			body.vely = 2.6;
		}
		if (sfw::getKey('S'))
		{
			//body.y -= 2;
		}
		if (sfw::getKey('A') && body.grounded)
		{
			//body.x -= 2;
			body.velx = -2;
			walking = true;
			//walkForce += -0.2;
		}
		if (sfw::getKey('D') && body.grounded)
		{
			//body.x += 2;
			body.velx = 2;
			walking = true;
			//walkForce += 0.2;
		}

		if (!walking && body.grounded)
		{
			body.velx *= 0.1;
		}


		if (body.y + body.height < 0)
		{
			body.y = 600 + body.height;
		}
		else if (body.y - body.height > 600)
		{
			body.y = body.height - body.height;
		}

		if (body.x + body.width < 0)
		{
			body.x = 800 + body.width;
		}
		else if (body.x - body.width > 800)
		{
			body.x = body.width - body.width;
		}


		if (!body.grounded)
		{
			body.vely -= 0.1;
		}
		//body.velx += walkForce;
		//body.vely -= 0.1;
		//body.velx += 0.1;

		//body.y += body.vely;
		//body.x += body.velx;
	}
}

void Player::draw()
{
	if (enabled)
	{
		Box::draw(body.x, body.y, body.width, body.height);
	}
}

