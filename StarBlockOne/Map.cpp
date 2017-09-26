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

	for (int y = r.y - r.height / 2; y <= r.y + r.height / 2 && !hasHit; y += 10)
	{
		for (int x = r.x - r.width / 2; x <= r.x + r.width / 2 && !hasHit; x += 10)
		{
			if ((x / 10) >= 0 && (x / 10) < width &&
				(y / 10) >= 0 && (y / 10) < height &&
				tiles[(x / 10) + (y / 10) * width] == 1)
			{
				hasHit = true;

				if (r.y - r.height / 2 < y + 5 &&
					r.y - r.height / 2 > y - 5)
				{
					r.y = y + 5 + (r.height / 2);
				}

				r.velx = 0;
				r.vely = 0;
			}
		}
	}

	return hasHit;
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
