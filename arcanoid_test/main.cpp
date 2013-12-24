#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <conio.h>
#include <math.h>
#include <map>
#include <string>

#include "CVector2D.h"
#include "CDraw.h"

#include "CRectangle.h"

#include "CGameHud.h"


int main(int argc, char** args)
{
	CGameHud* CGameHudInstance = new CGameHud(argc, args);
	return 0;
}