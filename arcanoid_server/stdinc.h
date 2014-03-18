#pragma once
#include <stdlib.h>
#include <ctime>


static float getRandom(float from, float to)
{
	return from + (to - from) * rand() / RAND_MAX;
}