#pragma once
#include "GameObject.h"


class BaseParticle :
	public GameObject
{
public:
	BaseParticle();
	~BaseParticle();

	float x;
	float y;

	float velx;
	float vely;

	float timeLeft;

	virtual void update() override;
	virtual void draw() override;

protected:
	float lastTime;
};

