#include "CClient.h"
#include "CGameHud.h"
#include "../Shared/Types.h"
#include "SocketInstance.h"

CClient::CClient()
{
	this->gameStarted = false;
	this->clientReady = false;
	this->iPlayersNum = 0;
	this->iReadyPlayersNum = 0;
	this->sServerAdress = "";
	this->CGameHudInstance = NULL;
	this->playerID = -1;
	this->ptr_PlayerBat = NULL;
};

void CClient::initGameHud(int argc, char** args)
{
	this->CGameHudInstance = new CGameHud(argc, args);
	this->ptr_PlayerBat = this->getPlayerBatById(this->getPlayerID());
	this->CGameHudInstance->InitWindow();
}

CGameHud* CClient::getGameHudInstance()
{
	return this->CGameHudInstance;
}

CRectangle *CClient::getPlayerBatById(int playerID)
{
	return (playerID == 1) ? this->CGameHudInstance->batBottom : this->CGameHudInstance->batTop;
}

void CClient::onRoundFinish(int winPlayerId)
{
	if (!this->isGameStarted())
		return;

	this->gameStarted = false;

	const char data[] = { PACKET_TYPES::ROUND_FINISHED, this->getPlayerID(), winPlayerId };
	this->sendDataToServer(data);

	//this->CGameHudInstance->Ball->setPosition(this->CGameHudInstance->fWindowWidth / 2, this->CGameHudInstance->fWindowHeigth / 2);
	//this->CGameHudInstance->Ball->setVelocity(getRandom(-0.1f, 0.1f) * 8, getRandom(-0.1f, 0.1f) * 8);
}

void CClient::setPlayersNum(int num)
{
	this->iPlayersNum = num;
}

int CClient::getPlayersNum()
{
	return this->iPlayersNum;
}

void CClient::setPlayerID(int id)
{
	this->playerID = id;
}

int CClient::getPlayerID()
{
	return this->playerID;
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
	if (this->clientReady)
		return;

	this->clientReady = true;
	const char data[] = { PACKET_TYPES::CONFIRM_READY };
	this->sendDataToServer(data);
	//this->addReadyPlayer();
}

void CClient::startGame(float velX, float velY)
{
	this->gameStarted = true;

	if (!this->CGameHudInstance)
		return;

	this->CGameHudInstance->Ball->setPosition(this->CGameHudInstance->fWindowWidth / 2, this->CGameHudInstance->fWindowHeigth / 2);
	this->CGameHudInstance->Ball->setVelocity(velX, velY);
	this->CGameHudInstance->setReadyIndicatorVisible(false);
}

void CClient::startRound(float velX, float velY)
{
	this->gameStarted = true;

	if (!this->CGameHudInstance)
		return;

	this->CGameHudInstance->Ball->setPosition(this->CGameHudInstance->fWindowWidth / 2, this->CGameHudInstance->fWindowHeigth / 2);
	this->CGameHudInstance->Ball->setVelocity(velX, velY);
}


void CClient::addReadyPlayer()
{
	++this->iReadyPlayersNum;
	if (this->CGameHudInstance)
		this->CGameHudInstance->pReadyCircles[this->iReadyPlayersNum - 1]->setColor(0, 1, 0, 1);
}

void CClient::setReadyPlayer(int num)
{
	this->iReadyPlayersNum = num;
	if (this->CGameHudInstance)
		for (int i = 0; i < this->getPlayersNum(); ++i)
			if (i < this->iReadyPlayersNum)
				this->CGameHudInstance->pReadyCircles[i]->setColor(0, 1, 0, 1);
			else
				this->CGameHudInstance->pReadyCircles[i]->setColor(1, 1, 0, 1);
}

int CClient::getReadyPlayersNum()
{
	return this->iReadyPlayersNum;
}

void CClient::setServerAddress(std::string adress)
{
	this->sServerAdress = adress;
}

std::string CClient::getServerAddress()
{
	return this->sServerAdress;
}

void CClient::setServerAddressObject(CAddress adress)
{
	this->obj_CAddress = adress;
}

CAddress CClient::getServerAddressObject()
{
	return this->obj_CAddress;
}

void CClient::requestServerAddressFromConsole()
{
	std::string adress;
	std::cout << "Server adress: ";
	std::cin >> adress;
	this->setServerAddress(adress);
}

void CClient::sendDataToServer(const char *data)
{
	CSocketInstance->Send(this->getServerAddressObject(), data, sizeof(data));
}

void CClient::onDataReceived(CAddress from, char *data, int size)
{
	switch ((int)data[0])
	{
	case PACKET_TYPES::START_GAME:
		std::cout << "Start game x=" << (int)data[1] << " y=" << (int)data[2] << std::endl;
		this->startGame(data[1] / 10.0, data[2] / 10.0);
		break;
	case PACKET_TYPES::PLAYER_JOINED:
		std::cout << "New player joined" << std::endl;
		break;
	case PACKET_TYPES::PLAYER_READY:
		std::cout << "Yet anouther player ready" << std::endl;
		this->setReadyPlayer((int)data[1]);
		break;
	case PACKET_TYPES::PLAYER_MOVE_BAT:
		std::cout << "Player " << (int)data[1] << " moved bat" << std::endl;
		this->onPlayerMoveBat(data[1], data[2], data[3]);
		break;
	case PACKET_TYPES::START_NEW_ROUND:
		std::cout << "Start round x=" << (int)data[1] << " y=" << (int)data[2] << std::endl;
		this->startRound(data[1] / 10.0, data[2] / 10.0);
		break;
	default:
		std::cout << "SERVER SEND: " << (int)data[0] << std::endl;
		break;
	}
}

void CClient::onMovementStateChange(bool leftPressed, bool rightPressed)
{
	std::cout << "onMovementStateChange" << std::endl;
	if (rightPressed && leftPressed)
		this->ptr_PlayerBat->setVelocity(0.0, 0);
	else if (rightPressed)
		this->ptr_PlayerBat->setVelocity(1.0, 0);
	else if (leftPressed)
		this->ptr_PlayerBat->setVelocity(-1.0, 0);
	else
		this->ptr_PlayerBat->setVelocity(0.0, 0);

	CVector2D< float > vel = this->ptr_PlayerBat->getVelocity();

	const char data[] = { PACKET_TYPES::PLAYER_MOVE_BAT, this->getPlayerID(), (int)vel.x, (int)vel.y };
	this->sendDataToServer(data);
}

void CClient::onPlayerMoveBat(int playerID, int velX, int velY)
{
	this->getPlayerBatById(playerID)->setVelocity(velX, velY);
}