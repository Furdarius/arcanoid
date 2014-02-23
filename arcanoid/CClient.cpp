#include "CClient.h"
#include "CGameHud.h"

CClient::CClient() { };

void CClient::initGameHud(int argc, char** args)
{
	this->CGameHudInstance = new CGameHud(argc, args);
	this->CGameHudInstance->InitWindow();
}

CGameHud* CClient::getGameHudInstance()
{
	return this->CGameHudInstance;
}

void CClient::onRoundFinish()
{
	this->CGameHudInstance->Ball->setPosition(this->CGameHudInstance->fWindowWidth / 2, this->CGameHudInstance->fWindowHeigth / 2);
	this->CGameHudInstance->Ball->setVelocity(getRandom(-0.1f, 0.1f) * 8, getRandom(-0.1f, 0.1f) * 8);
}