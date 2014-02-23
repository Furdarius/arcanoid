#pragma once

#include "CDrawObject.h"

class CRectangle : public CDrawObject
{
	int iWidth;
	int iHeight;

	public:
		CRectangle(
            int x = 0, 
			int y = 0, 
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

		void setSize(float width, float height);
		std::vector<float> getSize();

		void checkCollision();
};