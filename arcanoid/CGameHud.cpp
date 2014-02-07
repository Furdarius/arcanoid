#include <Windows.h>
#include <iostream>
#include "CGameHud.h"


CGameHud::CGameHud(int argc, char** args)
{
	this->argc = argc;
	this->args = args;

	fWindowWidth = 1024;
	fWindowHeigth = 768;

	batWidth = fWindowWidth / 6;
	batHeigth = fWindowHeigth / 28;

	batPadding = batHeigth / 2;

	ballRadius = fWindowWidth * 0.025;

	float screenWidth = GetSystemMetrics(SM_CXSCREEN);
	float screenHeigth = GetSystemMetrics(SM_CYSCREEN);

	fWindowX = (screenWidth / 2) - (fWindowWidth / 2);
	fWindowY = (screenHeigth / 2) - (fWindowHeigth / 2);

	CDrawnInstance = new CDraw(fWindowX, fWindowY, fWindowWidth, fWindowHeigth, "Arcanoid Test Game");
	
	// Create HUD elements:
	batBottom = new CRectangle();
		batBottom->setPosition(fWindowWidth / 2 - batWidth / 2, fWindowHeigth - batHeigth - batPadding);
		batBottom->setSize(batWidth, batHeigth);
		CDrawnInstance->addDrawObject(batBottom);
	Ball = new CCircle();
		Ball->setRadius(ballRadius);
		Ball->setPosition(fWindowWidth / 2, fWindowHeigth / 2);
		Ball->setGravity(0, 0.0007);
	CDrawnInstance->addDrawObject(Ball);
}

void CGameHud::InitWindow()
{
	CDrawnInstance->initWindow(this->argc, this->args);
}

void CGameHud::onKey(unsigned char key, bool down)
{
	if (key == 32 && down)
	{
		float x = getRandom(-1.0f, 1.0f);
		float y = getRandom(-1.0f, 1.0f);
		Ball->setVelocity(x, y);
	}
}