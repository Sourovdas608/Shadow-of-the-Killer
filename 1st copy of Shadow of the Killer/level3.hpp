#ifndef LEVEL3_H
#define LEVEL3_H

#include "Utils.hpp" // Make sure Utils.hpp contains screenWidth and screenHeight
#include "music.hpp" // For sounds
#include "menu.hpp"  // For GameState and isPauseMenuActive
#include <iostream>
using namespace std;
#include <vector> // For std::vector
#include <cstdio> // For sprintf
#include <cstring> // For strlen

// Structure to define a clue area
struct Level3Clue {
	int x, y, width, height; // Bounding box of the clue
	const char* hoverImagePath; // Path to the image to show on hover
	int hoverImageId; // iGraphics image ID for the hover image
	bool isHovered; // True if the mouse is currently over this clue
	bool isFound;   // True if the clue has been clicked
	const char* name; // Name of the clue for display (e.g., in notes)
};

// Room structure to hold its background and clues
// A room now *might* belong to a person, but doesn't *have* to
struct Level3Room {
	const char* backgroundPath;
	int backgroundId;
	std::vector<Level3Clue> clues;
	bool allCluesFoundInRoom; // Track if all clues in *this specific room* are found
};

// NEW: Structure to represent a person, containing multiple rooms
struct Level3Person {
	const char* name; // The person's name (e.g., "Alex", "Ben")
	std::vector<Level3Room> rooms; // A list of rooms associated with this person
	bool allRoomsCleared; // True if all rooms for this person have had their clues found
};

// --- Level 3 Game State Variables ---
extern GameState currentState; // From menu.hpp
extern int HomePage; // Assuming these are defined elsewhere for menu navigation
extern int StartPage1;
extern int AboutPage;
extern int MutePage;
extern void playBackgroundMusic(); // Assuming this function exists for playing background music

const int NUM_PERSONS = 3; // We'll have 3 persons, each with their own rooms
Level3Person persons[NUM_PERSONS];
int currentPersonIndex = 0; // Index of the current person being investigated
int currentRoomIndexInPerson = 0; // Index of the current room within the current person's rooms

int totalCluesFound = 0;
int totalCluesInLevel = 0; // This will be calculated during initialization

// NEW: For displaying hover messages
char hoveredClueMessage[256] = ""; // Buffer to hold the message
bool showHoverClueMessage = false; // Flag to control visibility
int hoverMessageX = 10; // X position for the message
int hoverMessageY = 0; // Y position for the message

// Next Room Button (now conceptually "Next Area" or "Next Room for this Person")
int nextRoomButtonX = screenWidth - 150;
int nextRoomButtonY = screenHeight - 60;
int nextRoomButtonW = 120;
int nextRoomButtonH = 40;
bool isNextRoomButtonHovered = false;

// Game State for Level 3
enum Level3InternalState {
	EXPLORING_PERSON_ROOMS,
	LEVEL_COMPLETE_SCREEN // This state will now only be used for ESC to main menu, not for advancing to Level 4
};
Level3InternalState currentLevel3InternalState = EXPLORING_PERSON_ROOMS;

// Image ID for the level completion screen (kept for potential ESC to menu option)
int level3CompletionImageId = -1;

// Function declarations for Level 3
void level3Initialize();
void drawLevel3();
void level3PassiveMouseMove(int mx, int my);
void level3Mouse(int button, int state, int mx, int my);
void level3Keyboard(unsigned char key);
void level3SpecialKeyboard(unsigned char key);
void drawPauseMenu(); // Assuming this is defined in menu.hpp or similar

// Function implementations

