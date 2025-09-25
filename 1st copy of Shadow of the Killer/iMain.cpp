

#include "iGraphics.h"
#include "menu.hpp"
#include "level1.hpp"
#include "level2.hpp"
#include "level3.hpp"
#include "level4.hpp"

#include "Utils.hpp"


#include <iostream>
using namespace std;



//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

GameState currentState = MENU;
// Forward declaration of level4Initialize
void level4Initialize(); // Declare here so main can see it

void iDraw()
{
	iClear();
	if (currentState == MENU) drawMenu();
	else if (currentState == LEVEL1) drawLevel1();
	else if (currentState == LEVEL2) drawLevel2();
	else if (currentState == LEVEL3) drawLevel3();
	else if (currentState == LEVEL4) drawLevel4();
}

/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
	
}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	if (currentState == MENU) MenuPassiveMouseMove(mx, my);
	else if (currentState == LEVEL2) level2PassiveMouseMove(mx, my);	
	else if (currentState == LEVEL3) level3PassiveMouseMove(mx, my); 
	else if (currentState == LEVEL4) level4PassiveMouseMove(mx, my);

}

void iMouse(int button, int state, int mx, int my)
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (currentState == MENU) MenuMouse(button, state, mx, my);
		if (currentState == LEVEL1)MenuMouse(button, state, mx, my);                        //don't change menuMouse
		if (currentState == LEVEL1)level1Mouse(button, state, mx, my);
		if (currentState == LEVEL2)level2Mouse(button, state, mx, my);
		if (currentState == LEVEL3)level3Mouse(button, state, mx, my);
		if (currentState == LEVEL4)level4Mouse(button, state, mx, my);
		

		
	}
	
	
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


void iKeyboard(unsigned char key)
{
	if (key == 27) { // ESC key
		if (currentState == MENU && AboutPage==0) {
			exit(0);			
			return; 
		}
		else {
			
			isPauseMenuActive = !isPauseMenuActive;
		}
	}
	if (currentState == LEVEL1) level1Keyboard(key);
	else if (currentState == LEVEL2) level2Keyboard(key);
	else if (currentState == LEVEL3) level3Keyboard(key);
	else if (currentState == LEVEL4) level4Keyboard(key);

	
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (currentState == LEVEL1) level1SpecialKeyboard(key);
	else if (currentState == LEVEL2) level2SpecialKeyboard(key);
	else if (currentState == LEVEL3) level3SpecialKeyboard(key);
	else if (currentState == LEVEL4) level4SpecialKeyboard(key);
	
}


int main()
{

	iInitialize(screenWidth, screenHeight, "Shadow of the Killer");
	Menumain();

	level1main();
	funmain();
	level2main();
	level3Initialize();
	level4Initialize();
	iStart();
	return 0;
}