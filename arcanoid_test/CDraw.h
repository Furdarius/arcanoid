#pragma once

#include <GL/glut.h>
#include <string>
#include <vector>
#include "CDrawObject.h"

class CDraw 
{
	int iInitDisplayMode; // Display mode
	int iPosX, iPosY; // Widown size
	int iWindowW, iWindowH; // Widown size
	std::string sWindowName; // Window title
	int iBg_R, iBg_G, iBg_B, iBg_A; // Backgorund color
	int iFrameTime; // Time between frames;
	int iMatrixMode;

	protected:
		static CDraw *instance;
		std::vector<CDrawObject*> aDrawObjects;

	public:
		CDraw(const int& = 0, const int& = 0, const int& = 640, const int& = 480, const int& = GLUT_RGB, const std::string& = "Title", const float& = 0, const float& = 0, const float& = 0, const float& = 0, const int& = 25, const int& = GL_PROJECTION);

		void initWindow(int, char**);

		// ** Glut callbacks **
		void onRender();
	  //void onKeyboard(unsigned char, int, int);
		void onSpecKeyboard(int, int, int);
		void onReshape(int, int);
		void onTimer(int);
		void addDrawObject(CDrawObject*);

		// ** Static members using as glut callback **
		static void onRenderWrapper();
	  //static void onKeyboardWrapper(unsigned char, int, int);
		static void onSpecKeyboardWrapper(int, int, int);
		static void onReshapeWrapper(int, int);
		static void onTimerWrapper(int);
};