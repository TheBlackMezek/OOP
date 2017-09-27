#include "AABB.h"



AABB::AABB()
{
}


AABB::~AABB()
{
}



bool AABB::AABBvsAABB(AABB a, AABB b)
{
	if (a.maxx < b.minx || a.minx > b.maxx) { return false; }
	if (a.maxy < b.miny || a.miny > b.maxy) { return false; }

	return true;
}
