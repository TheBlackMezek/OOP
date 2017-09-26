#pragma once
class Box
{
public:
	Box();
	~Box();

	float width;
	float height;

	float x;
	float y;

	bool enabled;

	void draw();

	static void draw(float x, float y, float width, float height);
};

