#pragma once

#include "CDraw.h"
#include "CRectangle.h"
#include "CCircle.h"

class CGameHud
{
	protected:
		CDraw* CDrawnInstance;

		// HUD elements:
		CRectangle* batTop;
		CRectangle* batBottom;

		CCircle* Ball;

	public:
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

};