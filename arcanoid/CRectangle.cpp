#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "CRectangle.h"

void CRectangle::draw()
{
	std::vector<int> color = getColor();
	std::vector<float> position = getPosition();
	std::vector<float> size = getSize();

	int posX = position[0];
	int posY = position[1];

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