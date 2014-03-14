#pragma once

#include <string>

class CAddress
{
public:

	CAddress();
	CAddress( unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port );
	CAddress( unsigned int address, unsigned short port );
	CAddress( std::string address );
	unsigned int GetAddress() const;
	unsigned char GetA() const;
	unsigned char GetB() const;
	unsigned char GetC() const;
	unsigned char GetD() const;
	unsigned short GetPort() const;
	bool operator == ( const CAddress & other ) const;
	bool operator != ( const CAddress & other ) const;

private:

	unsigned int address;
	unsigned short port;
};