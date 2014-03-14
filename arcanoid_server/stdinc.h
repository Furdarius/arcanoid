#pragma once
#include <stdlib.h>

static float getRandom(float from, float to)
{
	return from + (to - from) * rand() / RAND_MAX;
}