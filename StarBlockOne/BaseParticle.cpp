#include "BaseParticle.h"

#include "sfwdraw.h"



BaseParticle::BaseParticle()
{
	x = 0;
	y = 0;

	velx = 0;
	vely = 0;

	timeLeft = 10;
}


BaseParticle::~BaseParticle()
{
}


void BaseParticle::update()
{
	if (enabled)
	{
		timeLeft -= sfw::getDeltaTime();

		x += velx;
		y += vely;
	}
}

void BaseParticle::draw()
{
	if (enabled)
	{
		sfw::drawCircle(x, y, 1);
	}
}
