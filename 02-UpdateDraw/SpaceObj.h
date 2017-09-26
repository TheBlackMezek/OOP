#pragma once
class SpaceObj
{
public:
	SpaceObj();
	~SpaceObj();

	float x;
	float y;

	float velx;
	float vely;

	float mass;

	int size;



	void update();

	void draw();

};

