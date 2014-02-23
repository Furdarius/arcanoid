#include "CClient.h"
#include "CGameHud.h"

CClient::CClient()
{
	this->gameStarted = false;
	this->clientReady = false;
	this->setPlayersNum(2);
	this->iReadyPlayersNum = 0;
};

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

void CClient::setPlayersNum(int num)
{
	this->iPlayersNum = num;
}

int CClient::getPlayersNum()
{
	return this->iPlayersNum;
}

bool CClient::isGameStarted()
{
	return this->gameStarted;
}

bool CClient::isClientReady()
{
	return this->clientReady;
}

void CClient::confirmClientReady()
{
	this->clientReady = true;
	this->addReadyPlayer();
}

void CClient::startGame()
{
	this->gameStarted = true;
	this->CGameHudInstance->Ball->setVelocity(getRandom(-0.3f, 0.3f), getRandom(-0.3f, 0.3f));
	this->CGameHudInstance->setReadyIndicatorVisible(false);
}

void CClient::addReadyPlayer()
{
	++this->iReadyPlayersNum;
	this->CGameHudInstance->pReadyCircles[this->iReadyPlayersNum - 1]->setColor(0, 1, 0, 1);
	if (this->iReadyPlayersNum == this->iPlayersNum)
		this->startGame();
}