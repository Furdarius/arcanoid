#include "CClient.h"
#include "ClientInstance.h"
#include <iostream>

CClient* CClientInstance;

int main(int argc, char** args)
{
	CClientInstance = new CClient();
	CClientInstance->initGameHud(argc, args);
	return 0;
}