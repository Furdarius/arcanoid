#pragma once

#include "../Shared/CAddress.h";

class CPlayer
{
	protected:
		CAddress PlayerAdress;

	public:
		CPlayer();
		CPlayer(CAddress address);

		CAddress getAdressObject();
};