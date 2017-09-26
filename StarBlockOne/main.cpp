

#include "sfwdraw.h"


#include "Player.h"




int main()
{
	sfw::initContext(800, 600, "Hello world!");

	sfw::setBackgroundColor(BLACK);



	Player player;
	player.x = 100;
	player.y = 100;




	while (sfw::stepContext())
	{
		player.draw();
	}




	sfw::termContext();

	return 0;
}