void level3Initialize() {


	// Reset game state
	currentPersonIndex = 0;
	currentRoomIndexInPerson = 0;
	totalCluesFound = 0;
	totalCluesInLevel = 0; // Reset
	isNextRoomButtonHovered = false;
	currentLevel3InternalState = EXPLORING_PERSON_ROOMS;

	// NEW: Reset hover message state
	sprintf_s(hoveredClueMessage, sizeof(hoveredClueMessage), "");
	showHoverClueMessage = false;

	// Load level completion image once (kept for potential ESC to menu option)
	if (level3CompletionImageId == -1) {
		level3CompletionImageId = iLoadImage((char*)"image\\level3\\level3_next_level.bmp");
	}

	// --- Define Persons, their Rooms, and Clues ---
	// Person 0: Alex
	persons[0].name = "Father Elias";
	persons[0].allRoomsCleared = false;
	// Alex's Room 0: Antique Library
	persons[0].rooms.push_back({ "image\\Level3\\father study.bmp", -1, {}, false });
	persons[0].rooms[0].clues.push_back({ 700, 150, 270, 170, "image\\Level3\\FSC1B.bmp", -1, false, false, "A half-burnt paper with strange symbols lies on the desk. It's probably just notes for a sermon about ancient cults a red herring." });
	//persons[0].rooms[0].clues.push_back({ 750, 100, 120, 90, "image\\Level3\\FSC2.bmp", -1, false, false, "Burnt Candle" });

	// Alex's Room 1: Abandoned Study (Alex has two rooms!)
	persons[0].rooms.push_back({ "image\\Level3\\father coat.bmp", -1, {}, false });
	persons[0].rooms[1].clues.push_back({ 225, 170, 380, 550, "image\\Level3\\FRBB.bmp", -1, false, false, "A recently cleaned cassock hangs in the wardrobe, but a faint red stain remains on the cuff." });
	//persons[0].rooms[1].clues.push_back({ 500, 450, 100, 70, "image\\level3\\room1_clue1_hover.bmp", -1, false, false, "Broken Pen" });


	// Person 1: Ben
	persons[1].name = "Journalist";
	persons[1].allRoomsCleared = false;
	// Ben's Room 0: Dusty Office
	persons[1].rooms.push_back({ "image\\Level3\\journalist living room.bmp", -1, {}, false });
	persons[1].rooms[0].clues.push_back({ 350, 340, 550, 350, "image\\Level3\\JLC1B.bmp", -1, false, false, "A detailed timeline of Professor Kane's life, with the date of his murder circled in red." });
	persons[1].rooms[0].clues.push_back({ 10, 70, 350, 250, "image\\Level3\\JLC2B.bmp", -1, false, false, "Stacks of newspapers could contain headlines about Kane, linking the journalist's work to a personal obsession." });
	// Ben's Room 0: Dusty Office
	persons[1].rooms.push_back({ "image\\Level3\\journalist study  room.bmp", -1, {}, false });
	persons[1].rooms[1].clues.push_back({ 119, 60, 850, 600, "image\\Level3\\JOC1B.bmp", -1, false, false, "A timeline of Professor Kane's schedule is on the corkboard. The date of the murder is circled repeatedly, showing the journalist's obsessive interest." });
	//persons[1].rooms[0].clues.push_back({ 650, 50, 130, 80, "image\\level3\\room2_clue1_hover.bmp", -1, false, false, "Overturned Mug" });


	// Person 2: Charlie
	persons[2].name = "Deborah";
	persons[2].allRoomsCleared = false;
	// Charlie's Room 0: Forgotten Attic
	persons[2].rooms.push_back({ "image\\Level3\\deborah room.bmp", -1, {}, false });
	persons[2].rooms[0].clues.push_back({ 550, 50, 500, 300, "image\\Level3\\DRC1B.bmp", -1, false, false, "A handwritten note that reads 'Synchronicity is a myth' is found next to a partially burned photo" });
	persons[2].rooms[0].clues.push_back({ 30, 300, 500, 300, "image\\Level3\\DRC2B.bmp", -1, false, false, "Cryptic, encrypted files are visible on the desktop, labeled 'Project Chimera' and 'Orion Protocol." });



	// --- Load Images and Calculate Total Clues ---
	for (size_t p_idx = 0; p_idx < NUM_PERSONS; ++p_idx) {
		for (size_t r_idx = 0; r_idx < persons[p_idx].rooms.size(); ++r_idx) {
			Level3Room& room = persons[p_idx].rooms[r_idx];

			// Load room background
			if (room.backgroundId == -1) {
				room.backgroundId = iLoadImage((char*)room.backgroundPath);
			}
			// Load clue hover images for each room
			for (size_t c_idx = 0; c_idx < room.clues.size(); ++c_idx) {
				if (room.clues[c_idx].hoverImageId == -1) {
					room.clues[c_idx].hoverImageId = iLoadImage((char*)room.clues[c_idx].hoverImagePath);
				}
				// Reset clue states
				room.clues[c_idx].isHovered = false;
				room.clues[c_idx].isFound = false;
				totalCluesInLevel++; // Increment total clues
			}
			room.allCluesFoundInRoom = false; // Reset room completion status
		}
	}
	
}

