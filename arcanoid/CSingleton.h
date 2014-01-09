#pragma once

class CSingleton
{
	public:
		static CSingleton* Instance();
	protected:
		CSingleton();
	private:
		static CSingleton* _instance;
};