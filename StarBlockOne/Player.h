#pragma once


#include "GameObject.h"
#include "RigidBody.h"


class Player : public GameObject
{
public:
	Player();
	~Player();

	RigidBody body;

	virtual void update() override;
	virtual void draw() override;
};

