

#include <vector>
#include <time.h>

#include "sfwdraw.h"


#include "Player.h"
#include "Map.h"
#include "Cursor.h"
//#include "BaseParticle.h"
#include "BoxParticle.h"
#include "Emitter.h"




int main()
{
	srand(time(NULL));



	sfw::initContext(800, 600, "StarBlock One");

	sfw::setBackgroundColor(BLACK);



	Cursor cursor;

	std::vector<BaseParticle> ptcs;

	Player player;
	player.body.x = 10;
	player.body.y = 200;


	Map map(800 / 10, 600 / 10);
	map.addTile(0, 0);
	map.addTile(1, 0);
	map.addTile(2, 0);
	map.addTile(3, 0);
	map.addTile(4, 0);
	map.addTile(0, 1);
	map.addTile(2, 2);

	Emitter emitter;
	emitter.ptcs = &ptcs;
	emitter.x = 400;
	emitter.y = 300;




	while (sfw::stepContext())
	{
		emitter.update();

		for (int i = ptcs.size() - 1; i >= 0; --i)
		{
			if (ptcs[i].timeLeft <= 0)
			{
				ptcs.erase(ptcs.begin() + i);
			}
			else
			{
				ptcs[i].update();
			}
		}

		if (sfw::getMouseButton(1))
		{
			if (map.delTile(((int)sfw::getMouseX() + 5) / 10, ((int)sfw::getMouseY() + 5) / 10))
			{
				for (int i = 0; i < 5; ++i)
				{
					BaseParticle p;
					p.timeLeft = (float)(rand() % 15 - 10) / 10.0f;
					p.x = ((int)sfw::getMouseX() + 5) / 10 * 10;
					p.y = ((int)sfw::getMouseY() + 5) / 10 * 10;
					p.velx = (float)(rand() % 200 - 100) / 100.0f;
					p.vely = (float)(rand() % 200 - 100) / 100.0f;
					ptcs.push_back(p);
				}
			}
		}
		if (sfw::getMouseButton(0))
		{
			map.addTile(((int)sfw::getMouseX() + 5) / 10, ((int)sfw::getMouseY() + 5) / 10);
		}


		player.update();
		map.collide(player.body);



		for (int i = 0; i < ptcs.size(); ++i)
		{
			ptcs[i].draw();
		}

		player.draw();
		map.draw();

		cursor.draw();
	}




	sfw::termContext();

	return 0;
}