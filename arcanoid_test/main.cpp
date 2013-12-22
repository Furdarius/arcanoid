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


int main(int argc, char** args)
{
	CDraw* CDrawn = new CDraw();
	CRectangle* bita1 = new CRectangle(0, 0);
		bita1->setSize(100, 100);

	CDrawn->addDrawObject(bita1);
	CDrawn->initWindow(argc, args);
	return 0;
}