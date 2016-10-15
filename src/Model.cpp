#include "stdafx.h"
#include "Model.h"
#define PI 3.141592


unsigned Model::counter = 0;
transform Model::mode = Move;
direction Model::axe = axeX;

vector<Poligon> Model::triangulation(vector<int> vert)
{
	vector<Poligon> facet(vert.size() - 2);
	for (int i = 1; i < vert.size() - 1; i++)
	{
		vec *coord[3] = { &vertices[vert[0]], &vertices[vert[i]] , &vertices[vert[i + 1]]};
		poligons.push_back(vec(vert[0], vert[i], vert[i + 1]));
		facet[i-1] = Poligon(coord);
	}
	return facet;
}

Model::Model(vector<vec> _vertices, vector<vec> _shape)
{
	this->id = counter;
	counter++;
	selected = 0;
	this->position = _vertices[0];
	this->scale = _vertices[1];
	this->color = _vertices[2];
	this->angle = _vertices[3];
	//this->vertices.resize(_vertices.size() - 4);
	for (int i = 4; i < _vertices.size(); i++)
		this->vertices.push_back(_vertices[i]);

	this->shape.resize(_shape.size());
	for (int i = 0; i < this->shape.size(); i++)
	{
		unsigned c = size_t(_shape[i].x);
		vec a = vertices[c];
		vec *coord[3] = { &vertices[_shape[i].x], &vertices[_shape[i].y], &vertices[_shape[i].z] };
		shape[i] = Poligon(coord);
	}

	setBox();

	unsigned RGB = id;

	colorID.x = (RGB % 255) / 255.0;
	RGB = (RGB - colorID.x) / 255.0;
	colorID.y = (RGB % 255) / 255.0;
	RGB = (RGB - colorID.y) / 255.0;
	colorID.z = (RGB % 255) / 255.0;

	for (int i = 0; i < shape.size(); i++)
		shape[i].setColor(color);
}

vector<vec> Model::getPoligons()
{
	return this->poligons;
}

vector<Poligon> Model::getShape()
{
	return this->shape;
}

vector<vec> Model::getVertices()
{
	return this->vertices;
}

Model::Model(vec _position, double r)
{
	this->position = _position;
	this->id = counter;
	counter++;
	selected = 0;
	this->scale = vec(1.0, 1.0, 1.0);
	this->angle = vec(0.0, 0.0, 0.0);
	this->color = vec(0.6, 0.6, 0.6);
}

void Model::draw()
{
	glTranslated(position.x + box[3].x, position.y + box[1].y, position.z + box[1].z);

	glRotated(angle.x, 1.0, 0.0, 0.0);
	glRotated(angle.y, 0.0, 1.0, 0.0);
	glRotated(angle.z, 0.0, 0.0, 1.0);
	glScaled(scale.x, scale.y, scale.z);

	glColor3f(color.x, color.y, color.z);

	glTranslated(-box[3].x,-box[1].y, -box[1].z);

	for (int i = 0; i < shape.size(); i++)
	{
		shape[i].draw();
	}
	if (selected)
	{
		drawSelected();
		drawLevers();
	}

	glTranslated(box[3].x, box[1].y, box[1].z);

	glScaled(1/scale.x, 1/scale.y, 1/scale.z);

	glRotated(-angle.z, 0.0, 0.0, 1.0);
	glRotated(-angle.y, 0.0, 1.0, 0.0);
	glRotated(-angle.x, 1.0, 0.0, 0.0);
	glTranslated(-position.x - box[3].x, -position.y - box[1].y, -position.z - box[1].z);
}

void Model::drawSelected()
{
	if (vertices.size())
	{
		glDisable(GL_LIGHTING);
		glColor3f(0.0, 0.0, 1.0);
		glLineWidth(5.0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < vertices.size(); i++)
			glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
		glEnd();
		glEnable(GL_LIGHTING);
	}
}

