#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "CRectangle.h"
#include "ClientInstance.h"

void CRectangle::draw()
{
	this->checkCollision();
	std::vector<int> color = getColor();
	CPoint2D<float> position = getPosition();
	std::vector<float> size = getSize();

	int posX = position.x;
	int posY = position.y;

	int sizeW = size[0];
	int sizeH = size[1];

	glColor3f(color[0],color[1],color[2]);

	glBegin(GL_POLYGON);
        glVertex2f(posX, posY); // top - left
        glVertex2f(posX + sizeW, posY); // top - right
        glVertex2f(posX + sizeW, posY + sizeH); // bottom - right
		glVertex2f(posX, posY + sizeH); // bottom - left
	glEnd();
}

void CRectangle::setSize(float w, float h)
{
	iWidth = w;
	iHeight = h;
}

std::vector<float> CRectangle::getSize()
{
	std::vector<float> size(2, 0);
	size[0] = iWidth;
	size[1] = iHeight;
	return size;
}

void CRectangle::checkCollision()
{
	if ((this->position.x + this->iWidth) > CClientInstance->getGameHudInstance()->fWindowWidth)
		this->position.x = CClientInstance->getGameHudInstance()->fWindowWidth - this->iWidth;
	else if (this->position.x < 0)
		this->position.x = 0;
}