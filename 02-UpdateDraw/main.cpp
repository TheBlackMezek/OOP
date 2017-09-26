
#include <iostream>
//#include <math.h>

#include "sfwdraw.h"


#include "Player.h"
#include "Player2.h"
#include "SpaceObj.h"



struct vec2
{
	float x;
	float y;
};



float G = 0.1f;


float dist(float n1, float n2);
float dist(float x1, float y1, float x2, float y2);
float gravForce(float mass1, float mass2, float axisDist);
float mag(vec2 v);
void unit(vec2& v);



int main()
{
	sfw::initContext(800, 600, "Hello world!");

	sfw::setBackgroundColor(BLACK);

	float posy = 1;
	float posx = 1;

	float radians = 0;



	Player1 player;
	Player2 player2;

	const size_t spaceobjects = 3;
	SpaceObj objects[spaceobjects];

	objects[0].x = 400;
	objects[0].y = 300;
	objects[0].mass = 50;
	objects[0].size = 10;

	objects[1].x = 200;
	objects[1].y = 301;
	objects[1].vely = -0.5;
	objects[1].mass = 10;
	objects[1].size = 2;

	objects[2].x = 215;
	objects[2].y = 301;
	objects[2].vely = -0.9;
	objects[2].mass = 1;
	objects[2].size = 1;



	while (sfw::stepContext())
	{
		/*posy = sin(radians) * 100 + 300;
		posx = cos(radians) * 100 + 300;

		sfw::drawCircle(posx, posy, 100);

		radians += 0.01f;*/



		/*objects[1].velx += (0 < distx) - (distx < 0) * gravForce(objects[1].mass, objects[0].mass,
			dist(objects[1].x, objects[0].x));*/

		for (int i = 0; i < spaceobjects; ++i)
		{

			for (int q = 0; q < spaceobjects; ++q)
			{
				if (i != q)
				{

					vec2 distvec{ objects[q].x - objects[i].x, objects[q].y - objects[i].y };
					unit(distvec);


					float prevx = objects[i].x;
					float prevy = objects[i].y;

					float newdist = dist(	objects[i].x, objects[i].y,
											objects[q].x, objects[q].y);

					float grav = gravForce(objects[i].mass, objects[q].mass, newdist);


					objects[i].velx += grav * distvec.x;

					objects[i].x += objects[i].velx;

					newdist = dist(objects[i].x, objects[i].y,
						objects[q].x, objects[q].y);
					
					if (newdist < objects[i].size + objects[q].size)
					{
						objects[i].x = prevx;
						objects[i].velx = 0;
					}


					objects[i].vely += grav * distvec.y;

					objects[i].y += objects[i].vely;

					newdist = dist(objects[i].x, objects[i].y,
						objects[q].x, objects[q].y);

					if (newdist < objects[i].size + objects[q].size)
					{
						objects[i].y = prevy;
						objects[i].vely = 0;
					}



					/*float prevy = objects[i].y;

					float disty = objects[q].y - objects[i].y;

					objects[i].vely += ((0 < disty) - (disty < 0)) *
						gravForce(objects[i].mass, objects[q].mass,
						dist(objects[i].y, objects[q].y));

					objects[i].y += objects[i].vely;
					
					newdist = dist(objects[i].x, objects[i].y, objects[q].x, objects[q].y);

					if (newdist < objects[i].size + objects[q].size)
					{
						objects[i].y = prevy;
					}*/
				}
			}

			//objects[i].update();
		}

		for (int i = 0; i < spaceobjects; ++i)
		{
			objects[i].draw();
		}




		player.update();
		player2.update();

		player.draw();
		player2.draw();

		//posy += posyinc;

		/*if (posy == topy)
		{
			posyinc = -1;
		}
		else if (posy == 0)
		{
			posyinc = 1;
		}*/
	}

	sfw::termContext();

	return 0;
}





float dist(float n1, float n2)
{
	return sqrt(pow(n1 - n2, 2));
}

float dist(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

float gravForce(float mass1, float mass2, float axisDist)
{
	return G * ((mass2 * mass2) / (axisDist * axisDist));
}

float mag(vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

void unit(vec2& v)
{
	float l = mag(v);
	v.x /= l;
	v.y /= l;
}
