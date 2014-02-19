#pragma once

#include <vector>
#include "CDraw.h"
#include "CRectangle.h"
#include "CCircle.h"

static float getRandom(float from, float to)
{
	return from + (to - from) * rand() / RAND_MAX;
}

enum MovementState
{
	NONE = 0,
    LEFT,
    RIGHT
};

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

		std::vector< CCircle* > pReadyCircles;

		bool leftPressed;
		bool rightPressed;

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

		MovementState batMovement;

		CGameHud(int argc, char** args);

		void InitWindow();

		// Events
		void onKey(int key, bool down);
		void onMouseMove(int x, int y);
		void onRender();
};
