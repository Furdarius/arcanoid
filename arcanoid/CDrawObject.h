#pragma once

#include <vector>
#include "CVector2D.h"

class CDrawObject
{
	protected:
		float iPosX;
		float iPosY;

		int iColorR;
		int iColorG;
		int iColorB;
		int iColorA;

		bool bDynamic;

		CVector2D<float> velocity;
		CVector2D<float> gravity;

	public:
		CDrawObject(float x = 0, float y = 0, int r = 1, int g = 1, int b = 1, int a = 1);
		virtual ~CDrawObject() { };

		virtual void draw() { };

		void RecountPosition(float FrameTimeDelta);

		void setColor(int r, int g, int b, int a = 1);
		std::vector<int> getColor();

		void setPosition(float x, float y);
		std::vector<float> getPosition();

		void setGravity(float x, float y);
		CVector2D<float> getGravity();

		void setVelocity(float x, float y);
		CVector2D<float> getVelocity();

		void Render(float FrameTimeDelta);
};