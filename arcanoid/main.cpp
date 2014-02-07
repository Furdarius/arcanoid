#include "CGameHud.h"
#include "GameInstance.h"
#include <iostream>

CGameHud* CGameHudInstance;

int main(int argc, char** args)
{
	CGameHudInstance = new CGameHud(argc, args);
	CGameHudInstance->InitWindow();
	return 0;
}