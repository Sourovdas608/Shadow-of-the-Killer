#ifndef MUSIC_HPP
#define MUSIC_HPP
#include "Utils.hpp"
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



//------------------------------------------------------
// Background music
//------------------------------------------------------
inline void playBackgroundMusic() {
	if (isMusicOn) {
		PlaySound("music\\menu.wav", NULL, SND_LOOP | SND_ASYNC);
		// Loops async until stopped
	}
}

inline void stopBackgroundMusic() {
	PlaySound(NULL, 0, 0);
}


inline void playBackgroundMusic1() {
	if (isMusicOn) {
		PlaySound("music\\level1.wav", NULL, SND_LOOP | SND_ASYNC);
		// Loops async until stopped
	}
}

inline void stopBackgroundMusic1() {
	PlaySound(NULL, 0, 0);
}
//------------------------------------------------------
// Button click sound (plays once)
//------------------------------------------------------
inline void playClickSound() {
	PlaySound("music\\click.wav", NULL, SND_ASYNC);
	// plays once, does not loop
}

inline void playClickSound1() {
	PlaySound("music\\transition.wav", NULL, SND_ASYNC);
	// plays once, does not loop
}
inline void playClickSound2() {
	PlaySound("music\\sword.wav", NULL, SND_ASYNC);
	// plays once, does not loop
}

//------------------------------------------------------
// Other sounds can be added here (win sound, lose sound, etc.)
//------------------------------------------------------

#endif
