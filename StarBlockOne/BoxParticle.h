#pragma once
#include "BaseParticle.h"
class BoxParticle :
	public BaseParticle
{
public:
	BoxParticle();
	~BoxParticle();

	virtual void draw() override;
};

