#pragma once

#include "CDrawObject.h"


class CRectangle : public CDrawObject
{
	int iWidth;
	int iHeight;

	public:
		CRectangle(
            int x, 
			int y, 
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

		void setSize(int width, int height);
		std::vector<int> getSize();
};