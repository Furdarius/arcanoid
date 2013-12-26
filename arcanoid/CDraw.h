#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <string>
#include <vector>
#include <time.h>

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

	float fLastFrameTime;

	protected:
		static CDraw *instance;
		std::vector<CDrawObject*> aDrawObjects;

	public:
		CDraw(const int& iPosX = 0, const int& iPosY = 0, const int& iWindowW = 640, const int& iWindowH = 480,
			const std::string& sWindowName = "Title", const int& iInitDisplayMode = GLUT_RGB,
			const float& iBg_R = 0, const float& iBg_G = 0, const float& iBg_B = 0,
			const float& iBg_A = 0, const int& iFrameTime = 4, const int& iMatrixMode = GL_PROJECTION);

		/** Initializes GLUT and registers the callback functions. */
		void initWindow(int, char**);

		void addDrawObject(CDrawObject*);

		// ** Glut callbacks **

		/** Any animation drawing code can be run in the onRender method. */
		void onRender();

		/** Called when the window dimensions change.
			@param width - the width of the window in pixels
			@param height - the height of the window in pixels
        */
		void onReshape(int width, int height);

		/** Called when the mouse buttons are pressed. 
			@param button - the mouse buttons
			@param state - the state of the buttons
			@param x - the x coordinate
			@param y - the y coordinate
        */
		void onMouseButtonPress(int button, int state, int x, int y);

		/** Called when the mouse moves on the screen.
			@param x - the x coordinate
			@param y - the y coordinate
        */
		void onMouseMove(int x, int y);

		/** The keyboard function is called when a standard key is pressed down.
            @param key - the key press
            @param x - the x coordinate of the mouse
            @param y - the y coordinate of the mouse
        */
        virtual void onKeyboardDown( unsigned char key, int x, int y );
                
        /** The keyboard function is called when a standard key is "unpressed".
            @param key - the key press
            @param x - the x coordinate of the mouse
            @param y - the y coordinate of the mouse
        */
        virtual void onKeyboardUp( unsigned char key, int x, int y );
                
        /** The keyboard function is called when a special key is pressed down.
            (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys) 
            http://www.opengl.org/resources/libraries/glut/spec3/node54.html
            @param key - the key press
            @param x - the x coordinate of the mouse
            @param y - the y coordinate of the mouse
        */
        virtual void onSpecialKeyboardDown( int key, int x, int y );
                
        /** The keyboard function is called when a special key is "unpressed.
            (F1 keys, Home, Inser, Delete, Page Up/Down, End, arrow keys) 
            @param key - the key press
            @param x - the x coordinate of the mouse
            @param y - the y coordinate of the mouse
        */
        virtual void onSpecialKeyboardUp( int key, int x, int y ); 

		void run();
		void init();

		// ** Static members using as glut callback **
		static void renderWrapper();
		static void reshapeWrapper(int width, int height);
		static void runWrapper();
		static void mouseButtonPressWrapper(int button, int state, int x, int y);
		static void mouseMoveWrapper(int x, int y);
		static void keyboardDownWrapper(unsigned char key, int x, int y);
		static void keyboardUpWrapper(unsigned char key, int x, int y);
		static void specialKeyboardDownWrapper(int key, int x, int y);
		static void specialKeyboardUpWrapper(int key, int x, int y);
};