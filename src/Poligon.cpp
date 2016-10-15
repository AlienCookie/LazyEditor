#include "stdafx.h"
#include "Poligon.h"

vec findNormal(vec* _coor[3])
{
	vec a = vec(_coor[1]->x - _coor[0]->x, _coor[1]->y - _coor[0]->y, _coor[1]->z - _coor[0]->z);
	vec b = vec(_coor[2]->x - _coor[0]->x, _coor[2]->y - _coor[0]->y, _coor[2]->z - _coor[0]->z);

	return vec(
		a.y * b.z - b.y * a.z,
		a.z * b.x - a.x * b.z,
		a.x * b.y - b.x * a.y
		);
}

Poligon::Poligon(vec* _coord[3])
{
	this->coord[0] = _coord[0];
	this->coord[1] = _coord[1];
	this->coord[2] = _coord[2];

	this->normal = findNormal(_coord);
}


Poligon::~Poligon()
{
}

void Poligon::setColor(vec _color)
{
	this->color = _color;
}

void Poligon::setCoord(vec* _coord[3])
{
	this->coord[0] = _coord[0];
	this->coord[1] = _coord[1];
	this->coord[2] = _coord[2];
}

vec Poligon::getColor()
{
	return this->color;
}

vec Poligon::getNorm()
{
	return this->normal;
}

vec** Poligon::getCoord()
{
	return this->coord;
}

void Poligon::draw()
{
	glBegin(GL_TRIANGLES);
	//glColor3d(color.x, color.y, color.z);
	glNormal3f(normal.x, normal.y, normal.z);
	glVertex3d(coord[0]->x, coord[0]->y, coord[0]->z);
	glVertex3d(coord[1]->x, coord[1]->y, coord[1]->z);
	glVertex3d(coord[2]->x, coord[2]->y, coord[2]->z);
	glEnd();
}
