#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED
#include "Game.h"
#include <SDL_mixer.h>

class Audio {
private:
	Mix_Chunk* chunk = NULL;
	Mix_Music* music = NULL;
	int volume;

public:
	Audio();
	~Audio();

	void loadSound(const char* path);
	void loadMusic(const char* path);
	void playSound();
	void playSound(const int& v);
	void playMusic();
	void playMusic(const int& v);
	bool isPlaying();
	void pause();
	void resume();

};


#endif // AUDIO_H_INCLUDED
