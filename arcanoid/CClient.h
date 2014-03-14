#pragma once

#include <iostream>
#include <string>
#include "CGameHud.h"
#include "../Shared/CAddress.h"

class CClient
{
	protected:
		CGameHud* CGameHudInstance;
		int iPlayersNum;
		int iReadyPlayersNum;
		bool gameStarted;
		bool clientReady;
		std::string sServerAdress;
		CAddress obj_CAddress;
		int playerID;
		CRectangle *ptr_PlayerBat;

	public:
		CClient(void);

		void initGameHud(int argc, char** args);
		CGameHud* getGameHudInstance();

		void setPlayersNum(int num);
		int getPlayersNum();
		
		void setReadyPlayer(int num);
		void addReadyPlayer();
		int getReadyPlayersNum();

		void setPlayerID(int id);
		int getPlayerID();

		bool isGameStarted();

		bool isClientReady();
		void confirmClientReady();

		void startGame(float velX, float velY);

		void onRoundFinish();

		void setServerAddress(std::string adress);
		std::string getServerAddress();
		CAddress getServerAddressObject();
		void setServerAddressObject(CAddress adress);
		void requestServerAddressFromConsole();

		void sendDataToServer(const char *data);

		CRectangle *getPlayerBatById(int playerID);

		void onDataReceived(CAddress from, char *data, int size);
		void onMovementStateChange(bool leftPressed, bool rightPressed);
		void onPlayerMoveBat(int playerID, int velX, int velY);
};