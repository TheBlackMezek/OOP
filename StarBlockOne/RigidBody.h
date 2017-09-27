#pragma once


#include "AABB.h"


class RigidBody
{
public:
	RigidBody();
	~RigidBody();

	bool grounded;

	float x;
	float y;

	float velx;
	float vely;

	float width;
	float height;

	AABB aabb;


	void update();
};

