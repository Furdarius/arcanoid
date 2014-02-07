#pragma once

#include "CDrawObject.h"

class CCircle : public CDrawObject
{
	int iWidth;
	int iHeight;
	float fRadius;

	public:
		CCircle(
            int x = 0, 
			int y = 0,
			float radius = 5,
			int r = 1, 
			int g = 1, 
			int b = 1, 
			int a = 1
        ) : CDrawObject(
            x,
            y,
            r,
			g,
			b,
			a
        ) { };

		void draw();

		void setRadius(float radius);
		float getRadius();

		void checkCollision();
};