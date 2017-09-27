#pragma once
#include "GameObject.h"

#include <vector>



class Polygon :
	public GameObject
{
public:
	Polygon();
	~Polygon();

	virtual void draw() override;


	std::vector<float> xs;
	std::vector<float> ys;

};

