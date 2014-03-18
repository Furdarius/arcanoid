#include "CServer.h"
#include "Instances.h"
#include <iostream>
#include "stdinc.h"

CServer::CServer()
{
	this->iMaxPlayers = 2;
	this->iReadyPlayers = 0;
	this->aPlayersList = std::vector< CPlayer > ();
	this->aGameStateInfo = std::vector< int > (this->iMaxPlayers, 0);
}

void CServer::addPlayer(CPlayer player)
{
	this->aPlayersList.push_back(player);
}

bool CServer::isServerFull()
{
	return this->aPlayersList.size() >= this->iMaxPlayers;
}

void CServer::onDataReceived(CAddress from, char *data, int size)
{
	switch ((int)data[0])
	{
	case PACKET_TYPES::PLAYER_ASK_FOR_CONNECT:
		this->onPlayerAskJoin(from);
		break;
	case PACKET_TYPES::CONFIRM_READY:
		this->onPlayerReady(from);
		break;
	case PACKET_TYPES::PLAYER_MOVE_BAT:
		this->onPlayerMoveBat(from, data[1], data[2], data[3]);
		break;
	case PACKET_TYPES::ROUND_FINISHED:
		this->onRoundFinished(from, data[1], data[2]);
		break;
	default:
		break;
	}
}

void CServer::onPlayerAskJoin(CAddress address)
{
	if (!this->isServerFull())
	{
		std::cout << "Player joined" << std::endl;
		this->addPlayer(CPlayer(address));

		const char data[] = { PACKET_TYPES::SUCCESS_CONNECTION, this->iMaxPlayers, this->iReadyPlayers, this->getPlayersCount() };
		CSocketInstance->Send(address, data, sizeof(data));

		const char joinedData[] = { PACKET_TYPES::PLAYER_JOINED };
		this->sendToClients(joinedData);
	}
	else
	{
		std::cout << "Player tryed to join, but server is full" << std::endl;
		const char data[] = { PACKET_TYPES::ERROR_PACKET };
		CSocketInstance->Send(address, data, sizeof(data));
	}
}

void CServer::sendToClients(const char *data)
{
	for (int i = 0; i < this->aPlayersList.size(); ++i)
		CSocketInstance->Send(this->aPlayersList[i].getAdressObject(), data, sizeof(data));
}

void CServer::sendToClients(const char *data, CAddress besideAddress)
{
	for (int i = 0; i < this->aPlayersList.size(); ++i)
		if (besideAddress != this->aPlayersList[i].getAdressObject())
			CSocketInstance->Send(this->aPlayersList[i].getAdressObject(), data, sizeof(data));
}


int CServer::getPlayersCount()
{
	return this->aPlayersList.size();
}

void CServer::onPlayerReady(CAddress address)
{
	++this->iReadyPlayers;

	if (this->iReadyPlayers == this->iMaxPlayers)
		return this->onStartGame();

	const char data[] = { PACKET_TYPES::PLAYER_READY, this->iReadyPlayers};
	this->sendToClients(data);
}


void CServer::onStartGame()
{
	const char data[] = { PACKET_TYPES::START_GAME, getRandom(-10, 10), getRandom(-10, 10) };
	this->sendToClients(data);
}

void CServer::onPlayerMoveBat(CAddress address, int playerID, int velX, int velY)
{
	const char data[] = { PACKET_TYPES::PLAYER_MOVE_BAT, playerID, velX, velY };
	this->sendToClients(data, address);
}

bool CServer::doesStateInfoReady()
{
	for (int i = 0; i < this->aGameStateInfo.size(); ++i)
		if (this->aGameStateInfo[i] <= 0)
			return 0;
	return 1;
}

PACKET_TYPES CServer::getStateInfo()
{
	int state = -1;
	int cnt = 0;

	for (int i = 0; i < this->aGameStateInfo.size(); ++i)
	{
		int tmp = this->aGameStateInfo[i];
		int tmp_cnt = 0;
		for (int n = i; n < this->aGameStateInfo.size(); ++n)
			if (this->aGameStateInfo[n] == tmp)
				++tmp_cnt;
		if (tmp_cnt > cnt)
		{
			state = tmp;
			cnt = tmp_cnt;
		}
	}

	return (PACKET_TYPES)state;
}

bool CServer::getStateStatus(PACKET_TYPES state)
{
	int size = this->aGameStateInfo.size();
	int cnt = 0;
	for (int i = 0; i < size; ++i)
		if (this->aGameStateInfo[i] == state)
			++cnt;
	return (cnt >= size / 2);
}

void CServer::onRoundFinished(CAddress address, int playerID, int winPlayerId)
{
	this->aGameStateInfo[playerID - 1] = PACKET_TYPES::ROUND_FINISHED;
	if (!this->doesStateInfoReady())
		return;

	if (!this->getStateStatus(PACKET_TYPES::ROUND_FINISHED))
		return;

	const char data[] = { PACKET_TYPES::START_NEW_ROUND, getRandom(-10, 10), getRandom(-10, 10) };
	this->sendToClients(data);
}