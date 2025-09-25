#ifndef LEVEL2_H
#define LEVEL2_H
#include "level4.hpp"
#include "Utils.hpp"
#include "music.hpp"
#include "menu.hpp"
#include <string.h>
#include <stdio.h> // For sprintf

#define W 1100 // Adjusted for consistent width
#define H 700 // Adjusted for consistent height
#define MAX_QUESTIONS_PER_SUSPECT 5
#define NUM_SUSPECTS 3

int nextLevelImage;
int showNextLevel = 0; // 0 = interrogation ongoing, 1 = show cutscene

// Dialogue panel dimensions
int panelX = 50;
int panelY = 20;
int panelW = 950;
int panelH = 220;

// Label dimensions
int labelW = 120;
int labelH = 30;

// Question box dimensions (relative to panel)
int qBoxHeight = 60;
int qBoxXPos = 200;
int qBoxWidth = 700; // panelW - 260;

// Answer box dimensions (relative to panel)
int ansBoxX = 200;
int ansBoxY = 35; // Adjusted for better vertical centering
int ansBoxWidth = 700;
int ansBoxHeight = 180; // Adjusted for better vertical centering

// Game state variables
int hoverQuestion = -1; // Which question is hovered (0, 1, or 2)
int hoverAnswer = 0;    // Whether answer box is hovered
int hoverNextButton = 0; // Whether the next person button is hovered

int mode = 0; // 0 for questions, 1 for answer
int selectedIndex = -1; // Index in the specific suspect's questionsAll array
int visibleQuestionIndices[3]; // Indices of questions currently displayed (0-4 for each suspect)
int nextQuestionToDisplay = 3; // Index of the next question to show when one is answered
int questionsAnsweredCount[NUM_SUSPECTS] = { 0 }; // How many questions have been answered for each suspect

int bgImage[NUM_SUSPECTS]; // Array for background images
char *suspectNames[NUM_SUSPECTS] = { "Father Elias", "Journalist", "Deborah" };
int currentSuspect = 0; // 0: Father Elias, 1: Journalist, 2: Deborah

// Master arrays for all questions and answers
char *allQuestions[NUM_SUSPECTS][MAX_QUESTIONS_PER_SUSPECT] = {
	// Father Elias (Suspect 0)
	{
		"A threat note was found in Kane's trash. Matches your handwriting. Care to explain, Father?",
		"We also found a cassock in your quarters. Blood on the sleeve. What am I supposed to make of that?",
		"Funny thing, Father. Kane's killer lit candles like a ritual. Would you ever defile sacred rites that way?",
		"Parish records put you at a community dinner that same night. Any reason witnesses would lie for you?",
		"Your parishioners said you've been distant, losing sleep. Sounds like guilt, Father?"
	},
	// Journalist (Suspect 1) - Renamed from 'Suspect' for clarity
	{
		"Why did you have Professor Kane's home address in your notebook?",
		"Care to explain how you ended up drinking with a man who humiliated you?",
		"Witnesses place you near his home the night of the murder. What were you doing there?",
		"Kane taught that all religion was myth. Were you protecting your beat... or silencing the competition?",
		"You say you were following a lead on one of Kane's colleagues. Which one?"
	},
	// Deborah (Suspect 2)
	{
		"Witnesses saw a car matching yours near Kane's house the night he died. Care to explain where you were?",
		"You're familiar with ceremonial daggers - Kane was stabbed with precision. Doesn't that point straight to you?",
		"Neighbors say they heard a woman's voice reciting scripture near Kane's study that night. Sound familiar?",
		"You and Kane... when was the last time you actually spoke face-to-face?",
		"You lecture online these days. You were streaming live during Kane's murder. Doesn't leave you much room, does it?"
	}
};

