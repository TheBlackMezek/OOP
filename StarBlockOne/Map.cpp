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







bool Map::collide(RigidBody& r)
{
	bool hasHit = false;

	float velMag = sqrt((r.velx * r.velx) + (r.vely * r.vely));

	float unitX = r.velx / velMag;
	float unitY = r.vely / velMag;

	//All further numbers in map grid coords
	float rbot = r.y / 10;
	float rtop = (r.y + r.height - 1) / 10;
	float rlef = r.x / 10;
	float rrgt = (r.x + r.width - 1) / 10;


	//Raycasting from http://lodev.org/cgtutor/raycasting.html

	float rayDirY = r.vely / 10;
	float rayDirX = r.velx / 10;

	//Raycast from bottom left (origin) corner, if it works I'll do the rest with a function
	int mapX = int(rlef);
	int mapY = int(rbot);

	float sideDistX;
	float sideDistY;

	float deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
	float deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
	float perpWallDist; //perp for perpendicular

	float maxDist = velMag / 10.0f;
	float totalDist = 0;

	int stepX;
	int stepY;

	bool hit = false;
	int side;



	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (rlef - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - rlef) * deltaDistX;
	}

	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (rbot - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1 - rbot) * deltaDistY;
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



	while (!hit && totalDist <= maxDist)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			totalDist = sideDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			totalDist = sideDistY;
			mapY += stepY;
			side = 1;
		}

		if (mapX >= 0 && mapX < width && mapY >= 0 && mapY < height && tiles[mapX + mapY * width] > 0)
		{
			hit = true;
		}
	}


	if (hit)
	{
		r.x += totalDist * 10 * unitX;
		r.y += totalDist * 10 * unitY;

		r.velx = 0;
		r.vely = 0;
	}






	if (side == 0)
	{
		perpWallDist = (mapX - rlef + (1 - stepX) / 2) / rayDirX;
	}
	else
	{
		perpWallDist = (mapY - rbot + (1 - stepY) / 2) / rayDirY;
	}





	/*int tbot = floor((rbot + 1) / 10) * 10;
	int tbotGround = floor(rbot / 10) * 10;
	int ttop = floor(rtop / 10) * 10;
	int tlef = floor((rlef + 1) / 10) * 10;
	int trgt = floor(rrgt / 10) * 10;

	//int tbotGround = ((int)rbot / 10) * 10;



	if (tbotGround >= 0 && tbotGround < height * 10)
	{
		for (int x = tlef; x <= trgt; x += 10)
		{
			//sfw::drawCircle(x+5, tbot+5, 5);
			if (x >= 0 && x < width * 10 &&
				tiles[(x / 10) + (tbotGround / 10) * width] == 1)
			{
				r.y = tbotGround + 10;
				r.vely = 0;

				float rbot = r.y;
				float rtop = r.y + r.height - 1;

				int tbot = floor((rbot + 1) / 10) * 10;
				int ttop = floor(rtop / 10) * 10;

				break;
			}
		}
	}

	if (trgt >= 0 && trgt < width * 10)
	{
		for (int y = tbot; y <= ttop; y += 10)
		{
			sfw::drawCircle(trgt +5, y+5, 5);
			if (y >= 0 && y < height * 10 &&
				tiles[(trgt / 10) + (y / 10) * width] == 1)
			{
				r.x = trgt - 9;
				r.velx = 0;
				break;
			}
		}
	}*/




	//r.grounded = false;
	
	//for (int y = r.y - r.height + 5; y > 0 && y <= r.y + r.height + 9; y += 10)
	//{
	//	int tiley = y / 10;
	//	for (int x = r.x - r.width + 5; x > 0 && x <= r.x + r.width + 9; x += 10)
	//	{
	//		int tilex = x / 10;
	//
	//		sfw::drawCircle(tilex * 10, tiley * 10, 5);
	//		Box::draw(r.x, r.y, r.width * 2, r.height * 2);
	//
	//		if (tilex >= 0 && tilex < width &&
	//			tiley >= 0 && tiley < height &&
	//			tiles[tilex + tiley * width] == 1)
	//		{
	//			if (!hasHit)
	//			{
	//				//r.vely = 0;
	//			}
	//
	//
	//			hasHit = true;
	//
	//			int dirxmod = 1;
	//			int dirymod = 1;
	//
	//			float xdepth = 0;
	//			float ydepth = 0;
	//
	//			if (r.x - r.width < tilex * 10 + 5 &&
	//				r.x - r.width > tilex * 10 - 5)
	//			{
	//				xdepth = (tilex * 10 + 5) - (r.x - r.width);
	//				dirxmod = -1;
	//			}
	//			else if (r.x + r.width < tilex * 10 + 5 &&
	//					 r.x + r.width > tilex * 10 - 5)
	//			{
	//				xdepth = (tilex * 10 - 5) - (r.x + r.width);
	//			}
	//
	//			if (r.y - r.height < tiley * 10 + 5 &&
	//				r.y - r.height > tiley * 10 - 5)
	//			{
	//				ydepth = (tiley * 10 + 5) - (r.y - r.height);
	//				dirymod = -1;
	//				if (r.vely < 0)
	//				{
	//					r.grounded = true;
	//				}
	//			}
	//			else if (r.y + r.height < tiley * 10 + 5 &&
	//					 r.y + r.height > tiley * 10 - 5)
	//			{
	//				ydepth = (tiley * 10 - 5) - (r.y + r.height);
	//				if (r.vely < 0)
	//				{
	//					r.grounded = true;
	//				}
	//			}
	//
	//
	//			float xtimeout = (r.velx == 0) ? 0 : xdepth / abs(r.velx);
	//			float ytimeout = (r.vely == 0) ? 0 : ydepth / abs(r.vely);
	//
	//			//float xtimeout = xdepth / abs(r.velx);
	//			//float ytimeout = ydepth / abs(r.vely);
	//
	//
	//			if (xtimeout < ytimeout)
	//			{
	//				r.velx += xdepth * dirxmod;
	//				r.vely += r.vely * (r.velx / xdepth) * dirymod;
	//				//r.x += xdepth * dirxmod;
	//				//r.y += r.vely * (r.velx / xdepth) * dirymod;
	//			}
	//			else if (xtimeout > ytimeout)
	//			{
	//				r.vely += ydepth * dirymod;
	//				r.velx += r.velx * (r.vely / ydepth) * dirxmod;
	//				//r.y += ydepth * dirymod;
	//				//r.x += r.velx * (r.vely / ydepth) * dirxmod;
	//			}
	//
	//			
	//
	//
	//
	//			/*if (r.y - r.height < tiley * 10 + 5 &&
	//				r.y - r.height > tiley * 10 - 5)
	//			{
	//				r.y = tiley * 10 + 5 + (r.height);
	//			}*/
	//
	//			/*if (r.x - r.width < tilex * 10 + 5 &&
	//				r.x - r.width > tilex * 10 - 5)
	//			{
	//				r.x = tilex * 10 + 5 + (r.width / 2);
	//			}
	//
	//			if (r.x + r.width > tilex * 10 + 5 &&
	//				r.x + r.width < tilex * 10 - 5)
	//			{
	//				r.x = tilex * 10 - 5 - (r.width);
	//			}*/
	//		}
	//	}
	//}
	//
	//if (hasHit)
	//{
	//	r.x += r.velx;
	//	r.y += r.vely;
	//
	//	r.velx = 0;
	//	r.vely = 0;
	//}

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
