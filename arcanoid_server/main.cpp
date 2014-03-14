#include <iostream>
#include <string>
#include "../Shared/SockNet.h"
#include "CServer.h"
#include "Instances.h"

CServer* CServerInstance;
CSocket* CSocketInstance;

int main(int argc, char *argv[])
{
	if ( !InitializeSockets() )
	{
		printf( "failed to initialize sockets\n" );
		return 1;
	}

	CServerInstance = new CServer();

	int port = 30000;

	if ( argc == 2 )
		port = atoi( argv[1] );

	printf( "Creating socket on port %d\n", port );

	CSocketInstance = new CSocket(port);

	if (!CSocketInstance->IsCreated())
	{
		printf( "failed to create socket!\n" );
		return 1;
	}

	printf( "Start listening port %d\n", port );
	while (1)
    {
        CAddress sender;
        char buffer[256];
        if (int bytes_read = CSocketInstance->Receive(sender, buffer, sizeof(buffer)))
			CServerInstance->onDataReceived(sender, buffer, bytes_read);
        
    }
	printf( "Stop listening port %d\n", port );

	
	ShutdownSockets();

	return 0;
}