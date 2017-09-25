#include "PiggyBank.h"



PiggyBank::PiggyBank()
{
}


PiggyBank::~PiggyBank()
{
}

void PiggyBank::deposit(float m)
{
	money += m;
}
float PiggyBank::empty()
{
	float ret = money;
	money = 0;
	return ret;
}

const float PiggyBank::balance()
{
	return money;
}
