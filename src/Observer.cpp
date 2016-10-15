#include "stdafx.h"
#include "Observer.h"

#define PI 3.141592

Observer::Observer(vec _observerPosition)
{
	setPosition(_observerPosition);
	setViewPoint(vec(0.0, 0.0, 0.0));
	setViewAngle(vec(0.0, 1.0, 0.0));
	angleY  = asin(position.y  / position.length()) * 180 / PI ;
	angleX  = -asin(position.x / cos(angleY / 180 * PI) / position .length()) * 180 / PI;
	
}


Observer::~Observer()
{
}


void Observer::setPosition(vec _position)
{
	this->position = _position;
}

void Observer::setViewPoint(vec _position)
{
	this->viewPoint = _position;
}

void Observer::setViewAngle(vec _angle)
{
	this->viewAngle = _angle;
}


vec Observer::getPosition()
{
	return this->position;
}

vec Observer::geViewPoint()
{
	return this->viewPoint;
}

vec Observer::getViewAngle()
{
	return this->viewAngle;
}


void Observer::applyRotate(POINT mouseShift)
{
	angleX += mouseShift.x;
	angleY += mouseShift.y;

	//Y limit
	if (angleY<-89.999) angleY = -89.999;
	if (angleY>89.999) angleY = 89.999;

	double radius = (position - viewPoint).length(); //distance to the object we are looking at

	position.x = sin(-angleX / 180 * PI) * cos(angleY / 180 * PI) * radius + viewPoint.x;
	position.y = sin(angleY / 180 * PI) * radius + viewPoint.y;
	position.z = cos(-angleX / 180 * PI) * cos(angleY / 180 * PI) * radius + viewPoint.z;
}

void Observer::applyShift(POINT mouseShift)
{
	double lenght = (position - viewPoint).length();
	
	position.x -= (cos(angleX / 180 * PI) *  mouseShift.x - sin(angleX / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI)*lenght/300;
	viewPoint.x -= (cos(angleX / 180 * PI) *  mouseShift.x - sin(angleX / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI)*lenght/300;
	position.y += cos(angleY / 180 * PI) * mouseShift.y/400*lenght;
	viewPoint.y += cos(angleY / 180 * PI) * mouseShift.y/400*lenght;
	position.z -= (cos((angleX - 90) / 180 * PI) *  mouseShift.x - sin((angleX - 90) / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) * lenght/300;
	viewPoint.z -= (cos((angleX - 90) / 180 * PI) *  mouseShift.x - sin((angleX - 90) / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) * lenght/300;
}

void Observer::changeDistance(float shift) 
{
	double radius = (position - viewPoint).length(); //distance to the object we are looking at

	position.x = sin(-angleX / 180 * PI) * cos(angleY / 180 * PI) * (radius-shift) + viewPoint.x;
	position.y = sin(angleY / 180 * PI) * (radius - shift) + viewPoint.y;
	position.z = cos(-angleX / 180 * PI) * cos(angleY / 180 * PI) * (radius - shift) + viewPoint.z;
}


void Observer::moving(POINT mouseShift, Model* selected)
{
	vec objectPosition = selected->getPosition();

	double lenght = (position - viewPoint).length();

	switch (selected->getAxe())
	{
	case axeX:
		objectPosition.x += (cos(angleX / 180 * PI) *  mouseShift.x - sin(angleX / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) /400 * lenght;
		break;
	case axeY:
		objectPosition.y -= cos(angleY / 180 * PI) * mouseShift.y / 1000 * lenght;
		break;
	case axeZ:
		objectPosition.z += (cos((angleX - 90) / 180 * PI) *  mouseShift.x - sin((angleX - 90) / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) / 400 * lenght;
		break;
	}
	selected->setPosition(objectPosition);
}

void Observer::freeMoving(POINT mouseShift, Model* selected)
{
	vec objectPosition = selected->getPosition();

	double lenght = (position - viewPoint).length();

	objectPosition.x += (cos(angleX / 180 * PI) *  mouseShift.x - sin(angleX / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) /600 * lenght;
	objectPosition.y -= cos(angleY / 180 * PI) * mouseShift.y / 800 * lenght;
	objectPosition.z += (cos((angleX - 90) / 180 * PI) *  mouseShift.x - sin((angleX - 90) / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) /600 * lenght;

	selected->setPosition(objectPosition);
}

void Observer::scaling(POINT mouseShift, Model* selected)
{
	vec objectScale = selected->getScale();
	switch (selected->getAxe())
	{
	case axeX:
		objectScale.x += (cos(angleX / 180 * PI) *  mouseShift.x - sin(angleX / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) / 100;
		break;
	case axeY:
		objectScale.y -= cos(angleY / 180 * PI) * mouseShift.y / 400;
		break;
	case axeZ:
		objectScale.z += (cos((angleX - 90) / 180 * PI) *  mouseShift.x - sin((angleX - 90) / 180 * PI) *  mouseShift.y)* sin(angleY / 180 * PI) / 100;
		break;
	}
	selected->setScale(objectScale);
}

void Observer::colorChange(POINT mouseShift, Model* selected)
{
	vec objectColor = selected->getColor();
	switch (selected->getAxe())
	{
	case axeX:
		objectColor.x -= mouseShift.x / 1000.0;
		if (objectColor.x > 1.0) objectColor.x = 1.0;
		break;
	case axeY:
		objectColor.y -= mouseShift.y / 1000.0;
		if (objectColor.y > 1.0) objectColor.y = 1.0;
		break;
	case axeZ:
		objectColor.z -= mouseShift.x / 1000.0;
		if (objectColor.z > 1.0) objectColor.z = 1.0;
		break;
	}
	selected->setColor(objectColor);
}

void Observer::rotating(POINT mouseShift, Model* selected)
{
	vec objectAngle = selected->getAngle();

	switch (selected->getAxe())
	{
	case axeX:
		objectAngle.y -= mouseShift.x;
		break;
	case axeY:
		objectAngle.x -= mouseShift.y;
		break;
	case axeZ:
		objectAngle.z -= mouseShift.x;
		break;
	}
	selected->setAngle(objectAngle);
}


void Observer::show()
{
	gluLookAt(
		position.x, position.y, position.z,
		viewPoint.x, viewPoint.y, viewPoint.z,
		viewAngle.x, viewAngle.y, viewAngle.z);
}
