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







RaycastReturn Map::raycastCollide(float x, float y, float velx, float vely)
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

	//Raycast from bottom left (origin) corner
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

	bool hit = false;
	int side;



	if (rayDirX < 0)
	{
		stepX = -1;
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

	if (mapX >= 0 &&
		mapX < width &&
		mapY >= 0 &&
		mapY < height &&
		tiles[mapX + mapY * width] > 0)
	{
		hit = true;
	}

	float prevDist = 0;

	while (!hit && totalDist <= maxDist)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
			//if (sideDistX > totalDist)
			//{
				prevDist = totalDist;
				totalDist = sideDistX;
			//}
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
			//if (sideDistY > totalDist)
			//{
				prevDist = totalDist;
				totalDist = sideDistY;
			//}
		}

		if (mapX >= 0 &&
			mapX < width &&
			mapY >= 0 &&
			mapY < height &&
			tiles[mapX + mapY * width] > 0)
		{
			hit = true;
			totalDist = prevDist;
		}
	}

	sfw::drawLine(	x * 10,
					y * 10,
					(x * 10) + (unitX * totalDist * 10),
					(y * 10) + (unitY * totalDist * 10), RED);
	if (hit && totalDist * 10 <= velMag)
	{
		//return totalDist;
		return RaycastReturn{ totalDist, side };
	}
	else
	{
		//return -1;
		return RaycastReturn{ -1, side };
	}
}

bool Map::collide(RigidBody& r)
{
	bool hasHit = false;
	int hitSide = -1;


	float velMag = sqrt((r.velx * r.velx) + (r.vely * r.vely));

	float unitX = r.velx / velMag;
	float unitY = r.vely / velMag;

	
	RaycastReturn botLefRay = raycastCollide(r.x,				r.y,				r.velx, r.vely);
	RaycastReturn botRgtRay = raycastCollide(r.x + r.width - 1,	r.y,				r.velx, r.vely);
	RaycastReturn topLefRay = raycastCollide(r.x,				r.y + r.height - 1, r.velx, r.vely);
	RaycastReturn topRgtRay = raycastCollide(r.x + r.width - 1,	r.y + r.height - 1, r.velx, r.vely);

	float botLefDist = botLefRay.dist;
	float botRgtDist = botRgtRay.dist;
	float topLefDist = topLefRay.dist;
	float topRgtDist = topRgtRay.dist;



	if (botLefDist != -1 &&
		(botLefDist <= topRgtDist || topRgtDist == -1) &&
		(botLefDist <= topLefDist || topLefDist == -1) &&
		(botLefDist <= botRgtDist || botRgtDist == -1))
	{
		r.x += botLefDist * 10 * unitX;
		r.y += botLefDist * 10 * unitY;

		//r.velx = 0;
		//r.vely = 0;
		hasHit = true;
		hitSide = botLefRay.side;
	}
	else if (botRgtDist != -1 &&
		(botRgtDist <= topRgtDist || topRgtDist == -1) &&
		(botRgtDist <= topLefDist || topLefDist == -1) &&
		(botRgtDist <= botLefDist || botLefDist == -1))
	{
		r.x -= botRgtDist * 10 * unitX;
		r.y += botRgtDist * 10 * unitY;

		//r.velx = 0;
		//r.vely = 0;
		hasHit = true;
		hitSide = botRgtRay.side;
	}
	else if (topLefDist != -1 &&
		(topLefDist <= topRgtDist || topRgtDist == -1) &&
		(topLefDist <= botRgtDist || botRgtDist == -1) &&
		(topLefDist <= botLefDist || botLefDist == -1))
	{
		r.x += topLefDist * 10 * unitX;
		r.y -= topLefDist * 10 * unitY;

		//r.velx = 0;
		//r.vely = 0;
		hasHit = true;
		hitSide = topLefRay.side;
	}
	else if (topRgtDist != -1 &&
		(topRgtDist <= botRgtDist || botRgtDist == -1) &&
		(topRgtDist <= topLefDist || topLefDist == -1) &&
		(topRgtDist <= botLefDist || botLefDist == -1))
	{
		r.x -= topRgtDist * 10 * unitX;
		r.y -= topRgtDist * 10 * unitY;

		//r.velx = 0;
		//r.vely = 0;
		hasHit = true;
		hitSide = topRgtRay.side;
	}
	

	if (hitSide == 0)
	{
		float velStart = r.vely;

		if (r.vely * r.velx > 0)
		{
			r.vely -= r.velx;
		}
		else if (r.vely * r.velx < 0)
		{
			r.vely += r.velx;
		}

		if (r.vely * velStart < 0)
		{
			r.vely = 0;
		}
		else if ((r.vely < 0 && r.vely > -0.1) || (r.vely > 0 && r.vely < 0.1))
		{
			r.vely = 0;
		}

		r.velx = 0;
	}
	else if (hitSide == 1)
	{
		float velStart = r.velx;

		if (r.vely * r.velx > 0)
		{
			r.velx -= r.vely;
		}
		else if (r.vely * r.velx < 0)
		{
			r.velx += r.vely;
		}


		if (r.velx * velStart < 0)
		{
			r.velx = 0;
		}
		else if ((r.velx < 0 && r.velx > -0.1) || (r.velx > 0 && r.velx < 0.1))
		{
			r.velx = 0;
		}

		if (r.vely < 0)
		{
			r.grounded = true;
		}

		r.vely = 0;
	}




	if (r.grounded)
	{
		sfw::drawCircle(0, 0, 10);
		botLefRay = raycastCollide(r.x, r.y, 0, -0.1);
		botRgtRay = raycastCollide(r.x + r.width - 1, r.y, 0, -0.1);

		if ((botLefRay.dist == -1 || botLefRay.dist > 0.1) &&
			(botRgtRay.dist == -1 || botRgtRay.dist > 0.1))
		{
			r.grounded = false;
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