char *allAnswers[NUM_SUSPECTS][MAX_QUESTIONS_PER_SUSPECT] = {
	// Father Elias Answers
	{
		"Yes, I wrote it. In anger, after he mocked the Church at our last debate.\n"
		"But it was a warning, not a death sentence. Words born of frustration,\n"
		"nothing more.",

		"I tend the sick, Detective. I comfort the dying. That blood came from a\n"
		"parishioner I helped after an accident - not from Kane. Test it, and\n"
		"you'll see. Truth doesn't fear evidence.",

		"Never. That was no Christian ritual. It was mockery. Whoever staged it knew\n"
		"just enough to twist the holy into something grotesque. That's not my hand.",

		"No reason. Ask them yourself. I was there, ladling soup and blessing bread\n"
		"until the candles burned low. I could not have slipped away unnoticed -\n"
		"not in a hall full of eyes.",

		"I've been losing sleep, yes - but not over Kane. My parish is struggling,\n"
		"families in need, debts piling high. Guilt, yes... but not the kind you speak of."
	},
	// Journalist Answers
	{
		"I track everyone I cover-their academics and political views.\n"
		"Kane was another source. You can't expose corruption if you don't\n"
		"know where the players live. Doesn't mean I killed him.",

		"He invited me. Said he could \"set me straight.\" We argued over wine.\n"
		"He drank; I listened. I left before things got ugly. If there was a mug,\n"
		"he didn't bother washing it.",

		"I was following a lead on another story-one of his colleagues.\n"
		"I happened to pass by Kane's street. Bad timing. I wasn't lurking;\n"
		"I've got enough dirt to dig without peeking in windows.",

		"That's rich. He wasn't competition. He was material. A headline waiting\n"
		"to happen. If anything, I wanted him alive. His mouth brought me stories.\n"
		"Killing him would've killed my career too.",

		"Father Elias Monteiro. He's been on my radar-debts, whispers about him\n"
		"breaking vows. Kane's murder derailed that story, but I've still got\n"
		"the notes if you want to see them."
	},
	// Deborah Answers
	{
		"I drove past, yes. His house was on my way home from a speaking engagement.\n"
		"I had no reason to stop. If I'd wanted to kill him, I wouldn't have left\n"
		"my car out in the open.",

		"Knowledge isn't guilt. I've studied a hundred ways people once worshipped.\n"
		"Knowing how a thing is done doesn't mean I'd ever do it. If you found me\n"
		"with a scalpel, would you accuse me of surgery?",

		"Convenient, isn't it? A voice in the dark, faceless, nameless. It could've\n"
		"been anyone. Quoting scripture doesn't make it mine. Plenty of zealots twist\n"
		"verses into weapons.",

		"Three years ago, at a panel. He called me a fraud on stage. I never saw him\n"
		"again. If I had gone to his house, do you really think he'd have let me in?",

		"Exactly. Hundreds of viewers saw me live. Unless I've learned to split myself\n"
		"in two, I couldn't have been in Kane's study with a blade in my hand."
	}
};

void resetQuestionsForSuspect() {
	selectedIndex = -1;
	mode = 0; // Always start in question mode
	for (int i = 0; i < 3; i++) {
		visibleQuestionIndices[i] = i;
	}
	nextQuestionToDisplay = 3;
}

void drawMultilineText(int x, int yTop, const char *text, int lineGap, void* font) {
	char buf[2048];
	strncpy_s(buf, sizeof(buf), text, _TRUNCATE);
	buf[sizeof(buf)-1] = '\0';

	int lineY = yTop;
	char *context = nullptr;
	char *line = strtok_s(buf, "\n", &context);
	while (line != nullptr) {
		iText(x, lineY, line, font);
		lineY -= lineGap;
		line = strtok_s(nullptr, "\n", &context);
	}
}