void drawLevel3() {
	iClear();
	if (isPauseMenuActive) {
		drawPauseMenu();
		return;
	}

	if (currentLevel3InternalState == LEVEL_COMPLETE_SCREEN) {
		// This block will now only show if ESC is pressed during investigation
		// and then somehow you tried to exit to main menu from a completion state.
		// For direct Level 4 transition, this screen will be skipped.
		if (level3CompletionImageId != -1) {
			iShowImage(0, 0, screenWidth, screenHeight, level3CompletionImageId);
			iSetColor(255, 255, 255);
			iText(screenWidth / 2 - 200, 50, "Level complete! Press ESC to return to main menu.", GLUT_BITMAP_HELVETICA_18);
		}
		return;
	}

	// Get current person and room
	Level3Person& currentPerson = persons[currentPersonIndex];
	Level3Room& currentRoom = currentPerson.rooms[currentRoomIndexInPerson];

	// --- Draw Current Room Background ---
	if (currentRoom.backgroundId != -1) {
		iShowImage(0, 0, screenWidth, screenHeight, currentRoom.backgroundId);
	}

	// --- Draw Clues ---
	for (size_t i = 0; i < currentRoom.clues.size(); ++i) {
		Level3Clue& clue = currentRoom.clues[i];
		if (!clue.isFound) { // Only draw if not found
			if (clue.isHovered) {
				if (clue.hoverImageId != -1) {
					iShowImage(clue.x, clue.y, clue.width, clue.height, clue.hoverImageId);
				}
				iSetColor(0, 255, 0); // Green for hovered
				iRectangle(clue.x, clue.y, clue.width, clue.height);
			}
			else {
				iSetColor(255, 255, 0); // Yellow highlight for unfound clues
			}
		}
		else {
			iSetColor(255, 0, 0); // Red for found clues
		}
	}

	// --- Draw Hovered Clue Message in Dialog Box ---
	if (showHoverClueMessage && strlen(hoveredClueMessage) > 0) {
		// Draw the dialog box background
		iSetColor(0, 0, 0); // Black background for the dialog box with some transparency if needed
		iFilledRectangle(30, 40, screenWidth - 60, 50); // A rectangle at the bottom (with some padding)

		// Draw the clue message inside the dialog box
		iSetColor(255, 255, 255); // White text color
		iText(60, 58, hoveredClueMessage, GLUT_BITMAP_HELVETICA_12); // Display the hovered clue message
	}

	// --- Draw Next Room Button ---
	if (isNextRoomButtonHovered) {
		iSetColor(100, 100, 255); // Highlighted color
	}
	else {
		iSetColor(50, 50, 150); // Default dark blue
	}
	iFilledRectangle(nextRoomButtonX, nextRoomButtonY, nextRoomButtonW, nextRoomButtonH);
	iSetColor(255, 255, 255);
	// Button text changes based on context
	if (static_cast<size_t>(currentRoomIndexInPerson) < currentPerson.rooms.size() - 1) {
		iText(nextRoomButtonX + 10, nextRoomButtonY + 15, "Next Room", GLUT_BITMAP_HELVETICA_12);
	}
	else if (static_cast<size_t>(currentPersonIndex) < NUM_PERSONS - 1) {
		iText(nextRoomButtonX + 10, nextRoomButtonY + 15, "Next Person", GLUT_BITMAP_HELVETICA_12);
	}
	else {
		iText(nextRoomButtonX + 10, nextRoomButtonY + 15, "Finish Level", GLUT_BITMAP_HELVETICA_12);
	}

	// --- Draw Clue Count on screen ---
	iSetColor(255, 255, 255);
	char clueCountText[50];
	sprintf_s(clueCountText, sizeof(clueCountText), "Clues Found: %d", totalCluesFound);
	iText(10, screenHeight - 30, clueCountText, GLUT_BITMAP_HELVETICA_18);

	// --- Draw Person's Name on a Note ---
	iSetColor(69, 104, 130); // Brown color for the note
	iFilledRectangle(10, screenHeight - 80, 110, 40); // Position the note

	iSetColor(255, 255, 255); // White color for text
	char personNameBuffer[64]; // Make sure this buffer is large enough for the longest name
	sprintf_s(personNameBuffer, sizeof(personNameBuffer), "%s", currentPerson.name);
	iText(20, screenHeight - 65, personNameBuffer, GLUT_BITMAP_HELVETICA_18); // Display the person's name
}


