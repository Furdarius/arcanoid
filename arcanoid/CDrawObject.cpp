#include "CDrawObject.h"
#include "GameInstance.h"
#include <iostream>

CDrawObject::CDrawObject(float x, float y, int r, int g, int b, int a)
{
	setPosition(x, y);
	setColor(r, g, b, a);
	setVelocity(0.0, 0.0);
	setGravity(0.0, 0.0);
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
	iPosX = x;
	iPosY = y;
}

std::vector<float> CDrawObject::getPosition()
{
	std::vector<float> position(2, 0.0);
	position[0] = iPosX;
	position[1] = iPosY;
	return position;
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
	std::vector<float> pos = getPosition();
	pos[0] += dt * (float)velocity.x;
	pos[1] += dt * (float)velocity.y;
	setPosition(pos[0], pos[1]);
}

void CDrawObject::Render(float dt)
{
	RecountPosition(dt);
	draw();
}