#include "Emitter.h"

#include "sfwdraw.h"


Emitter::Emitter()
{
	ptcs = nullptr;

	spawnTimer = 0;

	interval = 1;
	amt = 5;

	lifemax = 3;
	lifemin = 1;

	velxmax = 5;
	velxmin = -5;
	velymax = 5;
	velymin = -5;
}


Emitter::~Emitter()
{
}



void Emitter::update()
{
	spawnTimer += sfw::getDeltaTime();

	if (spawnTimer >= interval)
	{
		for (int i = 0; i < amt; ++i)
		{
			BaseParticle p;
			p.timeLeft = rand() % (lifemax - lifemin) + lifemin;
			p.x = x;
			p.y = y;
			p.velx = rand() % (velxmax - velxmin) + velxmin;
			p.vely = rand() % (velymax - velymin) + velymin;
			ptcs->push_back(p);
		}

		spawnTimer -= interval;
	}
}
