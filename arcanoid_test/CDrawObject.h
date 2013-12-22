#pragma once

#include <vector>

class CDrawObject
{
	int iPosX;
	int iPosY;

	int iColorR;
	int iColorG;
	int iColorB;
	int iColorA;

	public:
		CDrawObject(int x, int y, int r = 1, int g = 1, int b = 1, int a = 1)
		{
			setPosition(x, y);
			setColor(r, g, b, a);
		}

		virtual ~CDrawObject() { };

		virtual void draw() { };

		void setColor(int r, int g, int b, int a = 1)
		{
			iColorR = r;
			iColorG = g;
			iColorB = b;
			iColorA = a;
		}

		std::vector<int> getColor()
		{
			std::vector<int> color(4, 0);
			color[0] = iColorR;
			color[1] = iColorG;
			color[2] = iColorB;
			color[3] = iColorA;
			return color;
		}

		void setPosition(int x, int y)
		{
			iPosX = x;
			iPosY = y;
		}

		std::vector<int> getPosition()
		{
			std::vector<int> position(2, 0);
			position[0] = iPosX;
			position[1] = iPosY;
			return position;
		}
};