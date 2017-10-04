#pragma once


#include <vector>

#include "GameObject.h"
#include "RigidBody.h"






struct RaycastReturn
{
	float dist;
	int side;
};



class Map : public GameObject
{
public:
	Map(int w, int h);
	~Map();

	int width;
	int height;

	virtual void update() override;
	virtual void draw() override;

	RaycastReturn raycastCollide(float x, float y, float velx, float vely);
	bool collide(RigidBody& r);

	bool addTile(int x, int y);
	bool delTile(int x, int y);

private:
	std::vector<int> tiles;
};
