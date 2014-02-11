#pragma once

#include "CDraw.h"
#include "CRectangle.h"
#include "CCircle.h"

static float getRandom(float from, float to)
{
	return from + (to - from) * rand() / RAND_MAX;
}

class CGameHud
{
	protected:
		CDraw* CDrawnInstance;
		int argc;
		char** args;

	public:
		// HUD elements:
		CRectangle* batTop;
		CRectangle* batBottom;

		CCircle* Ball;

		// Settings:

		// Game window size:
		float fWindowX;
		float fWindowY;

		// Game window size:
		float fWindowWidth;
		float fWindowHeigth;

		// Bat settisizengs:
		float batWidth;
		float batHeigth;

		float batPadding;

		// Ball size:
		float ballRadius;

		CGameHud(int argc, char** args);

		void InitWindow();

		// Events
		void onKey(unsigned char key, bool down);
		void onMouseMove(int x, int y);
};
