#include <iostream>
#include <process.h>
#include <string>
#include "CClient.h"
#include "ClientInstance.h"
#include "SocketInstance.h"
#include "../Shared/SockNet.h"
#include "../Shared/Types.h"

CClient* CClientInstance;
CSocket* CSocketInstance;

unsigned __stdcall fReadSocketDataThread( void* pArguments )
{
	CAddress sender;
    char buffer[256];
	while (1)
        if (int size = CSocketInstance->Receive(sender, buffer, sizeof(buffer)) && sender == CClientInstance->getServerAddressObject())
			CClientInstance->onDataReceived(sender, buffer, size);
    //_endthreadex( 0 );
    return 0;
} 

int main(int argc, char** args)
{
	if ( !InitializeSockets() )
	{
		printf( "failed to initialize sockets\n" );
		return 1;
	}
	HANDLE hThread;
    unsigned threadID;

	CClientInstance = new CClient();
	CSocketInstance = new CSocket();
	//CClientInstance->requestServerAddressFromConsole();
	CClientInstance->setServerAddressObject(CAddress(127, 0, 0, 1, 30000));

	CSocketInstance->Create();

	std::cout << "Connecting to server..." << std::endl;
	const char data[] = { PACKET_TYPES::PLAYER_ASK_FOR_CONNECT };
	bool st = CSocketInstance->Send(CClientInstance->getServerAddressObject(), data, sizeof(data));

	CAddress sender;
    char buffer[256];
	while (1)
        if (CSocketInstance->Receive(sender, buffer, sizeof(buffer)) && sender == CClientInstance->getServerAddressObject())
			break;

	if (buffer[0] == PACKET_TYPES::SUCCESS_CONNECTION)
	{
		std::cout << "Success connection" << std::endl;
		CClientInstance->setPlayersNum(buffer[1]);
		CClientInstance->setReadyPlayer(buffer[2]);
		CClientInstance->setPlayerID(buffer[3]);
		hThread = (HANDLE)_beginthreadex( NULL, 0, &fReadSocketDataThread, NULL, 0, &threadID );
	}
	else
		std::cout << "Error: Server say: " << std::string(buffer) << std::endl;

	CClientInstance->initGameHud(argc, args);
	system("pause");
	ShutdownSockets();
	return 0;
}