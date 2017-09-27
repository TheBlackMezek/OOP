#pragma once
class Line
{
public:
	Line();
	~Line();

	float startx;
	float starty;

	float endx;
	float endy;

	bool enabled;

	void draw();
	static void draw(float x1, float y1, float x2, float y2);
};

