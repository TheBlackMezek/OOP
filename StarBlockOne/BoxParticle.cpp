#include "BoxParticle.h"

#include "Box.h"



BoxParticle::BoxParticle()
{
}


BoxParticle::~BoxParticle()
{
}



void BoxParticle::draw()
{
	Box::draw(x, y, 2, 2);
}
