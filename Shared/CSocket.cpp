#include "SockNet.h"

CSocket::CSocket()
{
	this->socket = 0;
}

CSocket::CSocket(unsigned short port, int nonBlocking)
{
	this->socket = 0;
	if (this->Create())
		this->Bind(port, nonBlocking);
}
	
CSocket::~CSocket()
{
	Close();
}

bool CSocket::Create()
{
	if (this->IsCreated())
		return true;

	this->socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->socket < 0)
	{
		// nix - errno, win - WSAGetLastError()
		//printf("CSocket::Create error:  %d\n", WSAGetLastError());
		this->socket = 0;
		return false;
	}

	return true;
}
	
bool CSocket::Bind(unsigned short port, int nonBlocking)
{
	assert( this->IsCreated() );

	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(port);

	// If no error occurs, bind returns zero. Otherwise, it returns SOCKET_ERROR, and a specific error code can be retrieved by calling WSAGetLastError.
	if (bind(socket, (const sockaddr*) &local_addr, sizeof(local_addr)))
		return false;

	if (!this->setBlocking(nonBlocking))
		return false;
		
	return true;
}

bool CSocket::setBlocking(int nonBlocking)
{
	#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		if (fcntl( socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1 )
		{
			printf( "Failed to set non-blocking socket\n" );
			Close();
			return false;
		}
	#elif PLATFORM == PLATFORM_WINDOWS
		DWORD block = nonBlocking;
		if ( ioctlsocket( socket, FIONBIO, &block) != 0 )
		{
			printf( "Failed to set non-blocking socket\n" );
			Close();
			return false;
		}
	#endif

	return true;
}
	
void CSocket::Close()
{
	if (this->IsCreated())
	{
		#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
			close( this->socket );
		#elif PLATFORM == PLATFORM_WINDOWS
			closesocket( this->socket );
		#endif
		this->socket = 0;
	}
}
	
bool CSocket::IsCreated() const
{
	return socket != 0;
}
	
bool CSocket::Send(const CAddress &destination, const char *data, int size)
{
	assert( data );
	assert( size > 0 );
		
	if (!this->IsCreated())
	{
		printf("CSocket::Send error: Socket not created\n");
		return false;
	}

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(destination.GetAddress());
	address.sin_port = htons((unsigned short) destination.GetPort());

	int sent_bytes = sendto(socket, data, size, 0, (sockaddr*) &address, sizeof(sockaddr_in));

	return sent_bytes == size;
}
	
int CSocket::Receive(CAddress &sender, char *data, int size)
{
	assert( data );
	assert( size > 0 );
		
	if ( socket == 0 )
		return false;
			
	#if PLATFORM == PLATFORM_WINDOWS
		typedef int socklen_t;
	#endif
			
	sockaddr_in from;
	socklen_t fromLength = sizeof(from);

	int received_bytes = recvfrom( socket, data, size, 0, (sockaddr*)&from, &fromLength );

	if ( received_bytes <= 0 )
		return 0;

	unsigned int address = ntohl(from.sin_addr.s_addr);
	unsigned int port = ntohs(from.sin_port);

	sender = CAddress( address, port );

	return received_bytes;
}