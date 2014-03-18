#include <Windows.h>
#include <iostream>

#include "CGameHud.h"
#include "ClientInstance.h"

CGameHud::CGameHud(int argc, char** args)
{

	this->argc = argc;
	this->args = args;
	this->leftPressed = false;
	this->rightPressed = false;

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
		
	batTop = new CRectangle();
		batTop->setPosition(fWindowWidth / 2 - batWidth / 2, batHeigth - batPadding);
		batTop->setSize(batWidth, batHeigth);

	Ball = new CCircle(fWindowWidth / 2, fWindowHeigth / 2, ballRadius, 1, 0, 0, 1);
		//Ball->setGravity(0, 0.0007);
		//Ball->setVelocity(getRandom(-0.3f, 0.3f), getRandom(-0.3f, 0.3f));
	CDrawnInstance->addDrawObject(Ball);
	CDrawnInstance->addDrawObject(batBottom);

	CDrawnInstance->addDrawObject(batTop);

	int NUM = CClientInstance->getPlayersNum();

	for (size_t i = 0; i < NUM; ++i)
	{
		CCircle *tmpReadyIndicator = new CCircle(fWindowWidth / 2 - (((NUM - 1) * 50) / 2) + (i * 50), fWindowHeigth / 4, 20.0, 1, 1, 0);
		if (i < CClientInstance->getReadyPlayersNum())
			tmpReadyIndicator->setColor(0, 1, 0, 1);
		pReadyCircles.push_back(tmpReadyIndicator);
		CDrawnInstance->addDrawObject(tmpReadyIndicator);
	}
}

void CGameHud::InitWindow()
{
	CDrawnInstance->initWindow(this->argc, this->args);
}

void CGameHud::onKey(int key, bool down)
{
	if (key == 32 && down)
	{
		if (!CClientInstance->isGameStarted())
			CClientInstance->confirmClientReady();
		//Ball->setVelocity(getRandom(-1.0f, 1.0f), getRandom(-1.0f, 1.0f));
	}
	else if (key == 102 && CClientInstance->isGameStarted())
	{
		if (this->rightPressed != down)
		{
			this->rightPressed = down;
			CClientInstance->onMovementStateChange(this->leftPressed, this->rightPressed);
		}
	}
	else if (key == 100 && CClientInstance->isGameStarted())
	{
		if (this->leftPressed != down)
		{
			this->leftPressed = down;
			CClientInstance->onMovementStateChange(this->leftPressed, this->rightPressed);
		}
	}
}

void CGameHud::onMouseMove(int x, int y)
{
	/*
	Ball->setPosition(x, y);
	Ball->setGravity(0.0, 0.0);
	Ball->setVelocity(0.0, 0.0);
	*/
}

void CGameHud::onRender()
{
	/*
	CPoint2D<float> ballPos = Ball->getPosition();
	CPoint2D<float> batPos = batTop->getPosition();
	std::vector<float> batSize = batTop->getSize();
	batTop->setPosition(ballPos.x - batSize[0] / 2, batPos.y);
	*/
}

void CGameHud::setReadyIndicatorVisible(bool state)
{
	for (size_t i = 0; i < this->pReadyCircles.size(); ++i)
		this->pReadyCircles[i]->setVisible(state);
}