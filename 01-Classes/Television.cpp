#include "Television.h"



Television::Television()
{
}


Television::~Television()
{
}


void Television::incVolume()
{
	++volume;
	if (volume > 100)
	{
		volume = 100;
	}
}
void Television::decVolume()
{
	--volume;
	if (volume < 0)
	{
		volume = 0;
	}
}

void Television::incChannel()
{
	++channel;
	if (channel > 100)
	{
		channel = 100;
	}
}
void Television::decChannel()
{
	--channel;
	if (channel < 0)
	{
		channel = 0;
	}
}
