#include <string>
#include "SockNet.h"

CAddress::CAddress()
{
	this->address = 0;
	this->port = 0;
};

CAddress::CAddress( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port )
{
	this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
	this->port = port;
}
	
CAddress::CAddress( unsigned int address, unsigned short port )
{
	this->address = address;
	this->port = port;
}

CAddress::CAddress( std::string address )
{
	// TODO
}

unsigned int CAddress::GetAddress() const
{
	return address;
}
	
unsigned char CAddress::GetA() const
{
	return ( unsigned char ) ( address >> 24 );
}
	
unsigned char CAddress::GetB() const
{
	return ( unsigned char ) ( address >> 16 );
}
	
unsigned char CAddress::GetC() const
{
	return ( unsigned char ) ( address >> 8 );
}
	
unsigned char CAddress::GetD() const
{
	return ( unsigned char ) ( address );
}
	
unsigned short CAddress::GetPort() const
{ 
	return port;
}
	
bool CAddress::operator == ( const CAddress & other ) const
{
	return address == other.address && port == other.port;
}
	
bool CAddress::operator != ( const CAddress & other ) const
{
	return ! ( *this == other );
}