#pragma once
class GameObject
{
public:
	GameObject();
	~GameObject();

	bool enabled;

	virtual void update();
	virtual void draw();
};

