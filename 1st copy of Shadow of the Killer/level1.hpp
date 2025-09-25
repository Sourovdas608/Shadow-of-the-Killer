#ifndef LEVEL1_H
#define LEVEL1_H
#include "Utils.hpp"
#include "music.hpp"
#include "menu.hpp"
#include <string.h>
#include<stdio.h>
#include <iostream>
using namespace std;

int newscreenWidth = 850;

int cluecount = 0;


int characterHeight = 84;
int characterWidth = 70;
int charX = 350, charY = 100;

int newX = charX, newY = charY;


int currentFrame = 0;
int totalFrames = 4;

int activeClueIndex = -1; // Tracks which clue is near and clickable
//bool showClueText = false;

//==========================================================================================================




//===================================================================
//--------------------------------------------side room------------------------------------------

// --- NEW: room state ---
int activeRoom = 0;  // 0 = default main room, 1..4 = others

// preview positions (stack vertically right side)
int roomPreviewX = screenWidth - roomThumbW; // stick to right edge
int roomPreviewYStart = screenHeight - roomThumbH; // start near top
int roomPreviewGap = 0;



struct RoomPreview {
	int x, y;
	int w, h;
	const char* image;
};



RoomPreview previews[numRooms] = {

	{ 0, 0, roomThumbW, roomThumbH, "image\\room\\readingroom_preview.bmp" },
	{ 0, 0, roomThumbW, roomThumbH, "image\\room\\livingroom_preview.bmp" },
	{ 0, 0, roomThumbW, roomThumbH, "image\\room\\kitchen_preview.bmp" },
	{ 0, 0, roomThumbW, roomThumbH, "image\\room\\bedroom_preview.bmp" }
};


char* roomImages[numRooms] = {

	(char*)"image\\room\\readingroom.bmp",
	(char*)"image\\room\\livingroom.bmp",
	(char*)"image\\room\\kitchen.bmp",
	(char*)"image\\room\\bedroom.bmp",

};
//------------------------------------------------------------------------------------------------------------