void Model::setBox()
{
	for (int i = 0; i < 6; i++)
		box[i] = vertices[0];
	for (int i = 1; i < vertices.size(); i++)
	{
		if(vertices[i].x < box[0].x)
			box[0].x = vertices[i].x;
		if (vertices[i].x > box[1].x)
			box[1].x = vertices[i].x;

		if (vertices[i].y < box[2].y)
			box[2].y = vertices[i].y;
		if (vertices[i].y > box[3].y)
			box[3].y = vertices[i].y;

		if (vertices[i].z < box[4].z)
			box[4].z = vertices[i].z;
		if (vertices[i].z > box[5].z)
			box[5].z = vertices[i].z;
	}

	box[2].x = box[3].x = box[4].x = box[5].x = (box[0].x + box[1].x) / 2.0;
	box[0].y = box[1].y = box[4].y = box[5].y = (box[2].y + box[3].y) / 2.0;
	box[0].z = box[1].z = box[2].z = box[3].z = (box[4].z + box[5].z) / 2.0;
}

void Model::setAxe(direction _axe)
{
	axe = _axe;
}

void Model::setScale(vec _scale)
{
	this->scale = _scale;
}

void Model::setAngle(vec _angle)
{
	this->angle = _angle;
}

void Model::setColor(vec _color)
{
	this->color = _color;
}

void Model::setOverline(vector<vec> _overLine)
{
	this->overLine = _overLine;
}

void Model::setPosition(vec _position)
{
	this->position = _position;
}

vec Model::getScale()
{
	return this->scale;
}

vec Model::getColor()
{
	return this->color;
}

unsigned Model::getID()
{
	return this->id;
}

vec Model::getColorID()
{
	return this->colorID;
}

vec Model::getAngle()
{
	return this->angle;
}

vec Model::getPosition()
{
	return this->position;
}

vec * Model::getBox()
{
	return box;
}

direction Model::getAxe()
{
	return axe;
}

void Model::drawLevers()
{
	double sX = 0.2 / scale.x;
	double bX = 0.6 / scale.x;

	double sY = 0.2 / scale.y;
	double bY = 0.6 / scale.y;

	double sZ = 0.2 / scale.z;
	double bZ = 0.6 / scale.z;

#pragma region drawing
	glDisable(GL_LIGHTING);
	glBegin(GL_TRIANGLES);

	glColor3f(0.0, 1.0, 0.0);

		glVertex3d(box[0].x - sX, box[0].y, box[0].z + sZ);
		glVertex3d(box[0].x - bX, box[0].y, box[0].z);
		glVertex3d(box[0].x - sX, box[0].y, box[0].z - sZ);

		glVertex3d(box[1].x + sX, box[1].y, box[1].z + sZ);
		glVertex3d(box[1].x + bX, box[1].y, box[1].z);
		glVertex3d(box[1].x + sX, box[1].y, box[1].z - sZ);

		glVertex3d(box[0].x - sX, box[0].y + sY, box[0].z);
		glVertex3d(box[0].x - bX, box[0].y, box[0].z);
		glVertex3d(box[0].x - sX, box[0].y - sY, box[0].z);

		glVertex3d(box[1].x + sX, box[1].y + sY, box[1].z);
		glVertex3d(box[1].x + bX, box[1].y, box[1].z);
		glVertex3d(box[1].x + sX, box[1].y - sY, box[1].z);

		glColor3f(0.0, 254.0/255.0, 0.0);

		glVertex3d(box[2].x, box[2].y - sY, box[2].z + sZ);
		glVertex3d(box[2].x, box[2].y - bY, box[2].z);
		glVertex3d(box[2].x, box[2].y - sY, box[2].z - sZ);

		glVertex3d(box[3].x, box[3].y + sY, box[3].z + sZ);
		glVertex3d(box[3].x, box[3].y + bY, box[3].z);
		glVertex3d(box[3].x, box[3].y + sY, box[3].z - sZ);

		glVertex3d(box[2].x + sX, box[2].y - sY, box[2].z);
		glVertex3d(box[2].x, box[2].y - bY, box[2].z);
		glVertex3d(box[2].x - sX, box[2].y - sY, box[2].z);

		glVertex3d(box[3].x + sX, box[3].y + sY, box[3].z);
		glVertex3d(box[3].x, box[3].y + bY, box[3].z);
		glVertex3d(box[3].x - sX, box[3].y + sY, box[3].z);

		glColor3f(0.0, 253.0 / 255.0, 0.0);

		glVertex3d(box[4].x + sX, box[4].y, box[4].z - sZ);
		glVertex3d(box[4].x, box[4].y, box[4].z - bZ);
		glVertex3d(box[4].x - sX, box[4].y, box[4].z - sZ);

		glVertex3d(box[5].x + sX, box[5].y, box[5].z + sZ);
		glVertex3d(box[5].x, box[5].y, box[5].z  + bZ);
		glVertex3d(box[5].x - sX, box[5].y, box[5].z + sZ);

		glVertex3d(box[4].x, box[4].y + sY, box[4].z - sZ);
		glVertex3d(box[4].x, box[4].y, box[4].z - bZ);
		glVertex3d(box[4].x, box[4].y - sY, box[4].z - sZ);

		glVertex3d(box[5].x, box[5].y + sY, box[5].z + sZ);
		glVertex3d(box[5].x, box[5].y, box[5].z + bZ);
		glVertex3d(box[5].x, box[5].y - sY, box[5].z + sZ);

	glEnd();
	glEnable(GL_LIGHTING);

#pragma endregion

}

