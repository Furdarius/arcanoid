#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <string>
#include "CCircle.h"
#include "CVector2D.h"
#include "GameInstance.h"

void CCircle::draw()
{
	checkCollision();
	std::vector<int> color = getColor();
	std::vector<float> position = getPosition();
	float radius = getRadius();

	int posX = position[0];
	int posY = position[1];

	glColor3f(color[0], color[1], color[2]);

	double _tmpPoint;
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(posX, posY);
		for( int i = 0; i <= radius + 1; i++ ) 
		{
			_tmpPoint = (float)i / radius * 3.1415f * 2.0f;
			glVertex2f(posX + cos(_tmpPoint) * radius, 
				posY + sin(_tmpPoint) * radius);
		}
    glEnd();
}

void CCircle::setRadius(float radius)
{
	fRadius = radius;
}

float CCircle::getRadius()
{
	return fRadius;
}

void CCircle::checkCollision()
{
	float radius = getRadius();

	if ((this->iPosX + radius) > CGameHudInstance->fWindowWidth)
	{
		this->iPosX = CGameHudInstance->fWindowWidth - radius;
		this->velocity.reflect(CVector2D<float>(-1.0f, 0.0f));
		this->velocity *= 0.8f;
	}
	else if ((this->iPosX - radius) < 0)
	{
		this->iPosX = radius;
		this->velocity.reflect(CVector2D<float>(1.0f, 0.0f));
		this->velocity *= 0.8f;
	}

	if ((this->iPosY + radius) > CGameHudInstance->fWindowHeigth)
	{
		this->iPosY = CGameHudInstance->fWindowHeigth - radius;
		this->velocity.reflect(CVector2D<float>(0.0f, -1.0f));
		this->velocity *= 0.8f;
	}
	else if ((this->iPosY - radius) < 0)
	{
		this->iPosY = radius;
		this->velocity.reflect(CVector2D<float>(0.0f, 1.0f));
		this->velocity *= 0.8f;
		//this->velocity.x *= 0.9999f; // friction
	}

	std::vector<float> batBottomPos = CGameHudInstance->batBottom->getPosition();
	std::vector<float> batBottomSize = CGameHudInstance->batBottom->getSize();

	if ((this->iPosY + radius) > batBottomPos[1]
		&& (this->iPosX + radius) > batBottomPos[0]
		&& (this->iPosY + radius) < batBottomPos[1] + batBottomSize[1]
		&& (this->iPosX - radius) < batBottomPos[0] + batBottomSize[0])
	{
		this->iPosY = batBottomPos[1] - radius;
		this->velocity.reflect(CVector2D<float>(0.0f, -1.0f));
		this->velocity *= 0.8f;
	}
}
