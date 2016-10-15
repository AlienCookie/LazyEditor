#pragma once
#include "Poligon.h"
#include <vector>

using namespace std;

enum transform { Move, Rotate, Scale, Color };
enum direction { axeX, axeY, axeZ };
enum modelType { CubeType, PiramidType };

class Model
{
protected:
	static transform mode;
	static direction axe;

	vector<Poligon> shape;
	vector<vec> vertices;
	vector<vec> poligons;
	vector<vec> overLine;

	vec position;
	vec color;
	vec colorID;
	vec angle;
	vec scale;
	vec box[6];

	unsigned id;
	bool selected;
	
public:
	static unsigned counter;
	Model() {};
	vector<Poligon> triangulation(vector<int> vert);
	Model(vector<vec> _vertices, vector<vec> _shape);
	vector<vec> getPoligons();
	vector<Poligon> getShape();
	vector<vec> getVertices();
	Model(vec _position, double r);
	virtual ~Model() {};

	void setSelected(bool isSelected);

	unsigned getId();

	void draw();
	void drawSelected();

	void setBox();
	void setAxe(direction _axe);
	void setScale(vec _scale);
	void setAngle(vec _angle);
	void setColor(vec _color);
	void setOverline(vector<vec> _overLine);
	void setPosition(vec _position);

	vec getScale();
	vec getColor();
	unsigned getID();
	vec getColorID();
	vec getAngle();
	vec getPosition();
	vec* getBox();
	direction getAxe();

	void drawLevers();
	void swapColors();
};

class Cube : public Model
{
public:
	Cube(vec _position, double r);
	~Cube ();

};

class Piramid : public Model
{
public:
	Piramid(vec _position, double r);
	~Piramid();
};