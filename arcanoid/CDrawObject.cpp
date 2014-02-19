#include "CDrawObject.h"
#include "GameInstance.h"

#include <iostream>

CDrawObject::CDrawObject(float x, float y, int r, int g, int b, int a)
{
	setPosition(x, y);
	setColor(r, g, b, a);
	setVelocity(0.0, 0.0);
	setGravity(0.0, 0.0);
	setVisible(true);
}

void CDrawObject::setColor(int r, int g, int b, int a)
{
	iColorR = r;
	iColorG = g;
	iColorB = b;
	iColorA = a;
}

std::vector<int> CDrawObject::getColor()
{
	std::vector<int> color(4, 0);
	color[0] = iColorR;
	color[1] = iColorG;
	color[2] = iColorB;
	color[3] = iColorA;
	return color;
}

void CDrawObject::setPosition(float x, float y)
{
	this->position.setup(x, y);
}

void CDrawObject::setPosition(CPoint2D<float> source)
{
	this->position = source;
}

CPoint2D<float> CDrawObject::getPosition()
{
	return this->position;
}

void CDrawObject::setVisible(bool state)
{
	this->bVisible = state;
}

bool CDrawObject::getVisible()
{
	return this->bVisible;
}

void CDrawObject::setGravity(float x, float y)
{
	gravity.setup(x, y);
}

CVector2D<float> CDrawObject::getGravity()
{
	return gravity;
}

void CDrawObject::setVelocity(float x, float y)
{
	velocity.setup(x, y);
}

CVector2D<float> CDrawObject::getVelocity()
{
	return velocity;
}

void CDrawObject::RecountPosition(float dt)
{
	velocity += gravity * dt;
	float maxvel = 5;
	velocity.x = std::min(velocity.x, maxvel);
	velocity.y = std::min(velocity.y, maxvel);
	CPoint2D<float> pos = getPosition();
	pos.x += dt * (float)velocity.x;
	pos.y += dt * (float)velocity.y;
	setPosition(pos);
}

void CDrawObject::Render(float dt)
{
	RecountPosition(dt);
	draw();
}