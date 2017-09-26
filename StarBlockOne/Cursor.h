#pragma once
#include "GameObject.h"
class Cursor :
	public GameObject
{
public:
	Cursor();
	~Cursor();

	virtual void update() override;
	virtual void draw() override;
};

