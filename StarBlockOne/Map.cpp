#include "Map.h"

#include <cmath>

#include "sfwdraw.h"

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
					Box::draw((x * 10), (y * 10), 10 - 1, 10 - 1);
				}
			}
		}
	}
}







float Map::raycastCollide(float x, float y, float velx, float vely)
{

	float velMag = sqrt((velx * velx) + (vely * vely));

	float unitX = velx / velMag;
	float unitY = vely / velMag;

	//All further numbers in map grid coords
	y /= 10;
	x /= 10;


	//Raycasting from http://lodev.org/cgtutor/raycasting.html

	float rayDirY = vely / 10;
	float rayDirX = velx / 10;

	//Raycast from bottom left (origin) corner, if it works I'll do the rest with a function
	int mapX = int(x);
	int mapY = int(y);

	float sideDistX;
	float sideDistY;

	float deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
	float deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
	float perpWallDist; //perp for perpendicular

						//float maxDist = velMag / 10.0f;
	float maxDist = 800;
	float totalDist = 0;

	int stepX;
	int stepY;

	int collisionModX = 0;
	int collisionModY = 0;

	bool hit = false;
	int side;



	if (rayDirX < 0)
	{
		stepX = -1;
		collisionModX = 0;
		sideDistX = (x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1 - x) * deltaDistX;
	}

	if (rayDirY < 0)
	{
		stepY = -1;
		collisionModY = 0;
		sideDistY = (y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1 - y) * deltaDistY;
	}


	if (sideDistX < sideDistY)
	{
		totalDist = sideDistX;
		side = 0;
	}
	else
	{
		totalDist = sideDistY;
		side = 1;
	}

	if (mapX >= 0 && mapX < width && mapY >= 0 && mapY < height && tiles[mapX + mapY * width] > 0)
	{
		hit = true;
	}

	float prevDist = 0;

	while (!hit && totalDist <= maxDist)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			//lastAdded = deltaDistX;
			prevDist = totalDist;
			totalDist = sideDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			//lastAdded = deltaDistY;
			prevDist = totalDist;
			totalDist = sideDistY;
			mapY += stepY;
			side = 1;
		}

		if (mapX + collisionModX >= 0 &&
			mapX + collisionModX < width &&
			mapY + collisionModY >= 0 &&
			mapY + collisionModY < height &&
			tiles[(mapX + collisionModX) + (mapY + collisionModY) * width] > 0)
		{
			hit = true;
			totalDist = prevDist;
			//totalDist -= lastAdded;
		}
	}


	if (hit && totalDist * 10 <= velMag)
	{
		return totalDist;
	}
	else
	{
		return -1;
	}
}

bool Map::collide(RigidBody& r)
{
	bool hasHit = false;


	float velMag = sqrt((r.velx * r.velx) + (r.vely * r.vely));

	float unitX = r.velx / velMag;
	float unitY = r.vely / velMag;

	
	float botLefDist = raycastCollide(r.x,					r.y,				r.velx, r.vely);
	float botRgtDist = raycastCollide(r.x + r.width - 1,	r.y,				r.velx, r.vely);
	float topLefDist = raycastCollide(r.x,					r.y + r.height - 1, r.velx, r.vely);
	float topRgtDist = raycastCollide(r.x + r.width - 1,	r.y + r.height - 1, r.velx, r.vely);



	if (botLefDist != -1 &&
		(botLefDist <= topRgtDist || topRgtDist == -1) &&
		(botLefDist <= topLefDist || topLefDist == -1) &&
		(botLefDist <= botRgtDist || botRgtDist == -1))
	{
		r.x += botLefDist * 10 * unitX;
		r.y += botLefDist * 10 * unitY;

		r.velx = 0;
		r.vely = 0;
	}
	else if (botRgtDist != -1 &&
		(botRgtDist <= topRgtDist || topRgtDist == -1) &&
		(botRgtDist <= topLefDist || topLefDist == -1) &&
		(botRgtDist <= botLefDist || botLefDist == -1))
	{
		r.x += botRgtDist * 10 * unitX;
		r.y += botRgtDist * 10 * unitY;

		r.velx = 0;
		r.vely = 0;
	}
	else if (topLefDist != -1 &&
		(topLefDist <= topRgtDist || topRgtDist == -1) &&
		(topLefDist <= botRgtDist || botRgtDist == -1) &&
		(topLefDist <= botLefDist || botLefDist == -1))
	{
		r.x += topLefDist * 10 * unitX;
		r.y += topLefDist * 10 * unitY;

		r.velx = 0;
		r.vely = 0;
	}
	else if (topRgtDist != -1 &&
		(topRgtDist <= botRgtDist || botRgtDist == -1) &&
		(topRgtDist <= topLefDist || topLefDist == -1) &&
		(topRgtDist <= botLefDist || botLefDist == -1))
	{
		r.x += topRgtDist * 10 * unitX;
		r.y += topRgtDist * 10 * unitY;

		r.velx = 0;
		r.vely = 0;
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
