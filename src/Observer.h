#pragma once
#include "arcball.h"
#include <GL/freeglut.h>
#include "Model.h"

class Observer
{
private:
	vec position;
	vec viewPoint; 
	vec viewAngle;

	float angleX, angleY;
public:
	Observer() {};
	Observer(vec _observerPosition);
	~Observer();

	void setPosition(vec _position);
	void setViewPoint(vec _position);
	void setViewAngle(vec _angle);

	vec getPosition();
	vec geViewPoint();
	vec getViewAngle();

	void applyRotate(POINT mouseShift);
	void applyShift(POINT mouseShift);
	void changeDistance(float shift);

	void moving(POINT mouseShift, Model* selected);
	void freeMoving(POINT mouseShift, Model * selected);
	void scaling(POINT mouseShift, Model* selected);
	void colorChange(POINT mouseShift, Model * selected);
	void rotating(POINT mouseShift, Model * selected);
	void show();
};

