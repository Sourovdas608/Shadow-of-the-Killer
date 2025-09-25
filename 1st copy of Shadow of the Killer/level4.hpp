#ifndef LEVEL4_H
#define LEVEL4_H

#include "Utils.hpp"
#include "music.hpp"
#include "menu.hpp"
#include <string> // For std::string


struct Suspect {
	int x, y, width, height;
	const char* name;
	const char* message;
	int id;
};

Suspect level4Suspects[] = {
	{ 140, 300, 200, 300, "Journalist", "Investigate the Journalist's notes.", 0 },
	{ 450, 300, 200, 300, "Deborah", "Question Deborah about her alibi.", 1 },
	{ 760, 300, 200, 300, "Father Elias", "Speak to Father Elias about the confession.", 2 }
};
const int NUM_LEVEL4_SUSPECTS = sizeof(level4Suspects) / sizeof(level4Suspects[0]);

int hoveredSuspectIndex = -1; 
const int CORRECT_SUSPECT_ID = 0;

// Level 4 Game State
enum Level4State {
	GUESSING,
	SHOWING_CORRECT_IMAGE, 
	SHOWING_GAMEOVER_IMAGE 
};
Level4State currentLevel4State = GUESSING;


int correctImageId = -1;
int gameOverImageId = -1;

void level4Initialize() {

	if (correctImageId == -1) { 
		correctImageId = iLoadImage("correct.bmp");
	}
	if (gameOverImageId == -1) { 
		gameOverImageId = iLoadImage("gameover.bmp");
	}

	currentLevel4State = GUESSING;
	hoveredSuspectIndex = -1;
}


void drawLevel4() {
	iClear();
	if (isPauseMenuActive) { 
		drawPauseMenu();     
		return;              
	}
	if (currentLevel4State == GUESSING) {
		iShowBMP(0, 0, "final.bmp"); 


		iSetColor(255, 255, 255);
		iText(screenWidth / 2 - 200, 70, "Press the corresponding number (1, 2, or 3) to select the culprit", GLUT_BITMAP_HELVETICA_12);


		if (hoveredSuspectIndex != -1) {
			iSetColor(255, 255, 0);

			// suspect name
			int nameTextWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)level4Suspects[hoveredSuspectIndex].name);
			iText((screenWidth - nameTextWidth) / 2, 140, (char*)level4Suspects[hoveredSuspectIndex].name, GLUT_BITMAP_TIMES_ROMAN_24);

			//suspect message
			// 
			const char* currentSuspectMessage = level4Suspects[hoveredSuspectIndex].message;
			int messageTextWidth = glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)currentSuspectMessage);
			iText((screenWidth - messageTextWidth) / 2, 105, (char*)currentSuspectMessage, GLUT_BITMAP_HELVETICA_18);
		}
	}
	else if (currentLevel4State == SHOWING_CORRECT_IMAGE) {
		if (correctImageId != -1) {
			iShowImage(0, 0, screenWidth, screenHeight, correctImageId);
		}
		
		iSetColor(255, 255, 255);
		iText(screenWidth / 2 - 150, 30, "Press 'M' for Main Menu or 'R' to restart", GLUT_BITMAP_HELVETICA_18);
	}
	else if (currentLevel4State == SHOWING_GAMEOVER_IMAGE) {
		if (gameOverImageId != -1) {
			iShowImage(0, 0, screenWidth, screenHeight, gameOverImageId);
		}
	
		iSetColor(255, 255, 255);
		iText(screenWidth / 2 - 150, 38, "Press 'M' for Main Menu or 'R' to try again", GLUT_BITMAP_HELVETICA_18);
	}
}


void level4PassiveMouseMove(int mx, int my) {
	if (currentLevel4State == GUESSING) {
		hoveredSuspectIndex = -1; // 
		for (int i = 0; i < NUM_LEVEL4_SUSPECTS; ++i) {
			
			if (mx >= level4Suspects[i].x && mx <= level4Suspects[i].x + level4Suspects[i].width &&
				my >= level4Suspects[i].y && my <= level4Suspects[i].y + level4Suspects[i].height) {
				hoveredSuspectIndex = i;
				break; 
			}
		}
	}
}


void level4Mouse(int button, int state, int mx, int my) {
	
	if (isPauseMenuActive && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	//	printf("Mouse clicked at: (%d, %d)\n", mx, my);


		// Exit button
		if (mx >= 388 && mx <= 709 &&
			my >= 235 && my <= 302) {
			playClickSound();
			HomePage = 1;
			StartPage1 = 0;
			AboutPage = 0;
			MutePage = 0;
			isPauseMenuActive = false;
			currentState = MENU;

			return; // 
		}

		// Resume button
		if (mx >= 389 && mx <= 710 &&
			my >= 319 && my <= 385) {
			playClickSound();
			isPauseMenuActive = false;
			return; // 
		}
	}


	//==============================================================================================================
	if (currentLevel4State == GUESSING && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < NUM_LEVEL4_SUSPECTS; ++i) {
			if (mx >= level4Suspects[i].x && mx <= level4Suspects[i].x + level4Suspects[i].width &&
				my >= level4Suspects[i].y && my <= level4Suspects[i].y + level4Suspects[i].height) {

				if (level4Suspects[i].id == CORRECT_SUSPECT_ID) {
					currentLevel4State = SHOWING_CORRECT_IMAGE;
					playClickSound(); // Play a positive sound
				}
				else {
					currentLevel4State = SHOWING_GAMEOVER_IMAGE;
				
				}
				break; 
			}
		}
	}

	if (currentLevel4State == SHOWING_CORRECT_IMAGE && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		if (mx >= 459 && mx <= 648 && my >= 223 && my <= 290) {
			
			exit(0);

		}
	}

}


void level4Keyboard(unsigned char key) {
	if (currentLevel4State == GUESSING) {
		
		int selectedIndex = -1;
		if (key == '1' && NUM_LEVEL4_SUSPECTS > 0) {
			selectedIndex = 0;
		}
		else if (key == '2' && NUM_LEVEL4_SUSPECTS > 1) {
			selectedIndex = 1;
		}
		else if (key == '3' && NUM_LEVEL4_SUSPECTS > 2) {
			selectedIndex = 2;
		}

		if (selectedIndex != -1) {
			if (level4Suspects[selectedIndex].id == CORRECT_SUSPECT_ID) {
				currentLevel4State = SHOWING_CORRECT_IMAGE;
				playClickSound();
			}
			else {
				currentLevel4State = SHOWING_GAMEOVER_IMAGE;
			
			}
		}
	}
	else if (currentLevel4State == SHOWING_CORRECT_IMAGE || currentLevel4State == SHOWING_GAMEOVER_IMAGE) {
		if (key == 'R' || key == 'r') {
			level4Initialize(); 
		}
		else if (key == 'M' || key == 'm') {
			currentState = MENU;
			level4Initialize();
			
		}
	}

	 
}


void level4SpecialKeyboard(unsigned char key) {
	
}

#endif