void level3PassiveMouseMove(int mx, int my) {
	if (isPauseMenuActive || currentLevel3InternalState == LEVEL_COMPLETE_SCREEN) return;

	// Check Next Room/Person button hover
	if (mx >= nextRoomButtonX && mx <= nextRoomButtonX + nextRoomButtonW &&
		my >= nextRoomButtonY && my <= nextRoomButtonY + nextRoomButtonH) {
		//if (!isNextRoomButtonHovered) playClickSound(); // Play sound only on first hover
		isNextRoomButtonHovered = true;
	}
	else {
		isNextRoomButtonHovered = false;
	}

	// Reset hover message before checking clues
	sprintf_s(hoveredClueMessage, sizeof(hoveredClueMessage), "");
	showHoverClueMessage = false;

	// Check Clue hovers
	Level3Room& currentRoom = persons[currentPersonIndex].rooms[currentRoomIndexInPerson];
	for (size_t i = 0; i < currentRoom.clues.size(); ++i) {
		Level3Clue& clue = currentRoom.clues[i];
		if (!clue.isFound) { // Only active if not found
			if (mx >= clue.x && mx <= clue.x + clue.width &&
				my >= clue.y && my <= clue.y + clue.height) {
				if (!clue.isHovered) {
					// Optionally play hover sound or some other action
				}
				clue.isHovered = true;

				// Set the message and position for the dialog box
				sprintf_s(hoveredClueMessage, sizeof(hoveredClueMessage), "%s", clue.name);
				showHoverClueMessage = true;
			}
			else {
				clue.isHovered = false;
			}
		}
		else {
			clue.isHovered = false; // Cannot hover a found clue
		}
	}
}



