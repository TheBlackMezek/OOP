#include "RigidBody.h"



RigidBody::RigidBody()
{
	grounded = false;

	x = 0;
	y = 0;

	velx = 0;
	vely = 0;

	width = 10;
	height = 10;
}


RigidBody::~RigidBody()
{
}




void RigidBody::update()
{
	x += velx;
	y += vely;
}
