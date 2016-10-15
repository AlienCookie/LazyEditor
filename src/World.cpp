#include "stdafx.h"
#include "World.h"


World::World(float _size)
{
	this->size = _size;
}


World::~World()
{
}

void World::draw()
{
	bool color = 0;
	glTranslated(-size / 2, 0.0, -size / 2);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			color ? glColor4f(1.0, 1.0, 1.0, 0.1) : glColor4f(0.5, 0.5, 0.5, 0.1);

			glBegin(GL_QUADS);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(1.0, 0.0, 0.0);
			glVertex3d(1.0, 0.0, 1.0);
			glVertex3d(0.0, 0.0, 1.0);
			glEnd();

			glTranslated(1.0, 0.0, 0.0);

			color = !color;
		}
		color = !color;
		glTranslated(-this->size, 0.0, 1.0);
	}
	glEnable(GL_LIGHTING);
	glTranslated(size / 2, 0.0, -size / 2);
}

