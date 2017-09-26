#pragma once


#include <vector>

#include "GameObject.h"
#include "RigidBody.h"


class Map : public GameObject
{
public:
	Map(int w, int h);
	~Map();

	int width;
	int height;

	virtual void update() override;
	virtual void draw() override;

	bool collide(RigidBody& r);

	void addTile(int x, int y);
	void delTile(int x, int y);

private:
	std::vector<int> tiles;
};
