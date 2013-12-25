#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "CCircle.h"

void CCircle::draw()
{
	std::vector<int> color = getColor();
	std::vector<int> position = getPosition();
	float radius = getRadius();

	int posX = position[0];
	int posY = position[1];

	glColor3f(color[0], color[1], color[2]);

	double _tmpPoint;
    glBegin(GL_TRIANGLE_FAN);
		glVertex2f(posX, posY);
		for( int i = 0; i <= radius; i++ ) 
		{
			_tmpPoint = (float)i / radius * 3.1415f * 2.0f;
			glVertex2f(posX + cos(_tmpPoint) * (radius / 10), 
				posY + sin(_tmpPoint) * (radius / 10));
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