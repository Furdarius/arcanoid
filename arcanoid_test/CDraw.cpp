#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "CDraw.h"

CDraw *CDraw::instance = NULL;

CDraw::CDraw(const int& _iPosX, const int& _iPosY, const int& _iWindowW, const int& _iWindowH, const int& _iInitDisplayMode, const std::string& _sWindowName, const float& _iBg_R, const float& _iBg_G, const float& _iBg_B, const float& _iBg_A, const int& _iFrameTime, const int& _iMatrixMode)
{
	iPosX = _iPosX;
	iPosY = _iPosX;
	iWindowW = _iWindowW;
	iWindowH = _iWindowH;
	iInitDisplayMode = _iInitDisplayMode;
	sWindowName = _sWindowName;
	iBg_R = _iBg_R;
	iBg_G = _iBg_G;
	iBg_B = _iBg_B;
	iBg_A = _iBg_A;
	iFrameTime = _iFrameTime;
	iMatrixMode = _iMatrixMode;
}

void CDraw::initWindow(int argc, char** argv)
{
	instance = this;

	glutInit(&argc, argv);
	glutInitDisplayMode(iInitDisplayMode);
	glutInitWindowSize(iWindowW, iWindowH);
	glutCreateWindow (sWindowName.c_str());
	glClearColor(iBg_R,iBg_G,iBg_B,iBg_A);
	glMatrixMode(iMatrixMode);
	glLoadIdentity();
	gluOrtho2D(iPosX, iPosX + iWindowW, iPosY, iPosY + iWindowH);
	glutDisplayFunc(onRenderWrapper);
	glutSpecialFunc(onSpecKeyboardWrapper);
	glutReshapeFunc(onReshapeWrapper);
	glutTimerFunc(iFrameTime, onTimerWrapper, 0);
	glutMainLoop();
}

void CDraw::onRender(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < (int)aDrawObjects.size(); ++i)
	{
		aDrawObjects[i]->draw();
	}
	/*
	glColor3f(1.0,1.0,1.0);


	int posX = 100;
	int posY = 100;

	int lineSizeW = 300;
	int lineSizeH = 50;

	glBegin(GL_POLYGON);
        glVertex2f(posX, posY); // bottom - left
        glVertex2f(posX + lineSizeW, posY); // bottom - right
        glVertex2f(posX + lineSizeW, posY + lineSizeH); // top - right
        glVertex2f(posX, posY + lineSizeH); // top - left
	glEnd();
	*/
	//sceneUpdate();
	glFlush();
	glutSwapBuffers();
}

void CDraw::onSpecKeyboard(int key, int x, int y)
{

}

void CDraw::onReshape(int w, int h)
{

}

void CDraw::onTimer(int value)
{

}

void CDraw::addDrawObject(CDrawObject* pDrawObject)
{
	aDrawObjects.push_back(pDrawObject);
}

// ******************************************************************
// ** Static members. Callback functions **
// ******************************************************************

void CDraw::onRenderWrapper() {
	instance->onRender(); 
}

void CDraw::onSpecKeyboardWrapper(int key, int x, int y)
{
	instance->onSpecKeyboard(key, x, y);
}

void CDraw::onReshapeWrapper(int w, int h)
{
	instance->onReshape(w, h);
}

void CDraw::onTimerWrapper(int value)
{
	instance->onTimer(value);
}