#pragma once



//From https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331


class AABB
{
public:
	AABB();
	~AABB();

	float minx;
	float miny;

	float maxx;
	float maxy;



	static bool AABBvsAABB(AABB a, AABB b);

};