void drawWrappedText(int x, int yTop, int maxWidth, const char* text, void* font) {
	char buf[2048];
	strncpy_s(buf, sizeof(buf), text, _TRUNCATE);
	buf[sizeof(buf)-1] = '\0';

	char *token, *context = nullptr;
	char line[512] = "";
	int lineY = yTop;

	token = strtok_s(buf, " ", &context);
	while (token != nullptr) {
		char temp[512];
		strcpy_s(temp, sizeof(temp), line);

		if (strlen(temp) > 0) strcat_s(temp, sizeof(temp), " ");
		strcat_s(temp, sizeof(temp), token);

		int textWidth = glutBitmapLength(font, (const unsigned char*)temp);

		if (textWidth > maxWidth) {
			iText(x, lineY, line, font);
			lineY -= 20; // line gap
			strcpy_s(line, sizeof(line), token);
		}
		else {
			strcpy_s(line, sizeof(line), temp);
		}

		token = strtok_s(nullptr, " ", &context);
	}
	if (strlen(line) > 0) {
		iText(x, lineY, line, font);
	}
}

int pointInBox(int mx, int my, int x, int y, int w, int h) {
	return (mx >= x && mx <= x + w && my >= y && my <= y + h);
}

void drawLevel2(){
	iClear();
	if (isPauseMenuActive) {
		drawPauseMenu();
		return;
	}
	if (showNextLevel) {

		iShowImage(0, 0, W, H, nextLevelImage);
		iSetColor(255, 255, 255);
		//iText(W / 2 - 80, 50, "Press ENTER to continue...", GLUT_BITMAP_HELVETICA_18);
		return; // Stop drawing interrogation elements
	}

	// Draw background first
	iShowImage(0, 0, W, H, bgImage[currentSuspect]);

	// Dialogue panel
	iSetColor(30, 30, 30);
	iFilledRectangle(panelX, panelY, panelW, panelH);
	iSetColor(255, 255, 255);
	iRectangle(panelX, panelY, panelW, panelH);

	// "Next Person" Button
	int nextButtonX = W - 150;
	int nextButtonY = H - 50;
	int nextButtonW = 120;
	int nextButtonH = 30;

	if (hoverNextButton) {
		iSetColor(100, 100, 255); // Highlighted color
	}
	else {
		iSetColor(50, 50, 150); // Darker blue
	}
	iFilledRectangle(nextButtonX, nextButtonY, nextButtonW, nextButtonH);
	iSetColor(255, 253, 208);
	iText(nextButtonX + 10, nextButtonY + 10, "Next Person", GLUT_BITMAP_HELVETICA_12);

	if (mode == 0) {
		// Detective label
		iSetColor(50, 50, 200);  // blue
		iFilledRectangle(panelX + 10, panelY + panelH - labelH - 10, labelW, labelH);
		iSetColor(255, 255, 255);
		iText(panelX + 20, panelY + panelH - labelH + 2, "Detective", GLUT_BITMAP_HELVETICA_18);

		// Questions
		int qY = panelY + panelH - 10;
		for (int s = 0; s < 3; s++) {
			if (visibleQuestionIndices[s] != -1) { // If this slot has a question

				// Hover effect
				if (hoverQuestion == s) {
					iSetColor(200, 200, 255); // light blue
				}
				else {
					iSetColor(245, 245, 245); // normal
				}
				iFilledRectangle(qBoxXPos, qY - qBoxHeight, qBoxWidth, qBoxHeight);

				// We'll keep the border for all visible questions to distinguish them
				iSetColor(0, 0, 0);
				iRectangle(qBoxXPos, qY - qBoxHeight, qBoxWidth, qBoxHeight);

				// Draw wrapped text
				drawWrappedText(qBoxXPos + 10, qY - 20, qBoxWidth - 20, allQuestions[currentSuspect][visibleQuestionIndices[s]], GLUT_BITMAP_9_BY_15);

				qY -= (qBoxHeight + 10);
			}
		}
	}
	else if (mode == 1 && selectedIndex >= 0) {
		// Suspect label
		iSetColor(200, 50, 50); // red
		iFilledRectangle(panelX + 10, panelY + panelH - labelH - 10, labelW, labelH);
		iSetColor(255, 255, 255);
		iText(panelX + 20, panelY + panelH - labelH + 2, suspectNames[currentSuspect], GLUT_BITMAP_HELVETICA_18);

		// Answer box
		// Hover effect
		if (hoverAnswer) {
			iSetColor(255, 230, 230); // light red
		}
		else {
			iSetColor(245, 245, 245); // normal
		}
		iFilledRectangle(ansBoxX, ansBoxY, ansBoxWidth, ansBoxHeight);

		// Glow effect when clicked
		iSetColor(0, 255, 255); // golden border
		for (int b = 0; b < 3; b++)
			iRectangle(ansBoxX - b, ansBoxY - b, ansBoxWidth + 2 * b, ansBoxHeight + 2 * b);

		iSetColor(0, 0, 150);
		int textStartY = ansBoxY + ansBoxHeight - 20;
		drawWrappedText(ansBoxX + 10, textStartY, ansBoxWidth - 20, allAnswers[currentSuspect][selectedIndex], GLUT_BITMAP_9_BY_15);

		// Add a prompt to click to continue
		iSetColor(50, 50, 50);
		iText(ansBoxX + 10, ansBoxY + 5, "Click anywhere on the answer to continue...", GLUT_BITMAP_HELVETICA_12);
	}
}

