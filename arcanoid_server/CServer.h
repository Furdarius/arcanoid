#pragma once

#include <vector>
#include "CPlayer.h"
#include "../Shared/CAddress.h";
#include "../Shared/Types.h"


class CServer
{
	protected:
		std::vector< CPlayer > aPlayersList;
		int iMaxPlayers;
		int iReadyPlayers;

	public:
		CServer();
		
		void addPlayer(CPlayer player);
		int getPlayersCount();
		bool isServerFull();

		void sendToClients(const char *data);
		void sendToClients(const char *data, CAddress besideAddress);

		// Events:
		void onDataReceived(CAddress from, char *data, int size);
		void onPlayerAskJoin(CAddress address);
		void onPlayerReady(CAddress address);
		void onStartGame();
		void onPlayerMoveBat(CAddress address, int playerID, int velX, int velY);

};