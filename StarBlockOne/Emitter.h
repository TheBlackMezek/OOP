#pragma once
#include "GameObject.h"

#include <vector>

#include "BaseParticle.h"



class Emitter :
	public GameObject
{
public:
	Emitter();
	~Emitter();

	float x;
	float y;

	std::vector<BaseParticle>* ptcs;

	float interval;
	float amt;

	int lifemax;
	int lifemin;

	int velxmax;
	int velxmin;
	int velymax;
	int velymin;

	virtual void update() override;

protected:
	float spawnTimer;
};

