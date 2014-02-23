#pragma once

#include "CGameHud.h"

class CClient
{
	protected:
		CGameHud* CGameHudInstance;
		int iPlayersNum;
		int iReadyPlayersNum;
		bool gameStarted;
		bool clientReady;

	public:
		CClient(void);

		void initGameHud(int argc, char** args);
		CGameHud* getGameHudInstance();

		void setPlayersNum(int num);
		int getPlayersNum();
		
		void addReadyPlayer();

		bool isGameStarted();

		bool isClientReady();
		void confirmClientReady();

		void startGame();

		void onRoundFinish();
		
};