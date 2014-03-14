#pragma once

#include "SockNet.h"

class CSocket
{
public:

    CSocket();
	CSocket(unsigned short port, int nonBlocking = 1);
    ~CSocket();

	bool Create();
	bool IsCreated() const;

    bool Bind( unsigned short port, int nonBlocking = 1);

	// Set the socket I/O mode: In this case FIONBIO
	// enables or disables the blocking mode for the 
	// socket based on the numerical value of iMode.
	// If iMode = 0, blocking is enabled; 
	// If iMode != 0, non-blocking mode is enabled.
	bool setBlocking(int nonBlocking = 1);

    void Close();
    bool Send(const CAddress & destination, const char *data, int size);
    int Receive(CAddress & sender, char *data, int size);

private:

    int socket;
};