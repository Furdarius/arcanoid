#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include "CDraw.h"
#include "ClientInstance.h"
#include <iostream>

CDraw *CDraw::instance = NULL;

CDraw::CDraw(const int& _iPosX, const int& _iPosY, 
	const int& _iWindowW, const int& _iWindowH, 
	const std::string& _sWindowName,
	const int& _iInitDisplayMode,
	const float& _iBg_R, const float& _iBg_G, const float& _iBg_B,
	const float& _iBg_A, 
	const int& _iFrameTime,
	const int& _iMatrixMode)
{
	iPosX = _iPosX;
	iPosY = _iPosY;
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
	fLastFrameTime = 0;
}

void CDraw::initWindow(int argc, char** argv)
{
	instance = this;

	// Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(iInitDisplayMode);
    glutInitWindowPosition(iPosX, iPosY);
    glutInitWindowSize(iWindowW, iWindowH);
    glutCreateWindow(sWindowName.c_str());

    // Function callbacks with wrapper functions
    glutReshapeFunc(reshapeWrapper);
    glutMouseFunc(mouseButtonPressWrapper);
    glutMotionFunc(mouseMoveWrapper);
    glutDisplayFunc(renderWrapper);
    glutKeyboardFunc(keyboardDownWrapper);
    glutKeyboardUpFunc(keyboardUpWrapper);
    glutSpecialFunc(specialKeyboardDownWrapper);
    glutSpecialUpFunc(specialKeyboardUpWrapper);
                
    init();
    glutIdleFunc(runWrapper);
    glutMainLoop();
}


void CDraw::addDrawObject(CDrawObject* pDrawObject)
{
	aDrawObjects.push_back(pDrawObject);
}

void CDraw::run()
{
	glutPostRedisplay();
}

void CDraw::init() 
{
	glClearColor(iBg_R, iBg_G, iBg_B, iBg_A);
    glMatrixMode(iMatrixMode);
    glLoadIdentity();
	gluOrtho2D(0, iWindowW, iWindowH, 0);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
}

// ******************************************************************
// ** GLUT Events handlers **
// ******************************************************************

void CDraw::onRender(void)
{
	float _time = clock();
	float dt = _time - fLastFrameTime;

	if (dt >= iFrameTime)
	{
		glClearColor(iBg_R, iBg_G, iBg_B, iBg_A);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < (int)aDrawObjects.size(); ++i)
			if (aDrawObjects[i]->getVisible())
				aDrawObjects[i]->Render(dt);

		glFlush();
		glutSwapBuffers();

		fLastFrameTime = _time;
	}
	CClientInstance->getGameHudInstance()->onRender();
}
        
void CDraw::onReshape(int width, int height) {
	glutReshapeWindow(iWindowW, iWindowH);
	glViewport(0,0,(GLsizei)width,(GLsizei)height);
}
        
void CDraw::onMouseButtonPress(int button, int state, int x, int y) {
	//printf("MouseButtonPress: x: %d y: %d\n", x, y); 
}
        
void CDraw::onMouseMove(int x, int y) {
	//printf("MouseMove: x: %d y: %d\n", x, y);
	CClientInstance->getGameHudInstance()->onMouseMove(x, y);
}
        
void CDraw::onKeyboardDown(unsigned char key, int x, int y) 
{
    // Subclass and override this method
    //printf( "KeyboardDown: %c = %d\n", key, (int)key );
	if (key == 27)
		exit(0);
	CClientInstance->getGameHudInstance()->onKey(key, true);
}
        
void CDraw::onKeyboardUp( unsigned char key, int x, int y ) 
{
    // Subclass and override this method
   // printf( "KeyboardUp: %c \n", key );
	CClientInstance->getGameHudInstance()->onKey(key, false);
}
        
void CDraw::onSpecialKeyboardDown( int key, int x, int y ) 
{
    // Subclass and override this method
    //printf( "SpecialKeyboardDown: %d\n", key );
	CClientInstance->getGameHudInstance()->onKey(key, true);
}
        
void CDraw::onSpecialKeyboardUp( int key, int x, int y ) 
{
    // Subclass and override this method        
    // printf( "SpecialKeyboardUp: %d \n", key );
	CClientInstance->getGameHudInstance()->onKey(key, false);
}

// ******************************************************************
// ** Static functions which are passed to GLUT function callbacks **
// ******************************************************************
        
void CDraw::renderWrapper() {
    instance->onRender(); 
}
        
void CDraw::reshapeWrapper(int width, int height) {
    instance->onReshape(width, height);
}
        
void CDraw::runWrapper() {
    instance->run();
}
        
void CDraw::mouseButtonPressWrapper(int button, int state, int x, int y) {
    instance->onMouseButtonPress(button, state, x, y);
}
        
void CDraw::mouseMoveWrapper(int x, int y) {
    instance->onMouseMove(x, y);
}
                                                                                 
void CDraw::keyboardDownWrapper(unsigned char key, int x, int y) {
    instance->onKeyboardDown(key,x,y);
}
        
void CDraw::keyboardUpWrapper(unsigned char key, int x, int y) {
    instance->onKeyboardUp(key,x,y);
}
        
void CDraw::specialKeyboardDownWrapper(int key, int x, int y) {
    instance->onSpecialKeyboardDown(key,x,y);
}
        
void CDraw::specialKeyboardUpWrapper(int key, int x, int y) {
    instance->onSpecialKeyboardUp(key,x,y);
}