void level2MouseMove(int mx, int my) {
	// Empty implementation
}

void level2PassiveMouseMove(int mx, int my) {
	hoverQuestion = -1;
	hoverAnswer = 0;
	hoverNextButton = 0;

	// Only check for hovers if not showing next level screen
	if (!showNextLevel) {
		// Check for "Next Person" button hover
		int nextButtonX = W - 150;
		int nextButtonY = H - 50;
		int nextButtonW = 120;
		int nextButtonH = 30;
		if (pointInBox(mx, my, nextButtonX, nextButtonY, nextButtonW, nextButtonH)) {
			hoverNextButton = 1;
		}

		if (mode == 0) {
			int qY = panelY + panelH - 10;
			for (int s = 0; s < 3; s++) {
				if (visibleQuestionIndices[s] != -1) {
					if (pointInBox(mx, my, qBoxXPos, qY - qBoxHeight, qBoxWidth, qBoxHeight)) {
						hoverQuestion = s;
					}
				}
				qY -= (qBoxHeight + 10);
			}
		}
		else if (mode == 1) {
			if (pointInBox(mx, my, ansBoxX, ansBoxY, ansBoxWidth, ansBoxHeight)) {
				hoverAnswer = 1;
			}
		}
	}
}


void level2Mouse(int button, int state, int mx, int my) {

	//=================================================resume======================================================
	if (isPauseMenuActive && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
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
	// Check if we are on the "Next Level" image screen
	if (showNextLevel) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			//printf("Clicked on Next Level screen at: (%d, %d)\n", mx, my); // Still print for debugging

			if ((mx >= 383 && mx <= 725) && (my >= 320 && my <= 388)) {
			//	cout << "Transitioning to LEVEL3" << endl;
				currentState = LEVEL3; // Change to the next level (LEVEL3)
				// You might want to reset showNextLevel here if LEVEL3 doesn't handle it
				showNextLevel = 0;
			}

			else if ((mx >= 375 && mx <= 723) && (my >= 223 && my <= 300)) {
				//cout << "Exiting game from Next Level screen" << endl;
				//exit(0); // Exit the application
				// Or if you want to go to the main menu:
				playClickSound(); // Assuming you have this function available
				HomePage = 1;
				StartPage1 = 0;
				AboutPage = 0;
				MutePage = 0;
				isPauseMenuActive = false;
				currentState = MENU;
			}
		}
		return;
	}
	//cout << mx << " " << my << endl;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// "Next Person" Button Logic
		int nextButtonX = W - 150;
		int nextButtonY = H - 50;
		int nextButtonW = 120;
		int nextButtonH = 30;

		if (pointInBox(mx, my, nextButtonX, nextButtonY, nextButtonW, nextButtonH)) {
			if (currentSuspect < NUM_SUSPECTS - 1) {
				// Go to next suspect
				currentSuspect++;
				resetQuestionsForSuspect();
			}
			else {
				// All suspects done -> show next level cutscene
				showNextLevel = 1;
			}
			return; // Important: Return after handling button click
		}

		if (mode == 0) {
			// Detect question clicks
			int qY = panelY + panelH - 10;
			for (int s = 0; s < 3; s++) {
				if (visibleQuestionIndices[s] != -1) {
					if (pointInBox(mx, my, qBoxXPos, qY - qBoxHeight, qBoxWidth, qBoxHeight)) {
						selectedIndex = visibleQuestionIndices[s]; // Store the actual question index
						visibleQuestionIndices[s] = -1; // Mark this slot as answered
						questionsAnsweredCount[currentSuspect]++; // Increment answered questions for current suspect
						mode = 1; // Switch to show answer mode
						break;
					}
				}
				qY -= (qBoxHeight + 10);
			}
		}
		else if (mode == 1) { // Currently showing an answer
			// Close answer if clicked anywhere in the answer box area
			if (pointInBox(mx, my, ansBoxX, ansBoxY, ansBoxWidth, ansBoxHeight)) {
				// Find the first empty slot and fill it with the next question
				// Only if there are more questions for this suspect AND not all visible slots are filled
				if (nextQuestionToDisplay < MAX_QUESTIONS_PER_SUSPECT) {
					int filledSlot = 0;
					for (int s = 0; s < 3; s++) {
						if (visibleQuestionIndices[s] == -1) {
							visibleQuestionIndices[s] = nextQuestionToDisplay;
							nextQuestionToDisplay++;
							filledSlot = 1;
							break; // Only fill one slot
						}
					}
				}
				mode = 0; // Back to question mode
				selectedIndex = -1; // Reset selected index
			}
		}
	}
}

