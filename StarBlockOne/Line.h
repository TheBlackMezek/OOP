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
};

