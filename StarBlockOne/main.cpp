

#include "sfwdraw.h"


#include "Player.h"
#include "Map.h"
#include "Cursor.h"




int main()
{
	sfw::initContext(800, 600, "Hello world!");

	sfw::setBackgroundColor(BLACK);



	Cursor cursor;

	Player player;
	player.x = 10;
	player.y = 200;


	Map map(800 / 10, 600 / 10);
	map.addTile(0, 0);
	map.addTile(1, 0);
	map.addTile(2, 0);
	map.addTile(3, 0);
	map.addTile(4, 0);
	map.addTile(0, 1);
	map.addTile(2, 2);




	while (sfw::stepContext())
	{

		if (sfw::getMouseButton(1))
		{
			map.delTile(((int)sfw::getMouseX() + 5) / 10, ((int)sfw::getMouseY() + 5) / 10);
		}
		if (sfw::getMouseButton(0))
		{
			map.addTile(((int)sfw::getMouseX() + 5) / 10, ((int)sfw::getMouseY() + 5) / 10);
		}




		player.draw();
		map.draw();

		cursor.draw();
	}




	sfw::termContext();

	return 0;
}