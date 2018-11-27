#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "fssimplewindow.h"
#include "yssimplesound.h"

//============================================================
//This is the class for sound effects
//The audio player object is created when including this file since I declared it on the end of this script.

//To import your own sound effects or music just add a YsSoundPlayer::SoundData object, 
//modify the constructer and add a function for your later use
//After including this file, just call sound.your_play_audio_function() whenever you want the sound to be played
//=============================================================

class Sounds{
protected:
    YsSoundPlayer player;
    YsSoundPlayer::SoundData rebound,background; // add Sound data object here to be loaded later
public:
    Sounds();
    ~Sounds();
    //void PlayBackground(void);
    void PlayRebound(void);
};


Sounds::Sounds(){
    player.MakeCurrent();
	player.Start();
    //FsChangeToProgramDir();
    if(YSOK!=rebound.LoadWav("rebound.wav") &&
	   YSOK!=rebound.LoadWav("datafiles/rebound.wav"))
	{
		printf("Error!  Cannot load rebound.wav!\n");
	}
	/*
    if(YSOK!=background.LoadWav("music.wav") &&
	   YSOK!=background.LoadWav("music.wav"))
	{
		printf("Error!  Cannot load music.wav!\n");
	}
    */
}

Sounds::~Sounds(){}


/*
void Sounds::PlayBackground(void){
    player.PlayBackground(background);
}
*/

void Sounds::PlayRebound(void){
    player.Stop(rebound);
    player.PlayOneShot(rebound);
}


Sounds sound;