void Model::swapColors()
{
	vec temp = this->color;
	this->color = this->colorID;
	this->colorID = temp;
}


void Model::setSelected(bool isSelected)
{
	this->selected = isSelected;
}

unsigned Model::getId()
{
	return this->id;
}


Cube::Cube(vec _position, double r) : Model(_position, r)
{
	// adding vertices
	vertices.insert(vertices.begin(),
		{
			vec(0, 0, 0), vec(r, 0, 0), vec(0, 0, r), vec(r, 0, r),
			vec(0, r, 0), vec(r, r, 0), vec(0, r, r), vec(r, r, r)
		}
	);

	vector <Poligon> facet;
	facet = triangulation({ 0, 1, 3, 2});
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({ 4, 5, 1, 0 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({ 0, 2, 6, 4});
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({ 6, 7, 5, 4 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({ 2, 3, 7, 6 });
	shape.insert(shape.end(), facet.begin(), facet.end());
	
	facet = triangulation({ 5, 7, 3, 1 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	setBox();

	unsigned RGB = id;

	colorID.x = (RGB % 255) / 255.0;
	RGB = (RGB - colorID.x) / 255.0;
	colorID.y = (RGB % 255) / 255.0;
	RGB = (RGB - colorID.y) / 255.0;
	colorID.z = (RGB % 255) / 255.0;

	for (int i = 0; i < shape.size(); i++)
		shape[i].setColor(colorID);
}

Cube::~Cube()
{

}



Piramid::Piramid(vec _position, double r) : Model(_position, r)
{

	// adding vertices
	vertices.insert(vertices.begin(),
	{
		vec(0, 0, 0), vec(r, 0, 0), vec(r*cos(PI / 3), 0, r*sin(PI / 3)),
		vec(r*cos(PI/6)/2, r*sin(PI / 3), r*cos(PI / 6)/2)
	}
	);

	vector <Poligon> facet;
	facet = triangulation({0, 1, 2 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({ 3, 1, 0 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({ 0, 2, 3 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	facet = triangulation({3, 2, 1 });
	shape.insert(shape.end(), facet.begin(), facet.end());

	setBox();

	unsigned RGB = id;

	colorID.x = (RGB % 255) / 255.0;
	RGB = (RGB - colorID.x) / 255.0;
	colorID.y = (RGB % 255) / 255.0;
	RGB = (RGB - colorID.y) / 255.0;
	colorID.z = (RGB % 255) / 255.0;

	for (int i = 0; i < shape.size(); i++)
		shape[i].setColor(color);
}

Piramid::~Piramid()
{
}