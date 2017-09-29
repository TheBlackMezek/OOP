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


	float rbot = r.y;
	float rtop = r.y + r.height - 1;
	float rlef = r.x;
	float rrgt = r.x + r.width - 1;



	int tbot = floor((rbot + 1) / 10) * 10;
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
	}




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
