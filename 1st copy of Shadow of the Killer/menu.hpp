#ifndef MENU_H
#define MENU_H
#include "Utils.hpp"
#include "music.hpp"


#include <iostream>
using namespace std;

enum GameState { MENU, LEVEL1, LEVEL2, LEVEL3, LEVEL4 };
extern GameState currentState;





void drawHomepage();
void drawHomepageInitial();
void drawStartPage();
void drawAboutPage();
void drawMutePage();

void drawPauseMenu();


void startButtonClickHandler();
void AboutButtonClickHandler();
void MuteButtonClickHandler();
void HomepageButtonClickHandler();
void AboutPageAreaClickHandler();
void ControlsButtonClickHandler(); // New: Handler for Controls button
void CreditsButtonClickHandler();  // New: Handler for Credits button


int startButtonClick = 0;
int AboutButtonClick = 0;
int MuteButtonClick = 0;






int HomePage = 3;
int StartPage1 = 0;
int AboutPage = 0;
int MutePage = 0;
int HomepageButton1 = 1;


bool isAboutPageAreaImageActive = false;
bool isControlsPageActive = false; // New: Flag for Controls page
bool isCreditsPageActive = false;  // New: Flag for Credits page


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://

void drawMenu()
{



	if (HomePage == 3 && (HomepageButton1 = 1)){
		drawHomepageInitial();
	}

	else if (HomePage == 1){
		drawHomepage();
	}
	else if (StartPage1 == 1){
		drawStartPage();
	}
	else if (AboutPage == 1){
		drawAboutPage();

		if (isAboutPageAreaImageActive) {
			iShowBMP(0, 0, "image\\about_detail.bmp"); // Assuming this is for the original "About" content
			iShowBMP2(0, 700 - 56, "image\\backbutton.bmp", 0xFFFFFF);
		}
		else if (isControlsPageActive) {
			iShowBMP(0, 0, "image\\controls.bmp"); // New: Image for controls
			iShowBMP2(0, 700 - 56, "image\\backbutton.bmp", 0xFFFFFF);
		}
		else if (isCreditsPageActive) {
			iShowBMP(0, 0, "image\\su.bmp"); // New: Image for credits
			iShowBMP2(0, 700 - 56, "image\\backbutton.bmp", 0xFFFFFF);
		}
	}
	else if (MutePage == 1){
		drawMutePage();
	}

	if ((HomePage != 1) && isPauseMenuActive) {
		drawPauseMenu();
		return;
	}





}


//*******************************************************************ipassiveMouse***********************************************************************//


void MenuPassiveMouseMove(int mx, int my) {
	if (HomePage == 3 && (HomepageButton1 = 1)){

		HomepageButtonClickHandler();
		//playClickSound1();
	}
}



void MenuMouse(int button, int state, int mx, int my)
{
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



	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		//printf("Mouse clicked at: (%d, %d)\n", mx, my);

		if ((HomePage == 1 || HomePage == 2) && (mx >= 357 && mx <= 662) && (my >= 351 && my <= 426)){
			playClickSound();

			startButtonClickHandler();
			//playBackgroundMusic1();
			isSlideshowActive = true;
		}


		else if ((HomePage == 1 || HomePage == 2) && (mx >= 357 && mx <= 662) && (my >= 243 && my <= 316)){
			playClickSound();
			AboutButtonClickHandler();
		}

		else if ((HomePage == 1 || HomePage == 2) && (mx >= 1033 && mx <= 1073) && (my >= 626 && my <= 667)){



		}

		else if (AboutPage == 1 && (mx >= 0 && mx <= 55) && (my >= screenHeight - 55 && my <= screenHeight)) {

			if (isAboutPageAreaImageActive || isControlsPageActive || isCreditsPageActive) {

				isAboutPageAreaImageActive = false;
				isControlsPageActive = false;
				isCreditsPageActive = false;
				
			}
			else {

				AboutPage = 0;
				HomePage = 1;
			
			}
		}

		else if (AboutPage == 1 && (mx >= 122 && mx <= 319) && (my >= 425 && my <= 486)) {
			//playClickSound();
			AboutPageAreaClickHandler();
			
		}

		else if (AboutPage == 1 && (mx >= 133 && mx <= 315) && (my >= 307 && my <= 366)) {
			//playClickSound();
			ControlsButtonClickHandler();
		
		}

		else if (AboutPage == 1 && (mx >= 136 && mx <= 307) && (my >= 204 && my <= 374)) {
			//playClickSound();
			CreditsButtonClickHandler();
			
		}



		else if (HomePage == 1 && (mx >= 1013 && mx <= 1071) && (my >= 35 && my <= 94)){
			playClickSound();
			MuteButtonClickHandler();
		}



		else if ((MutePage == 1) && (mx >= 1013 && mx <= 1071) && (my >= 35 && my <= 94)){
			playClickSound();

			HomePage = 1;
			MutePage = 0;
			isMusicOn = true;
			playBackgroundMusic();

		}





		//--------------------------------------------------------------------------------------------------------




		//-------------------------------------------------------------------------------------------------------





	}


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}