// Each room’s obstacle set
vector<Obstacle> roomObstacles[numRooms] = {
	// Room 0 (main room)
	{
		{ 148, 455, 232, 455 }, //table
		{ 232, 455, 236, 529 },   // chair
		{ 232, 455, 236, 529 },
		{ 271, 481, 399, 483 },
		{ 432, 487, 592, 485 },
		{ 596, 465, 595, 416 },
		{ 687, 422, 684, 244 },
		{ 686, 241, 617, 242 },
		{ 617, 239, 615, 125 },
		{ 618, 124, 695, 102 },
		{ 683, 103, 687, 30 },
		{ 687, 33, 191, 29 },
		{ 264, 85, 221, 143 },
		{ 210, 152, 138, 126 },
		{ 144, 123, 150, 193 },
		{ 134, 200, 132, 267 },
		{ 135, 267, 221, 266 },
		{ 134, 266, 218, 269 },
		{ 224, 270, 229, 357 },
		{ 226, 369, 205, 384 },
		{ 201, 383, 131, 384 },
		{ 135, 457, 131, 387 },
		{ 262, 77, 190, 31 },
		{ 600, 408, 683, 413 },
		{ 360, 462, 406, 474 },
		{ 404, 472, 450, 461 },
		{ 459, 460, 461, 394 },
		{ 362, 461, 361, 394 },
		{ 253, 391, 359, 395 },
		{ 254, 392, 544, 392 },
		{ 544, 392, 546, 282 },
		{ 546, 282, 254, 282 },
		{ 254, 282, 253, 389 }


	},

		// Room 1
	{
		//{ 301, 376, 519, 376 },
		{ 519, 364, 301, 362 },
		{ 521, 203, 299, 202 },
		{ 299, 202, 301, 362 },
		{ 519, 362, 521, 203 },
		{ 521, 203, 299, 202 },
		{ 299, 202, 301, 362 },
		{ 635, 408, 623, 351 },
		{ 623, 351, 625, 142 },
		{ 625, 142, 718, 142 },
		{ 718, 142, 703, 126 },
		{ 703, 126, 701, 52 },
		{ 702, 40, 294, 38 },
		//{ 699, 55, 294, 38 },
		//703 37 298 39
		{ 722, 412, 717, 560 },
		{ 717, 560, 511, 566 },
		{ 511, 566, 509, 563 },
		{ 509, 563, 499, 515 },
		{ 499, 515, 296, 507 },
		{ 296, 507, 295, 454 },
		{ 295, 454, 197, 395 },
		{ 197, 395, 120, 511 },
		{ 120, 511, 117, 54 },
		{ 167, 113, 236, 196 },
		{ 236, 196, 327, 115 },
		{ 327, 115, 288, 54 },
		//{ 288, 54, 699, 52 },
		{ 631, 400, 721, 399 },
		{ 315, 169, 505, 168 },
		{ 156, 107, 217, 38 }


	},

		// Room 2
	{
		{ 128, 389, 313, 387 },
		{ 313, 387, 318, 437 },
		{ 318, 437, 567, 437 },
		{ 567, 437, 620, 422 },
		{ 620, 422, 730, 426 },
		{ 730, 426, 759, 391 },
		{ 759, 391, 843, 390 },
		{ 843, 390, 845, 35 },
		{ 845, 35, 110, 34 },
		{ 110, 34, 116, 94 },
		{ 116, 94, 206, 98 },
		{ 206, 98, 214, 227 },
		{ 214, 227, 1, 282 },
		{ 171, 282, 122, 288 },
		{ 122, 288, 128, 387 },
		{ 408, 350, 692, 352 },
		{ 692, 352, 691, 175 },
		{ 691, 175, 662, 141 },
		{ 662, 141, 438, 144 },
		{ 438, 144, 413, 179 },
		{ 413, 179, 407, 350 }

	},

		// Room 3
	{
		{ 131, 431, 284, 430 },
		{ 300, 436, 362, 435 },
		{ 374, 450, 371, 255 },
		{ 374, 254, 586, 252 },
		{ 598, 311, 584, 457 },
		{ 594, 438, 658, 438 },
		{ 683, 438, 697, 332 },
		{ 697, 332, 678, 331 },
		{ 678, 331, 657, 261 },
		{ 657, 261, 668, 190 },
		{ 687, 166, 666, 114 },
		{ 666, 114, 673, 54 },
		{ 679, 30, 54, 28 },
		{ 59, 56, 79, 179 },
		{ 79, 179, 176, 169 },
		{ 176, 169, 199, 318 },
		{ 199, 318, 183, 374 },
		{ 183, 374, 112, 376 },
		{ 112, 376, 126, 429 },
		{ 373, 140, 373, 52 },
		{ 373, 52, 522, 49 },
		{ 522, 49, 520, 139 },
		{ 520, 142, 372, 141 }

	},

};


// Updated collision detection
bool isCollidingLine(int newX, int newY) {
	int radius = 18;   //changed from 20
	for (const auto& obs : roomObstacles[activeRoom]) {
		int x1 = obs.x1, y1 = obs.y1;
		int x2 = obs.x2, y2 = obs.y2;

		double dx = x2 - x1, dy = y2 - y1;
		double len2 = dx*dx + dy*dy;
		if (len2 == 0) continue;

		double t = ((newX - x1)*dx + (newY - y1)*dy) / len2;
		if (t < 0) t = 0; else if (t > 1) t = 1;

		double px = x1 + t*dx;
		double py = y1 + t*dy;

		double dist2 = (newX - px)*(newX - px) + (newY - py)*(newY - py);
		if (dist2 < radius * radius) return true;
	}
	return false;
}
//----------------------------------------------------------------------------------------------------------

// Walking frames for right
char *walkFrames[] = {
	"paint\\right1.bmp",
	"paint\\right2.bmp",
	"paint\\right3.bmp",
	"paint\\right4.bmp",

};

// Walking frames for left
char *backwalkFrames[] = {
	"paint\\left1.bmp",
	"paint\\left2.bmp",
	"paint\\left3.bmp",
	"paint\\left4.bmp",
};


char *upwalkFrames[] = {
	"paint\\up1.bmp",
	"paint\\up2.bmp",

};

