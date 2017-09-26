#include "Map.h"

#include "Box.h"



Map::Map(int w, int h)
{
	tiles.resize(w * h);

	width = w;
	height = h;

	for (int i = 0; i < w * h; ++i)
	{
		tiles[i] = 0;
	}
}


Map::~Map()
{
}



void Map::update()
{
	if (enabled)
	{

	}
}

void Map::draw()
{
	if (enabled)
	{
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				if (tiles[x + y * width] == 1)
				{
					Box::draw((x * 10), (y * 10), 8, 8);
				}
			}
		}
	}
}





void Map::addTile(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		tiles[x + y * width] = 1;
	}
}

void Map::delTile(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		tiles[x + y * width] = 0;
	}
}
