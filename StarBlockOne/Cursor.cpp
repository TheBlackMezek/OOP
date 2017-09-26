#include "Cursor.h"


#include "sfwdraw.h"



Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}



void Cursor::update()
{

}

void Cursor::draw()
{
	sfw::drawCircle(sfw::getMouseX(), sfw::getMouseY(), 1);
}