void level3Mouse(int button, int state, int mx, int my) {
	// Handle pause menu clicks
	if (isPauseMenuActive && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	//	cout << mx << " " << my << endl;

		if (mx >= 388 && mx <= 709 && my >= 235 && my <= 302) { // Exit button
			playClickSound();
			HomePage = 1;
			StartPage1 = 0;
			AboutPage = 0;
			MutePage = 0;
			isPauseMenuActive = false;
			currentState = MENU;
			return;
		}
		if (mx >= 389 && mx <= 710 && my >= 319 && my <= 385) { // Resume button
			playClickSound();
			isPauseMenuActive = false;
			return;
		}
	}

	// This block is no longer relevant for the direct transition to LEVEL4,
	// but keeping it for completeness if other aspects of the screen exist.
	if (currentLevel3InternalState == LEVEL_COMPLETE_SCREEN) {
		// Clicks on the completion screen are handled by keyboard (ENTER/ESC)
		return;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		//printf("Mouse clicked at: (%d, %d)\n", mx, my);

		// Get current person and room
		Level3Person& currentPerson = persons[currentPersonIndex];
		Level3Room& currentRoom = currentPerson.rooms[currentRoomIndexInPerson];

		// Check Next Room/Person button click
		if (isNextRoomButtonHovered) {
		//	playClickSound();
			currentRoomIndexInPerson++; // Try to move to the next room for this person

			if (static_cast<size_t>(currentRoomIndexInPerson) >= currentPerson.rooms.size()) {
				// All rooms for the current person are cleared
				// Move to the next person
				currentPersonIndex++;
				currentRoomIndexInPerson = 0; // Reset room index for the new person

				if (static_cast<size_t>(currentPersonIndex) >= NUM_PERSONS) {
					// All persons investigated, level complete!
					//printf("All persons investigated! Level 3 complete. Advancing to Level 4.\n");
					currentState = LEVEL4; // DIRECTLY TRANSITION TO LEVEL4

					return; // Exit as level is complete
				}
			}
			// Reset hover state for the new room (or first room of new person)
			Level3Room& newRoom = persons[currentPersonIndex].rooms[currentRoomIndexInPerson];
			for (size_t i = 0; i < newRoom.clues.size(); ++i) {
				newRoom.clues[i].isHovered = false;
			}
			// NEW: Clear any active hover message when changing rooms
			sprintf_s(hoveredClueMessage, sizeof(hoveredClueMessage), "");
			showHoverClueMessage = false;
			return;
		} 

		// Check Clue clicks
		for (size_t i = 0; i < currentRoom.clues.size(); ++i) {
			Level3Clue& clue = currentRoom.clues[i];
			if (!clue.isFound && clue.isHovered) { // Clicked a hovered, unfound clue
				//	playClickSound();
				clue.isFound = true;
				totalCluesFound++;
				//printf("Clue found: %s in %s's area! Total clues: %d\n", clue.name, currentPerson.name, totalCluesFound);

				// Check if all clues in the *current room* are now found
				bool allFoundInThisRoom = true;
				for (size_t j = 0; j < currentRoom.clues.size(); ++j) {
					if (!currentRoom.clues[j].isFound) {
						allFoundInThisRoom = false;
						break;
					}
				}
				currentRoom.allCluesFoundInRoom = allFoundInThisRoom;
				clue.isHovered = false; // No longer hovered once found

				// NEW: Clear the hover message as the clue is now found
				sprintf_s(hoveredClueMessage, sizeof(hoveredClueMessage), "");
				showHoverClueMessage = false;

				return; // Only process one clue click
			}
		}
	}
}

void level3Keyboard(unsigned char key) {
	if (isPauseMenuActive) {
		return;
	}

	// This entire block for LEVEL_COMPLETE_SCREEN is now essentially obsolete
	// because the transition to LEVEL4 happens directly on button click.
	// You can keep it if you want the ESC functionality to return to main menu.
	if (currentLevel3InternalState == LEVEL_COMPLETE_SCREEN) {
		// if (key == 13) { // ENTER key - This path will no longer be reached for LEVEL4 transition
		// 	printf("Advancing from Level 3 to Level 4.\n");
		// 	currentState = LEVEL4;
		// }
		if (key == 27) { // ESC key for Main Menu
			//printf("Returning to Main Menu from Level 3 completion screen.\n");
			currentState = MENU;
			level3Initialize(); // Reset level3 state
			playBackgroundMusic(); // Ensure menu music restarts if needed
		}
		return;
	}

	if (key == 27) {
		isPauseMenuActive = !isPauseMenuActive;
		//printf("Pause menu toggled: %s\n", isPauseMenuActive ? "Active" : "Inactive");
	}
}

void level3SpecialKeyboard(unsigned char key) {
	if (isPauseMenuActive || currentLevel3InternalState == LEVEL_COMPLETE_SCREEN) return;
}

#endif