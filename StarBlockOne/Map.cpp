#include "Map.h"

#include <cmath>

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

	for (int y = r.y - r.height + 5; y > 0 && y <= r.y + r.height; y += 10)
	{
		int tiley = y / 10;
		for (int x = r.x - r.width + 5; x > 0 && x <= r.x + r.width; x += 10)
		{
			int tilex = x / 10;

			if (tilex >= 0 && tilex < width &&
				tiley >= 0 && tiley < height &&
				tiles[tilex + tiley * width] == 1)
			{
				hasHit = true;

				int dirxmod = 1;
				int dirymod = 1;

				float xdepth = 0;
				float ydepth = 0;

				if (r.x - r.width < tilex * 10 + 5 &&
					r.x - r.width > tilex * 10 - 5)
				{
					xdepth = (tilex * 10 + 5) - (r.x - r.width);
					dirxmod = -1;
				}
				else if (r.x + r.width < tilex * 10 + 5 &&
						 r.x + r.width > tilex * 10 - 5)
				{
					xdepth = (tilex * 10 - 5) - (r.x + r.width);
				}

				if (r.y - r.height < tiley * 10 + 5 &&
					r.y - r.height > tiley * 10 - 5)
				{
					ydepth = (tiley * 10 + 5) - (r.y - r.height);
					dirymod = -1;
				}
				else if (r.y + r.height < tiley * 10 + 5 &&
						 r.y + r.height > tiley * 10 - 5)
				{
					ydepth = (tiley * 10 - 5) - (r.y + r.height);
				}


				float xtimeout = (r.velx == 0) ? 0 : xdepth / abs(r.velx);
				float ytimeout = (r.vely == 0) ? 0 : ydepth / abs(r.vely);

				//float xtimeout = xdepth / abs(r.velx);
				//float ytimeout = ydepth / abs(r.vely);


				if (xtimeout < ytimeout)
				{
					r.x += xdepth * dirxmod;
					r.y += r.vely * (r.velx / xdepth) * dirymod;
				}
				else if (xtimeout > ytimeout)
				{
					r.y += ydepth * dirymod;
					r.x += r.velx * (r.vely / ydepth) * dirxmod;
				}
				



				/*if (r.y - r.height < tiley * 10 + 5 &&
					r.y - r.height > tiley * 10 - 5)
				{
					r.y = tiley * 10 + 5 + (r.height);
				}*/

				/*if (r.x - r.width < tilex * 10 + 5 &&
					r.x - r.width > tilex * 10 - 5)
				{
					r.x = tilex * 10 + 5 + (r.width / 2);
				}

				if (r.x + r.width > tilex * 10 + 5 &&
					r.x + r.width < tilex * 10 - 5)
				{
					r.x = tilex * 10 - 5 - (r.width);
				}*/

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
