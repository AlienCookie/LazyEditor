#pragma once
#include <GL/freeglut.h>

class World
{
private:
	float size;
public:
	World() {};
	World(float _size);
	~World();

	void draw();
};

