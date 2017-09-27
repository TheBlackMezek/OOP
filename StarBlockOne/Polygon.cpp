#include "Polygon.h"

#include "Line.h"



Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}



void Polygon::draw()
{
	for (int i = 0; i < xs.size() - 1; ++i)
	{
		Line::draw(xs[i], ys[i], xs[i + 1], ys[i + 1]);
	}

	Line::draw(xs[xs.size() - 1], ys[xs.size() - 1], xs[0], ys[0]);
}
