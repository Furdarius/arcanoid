#pragma once

#include "CGameHud.h"

class CClient
{
	protected:
		CGameHud* CGameHudInstance;

	public:
		CClient(void);

		void initGameHud(int argc, char** args);
		CGameHud* getGameHudInstance();

		void onRoundFinish();
		
};