//-------------------------------------------------------------------------------------
void drawHomepageInitial(){

	if (HomepageButton1 = 1){

		iShowBMP(0, 0, "image\\background\\homebackground.bmp");
	}
}
void drawHomepage()
{
	iShowBMP(0, 0, "image\\background\\homebgon.bmp");

}


void drawStartPage(){
	stopBackgroundMusic();
	currentState = LEVEL1;
	playBackgroundMusic1();



}


void drawAboutPage(){
	iShowBMP(0, 0, "image\\page.bmp"); // This is the main About page background

	iShowBMP2(0, 700 - 56, "image\\backbutton.bmp", 0xFFFFFF);


}

void drawMutePage(){
	iShowBMP(0, 0, "image\\background\\homebgoff.bmp");
}

//----------------------------------------drawPauseMenu-------------------------------------------------------

void drawPauseMenu() {

	iShowBMP(0, 0, "image\\exit.bmp");

}

//-------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
void startButtonClickHandler(){
	HomePage = 0;
	StartPage1 = 1;
	//playBackgroundMusic1();
}


void AboutButtonClickHandler(){
	HomePage = 0;
	StartPage1 = 0;
	AboutPage = 1;
	isAboutPageAreaImageActive = false; // Ensure main About content is not active initially
	isControlsPageActive = false;       // Ensure controls are not active initially
	isCreditsPageActive = false;        // Ensure credits are not active initially
}

void MuteButtonClickHandler(){

	HomePage = 2;
	StartPage1 = 0;
	AboutPage = 0;
	MutePage = 1;
	isMusicOn = false;
	stopBackgroundMusic();





}


void AboutPageAreaClickHandler(){
	
	isAboutPageAreaImageActive = !isAboutPageAreaImageActive; 
	isControlsPageActive = false; 
	isCreditsPageActive = false;  
}


void ControlsButtonClickHandler() {

	isControlsPageActive = !isControlsPageActive;
	isAboutPageAreaImageActive = false;
	isCreditsPageActive = false;       
}


void CreditsButtonClickHandler() {

	isCreditsPageActive = !isCreditsPageActive; 
	isAboutPageAreaImageActive = false; 
	isControlsPageActive = false;    
}


//---------------------------------------------------------------------------------
void HomepageButtonClickHandler(){
	//playClickSound1();
	HomePage = 1;
	HomepageButton1 = 0;
	StartPage1 = 0;
	AboutPage = 0;
	MutePage = 0;
	playBackgroundMusic();
	isAboutPageAreaImageActive = false; 
	isControlsPageActive = false;
	isCreditsPageActive = false;
}


//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------


int Menumain()
{

	iSetTimer(100000, drawHomepage);  //for delay 2nd screen

	//playBackgroundMusic(); 

	return 0;
}



#endif