char *downwalkFrames[] = {
	"paint\\down1.bmp",
	"paint\\down2.bmp",

};



char currentImage[20] = "paint\\front.bmp"; // Start with walk1

char direction = 'r'; // r = right/left, u = up, d = down



//---------------------------------------------------------------------------------------



//--------------------------------clues-----------------------------------------------------------------

//723 373
Clue clues[12] = {
	{ 498, 386, 50, 30, false, "Desk drawers in a mess" },//1
	{ 685, 400, 60, 50, false, "Locked Windows" },			//2
	{ 510, 477, 70, 40, false, "Broken glasses" },			//3
	{ 414, 427, 80, 40, false, "Overturned chair" },		//4				//study
	{ 420, 235, 70, 50, false, "Replica ritual weaponss" },	//6
	{ 545, 531, 70, 40, false, "Glass case cracked" },         //7   


	{ 414, 332, 90, 40, false, "Two Glasses of water" },	//5
	{ 493, 226, 70, 90, false, "Threat Letter" },			//9	             //(Living room Dustbin).
	{ 682, 428, 70, 10, false, "Faint smell of incense" },  //10    


	{ 814, 451, 90, 40, false, "Two plates in the sink" },	//8
	{ 197, 464, 90, 40, false, "Old Interview Mug" },		//11	//(kitchen


	{ 737, 389, 70, 40, false, "Car Seen Near Kane’s House" }	//12   //(Bedroom Window)
};




// ---------------------------------- Slideshow Images ---------------------------------
int slideIndex = 0;
const int totalSlides = 6;

char* slideImages[totalSlides] = {
	(char*)"image\\newstory\\Cut1.bmp",
	(char*)"image\\newstory\\Cut2.bmp",
	(char*)"image\\newstory\\Cut3.bmp",
	(char*)"image\\newstory\\Cut4.bmp",
	(char*)"image\\newstory\\Cut5.bmp",
	(char*)"image\\newstory\\Cut6.bmp"
};

//---------------------------------------------------------------------------------------
int slide2Index = 0;
const int totalSlides2 = 3;


char* slide2Images[totalSlides2] = {
	(char*)"image\\newstory\\Cut7.bmp",
	(char*)"image\\newstory\\Cut8.bmp",
	(char*)"image\\newstory\\Cut9.bmp"
};


//--------------------------------------------------------------------------------------

bool isNearClue(int clueX, int clueY, int threshold = 100) {
	int dx = charX - clueX;
	int dy = charY - clueY;
	return (dx * dx + dy * dy) <= (threshold * threshold);
}


void drawNearbyClues(int startIndex, int endIndex, int radius) {
	activeClueIndex = -1;
	for (int i = startIndex; i < endIndex; i++) {
		if (!clues[i].found && isNearClue(clues[i].x, clues[i].y)) {
			iSetColor(150, 0, 0);
			iCircle(clues[i].x, clues[i].y, radius);
			activeClueIndex = i;
		}
	}
}