void level2Keyboard(unsigned char key) {
	if (showNextLevel && key == 13) { // ENTER key
		// This is where you'd transition to the actual next level or a win screen
	//	printf("Next level starting...\n");
		// For now, let's just exit or perhaps reset the game for a new round
		// exit(0);
		// Or if you have a "game over" or "victory" state, transition to that.
	}
	else if (!showNextLevel && mode == 1) {
		if (nextQuestionToDisplay < MAX_QUESTIONS_PER_SUSPECT) {
			int filledSlot = 0;
			for (int s = 0; s < 3; s++) {
				if (visibleQuestionIndices[s] == -1) {
					visibleQuestionIndices[s] = nextQuestionToDisplay;
					nextQuestionToDisplay++;
					filledSlot = 1;
					break; // Only fill one slot
				}
			}
		}
		mode = 0; // back to question mode
		selectedIndex = -1; // Reset selected index
	}


	//=====================================================================================================
	if (key == 'L' || key == 'l') {  // Press 'L' to go to level4
		currentState = LEVEL4;  // Transition to LEVEL4
	}


	if (isPauseMenuActive) {
		// If the pause menu is active, don't process game keyboard inputs
		return;
	}

	//=====================================================================================================
}

void level2SpecialKeyboard(unsigned char key) {
	if (isPauseMenuActive) {
		// If the pause menu is active, don't process game keyboard inputs
		return;
	}
	if (showNextLevel) return; // Ignore special keys if on next level screen

	if (key == GLUT_KEY_RIGHT) {
		// Handle right arrow key
	}
	if (key == GLUT_KEY_LEFT) {
		// Handle left arrow key
	}
	if (key == GLUT_KEY_HOME) {
		// Handle home key
	}

	if (isPauseMenuActive) {
		// If the pause menu is active, don't process game keyboard inputs
		return;
	}
}

int level2main() {
	///srand((unsigned)time(NULL));

	resetQuestionsForSuspect(); // Initialize questions for the first suspect

	//iInitialize(W, H, "Interrogation Room");

	// Load all background images
	bgImage[0] = iLoadImage("Interview2.bmp"); // Father Elias
	bgImage[1] = iLoadImage("Interview1.bmp"); // Journalist
	bgImage[2] = iLoadImage("Interview3.bmp"); // Deborah

	nextLevelImage = iLoadImage("NextLevel.bmp"); // your cutscene image

	return 0;
}

#endif