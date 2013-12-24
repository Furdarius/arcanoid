#include <Windows.h>
#include <iostream>

#include "CGameHud.h"


CGameHud::CGameHud(int argc, char** args)
{
	fWindowWidth = 1024;
	fWindowHeigth = 768;

	batWidth = fWindowWidth / 6;
	batHeigth = fWindowHeigth / 28;

	batPadding = batHeigth / 2;

	float screenWidth = GetSystemMetrics(SM_CXSCREEN);
	float screenHeigth = GetSystemMetrics(SM_CYSCREEN);

	fWindowX = (screenWidth / 2) - (fWindowWidth / 2);
	fWindowY = (screenHeigth / 2) - (fWindowHeigth / 2);

	CDrawnInstance = new CDraw(fWindowX, fWindowY, fWindowWidth, fWindowHeigth, "Arcanoid Test Game");
	
	// Create HUD elements:
	batBottom = new CRectangle();
		batBottom->setPosition(fWindowWidth / 2 - batWidth / 2, fWindowHeigth - batHeigth - batPadding);
		batBottom->setSize(batWidth, batHeigth);
	/*
	batTop = new CRectangle();
		batTop->setPosition(fWindowWidth / 2 - batWidth / 2, batPadding);
		batTop->setSize(batWidth, batHeigth);
	*/

	CDrawnInstance->addDrawObject(batBottom);
	//CDrawnInstance->addDrawObject(batTop);

	CDrawnInstance->initWindow(argc, args);
}