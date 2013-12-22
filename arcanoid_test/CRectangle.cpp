#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "CRectangle.h"

void CRectangle::draw()
{
	std::vector<int> color = getColor();
	std::vector<int> position = getPosition();
	std::vector<int> size = getSize();

	glColor3f(color[0],color[1],color[2]);

	int posX = position[0];
	int posY = position[1];

	int sizeW = size[0];
	int sizeH = size[1];

	glBegin(GL_POLYGON);
        glVertex2f(posX, posY); // bottom - left
        glVertex2f(posX + sizeW, posY); // bottom - right
        glVertex2f(posX + sizeW, posY + sizeH); // top - right
        glVertex2f(posX, posY + sizeH); // top - left
	glEnd();
}

void CRectangle::setSize(int w, int h)
{
	iWidth = w;
	iHeight = h;
}

std::vector<int> CRectangle::getSize()
{
	std::vector<int> size(2, 0);
	size[0] = iWidth;
	size[1] = iHeight;
	return size;
}