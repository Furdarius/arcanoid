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
		std::vector< int > aGameStateInfo;

	public:
		CServer();
		
		void addPlayer(CPlayer player);
		int getPlayersCount();
		bool isServerFull();

		void sendToClients(const char *data);
		void sendToClients(const char *data, CAddress besideAddress);

		bool doesStateInfoReady();
		PACKET_TYPES getStateInfo();
		bool getStateStatus(PACKET_TYPES state);

		// Events:
		void onDataReceived(CAddress from, char *data, int size);
		void onPlayerAskJoin(CAddress address);
		void onPlayerReady(CAddress address);
		void onStartGame();
		void onPlayerMoveBat(CAddress address, int playerID, int velX, int velY);
		void onRoundFinished(CAddress address, int playerID, int winPlayerId);
};