void drawLevel1(){
	if (isPauseMenuActive) {
		drawPauseMenu();
		return; // Skip drawing the game when paused
	}

	if (isSlideshowActive) {
		iShowBMP(0, 0, slideImages[slideIndex]);
		return;
	}
	else if (isSlideshow2Active) {
		iShowBMP(0, 0, slide2Images[slide2Index]);
		return;
	}


	//   background

	iShowBMP(0, 0, roomImages[activeRoom]);



	iShowBMP2(charX, charY, currentImage, 0xFFFFFF);
	//----------------------------------------------------------------------------------------
	// --- draw room previews (stacked on right side) ---
	for (int i = 0; i < numRooms; i++) {
		previews[i].x = screenWidth - roomThumbW;   // right margin
		previews[i].y = screenHeight - (i + 1) * (roomThumbH); // stack from top

		iShowBMP(previews[i].x, previews[i].y, (char*)previews[i].image);
		iRectangle(previews[i].x, previews[i].y, previews[i].w, previews[i].h);
	}



	// draw notepad on right side
	iSetColor(222, 184, 135);
	iFilledRectangle(notePadX, notePadY, notePadW, notePadH);
	iSetColor(0, 0, 0);
	iText(notePadX + 20, notePadY + notePadH - 40, "Notes:", GLUT_BITMAP_HELVETICA_18);

	//----------------------------------------------------------------------------------------
	// draw obstacles of current room
	iSetColor(255, 0, 0);
	for (const auto& obs : roomObstacles[activeRoom]) {
		//iLine(obs.x1, obs.y1, obs.x2, obs.y2);
	}


	//---------------------------------iDraw------------------------------------------------------
	
	

	if (activeRoom == 0) {
		drawNearbyClues(0, 6, 15);
	}
	else if (activeRoom == 1) {
		drawNearbyClues(6, 9, 15);
	}
	else if (activeRoom == 2) {
		drawNearbyClues(9, 11, 20);
	}
	else if (activeRoom == 3) {
		drawNearbyClues(11, 12, 15);

	}


	// Optional message when clue is found
	for (int i = 0; i < 12; i++) {
		if (clues[i].found) {
			iSetColor(155, 0, 0);
			// Display found clue names on the left side of the screen
			iText(notePadX + 20, (240 - (i * 20)), (char*)clues[i].name);

		}
	}
	
	//---------------------------------------------28-8-25------------------------------------------


	//---------------------------------------------------------------------------------------

}

void updateWalkFrame() {
	currentFrame = (currentFrame + 1) % totalFrames;
	strcpy_s(currentImage, sizeof(currentImage), walkFrames[currentFrame]);
}

void updatebackWalkFrame() {
	currentFrame = (currentFrame + 1) % totalFrames;
	strcpy_s(currentImage, sizeof(currentImage), backwalkFrames[currentFrame]);
}
//--------------------------------------------------------------------------------*------------------
void updatedownWalkFrame() {
	currentFrame = (currentFrame + 1) % 2;
	strcpy_s(currentImage, sizeof(currentImage), downwalkFrames[currentFrame]);
}

void updateupWalkFrame() {
	currentFrame = (currentFrame + 1) % 2;
	strcpy_s(currentImage, sizeof(currentImage), upwalkFrames[currentFrame]);
}
//--------------------------------------------------------------------------------------------------


void characterBoundary() {
	if (charX < 0) charX = 0;
	if (charY < 0) charY = 0;
	if (charX + characterWidth > newscreenWidth)
		charX = newscreenWidth - characterWidth;
	if (charY + characterHeight > screenHeight)
		charY = screenHeight - characterHeight;
}



/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/


void level1MouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void level1PassiveMouseMove(int mx, int my)
{

}

void level1Mouse(int button, int state, int mx, int my)
{
	//------------------------------Clue--------------------------------------

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (activeClueIndex != -1) {
			int clueX = clues[activeClueIndex].x;
			int clueY = clues[activeClueIndex].y;
			int dx = mx - clueX;
			int dy = my - clueY;
			if (dx * dx + dy * dy <= 15 * 15) {
				//clues[activeClueIndex].found = true;
				if (!clues[activeClueIndex].found) { // Only increment if clue was not already found
					clues[activeClueIndex].found = true;
					cluecount++; // Increment the counter here
					//printf("Clue found: %s at (%d, %d). Total clues found: %d\n", clues[activeClueIndex].name, mx, my, cluecount);
					//printf("Clue found: %s at (%d, %d)\n", clues[activeClueIndex].name, mx, my);


					//================================================================================

					// Call the function to store the clue in the file
					storeClueInFile(clues[activeClueIndex].name);
					//=========================================


					if (cluecount == 12) { // When 11 clues are found
						isSlideshow2Active = true; // Activate the second slideshow
						slide2Index = 0; // Start from the beginning of the second slideshow
						clearFileAfterLevelCompletion();
					}
				}
			}
		}

		// Keep your room switching logic here
		for (int i = 0; i < numRooms; i++) {
			if (mx >= previews[i].x && mx <= previews[i].x + previews[i].w &&
				my >= previews[i].y && my <= previews[i].y + previews[i].h) {
				activeRoom = i;
				charX = 350, charY = 100;

			}
		}
	}




	//---------------------------------------------------------------------------------------

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//cout << mx << " " << my << endl;
		for (int i = 0; i < numRooms; i++) {
			if (mx >= previews[i].x && mx <= previews[i].x + previews[i].w &&
				my >= previews[i].y && my <= previews[i].y + previews[i].h) {
				activeRoom = i; // room index									//
			}
		}

	}




	//=====================end of level 1==================================================28-8-25============================



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if ((currentState = LEVEL1) && (slide2Index == 2) && (mx >= 375 && mx <= 723) && (my >= 320 && my <= 388)){
		//	cout << "working";
			currentState = LEVEL2;
			clearFileAfterLevelCompletion();                      // for clear clue from text file

		}
		else if ((slide2Index == 2) && (mx >= 375 && mx <= 723) && (my >= 234 && my <= 300)){
			playClickSound();
			HomePage = 1;
			StartPage1 = 0;
			AboutPage = 0;
			MutePage = 0;
			isPauseMenuActive = false;
			currentState = MENU;
			return;



		}

	}








	//==========================================================================================================


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/

