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





bool Map::collide(RigidBody& r)
{
	bool hasHit = false;

	for (int y = r.y - r.height; y <= r.y + r.height; y += 10)
	{
		int tiley = y / 10;
		for (int x = r.x - r.width; x <= r.x + r.width; x += 10)
		{
			int tilex = x / 10;

			if (tilex >= 0 && tilex < width &&
				tiley >= 0 && tiley < height &&
				tiles[tilex + tiley * width] == 1)
			{
				hasHit = true;

				if (r.y - r.height / 2 < tiley * 10 + 5 &&
					r.y - r.height / 2 > tiley * 10 - 5)
				{
					r.y = tiley * 10 + 5 + (r.height / 2);
				}

				r.velx = 0;
				r.vely = 0;
			}
		}
	}

	return hasHit;
}


bool Map::addTile(int x, int y)
{
	bool ret = false;
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		if (tiles[x + y * width] == 0)
		{
			ret = true;
		}
		tiles[x + y * width] = 1;
	}
	return ret;
}

bool Map::delTile(int x, int y)
{
	bool ret = false;
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		if (tiles[x + y * width] == 1)
		{
			ret = true;
		}
		tiles[x + y * width] = 0;
	}
	return ret;
}
