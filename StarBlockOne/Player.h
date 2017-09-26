#pragma once


#include "GameObject.h"


class Player : public GameObject
{
public:
	Player();
	~Player();

	float x;
	float y;

	virtual void update() override;
	virtual void draw() override;
};

