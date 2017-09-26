#pragma once
class Player
{
public:
	Player();
	~Player();

	float x;
	float y;

	int size;

	bool enabled;

	void update();

	void draw();

};

