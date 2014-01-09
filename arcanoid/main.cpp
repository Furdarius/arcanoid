#include "CGameHud.h"


CGameHud* CGameHudInstance;


int main(int argc, char** args)
{
	CGameHudInstance = new CGameHud(argc, args);
	return 0;
}