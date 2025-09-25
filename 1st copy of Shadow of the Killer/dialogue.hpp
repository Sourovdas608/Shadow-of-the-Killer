#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include "iGraphics.h"

// dialogue state
int dialogueIndex = 0;
const int totalDialogues = 6;
int dialogueImages[totalDialogues];
bool isDialogueActive = true;

// load dialogue assets
void loadDialogues() {
	dialogueImages[0] = iLoadImage("Cut1.bmp");
	dialogueImages[1] = iLoadImage("Cut2.bmp");
	dialogueImages[2] = iLoadImage("Cut3.bmp");
	dialogueImages[3] = iLoadImage("Cut4.bmp");
	dialogueImages[4] = iLoadImage("Cut5.bmp");
	dialogueImages[5] = iLoadImage("Cut6.bmp");
}

// draw dialogue cutscene
void drawDialogue() {
	if (dialogueIndex >= 0 && dialogueIndex < totalDialogues) {
		iShowImage(0, 0, 1100, 700, dialogueImages[dialogueIndex]);
	}
}

// handle mouse for dialogue
void dialogueMouseHandler(int button, int state, int mx, int my) {
	if (!isDialogueActive) return;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (dialogueIndex < totalDialogues - 1) {
			dialogueIndex++;
		}
		else {
			isDialogueActive = false;   // finished
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (dialogueIndex > 0) dialogueIndex--;
	}
}

// handle keyboard for dialogue
void dialogueKeyHandler(int key) {
	if (!isDialogueActive) return;

	if (key == GLUT_KEY_RIGHT) {
		if (dialogueIndex < totalDialogues - 1) dialogueIndex++;
		else isDialogueActive = false;
	}
	if (key == GLUT_KEY_LEFT && dialogueIndex > 0) {
		dialogueIndex--;
	}
}

#endif
