#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS


struct Obstacle {
	int x1, y1;   // bottom-left corner
	int x2, y2;   // width and height
};
const int screenWidth = 1100;
const int screenHeight = 700;

// Global music state
bool isMusicOn = true;

//------------------------------------------------------------------------------------------------

bool isPauseMenuActive = false;


struct Clue {
	int x, y, width, height;
	bool found;
	const char* name;
};
//---------------------------------------------------------------------------------------




// notepad panel
const int notePadX = screenWidth - 250;   // left side now
const int notePadY = 0;
const int notePadW = 250;
const int notePadH = 300;

// how many side rooms (not counting main)
const int numRooms = 4;

// thumbnails (preview size)
const int roomThumbW = 250;
const int roomThumbH = 100;


//-----------------------------------------------------------------------------------------------------
// -------------------------------------------------- Dialogue state -----------------------------------

bool isSlideshowActive = false;
bool isSlideshow2Active = false;
//-----------------------------------------------------------------------------------------------------

//=======================================================================================================
#include <stdio.h>
void clearFileAfterLevelCompletion();
// Function to store the clue in the file
void storeClueInFile(const char* clueName) {
	FILE *fptr;

	// Open the file in append mode ("a"), so we don't overwrite existing content
	if (fopen_s(&fptr, "clue.txt", "a") != 0) {
		printf("Error opening file for appending!\n");
		return;
	}

	// Write the clue to the file
	int writeResult = fprintf(fptr, "Clue found: %s\n", clueName);

	// Check if the write was successful
	if (writeResult < 0) {
		printf("Error writing to file!\n");
		fclose(fptr);
		return;
	}



	// Close the file after writing
	fclose(fptr);

	// Simulate Level 1 completion
	// After completing Level 1, call the function to clear the file
	//clearFileAfterLevelCompletion();
}

// Function to clear the file after Level 1 completion
void clearFileAfterLevelCompletion() {
	FILE *fptr;

	// Open the file in write mode ("w") to truncate it (clear the content)
	if (fopen_s(&fptr, "clue.txt", "w") != 0) {
		printf("Error opening file for clearing!\n");
		return;
	}

	// Close the file immediately after clearing (file is now empty)
	fclose(fptr);
	printf("File cleared after Level 1 completion.\n");
}




// Main function
int funmain() {
	const char* clueName = "A Hidden Message";  // Example clue name
	storeClueInFile(clueName);  // Call the function to store the clue in the file

	return 0;
}

//===========================================================================================

#endif

