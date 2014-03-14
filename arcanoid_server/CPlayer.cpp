#include "CPlayer.h"

CPlayer::CPlayer()
{
	this->PlayerAdress = CAddress();
}

CPlayer::CPlayer(CAddress address)
{
	this->PlayerAdress = address;
}

CAddress CPlayer::getAdressObject()
{
	return this->PlayerAdress;
}