void level1Keyboard(unsigned char key) {
	int newX = charX, newY = charY;  // start from current position

	if (key == 'p') {
		isSlideshowActive = !isSlideshowActive;
		slideIndex = 0;
	}

	if (key == 'o') {  // toggle slideshow2
		isSlideshow2Active = true;
		slide2Index = 0;
	}

	if (key == 'd') {
		newX += 10;
		updateWalkFrame();
	}
	else if (key == 'a') {
		newX -= 10;
		updatebackWalkFrame();
	}
	else if (key == 'w') {
		newY += 10;
		updateupWalkFrame();
	}
	else if (key == 's') {
		newY -= 10;
		updatedownWalkFrame();
	}
	if (key == 'n') {   // Go to next level
		currentState = LEVEL2;
	}
	/*
	if (key == ' ') {
	PlaySound("music\\click.wav", NULL, SND_ASYNC);

	}
	*/
	if (key == 'q') {   // Press Q to go to LEVEL3
		currentState = LEVEL3;
	}
	if (key == 'w') {   // Press Q to go to LEVEL3
		currentState = LEVEL4;
	}


	//===============================================================================================================================================================

	// only commit if no collision
	if (!isCollidingLine(newX, newY)) {
		charX = newX;
		charY = newY;
	}

	characterBoundary();
}


void level1SpecialKeyboard(unsigned char key) {
	int newX = charX, newY = charY;

	if (isSlideshowActive) {
		if (key == GLUT_KEY_RIGHT) {
			playClickSound2();
			slideIndex++;
			if (slideIndex >= totalSlides) {
				slideIndex = 0;
				isSlideshowActive = false;
			}
		}
		else if (key == GLUT_KEY_LEFT) {
			playClickSound2();
			slideIndex--;
			if (slideIndex < 0) slideIndex = 0;
		}
	}
	if (isSlideshow2Active) {
		if (key == GLUT_KEY_RIGHT) {
			playClickSound2();
			slide2Index++;
			if (slide2Index >= totalSlides2) {
				slide2Index = 2;
				//isSlideshow2Active = false; // end slideshow2
			}
		}
		else if (key == GLUT_KEY_LEFT) {
			playClickSound2();
			slide2Index--;
			if (slide2Index < 0) {
				slide2Index = 0;
			}
		}
	}
	else {
		if (key == GLUT_KEY_RIGHT) {
			newX += 10;
			updateWalkFrame();
		}
		else if (key == GLUT_KEY_LEFT) {
			newX -= 10;
			updatebackWalkFrame();
		}
		else if (key == GLUT_KEY_UP) {
			newY += 10;
			updateupWalkFrame();
		}
		else if (key == GLUT_KEY_DOWN) {
			newY -= 10;
			updatedownWalkFrame();
		}

		if (!isCollidingLine(newX, newY)) {
			charX = newX;
			charY = newY;
		}
		characterBoundary();
	}
}
//-----------------------------------------------------------------------------28-8-258-------------------------



//-----------------------------------------------------------------------------------------------------------------


int level1main() {

	playBackgroundMusic1();

	return 0;
}

#endif