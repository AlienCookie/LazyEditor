#pragma once
#include "arcball.h"
#include <GL/freeglut.h>


class Poligon
{
protected:
	vec* coord[3];
	vec normal;
	vec color;
public:
	Poligon() {
		coord[0] = &vec(0.0, 0.0, 1.0);
		coord[1] = &vec(1.0, 0.0, 0.0);
		coord[2] = &vec(1.0, 1.0, 0.0);
	};
	Poligon(vec* _coord[3]);
	~Poligon();

	void setColor(vec _color);
	void setCoord(vec* _coord[3]);

	vec getColor();
	vec getNorm();
	vec** getCoord();

	void draw();
};

